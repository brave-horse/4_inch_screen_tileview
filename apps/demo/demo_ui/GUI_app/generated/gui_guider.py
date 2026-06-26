# Copyright 2026 NXP
# NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
# accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
# activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
# comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
# terms, then you may not retain, install, activate or otherwise use the software.

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct
import fs_driver

lv.init()
SDL.init(w=720,h=720)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(720*720*4)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 720
disp_drv.ver_res = 720
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init()
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

fs_drv = lv.fs_drv_t()
fs_driver.fs_register(fs_drv, 'Z')

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def anim_width_cb(obj, v):
    obj.set_width(v)

def anim_height_cb(obj, v):
    obj.set_height(v)

def anim_img_zoom_cb(obj, v):
    obj.set_zoom(v)

def anim_img_rotate_cb(obj, v):
    obj.set_angle(v)

global_font_cache = {}
def test_font(font_family, font_size):
    global global_font_cache
    if font_family + str(font_size) in global_font_cache:
        return global_font_cache[font_family + str(font_size)]
    if font_size % 2:
        candidates = [
            (font_family, font_size),
            (font_family, font_size-font_size%2),
            (font_family, font_size+font_size%2),
            ("montserrat", font_size-font_size%2),
            ("montserrat", font_size+font_size%2),
            ("montserrat", 16)
        ]
    else:
        candidates = [
            (font_family, font_size),
            ("montserrat", font_size),
            ("montserrat", 16)
        ]
    for (family, size) in candidates:
        try:
            if eval(f'lv.font_{family}_{size}'):
                global_font_cache[font_family + str(font_size)] = eval(f'lv.font_{family}_{size}')
                if family != font_family or size != font_size:
                    print(f'WARNING: lv.font_{family}_{size} is used!')
                return eval(f'lv.font_{family}_{size}')
        except AttributeError:
            try:
                load_font = lv.font_load(f"Z:MicroPython/lv_font_{family}_{size}.fnt")
                global_font_cache[font_family + str(font_size)] = load_font
                return load_font
            except:
                if family == font_family and size == font_size:
                    print(f'WARNING: lv.font_{family}_{size} is NOT supported!')

global_image_cache = {}
def load_image(file):
    global global_image_cache
    if file in global_image_cache:
        return global_image_cache[file]
    try:
        with open(file,'rb') as f:
            data = f.read()
    except:
        print(f'Could not open {file}')
        sys.exit()

    img = lv.img_dsc_t({
        'data_size': len(data),
        'data': data
    })
    global_image_cache[file] = img
    return img

def calendar_event_handler(e,obj):
    code = e.get_code()

    if code == lv.EVENT.VALUE_CHANGED:
        source = e.get_current_target()
        date = lv.calendar_date_t()
        if source.get_pressed_date(date) == lv.RES.OK:
            source.set_highlighted_dates([date], 1)

def spinbox_increment_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.increment()
def spinbox_decrement_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.decrement()

def digital_clock_cb(timer, obj, current_time, show_second, use_ampm):
    hour = int(current_time[0])
    minute = int(current_time[1])
    second = int(current_time[2])
    ampm = current_time[3]
    second = second + 1
    if second == 60:
        second = 0
        minute = minute + 1
        if minute == 60:
            minute = 0
            hour = hour + 1
            if use_ampm:
                if hour == 12:
                    if ampm == 'AM':
                        ampm = 'PM'
                    elif ampm == 'PM':
                        ampm = 'AM'
                if hour > 12:
                    hour = hour % 12
    hour = hour % 24
    if use_ampm:
        if show_second:
            obj.set_text("%d:%02d:%02d %s" %(hour, minute, second, ampm))
        else:
            obj.set_text("%d:%02d %s" %(hour, minute, ampm))
    else:
        if show_second:
            obj.set_text("%d:%02d:%02d" %(hour, minute, second))
        else:
            obj.set_text("%d:%02d" %(hour, minute))
    current_time[0] = hour
    current_time[1] = minute
    current_time[2] = second
    current_time[3] = ampm

def analog_clock_cb(timer, obj):
    datetime = time.localtime()
    hour = datetime[3]
    if hour >= 12: hour = hour - 12
    obj.set_time(hour, datetime[4], datetime[5])

def datetext_event_handler(e, obj):
    code = e.get_code()
    target = e.get_target()
    if code == lv.EVENT.FOCUSED:
        if obj is None:
            bg = lv.layer_top()
            bg.add_flag(lv.obj.FLAG.CLICKABLE)
            obj = lv.calendar(bg)
            scr = target.get_screen()
            scr_height = scr.get_height()
            scr_width = scr.get_width()
            obj.set_size(int(scr_width * 0.8), int(scr_height * 0.8))
            datestring = target.get_text()
            year = int(datestring.split('/')[0])
            month = int(datestring.split('/')[1])
            day = int(datestring.split('/')[2])
            obj.set_showed_date(year, month)
            highlighted_days=[lv.calendar_date_t({'year':year, 'month':month, 'day':day})]
            obj.set_highlighted_dates(highlighted_days, 1)
            obj.align(lv.ALIGN.CENTER, 0, 0)
            lv.calendar_header_arrow(obj)
            obj.add_event_cb(lambda e: datetext_calendar_event_handler(e, target), lv.EVENT.ALL, None)
            scr.update_layout()

def datetext_calendar_event_handler(e, obj):
    code = e.get_code()
    target = e.get_current_target()
    if code == lv.EVENT.VALUE_CHANGED:
        date = lv.calendar_date_t()
        if target.get_pressed_date(date) == lv.RES.OK:
            obj.set_text(f"{date.year}/{date.month}/{date.day}")
            bg = lv.layer_top()
            bg.clear_flag(lv.obj.FLAG.CLICKABLE)
            bg.set_style_bg_opa(lv.OPA.TRANSP, 0)
            target.delete()

# Create ui_home_screen
ui_home_screen = lv.obj()
ui_home_screen.set_size(720, 720)
ui_home_screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_1
ui_home_screen_cont_1 = lv.obj(ui_home_screen)
ui_home_screen_cont_1.set_pos(0, -430)
ui_home_screen_cont_1.set_size(720, 320)
ui_home_screen_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_cont_2
ui_home_screen_cont_2 = lv.obj(ui_home_screen_cont_1)
ui_home_screen_cont_2.set_pos(47, 19)
ui_home_screen_cont_2.set_size(640, 151)
ui_home_screen_cont_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_2.set_style_radius(20, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_2.set_style_bg_color(lv.color_hex(0x393939), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_MainSetBtn
ui_home_screen_MainSetBtn = lv.btn(ui_home_screen_cont_2)
ui_home_screen_MainSetBtn_label = lv.label(ui_home_screen_MainSetBtn)
ui_home_screen_MainSetBtn_label.set_text("")
ui_home_screen_MainSetBtn_label.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_MainSetBtn_label.set_width(lv.pct(100))
ui_home_screen_MainSetBtn_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_MainSetBtn.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_MainSetBtn.set_pos(28, 25)
ui_home_screen_MainSetBtn.set_size(100, 100)
# Set style for ui_home_screen_MainSetBtn, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_MainSetBtn.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_MainSetBtn.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_MainSetBtn.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_MainSetBtn.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_MainSetBtn.set_style_radius(80, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_MainSetBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_MainSetBtn.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_MainSetBtn.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_MainSetBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_MainSetBtn.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_MainSetImg
ui_home_screen_MainSetImg = lv.img(ui_home_screen_cont_2)
ui_home_screen_MainSetImg.set_src("B:MicroPython/_sSetting_alpha_46x46.bin")
ui_home_screen_MainSetImg.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_MainSetImg.set_pivot(50,50)
ui_home_screen_MainSetImg.set_angle(0)
ui_home_screen_MainSetImg.set_pos(53, 52)
ui_home_screen_MainSetImg.set_size(46, 46)
# Set style for ui_home_screen_MainSetImg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_MainSetImg.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_MainSetImg.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_MainSetImg.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_btn_4
ui_home_screen_btn_4 = lv.btn(ui_home_screen_cont_2)
ui_home_screen_btn_4_label = lv.label(ui_home_screen_btn_4)
ui_home_screen_btn_4_label.set_text("")
ui_home_screen_btn_4_label.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_btn_4_label.set_width(lv.pct(100))
ui_home_screen_btn_4_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_btn_4.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_btn_4.set_pos(191, 23)
ui_home_screen_btn_4.set_size(100, 100)
# Set style for ui_home_screen_btn_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_btn_4.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_4.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_4.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_4.set_style_radius(80, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_4.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_btn_5
ui_home_screen_btn_5 = lv.btn(ui_home_screen_cont_2)
ui_home_screen_btn_5_label = lv.label(ui_home_screen_btn_5)
ui_home_screen_btn_5_label.set_text("")
ui_home_screen_btn_5_label.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_btn_5_label.set_width(lv.pct(100))
ui_home_screen_btn_5_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_btn_5.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_btn_5.set_pos(350, 25)
ui_home_screen_btn_5.set_size(100, 100)
# Set style for ui_home_screen_btn_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_btn_5.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_5.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_5.set_style_radius(80, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_5.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_5.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_5.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_btn_6
ui_home_screen_btn_6 = lv.btn(ui_home_screen_cont_2)
ui_home_screen_btn_6_label = lv.label(ui_home_screen_btn_6)
ui_home_screen_btn_6_label.set_text("")
ui_home_screen_btn_6_label.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_btn_6_label.set_width(lv.pct(100))
ui_home_screen_btn_6_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_btn_6.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_btn_6.set_pos(509, 25)
ui_home_screen_btn_6.set_size(100, 100)
# Set style for ui_home_screen_btn_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_btn_6.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_6.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_6.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_6.set_style_radius(80, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_6.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_6.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_6.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_3
ui_home_screen_img_3 = lv.img(ui_home_screen_cont_2)
ui_home_screen_img_3.set_src("B:MicroPython/_sHome_alpha_46x46.bin")
ui_home_screen_img_3.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_3.set_pivot(50,50)
ui_home_screen_img_3.set_angle(0)
ui_home_screen_img_3.set_pos(536, 46)
ui_home_screen_img_3.set_size(46, 46)
# Set style for ui_home_screen_img_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_4
ui_home_screen_img_4 = lv.img(ui_home_screen_cont_2)
ui_home_screen_img_4.set_src("B:MicroPython/_sManual_alpha_46x46.bin")
ui_home_screen_img_4.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_4.set_pivot(50,50)
ui_home_screen_img_4.set_angle(0)
ui_home_screen_img_4.set_pos(377, 51)
ui_home_screen_img_4.set_size(46, 46)
# Set style for ui_home_screen_img_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_4.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_4.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_6
ui_home_screen_img_6 = lv.img(ui_home_screen_cont_2)
ui_home_screen_img_6.set_src("B:MicroPython/_sSleep_on_alpha_46x46.bin")
ui_home_screen_img_6.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_6.set_pivot(50,50)
ui_home_screen_img_6.set_angle(0)
ui_home_screen_img_6.set_pos(216, 50)
ui_home_screen_img_6.set_size(46, 46)
# Set style for ui_home_screen_img_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_6.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_6.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_6.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_2
ui_home_screen_img_2 = lv.img(ui_home_screen_cont_2)
ui_home_screen_img_2.set_src("B:MicroPython/_sSleep_off_alpha_46x46.bin")
ui_home_screen_img_2.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_2.set_pivot(50,50)
ui_home_screen_img_2.set_angle(0)
ui_home_screen_img_2.set_pos(216, 50)
ui_home_screen_img_2.set_size(46, 46)
# Set style for ui_home_screen_img_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_slider_1
ui_home_screen_slider_1 = lv.slider(ui_home_screen_cont_1)
ui_home_screen_slider_1.set_range(0, 100)
ui_home_screen_slider_1.set_mode(lv.slider.MODE.NORMAL)
ui_home_screen_slider_1.set_value(50, lv.ANIM.OFF)
ui_home_screen_slider_1.set_pos(47, 199)
ui_home_screen_slider_1.set_size(640, 62)
# Set style for ui_home_screen_slider_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_slider_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_slider_1.set_style_bg_color(lv.color_hex(0x393939), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_slider_1.set_style_radius(40, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_slider_1.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_slider_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for ui_home_screen_slider_1, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
ui_home_screen_slider_1.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
ui_home_screen_slider_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.INDICATOR|lv.STATE.DEFAULT)
ui_home_screen_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.DEFAULT)
ui_home_screen_slider_1.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for ui_home_screen_slider_1, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
ui_home_screen_slider_1.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
ui_home_screen_slider_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.KNOB|lv.STATE.DEFAULT)
ui_home_screen_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
ui_home_screen_slider_1.set_style_radius(36, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create ui_home_screen_img_5
ui_home_screen_img_5 = lv.img(ui_home_screen_cont_1)
ui_home_screen_img_5.set_src("B:MicroPython/_sSun_alpha_30x34.bin")
ui_home_screen_img_5.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_5.set_pivot(50,50)
ui_home_screen_img_5.set_angle(0)
ui_home_screen_img_5.set_pos(71, 212)
ui_home_screen_img_5.set_size(30, 34)
# Set style for ui_home_screen_img_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_5.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_5.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_tileview_1
ui_home_screen_tileview_1 = lv.tileview(ui_home_screen)
ui_home_screen_tileview_1_tile_0 = ui_home_screen_tileview_1.add_tile(0, 0, lv.DIR.RIGHT)
ui_home_screen_tileview_1_tile_1 = ui_home_screen_tileview_1.add_tile(1, 0, lv.DIR.LEFT | lv.DIR.RIGHT)
ui_home_screen_tileview_1_tile_2 = ui_home_screen_tileview_1.add_tile(2, 0, lv.DIR.LEFT | lv.DIR.RIGHT)
ui_home_screen_tileview_1_tile_3 = ui_home_screen_tileview_1.add_tile(3, 0, lv.DIR.LEFT | lv.DIR.RIGHT)
ui_home_screen_tileview_1_tile_4 = ui_home_screen_tileview_1.add_tile(4, 0, lv.DIR.LEFT | lv.DIR.RIGHT)
ui_home_screen_tileview_1_tile_5 = ui_home_screen_tileview_1.add_tile(5, 0, lv.DIR.LEFT | lv.DIR.RIGHT)
ui_home_screen_tileview_1_tile_6 = ui_home_screen_tileview_1.add_tile(6, 0, lv.DIR.LEFT)
ui_home_screen_tileview_1.set_pos(0, 0)
ui_home_screen_tileview_1.set_size(720, 720)
ui_home_screen_tileview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_tileview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_tileview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tileview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tileview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tileview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tileview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_tileview_1, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
ui_home_screen_tileview_1.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
ui_home_screen_tileview_1.set_style_bg_color(lv.color_hex(0xeaeff3), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
ui_home_screen_tileview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
ui_home_screen_tileview_1.set_style_radius(0, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create ui_home_screen_tabview_5
ui_home_screen_tabview_5 = lv.tabview(ui_home_screen_tileview_1_tile_2, lv.DIR.TOP, 0)
ui_home_screen_tabview_5.set_pos(0, 0)
ui_home_screen_tabview_5.set_size(720, 720)
ui_home_screen_tabview_5.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_tabview_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_tabview_5.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_5.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_5.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_5.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_5.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_5.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_tabview_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_ui_home_screen_tabview_5_extra_btnm_main_default = lv.style_t()
style_ui_home_screen_tabview_5_extra_btnm_main_default.init()
style_ui_home_screen_tabview_5_extra_btnm_main_default.set_bg_opa(255)
style_ui_home_screen_tabview_5_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_ui_home_screen_tabview_5_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_ui_home_screen_tabview_5_extra_btnm_main_default.set_border_width(0)
style_ui_home_screen_tabview_5_extra_btnm_main_default.set_radius(0)
ui_home_screen_tabview_5.get_tab_btns().add_style(style_ui_home_screen_tabview_5_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_tabview_5, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_ui_home_screen_tabview_5_extra_btnm_items_default = lv.style_t()
style_ui_home_screen_tabview_5_extra_btnm_items_default.init()
style_ui_home_screen_tabview_5_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_ui_home_screen_tabview_5_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_ui_home_screen_tabview_5_extra_btnm_items_default.set_text_opa(255)
ui_home_screen_tabview_5.get_tab_btns().add_style(style_ui_home_screen_tabview_5_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for ui_home_screen_tabview_5, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_ui_home_screen_tabview_5_extra_btnm_items_checked = lv.style_t()
style_ui_home_screen_tabview_5_extra_btnm_items_checked.init()
style_ui_home_screen_tabview_5_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_ui_home_screen_tabview_5_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_ui_home_screen_tabview_5_extra_btnm_items_checked.set_text_opa(255)
style_ui_home_screen_tabview_5_extra_btnm_items_checked.set_border_width(0)
style_ui_home_screen_tabview_5_extra_btnm_items_checked.set_radius(0)
style_ui_home_screen_tabview_5_extra_btnm_items_checked.set_bg_opa(255)
style_ui_home_screen_tabview_5_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_ui_home_screen_tabview_5_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
ui_home_screen_tabview_5.get_tab_btns().add_style(style_ui_home_screen_tabview_5_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
ui_home_screen_tabview_5_tab_1 = ui_home_screen_tabview_5.add_tab("")
ui_home_screen_tabview_5_tab_1_label = lv.label(ui_home_screen_tabview_5_tab_1)
ui_home_screen_tabview_5_tab_1_label.set_text("")

# Create ui_home_screen_cont_35
ui_home_screen_cont_35 = lv.obj(ui_home_screen_tabview_5_tab_1)
ui_home_screen_cont_35.set_pos(348, 697)
ui_home_screen_cont_35.set_size(320, 210)
ui_home_screen_cont_35.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_35, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_35.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_35.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_35.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_35.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_35.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_35.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_35.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_35.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_98
ui_home_screen_img_98 = lv.img(ui_home_screen_cont_35)
ui_home_screen_img_98.set_src("B:MicroPython/_Lscene8_alpha_320x210.bin")
ui_home_screen_img_98.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_98.set_pivot(50,50)
ui_home_screen_img_98.set_angle(0)
ui_home_screen_img_98.set_pos(0, 0)
ui_home_screen_img_98.set_size(320, 210)
# Set style for ui_home_screen_img_98, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_98.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_98.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_98.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_52
ui_home_screen_label_52 = lv.label(ui_home_screen_cont_35)
ui_home_screen_label_52.set_text("场景八")
ui_home_screen_label_52.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_52.set_width(lv.pct(100))
ui_home_screen_label_52.set_pos(115, 145)
ui_home_screen_label_52.set_size(140, 35)
# Set style for ui_home_screen_label_52, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_52.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_52.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_52.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_52.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_52.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_52.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_52.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_52.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_52.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_52.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_52.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_52.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_52.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_52.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_97
ui_home_screen_img_97 = lv.img(ui_home_screen_cont_35)
ui_home_screen_img_97.set_src("B:MicroPython/_sLscene8_alpha_45x45.bin")
ui_home_screen_img_97.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_97.set_pivot(50,50)
ui_home_screen_img_97.set_angle(0)
ui_home_screen_img_97.set_pos(135, 40)
ui_home_screen_img_97.set_size(45, 45)
# Set style for ui_home_screen_img_97, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_97.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_97.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_97.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_34
ui_home_screen_cont_34 = lv.obj(ui_home_screen_tabview_5_tab_1)
ui_home_screen_cont_34.set_pos(7, 697)
ui_home_screen_cont_34.set_size(320, 210)
ui_home_screen_cont_34.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_34, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_34.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_34.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_34.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_34.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_34.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_34.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_34.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_34.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_96
ui_home_screen_img_96 = lv.img(ui_home_screen_cont_34)
ui_home_screen_img_96.set_src("B:MicroPython/_Lscene7_alpha_320x210.bin")
ui_home_screen_img_96.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_96.set_pivot(50,50)
ui_home_screen_img_96.set_angle(0)
ui_home_screen_img_96.set_pos(0, 0)
ui_home_screen_img_96.set_size(320, 210)
# Set style for ui_home_screen_img_96, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_96.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_96.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_96.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_51
ui_home_screen_label_51 = lv.label(ui_home_screen_cont_34)
ui_home_screen_label_51.set_text("场景七")
ui_home_screen_label_51.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_51.set_width(lv.pct(100))
ui_home_screen_label_51.set_pos(115, 145)
ui_home_screen_label_51.set_size(102, 30)
# Set style for ui_home_screen_label_51, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_51.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_51.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_51.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_51.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_51.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_51.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_51.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_51.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_51.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_51.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_51.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_51.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_51.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_51.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_95
ui_home_screen_img_95 = lv.img(ui_home_screen_cont_34)
ui_home_screen_img_95.set_src("B:MicroPython/_sLscene7_alpha_45x45.bin")
ui_home_screen_img_95.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_95.set_pivot(50,50)
ui_home_screen_img_95.set_angle(0)
ui_home_screen_img_95.set_pos(135, 40)
ui_home_screen_img_95.set_size(45, 45)
# Set style for ui_home_screen_img_95, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_95.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_95.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_95.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_33
ui_home_screen_cont_33 = lv.obj(ui_home_screen_tabview_5_tab_1)
ui_home_screen_cont_33.set_pos(348, 467)
ui_home_screen_cont_33.set_size(320, 210)
ui_home_screen_cont_33.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_33, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_33.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_33.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_33.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_33.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_33.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_33.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_33.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_33.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_94
ui_home_screen_img_94 = lv.img(ui_home_screen_cont_33)
ui_home_screen_img_94.set_src("B:MicroPython/_Lscene6_alpha_320x210.bin")
ui_home_screen_img_94.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_94.set_pivot(50,50)
ui_home_screen_img_94.set_angle(0)
ui_home_screen_img_94.set_pos(0, 0)
ui_home_screen_img_94.set_size(320, 210)
# Set style for ui_home_screen_img_94, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_94.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_94.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_94.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_50
ui_home_screen_label_50 = lv.label(ui_home_screen_cont_33)
ui_home_screen_label_50.set_text("场景六")
ui_home_screen_label_50.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_50.set_width(lv.pct(100))
ui_home_screen_label_50.set_pos(115, 145)
ui_home_screen_label_50.set_size(133, 35)
# Set style for ui_home_screen_label_50, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_50.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_50.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_50.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_50.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_50.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_50.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_50.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_50.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_50.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_50.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_50.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_50.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_50.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_50.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_93
ui_home_screen_img_93 = lv.img(ui_home_screen_cont_33)
ui_home_screen_img_93.set_src("B:MicroPython/_sLscene6_alpha_45x45.bin")
ui_home_screen_img_93.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_93.set_pivot(50,50)
ui_home_screen_img_93.set_angle(0)
ui_home_screen_img_93.set_pos(135, 40)
ui_home_screen_img_93.set_size(45, 45)
# Set style for ui_home_screen_img_93, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_93.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_93.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_93.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_32
ui_home_screen_cont_32 = lv.obj(ui_home_screen_tabview_5_tab_1)
ui_home_screen_cont_32.set_pos(8, 467)
ui_home_screen_cont_32.set_size(320, 210)
ui_home_screen_cont_32.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_32, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_32.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_32.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_32.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_32.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_32.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_32.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_32.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_32.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_92
ui_home_screen_img_92 = lv.img(ui_home_screen_cont_32)
ui_home_screen_img_92.set_src("B:MicroPython/_Lscene5_alpha_320x210.bin")
ui_home_screen_img_92.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_92.set_pivot(50,50)
ui_home_screen_img_92.set_angle(0)
ui_home_screen_img_92.set_pos(0, 0)
ui_home_screen_img_92.set_size(320, 210)
# Set style for ui_home_screen_img_92, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_92.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_92.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_92.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_49
ui_home_screen_label_49 = lv.label(ui_home_screen_cont_32)
ui_home_screen_label_49.set_text("场景五")
ui_home_screen_label_49.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_49.set_width(lv.pct(100))
ui_home_screen_label_49.set_pos(115, 145)
ui_home_screen_label_49.set_size(119, 30)
# Set style for ui_home_screen_label_49, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_49.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_49.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_49.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_49.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_49.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_49.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_49.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_49.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_49.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_49.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_49.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_49.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_49.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_49.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_91
ui_home_screen_img_91 = lv.img(ui_home_screen_cont_32)
ui_home_screen_img_91.set_src("B:MicroPython/_sLscene5_alpha_45x45.bin")
ui_home_screen_img_91.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_91.set_pivot(50,50)
ui_home_screen_img_91.set_angle(0)
ui_home_screen_img_91.set_pos(135, 40)
ui_home_screen_img_91.set_size(45, 45)
# Set style for ui_home_screen_img_91, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_91.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_91.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_91.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_31
ui_home_screen_cont_31 = lv.obj(ui_home_screen_tabview_5_tab_1)
ui_home_screen_cont_31.set_pos(348, 237)
ui_home_screen_cont_31.set_size(320, 210)
ui_home_screen_cont_31.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_31, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_31.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_31.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_31.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_31.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_31.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_31.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_31.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_31.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_90
ui_home_screen_img_90 = lv.img(ui_home_screen_cont_31)
ui_home_screen_img_90.set_src("B:MicroPython/_Lscene4_alpha_320x210.bin")
ui_home_screen_img_90.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_90.set_pivot(50,50)
ui_home_screen_img_90.set_angle(0)
ui_home_screen_img_90.set_pos(0, -1)
ui_home_screen_img_90.set_size(320, 210)
# Set style for ui_home_screen_img_90, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_90.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_90.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_90.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_48
ui_home_screen_label_48 = lv.label(ui_home_screen_cont_31)
ui_home_screen_label_48.set_text("场景四")
ui_home_screen_label_48.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_48.set_width(lv.pct(100))
ui_home_screen_label_48.set_pos(115, 145)
ui_home_screen_label_48.set_size(124, 40)
# Set style for ui_home_screen_label_48, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_48.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_48.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_48.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_48.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_48.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_48.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_48.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_48.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_48.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_48.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_48.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_48.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_48.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_48.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_89
ui_home_screen_img_89 = lv.img(ui_home_screen_cont_31)
ui_home_screen_img_89.set_src("B:MicroPython/_sLscene4_alpha_45x45.bin")
ui_home_screen_img_89.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_89.set_pivot(50,50)
ui_home_screen_img_89.set_angle(0)
ui_home_screen_img_89.set_pos(135, 40)
ui_home_screen_img_89.set_size(45, 45)
# Set style for ui_home_screen_img_89, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_89.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_89.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_89.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_30
ui_home_screen_cont_30 = lv.obj(ui_home_screen_tabview_5_tab_1)
ui_home_screen_cont_30.set_pos(8, 237)
ui_home_screen_cont_30.set_size(320, 210)
ui_home_screen_cont_30.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_30, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_30.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_30.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_30.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_30.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_30.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_30.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_30.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_30.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_88
ui_home_screen_img_88 = lv.img(ui_home_screen_cont_30)
ui_home_screen_img_88.set_src("B:MicroPython/_Lscene3_alpha_320x210.bin")
ui_home_screen_img_88.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_88.set_pivot(50,50)
ui_home_screen_img_88.set_angle(0)
ui_home_screen_img_88.set_pos(0, 0)
ui_home_screen_img_88.set_size(320, 210)
# Set style for ui_home_screen_img_88, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_88.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_88.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_88.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_47
ui_home_screen_label_47 = lv.label(ui_home_screen_cont_30)
ui_home_screen_label_47.set_text("场景三")
ui_home_screen_label_47.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_47.set_width(lv.pct(100))
ui_home_screen_label_47.set_pos(115, 145)
ui_home_screen_label_47.set_size(122, 35)
# Set style for ui_home_screen_label_47, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_47.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_47.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_47.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_47.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_47.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_47.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_47.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_47.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_47.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_47.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_47.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_47.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_47.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_47.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_87
ui_home_screen_img_87 = lv.img(ui_home_screen_cont_30)
ui_home_screen_img_87.set_src("B:MicroPython/_sLscene3_alpha_45x45.bin")
ui_home_screen_img_87.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_87.set_pivot(50,50)
ui_home_screen_img_87.set_angle(0)
ui_home_screen_img_87.set_pos(135, 40)
ui_home_screen_img_87.set_size(45, 45)
# Set style for ui_home_screen_img_87, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_87.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_87.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_87.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_29
ui_home_screen_cont_29 = lv.obj(ui_home_screen_tabview_5_tab_1)
ui_home_screen_cont_29.set_pos(348, 7)
ui_home_screen_cont_29.set_size(320, 210)
ui_home_screen_cont_29.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_29, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_29.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_29.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_29.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_29.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_29.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_29.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_29.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_29.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_86
ui_home_screen_img_86 = lv.img(ui_home_screen_cont_29)
ui_home_screen_img_86.set_src("B:MicroPython/_Lscene2_alpha_320x210.bin")
ui_home_screen_img_86.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_86.set_pivot(50,50)
ui_home_screen_img_86.set_angle(0)
ui_home_screen_img_86.set_pos(0, -3)
ui_home_screen_img_86.set_size(320, 210)
# Set style for ui_home_screen_img_86, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_86.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_86.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_86.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_46
ui_home_screen_label_46 = lv.label(ui_home_screen_cont_29)
ui_home_screen_label_46.set_text("场景二")
ui_home_screen_label_46.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_46.set_width(lv.pct(100))
ui_home_screen_label_46.set_pos(116, 145)
ui_home_screen_label_46.set_size(150, 40)
# Set style for ui_home_screen_label_46, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_46.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_46.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_46.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_46.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_46.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_46.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_46.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_46.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_46.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_46.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_46.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_46.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_46.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_46.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_85
ui_home_screen_img_85 = lv.img(ui_home_screen_cont_29)
ui_home_screen_img_85.set_src("B:MicroPython/_sLscene2_alpha_45x45.bin")
ui_home_screen_img_85.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_85.set_pivot(50,50)
ui_home_screen_img_85.set_angle(0)
ui_home_screen_img_85.set_pos(135, 40)
ui_home_screen_img_85.set_size(45, 45)
# Set style for ui_home_screen_img_85, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_85.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_85.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_85.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_28
ui_home_screen_cont_28 = lv.obj(ui_home_screen_tabview_5_tab_1)
ui_home_screen_cont_28.set_pos(8, 5)
ui_home_screen_cont_28.set_size(320, 210)
ui_home_screen_cont_28.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_28, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_28.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_28.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_28.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_28.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_28.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_28.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_28.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_28.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_84
ui_home_screen_img_84 = lv.img(ui_home_screen_cont_28)
ui_home_screen_img_84.set_src("B:MicroPython/_Lscene1_alpha_320x210.bin")
ui_home_screen_img_84.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_84.set_pivot(50,50)
ui_home_screen_img_84.set_angle(0)
ui_home_screen_img_84.set_pos(0, 0)
ui_home_screen_img_84.set_size(320, 210)
# Set style for ui_home_screen_img_84, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_84.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_84.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_84.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_45
ui_home_screen_label_45 = lv.label(ui_home_screen_cont_28)
ui_home_screen_label_45.set_text("场景一")
ui_home_screen_label_45.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_45.set_width(lv.pct(100))
ui_home_screen_label_45.set_pos(115, 145)
ui_home_screen_label_45.set_size(90, 40)
# Set style for ui_home_screen_label_45, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_45.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_45.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_45.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_45.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_45.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_45.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_45.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_45.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_45.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_45.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_45.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_45.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_45.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_45.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_83
ui_home_screen_img_83 = lv.img(ui_home_screen_cont_28)
ui_home_screen_img_83.set_src("B:MicroPython/_sLscene1_alpha_45x45.bin")
ui_home_screen_img_83.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_83.set_pivot(50,50)
ui_home_screen_img_83.set_angle(0)
ui_home_screen_img_83.set_pos(135, 40)
ui_home_screen_img_83.set_size(45, 45)
# Set style for ui_home_screen_img_83, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_83.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_83.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_83.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_1
ui_home_screen_img_1 = lv.img(ui_home_screen_tileview_1_tile_3)
ui_home_screen_img_1.set_src("B:MicroPython/_color1_alpha_720x720.bin")
ui_home_screen_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_1.set_pivot(50,50)
ui_home_screen_img_1.set_angle(0)
ui_home_screen_img_1.set_pos(0, 0)
ui_home_screen_img_1.set_size(720, 720)
# Set style for ui_home_screen_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_1
ui_home_screen_label_1 = lv.label(ui_home_screen_tileview_1_tile_3)
ui_home_screen_label_1.set_text("2026/06/01")
ui_home_screen_label_1.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_1.set_width(lv.pct(100))
ui_home_screen_label_1.set_pos(67, 114)
ui_home_screen_label_1.set_size(172, 43)
# Set style for ui_home_screen_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_2
ui_home_screen_label_2 = lv.label(ui_home_screen_tileview_1_tile_3)
ui_home_screen_label_2.set_text("星期一")
ui_home_screen_label_2.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_2.set_width(lv.pct(100))
ui_home_screen_label_2.set_pos(61, 180)
ui_home_screen_label_2.set_size(118, 40)
# Set style for ui_home_screen_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_2.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_btn_65
ui_home_screen_btn_65 = lv.btn(ui_home_screen_tileview_1_tile_3)
ui_home_screen_btn_65.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_btn_65_label = lv.label(ui_home_screen_btn_65)
ui_home_screen_btn_65_label.set_text("")
ui_home_screen_btn_65_label.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_btn_65_label.set_width(lv.pct(100))
ui_home_screen_btn_65_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_btn_65.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_btn_65.set_pos(484, 484)
ui_home_screen_btn_65.set_size(236, 236)
# Set style for ui_home_screen_btn_65, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_btn_65.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_65.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_65.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_65.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_65.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_65.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_65.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_65.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for ui_home_screen_btn_65, Part: lv.PART.MAIN, State: lv.STATE.DISABLED.
ui_home_screen_btn_65.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DISABLED)
ui_home_screen_btn_65.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DISABLED)
ui_home_screen_btn_65.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DISABLED)
ui_home_screen_btn_65.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DISABLED)
ui_home_screen_btn_65.set_style_radius(5, lv.PART.MAIN|lv.STATE.DISABLED)
ui_home_screen_btn_65.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DISABLED)
ui_home_screen_btn_65.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DISABLED)
ui_home_screen_btn_65.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DISABLED)
ui_home_screen_btn_65.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DISABLED)

# Create ui_home_screen_btn_64
ui_home_screen_btn_64 = lv.btn(ui_home_screen_tileview_1_tile_3)
ui_home_screen_btn_64.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_btn_64_label = lv.label(ui_home_screen_btn_64)
ui_home_screen_btn_64_label.set_text("")
ui_home_screen_btn_64_label.set_long_mode(lv.label.LONG.CLIP)
ui_home_screen_btn_64_label.set_width(lv.pct(100))
ui_home_screen_btn_64_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_btn_64.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_btn_64.set_pos(484, 243)
ui_home_screen_btn_64.set_size(236, 236)
# Set style for ui_home_screen_btn_64, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_btn_64.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_64.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_64.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_64.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_64.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_64.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_64.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_64.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_btn_63
ui_home_screen_btn_63 = lv.btn(ui_home_screen_tileview_1_tile_3)
ui_home_screen_btn_63.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_btn_63_label = lv.label(ui_home_screen_btn_63)
ui_home_screen_btn_63_label.set_text("")
ui_home_screen_btn_63_label.set_long_mode(lv.label.LONG.CLIP)
ui_home_screen_btn_63_label.set_width(lv.pct(100))
ui_home_screen_btn_63_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_btn_63.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_btn_63.set_pos(484, 0)
ui_home_screen_btn_63.set_size(236, 236)
# Set style for ui_home_screen_btn_63, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_btn_63.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_63.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_63.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_63.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_63.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_63.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_63.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_btn_63.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_63
ui_home_screen_label_63 = lv.label(ui_home_screen_tileview_1_tile_3)
ui_home_screen_label_63.set_text("按键1")
ui_home_screen_label_63.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_63.set_width(lv.pct(100))
ui_home_screen_label_63.set_pos(566, 170)
ui_home_screen_label_63.set_size(72, 32)
# Set style for ui_home_screen_label_63, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_63.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_63.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_63.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_63.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_63.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_63.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_63.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_63.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_63.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_63.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_63.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_63.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_63.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_63.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_off_63_2
ui_home_screen_img_off_63_2 = lv.img(ui_home_screen_tileview_1_tile_3)
ui_home_screen_img_off_63_2.set_src("B:MicroPython/_HlightOn_alpha_30x45.bin")
ui_home_screen_img_off_63_2.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_off_63_2.set_pivot(50,50)
ui_home_screen_img_off_63_2.set_angle(0)
ui_home_screen_img_off_63_2.set_pos(587, 81)
ui_home_screen_img_off_63_2.set_size(30, 45)
# Set style for ui_home_screen_img_off_63_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_off_63_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_off_63_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_off_63_2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_off_63_1
ui_home_screen_img_off_63_1 = lv.img(ui_home_screen_tileview_1_tile_3)
ui_home_screen_img_off_63_1.set_src("B:MicroPython/_HlightOff_alpha_30x45.bin")
ui_home_screen_img_off_63_1.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_off_63_1.set_pivot(50,50)
ui_home_screen_img_off_63_1.set_angle(0)
ui_home_screen_img_off_63_1.set_pos(587, 81)
ui_home_screen_img_off_63_1.set_size(30, 45)
# Set style for ui_home_screen_img_off_63_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_off_63_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_off_63_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_off_63_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_64
ui_home_screen_label_64 = lv.label(ui_home_screen_tileview_1_tile_3)
ui_home_screen_label_64.set_text("按键2")
ui_home_screen_label_64.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_64.set_width(lv.pct(100))
ui_home_screen_label_64.set_pos(563, 410)
ui_home_screen_label_64.set_size(78, 32)
# Set style for ui_home_screen_label_64, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_64.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_64.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_64.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_64.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_64.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_64.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_64.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_64.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_64.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_64.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_64.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_64.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_64.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_64.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_on_64_2
ui_home_screen_img_on_64_2 = lv.img(ui_home_screen_tileview_1_tile_3)
ui_home_screen_img_on_64_2.set_src("B:MicroPython/_HlightOn_alpha_30x45.bin")
ui_home_screen_img_on_64_2.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_on_64_2.set_pivot(50,50)
ui_home_screen_img_on_64_2.set_angle(0)
ui_home_screen_img_on_64_2.set_pos(587, 316)
ui_home_screen_img_on_64_2.set_size(30, 45)
# Set style for ui_home_screen_img_on_64_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_on_64_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_on_64_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_on_64_2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_off_64_1
ui_home_screen_img_off_64_1 = lv.img(ui_home_screen_tileview_1_tile_3)
ui_home_screen_img_off_64_1.set_src("B:MicroPython/_HlightOff_alpha_30x45.bin")
ui_home_screen_img_off_64_1.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_off_64_1.set_pivot(50,50)
ui_home_screen_img_off_64_1.set_angle(0)
ui_home_screen_img_off_64_1.set_pos(587, 316)
ui_home_screen_img_off_64_1.set_size(30, 45)
# Set style for ui_home_screen_img_off_64_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_off_64_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_off_64_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_off_64_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_65
ui_home_screen_label_65 = lv.label(ui_home_screen_tileview_1_tile_3)
ui_home_screen_label_65.set_text("按键3")
ui_home_screen_label_65.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_65.set_width(lv.pct(100))
ui_home_screen_label_65.set_pos(562, 650)
ui_home_screen_label_65.set_size(80, 32)
# Set style for ui_home_screen_label_65, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_65.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_65.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_65.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_65.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_65.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_65.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_65.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_65.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_65.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_65.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_65.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_65.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_65.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_65.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_off_65_2
ui_home_screen_img_off_65_2 = lv.img(ui_home_screen_tileview_1_tile_3)
ui_home_screen_img_off_65_2.set_src("B:MicroPython/_HlightOn_alpha_30x45.bin")
ui_home_screen_img_off_65_2.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_off_65_2.set_pivot(50,50)
ui_home_screen_img_off_65_2.set_angle(0)
ui_home_screen_img_off_65_2.set_pos(587, 559)
ui_home_screen_img_off_65_2.set_size(30, 45)
# Set style for ui_home_screen_img_off_65_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_off_65_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_off_65_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_off_65_2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_off_65_1
ui_home_screen_img_off_65_1 = lv.img(ui_home_screen_tileview_1_tile_3)
ui_home_screen_img_off_65_1.set_src("B:MicroPython/_HlightOff_alpha_30x45.bin")
ui_home_screen_img_off_65_1.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_off_65_1.set_pivot(50,50)
ui_home_screen_img_off_65_1.set_angle(0)
ui_home_screen_img_off_65_1.set_pos(587, 559)
ui_home_screen_img_off_65_1.set_size(30, 45)
# Set style for ui_home_screen_img_off_65_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_off_65_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_off_65_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_off_65_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_tabview_3
ui_home_screen_tabview_3 = lv.tabview(ui_home_screen_tileview_1_tile_4, lv.DIR.TOP, 85)
ui_home_screen_tabview_3.set_pos(0, 0)
ui_home_screen_tabview_3.set_size(720, 720)
ui_home_screen_tabview_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_tabview_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_tabview_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_3.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_3.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_3.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_3.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_tabview_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_ui_home_screen_tabview_3_extra_btnm_main_default = lv.style_t()
style_ui_home_screen_tabview_3_extra_btnm_main_default.init()
style_ui_home_screen_tabview_3_extra_btnm_main_default.set_bg_opa(255)
style_ui_home_screen_tabview_3_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_ui_home_screen_tabview_3_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_ui_home_screen_tabview_3_extra_btnm_main_default.set_border_width(0)
style_ui_home_screen_tabview_3_extra_btnm_main_default.set_radius(0)
ui_home_screen_tabview_3.get_tab_btns().add_style(style_ui_home_screen_tabview_3_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_tabview_3, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_ui_home_screen_tabview_3_extra_btnm_items_default = lv.style_t()
style_ui_home_screen_tabview_3_extra_btnm_items_default.init()
style_ui_home_screen_tabview_3_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_ui_home_screen_tabview_3_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_ui_home_screen_tabview_3_extra_btnm_items_default.set_text_opa(255)
ui_home_screen_tabview_3.get_tab_btns().add_style(style_ui_home_screen_tabview_3_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for ui_home_screen_tabview_3, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_ui_home_screen_tabview_3_extra_btnm_items_checked = lv.style_t()
style_ui_home_screen_tabview_3_extra_btnm_items_checked.init()
style_ui_home_screen_tabview_3_extra_btnm_items_checked.set_text_color(lv.color_hex(0x2195f6))
style_ui_home_screen_tabview_3_extra_btnm_items_checked.set_text_font(test_font("montserratMedium", 12))
style_ui_home_screen_tabview_3_extra_btnm_items_checked.set_text_opa(255)
style_ui_home_screen_tabview_3_extra_btnm_items_checked.set_border_width(0)
style_ui_home_screen_tabview_3_extra_btnm_items_checked.set_radius(0)
style_ui_home_screen_tabview_3_extra_btnm_items_checked.set_bg_opa(255)
style_ui_home_screen_tabview_3_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x243241))
style_ui_home_screen_tabview_3_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
ui_home_screen_tabview_3.get_tab_btns().add_style(style_ui_home_screen_tabview_3_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
ui_home_screen_tabview_3_tab_1 = ui_home_screen_tabview_3.add_tab("")
ui_home_screen_tabview_3_tab_1_label = lv.label(ui_home_screen_tabview_3_tab_1)
ui_home_screen_tabview_3_tab_1_label.set_text("")

# Create ui_home_screen_cont_27
ui_home_screen_cont_27 = lv.obj(ui_home_screen_tabview_3_tab_1)
ui_home_screen_cont_27.set_pos(1, 0)
ui_home_screen_cont_27.set_size(330, 195)
ui_home_screen_cont_27.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_27, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_27.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_27.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_27.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_27.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_27.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_27.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_27.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_27.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_27.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_27.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_imgbtn_9
ui_home_screen_imgbtn_9 = lv.imgbtn(ui_home_screen_cont_27)
ui_home_screen_imgbtn_9.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_9.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_onoff_off_alpha_48x48.bin", None)
ui_home_screen_imgbtn_9.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_onoff_on_alpha_48x48.bin", None)
ui_home_screen_imgbtn_9.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_9_label = lv.label(ui_home_screen_imgbtn_9)
ui_home_screen_imgbtn_9_label.set_text("")
ui_home_screen_imgbtn_9_label.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_imgbtn_9_label.set_width(lv.pct(100))
ui_home_screen_imgbtn_9_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_imgbtn_9.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_imgbtn_9.set_pos(248, 29)
ui_home_screen_imgbtn_9.set_size(48, 48)
# Set style for ui_home_screen_imgbtn_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_imgbtn_9.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_9.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_9.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_9.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_9.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_9.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_9.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_imgbtn_9, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
ui_home_screen_imgbtn_9.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_9.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_9.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_9.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_9.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for ui_home_screen_imgbtn_9, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
ui_home_screen_imgbtn_9.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_9.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_9.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_9.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_9.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for ui_home_screen_imgbtn_9, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
ui_home_screen_imgbtn_9.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create ui_home_screen_img_61
ui_home_screen_img_61 = lv.img(ui_home_screen_cont_27)
ui_home_screen_img_61.set_src("B:MicroPython/_sdev_on_alpha_50x57.bin")
ui_home_screen_img_61.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_61.set_pivot(50,50)
ui_home_screen_img_61.set_angle(0)
ui_home_screen_img_61.set_pos(34, 20)
ui_home_screen_img_61.set_size(50, 57)
# Set style for ui_home_screen_img_61, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_61.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_61.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_61.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_60
ui_home_screen_img_60 = lv.img(ui_home_screen_cont_27)
ui_home_screen_img_60.set_src("B:MicroPython/_sdev_off_alpha_50x57.bin")
ui_home_screen_img_60.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_60.set_pivot(50,50)
ui_home_screen_img_60.set_angle(0)
ui_home_screen_img_60.set_pos(34, 20)
ui_home_screen_img_60.set_size(50, 57)
# Set style for ui_home_screen_img_60, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_60.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_60.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_60.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_36
ui_home_screen_label_36 = lv.label(ui_home_screen_cont_27)
ui_home_screen_label_36.set_text("色温灯")
ui_home_screen_label_36.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_36.set_width(lv.pct(100))
ui_home_screen_label_36.set_pos(20, 135)
ui_home_screen_label_36.set_size(100, 35)
# Set style for ui_home_screen_label_36, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_36.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_36.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_36.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_36.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_36.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_36.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_36.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_36.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_36.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_36.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_36.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_36.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_36.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_36.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_26
ui_home_screen_cont_26 = lv.obj(ui_home_screen_tabview_3_tab_1)
ui_home_screen_cont_26.set_pos(343, 0)
ui_home_screen_cont_26.set_size(330, 195)
ui_home_screen_cont_26.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_26, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_26.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_26.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_26.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_26.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_26.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_26.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_26.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_26.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_26.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_26.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_59
ui_home_screen_img_59 = lv.img(ui_home_screen_cont_26)
ui_home_screen_img_59.set_src("B:MicroPython/_sLSOn_alpha_65x43.bin")
ui_home_screen_img_59.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_59.set_pivot(50,50)
ui_home_screen_img_59.set_angle(0)
ui_home_screen_img_59.set_pos(20, 42)
ui_home_screen_img_59.set_size(65, 43)
# Set style for ui_home_screen_img_59, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_59.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_59.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_59.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_58
ui_home_screen_img_58 = lv.img(ui_home_screen_cont_26)
ui_home_screen_img_58.set_src("B:MicroPython/_sLSOff_alpha_65x43.bin")
ui_home_screen_img_58.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_58.set_pivot(50,50)
ui_home_screen_img_58.set_angle(0)
ui_home_screen_img_58.set_pos(20, 42)
ui_home_screen_img_58.set_size(65, 43)
# Set style for ui_home_screen_img_58, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_58.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_58.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_58.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_imgbtn_8
ui_home_screen_imgbtn_8 = lv.imgbtn(ui_home_screen_cont_26)
ui_home_screen_imgbtn_8.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_8.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_onoff_off_alpha_48x48.bin", None)
ui_home_screen_imgbtn_8.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_onoff_on_alpha_48x48.bin", None)
ui_home_screen_imgbtn_8.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_8_label = lv.label(ui_home_screen_imgbtn_8)
ui_home_screen_imgbtn_8_label.set_text("")
ui_home_screen_imgbtn_8_label.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_imgbtn_8_label.set_width(lv.pct(100))
ui_home_screen_imgbtn_8_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_imgbtn_8.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_imgbtn_8.set_pos(250, 30)
ui_home_screen_imgbtn_8.set_size(48, 48)
# Set style for ui_home_screen_imgbtn_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_imgbtn_8.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_8.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_8.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_8.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_8.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_8.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_imgbtn_8, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
ui_home_screen_imgbtn_8.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_8.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_8.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_8.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for ui_home_screen_imgbtn_8, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
ui_home_screen_imgbtn_8.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_8.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_8.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_8.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for ui_home_screen_imgbtn_8, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
ui_home_screen_imgbtn_8.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create ui_home_screen_label_35
ui_home_screen_label_35 = lv.label(ui_home_screen_cont_26)
ui_home_screen_label_35.set_text("灯  带")
ui_home_screen_label_35.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_35.set_width(lv.pct(100))
ui_home_screen_label_35.set_pos(19, 135)
ui_home_screen_label_35.set_size(92, 32)
# Set style for ui_home_screen_label_35, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_35.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_35.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_35.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_35.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_35.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_35.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_35.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_35.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_35.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_35.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_35.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_35.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_35.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_35.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_25
ui_home_screen_cont_25 = lv.obj(ui_home_screen_tabview_3_tab_1)
ui_home_screen_cont_25.set_pos(0, 211)
ui_home_screen_cont_25.set_size(330, 195)
ui_home_screen_cont_25.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_25, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_25.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_25.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_25.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_25.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_25.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_25.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_25.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_25.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_25.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_25.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_57
ui_home_screen_img_57 = lv.img(ui_home_screen_cont_25)
ui_home_screen_img_57.set_src("B:MicroPython/_sMLOn_alpha_70x4.bin")
ui_home_screen_img_57.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_57.set_pivot(50,50)
ui_home_screen_img_57.set_angle(0)
ui_home_screen_img_57.set_pos(30, 40)
ui_home_screen_img_57.set_size(70, 4)
# Set style for ui_home_screen_img_57, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_57.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_57.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_57.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_56
ui_home_screen_img_56 = lv.img(ui_home_screen_cont_25)
ui_home_screen_img_56.set_src("B:MicroPython/_sMLOff_alpha_70x4.bin")
ui_home_screen_img_56.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_56.set_pivot(50,50)
ui_home_screen_img_56.set_angle(0)
ui_home_screen_img_56.set_pos(30, 40)
ui_home_screen_img_56.set_size(70, 4)
# Set style for ui_home_screen_img_56, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_56.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_56.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_56.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_imgbtn_7
ui_home_screen_imgbtn_7 = lv.imgbtn(ui_home_screen_cont_25)
ui_home_screen_imgbtn_7.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_7.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_onoff_off_alpha_48x48.bin", None)
ui_home_screen_imgbtn_7.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_onoff_on_alpha_48x48.bin", None)
ui_home_screen_imgbtn_7.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_7_label = lv.label(ui_home_screen_imgbtn_7)
ui_home_screen_imgbtn_7_label.set_text("")
ui_home_screen_imgbtn_7_label.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_imgbtn_7_label.set_width(lv.pct(100))
ui_home_screen_imgbtn_7_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_imgbtn_7.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_imgbtn_7.set_pos(250, 30)
ui_home_screen_imgbtn_7.set_size(48, 48)
# Set style for ui_home_screen_imgbtn_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_imgbtn_7.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_7.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_7.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_7.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_7.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_imgbtn_7, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
ui_home_screen_imgbtn_7.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_7.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_7.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for ui_home_screen_imgbtn_7, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
ui_home_screen_imgbtn_7.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_7.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_7.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for ui_home_screen_imgbtn_7, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
ui_home_screen_imgbtn_7.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create ui_home_screen_label_34
ui_home_screen_label_34 = lv.label(ui_home_screen_cont_25)
ui_home_screen_label_34.set_text("磁吸灯")
ui_home_screen_label_34.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_34.set_width(lv.pct(100))
ui_home_screen_label_34.set_pos(18, 135)
ui_home_screen_label_34.set_size(100, 35)
# Set style for ui_home_screen_label_34, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_34.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_34.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_34.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_34.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_34.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_34.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_34.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_34.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_34.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_34.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_34.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_34.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_34.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_34.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_24
ui_home_screen_cont_24 = lv.obj(ui_home_screen_tabview_3_tab_1)
ui_home_screen_cont_24.set_pos(343, 209)
ui_home_screen_cont_24.set_size(330, 195)
ui_home_screen_cont_24.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_24, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_24.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_24.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_24.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_24.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_24.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_24.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_24.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_24.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_24.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_24.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_55
ui_home_screen_img_55 = lv.img(ui_home_screen_cont_24)
ui_home_screen_img_55.set_src("B:MicroPython/_sRGBLOn_alpha_60x58.bin")
ui_home_screen_img_55.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_55.set_pivot(50,50)
ui_home_screen_img_55.set_angle(0)
ui_home_screen_img_55.set_pos(27, 27)
ui_home_screen_img_55.set_size(60, 58)
# Set style for ui_home_screen_img_55, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_55.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_55.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_55.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_54
ui_home_screen_img_54 = lv.img(ui_home_screen_cont_24)
ui_home_screen_img_54.set_src("B:MicroPython/_sRGBLOff_alpha_60x58.bin")
ui_home_screen_img_54.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_54.set_pivot(50,50)
ui_home_screen_img_54.set_angle(0)
ui_home_screen_img_54.set_pos(27, 27)
ui_home_screen_img_54.set_size(60, 58)
# Set style for ui_home_screen_img_54, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_54.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_54.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_54.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_imgbtn_6
ui_home_screen_imgbtn_6 = lv.imgbtn(ui_home_screen_cont_24)
ui_home_screen_imgbtn_6.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_6.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_onoff_off_alpha_48x48.bin", None)
ui_home_screen_imgbtn_6.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_onoff_on_alpha_48x48.bin", None)
ui_home_screen_imgbtn_6.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_6_label = lv.label(ui_home_screen_imgbtn_6)
ui_home_screen_imgbtn_6_label.set_text("")
ui_home_screen_imgbtn_6_label.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_imgbtn_6_label.set_width(lv.pct(100))
ui_home_screen_imgbtn_6_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_imgbtn_6.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_imgbtn_6.set_pos(250, 30)
ui_home_screen_imgbtn_6.set_size(48, 48)
# Set style for ui_home_screen_imgbtn_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_imgbtn_6.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_6.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_6.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_6.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_6.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_imgbtn_6, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
ui_home_screen_imgbtn_6.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_6.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_6.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for ui_home_screen_imgbtn_6, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
ui_home_screen_imgbtn_6.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_6.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_6.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for ui_home_screen_imgbtn_6, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
ui_home_screen_imgbtn_6.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create ui_home_screen_label_33
ui_home_screen_label_33 = lv.label(ui_home_screen_cont_24)
ui_home_screen_label_33.set_text("彩色灯")
ui_home_screen_label_33.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_33.set_width(lv.pct(100))
ui_home_screen_label_33.set_pos(20, 135)
ui_home_screen_label_33.set_size(90, 35)
# Set style for ui_home_screen_label_33, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_33.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_33.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_33.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_33.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_33.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_33.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_33.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_33.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_33.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_33.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_33.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_33.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_33.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_33.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_23
ui_home_screen_cont_23 = lv.obj(ui_home_screen_tabview_3_tab_1)
ui_home_screen_cont_23.set_pos(0, 421)
ui_home_screen_cont_23.set_size(330, 195)
ui_home_screen_cont_23.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_23, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_23.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_23.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_23.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_23.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_23.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_23.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_23.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_23.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_23.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_23.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_53
ui_home_screen_img_53 = lv.img(ui_home_screen_cont_23)
ui_home_screen_img_53.set_src("B:MicroPython/_sFCOn_alpha_49x43.bin")
ui_home_screen_img_53.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_53.set_pivot(50,50)
ui_home_screen_img_53.set_angle(0)
ui_home_screen_img_53.set_pos(26, 38)
ui_home_screen_img_53.set_size(49, 43)
# Set style for ui_home_screen_img_53, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_53.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_53.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_53.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_52
ui_home_screen_img_52 = lv.img(ui_home_screen_cont_23)
ui_home_screen_img_52.set_src("B:MicroPython/_sFCOff_alpha_49x43.bin")
ui_home_screen_img_52.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_52.set_pivot(50,50)
ui_home_screen_img_52.set_angle(0)
ui_home_screen_img_52.set_pos(26, 38)
ui_home_screen_img_52.set_size(49, 43)
# Set style for ui_home_screen_img_52, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_52.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_52.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_52.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_32
ui_home_screen_label_32 = lv.label(ui_home_screen_cont_23)
ui_home_screen_label_32.set_text("布  帘")
ui_home_screen_label_32.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_32.set_width(lv.pct(100))
ui_home_screen_label_32.set_pos(20, 135)
ui_home_screen_label_32.set_size(82, 35)
# Set style for ui_home_screen_label_32, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_32.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_32.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_32.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_32.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_32.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_32.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_32.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_32.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_32.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_32.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_32.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_32.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_32.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_32.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_51
ui_home_screen_img_51 = lv.img(ui_home_screen_cont_23)
ui_home_screen_img_51.set_src("B:MicroPython/_sClose_alpha_60x60.bin")
ui_home_screen_img_51.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_51.set_pivot(50,50)
ui_home_screen_img_51.set_angle(0)
ui_home_screen_img_51.set_pos(249, 29)
ui_home_screen_img_51.set_size(60, 60)
# Set style for ui_home_screen_img_51, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_51.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_51.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_51.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_50
ui_home_screen_img_50 = lv.img(ui_home_screen_cont_23)
ui_home_screen_img_50.set_src("B:MicroPython/_sOpen_alpha_60x60.bin")
ui_home_screen_img_50.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_50.set_pivot(50,50)
ui_home_screen_img_50.set_angle(0)
ui_home_screen_img_50.set_pos(159, 29)
ui_home_screen_img_50.set_size(60, 60)
# Set style for ui_home_screen_img_50, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_50.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_50.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_50.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_22
ui_home_screen_cont_22 = lv.obj(ui_home_screen_tabview_3_tab_1)
ui_home_screen_cont_22.set_pos(345, 420)
ui_home_screen_cont_22.set_size(330, 195)
ui_home_screen_cont_22.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_22, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_22.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_22.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_22.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_22.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_22.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_22.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_22.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_22.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_22.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_22.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_49
ui_home_screen_img_49 = lv.img(ui_home_screen_cont_22)
ui_home_screen_img_49.set_src("B:MicroPython/_sFCOn_alpha_49x43.bin")
ui_home_screen_img_49.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_49.set_pivot(50,50)
ui_home_screen_img_49.set_angle(0)
ui_home_screen_img_49.set_pos(23, 39)
ui_home_screen_img_49.set_size(49, 43)
# Set style for ui_home_screen_img_49, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_49.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_49.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_49.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_48
ui_home_screen_img_48 = lv.img(ui_home_screen_cont_22)
ui_home_screen_img_48.set_src("B:MicroPython/_sFCOff_alpha_49x43.bin")
ui_home_screen_img_48.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_48.set_pivot(50,50)
ui_home_screen_img_48.set_angle(0)
ui_home_screen_img_48.set_pos(23, 38)
ui_home_screen_img_48.set_size(49, 43)
# Set style for ui_home_screen_img_48, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_48.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_48.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_48.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_31
ui_home_screen_label_31 = lv.label(ui_home_screen_cont_22)
ui_home_screen_label_31.set_text("纱  帘")
ui_home_screen_label_31.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_31.set_width(lv.pct(100))
ui_home_screen_label_31.set_pos(20, 135)
ui_home_screen_label_31.set_size(82, 35)
# Set style for ui_home_screen_label_31, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_31.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_31.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_31.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_31.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_31.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_31.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_31.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_31.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_31.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_31.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_31.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_31.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_31.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_31.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_47
ui_home_screen_img_47 = lv.img(ui_home_screen_cont_22)
ui_home_screen_img_47.set_src("B:MicroPython/_sOpen_alpha_60x60.bin")
ui_home_screen_img_47.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_47.set_pivot(50,50)
ui_home_screen_img_47.set_angle(0)
ui_home_screen_img_47.set_pos(160, 29)
ui_home_screen_img_47.set_size(60, 60)
# Set style for ui_home_screen_img_47, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_47.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_47.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_47.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_46
ui_home_screen_img_46 = lv.img(ui_home_screen_cont_22)
ui_home_screen_img_46.set_src("B:MicroPython/_sClose_alpha_60x60.bin")
ui_home_screen_img_46.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_46.set_pivot(50,50)
ui_home_screen_img_46.set_angle(0)
ui_home_screen_img_46.set_pos(250, 30)
ui_home_screen_img_46.set_size(60, 60)
# Set style for ui_home_screen_img_46, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_46.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_46.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_46.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_21
ui_home_screen_cont_21 = lv.obj(ui_home_screen_tabview_3_tab_1)
ui_home_screen_cont_21.set_pos(0, 630)
ui_home_screen_cont_21.set_size(330, 195)
ui_home_screen_cont_21.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_21, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_21.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_21.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_21.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_21.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_21.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_21.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_21.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_21.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_21.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_21.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_45
ui_home_screen_img_45 = lv.img(ui_home_screen_cont_21)
ui_home_screen_img_45.set_src("B:MicroPython/_sRBOn_alpha_65x20.bin")
ui_home_screen_img_45.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_45.set_pivot(50,50)
ui_home_screen_img_45.set_angle(0)
ui_home_screen_img_45.set_pos(26, 35)
ui_home_screen_img_45.set_size(65, 20)
# Set style for ui_home_screen_img_45, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_45.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_45.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_45.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_44
ui_home_screen_img_44 = lv.img(ui_home_screen_cont_21)
ui_home_screen_img_44.set_src("B:MicroPython/_sRBOff_alpha_65x43.bin")
ui_home_screen_img_44.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_44.set_pivot(50,50)
ui_home_screen_img_44.set_angle(0)
ui_home_screen_img_44.set_pos(26, 36)
ui_home_screen_img_44.set_size(65, 43)
# Set style for ui_home_screen_img_44, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_44.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_44.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_44.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_30
ui_home_screen_label_30 = lv.label(ui_home_screen_cont_21)
ui_home_screen_label_30.set_text("卷  帘")
ui_home_screen_label_30.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_30.set_width(lv.pct(100))
ui_home_screen_label_30.set_pos(20, 135)
ui_home_screen_label_30.set_size(82, 35)
# Set style for ui_home_screen_label_30, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_30.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_30.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_30.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_30.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_30.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_30.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_30.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_30.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_30.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_30.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_30.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_30.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_30.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_30.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_43
ui_home_screen_img_43 = lv.img(ui_home_screen_cont_21)
ui_home_screen_img_43.set_src("B:MicroPython/_sDown_alpha_60x60.bin")
ui_home_screen_img_43.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_43.set_pivot(50,50)
ui_home_screen_img_43.set_angle(0)
ui_home_screen_img_43.set_pos(250, 110)
ui_home_screen_img_43.set_size(60, 60)
# Set style for ui_home_screen_img_43, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_43.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_43.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_43.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_42
ui_home_screen_img_42 = lv.img(ui_home_screen_cont_21)
ui_home_screen_img_42.set_src("B:MicroPython/_sUp_alpha_60x60.bin")
ui_home_screen_img_42.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_42.set_pivot(50,50)
ui_home_screen_img_42.set_angle(0)
ui_home_screen_img_42.set_pos(250, 21)
ui_home_screen_img_42.set_size(60, 60)
# Set style for ui_home_screen_img_42, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_42.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_42.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_42.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_20
ui_home_screen_cont_20 = lv.obj(ui_home_screen_tabview_3_tab_1)
ui_home_screen_cont_20.set_pos(345, 630)
ui_home_screen_cont_20.set_size(330, 195)
ui_home_screen_cont_20.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_20, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_20.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_20.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_20.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_20.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_20.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_20.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_20.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_20.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_20.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_20.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_41
ui_home_screen_img_41 = lv.img(ui_home_screen_cont_20)
ui_home_screen_img_41.set_src("B:MicroPython/_sDreamOn_alpha_54x41.bin")
ui_home_screen_img_41.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_41.set_pivot(50,50)
ui_home_screen_img_41.set_angle(0)
ui_home_screen_img_41.set_pos(28, 34)
ui_home_screen_img_41.set_size(54, 41)
# Set style for ui_home_screen_img_41, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_41.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_41.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_41.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_40
ui_home_screen_img_40 = lv.img(ui_home_screen_cont_20)
ui_home_screen_img_40.set_src("B:MicroPython/_sDreamOff_alpha_54x41.bin")
ui_home_screen_img_40.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_40.set_pivot(50,50)
ui_home_screen_img_40.set_angle(0)
ui_home_screen_img_40.set_pos(28, 34)
ui_home_screen_img_40.set_size(54, 41)
# Set style for ui_home_screen_img_40, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_40.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_40.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_40.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_29
ui_home_screen_label_29 = lv.label(ui_home_screen_cont_20)
ui_home_screen_label_29.set_text("梦幻帘")
ui_home_screen_label_29.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_29.set_width(lv.pct(100))
ui_home_screen_label_29.set_pos(20, 135)
ui_home_screen_label_29.set_size(92, 35)
# Set style for ui_home_screen_label_29, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_29.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_29.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_29.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_29.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_29.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_29.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_29.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_29.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_29.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_29.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_29.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_29.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_29.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_29.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_39
ui_home_screen_img_39 = lv.img(ui_home_screen_cont_20)
ui_home_screen_img_39.set_src("B:MicroPython/_sClose_alpha_60x60.bin")
ui_home_screen_img_39.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_39.set_pivot(50,50)
ui_home_screen_img_39.set_angle(0)
ui_home_screen_img_39.set_pos(250, 30)
ui_home_screen_img_39.set_size(60, 60)
# Set style for ui_home_screen_img_39, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_39.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_39.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_39.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_38
ui_home_screen_img_38 = lv.img(ui_home_screen_cont_20)
ui_home_screen_img_38.set_src("B:MicroPython/_sOpen_alpha_60x60.bin")
ui_home_screen_img_38.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_38.set_pivot(50,50)
ui_home_screen_img_38.set_angle(0)
ui_home_screen_img_38.set_pos(160, 30)
ui_home_screen_img_38.set_size(60, 60)
# Set style for ui_home_screen_img_38, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_38.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_38.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_38.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_19
ui_home_screen_cont_19 = lv.obj(ui_home_screen_tabview_3_tab_1)
ui_home_screen_cont_19.set_pos(0, 840)
ui_home_screen_cont_19.set_size(330, 195)
ui_home_screen_cont_19.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_19, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_19.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_19.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_19.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_19.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_19.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_19.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_19.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_19.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_19.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_19.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_imgbtn_5
ui_home_screen_imgbtn_5 = lv.imgbtn(ui_home_screen_cont_19)
ui_home_screen_imgbtn_5.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_5.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_onoff_off_alpha_48x48.bin", None)
ui_home_screen_imgbtn_5.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_onoff_on_alpha_48x48.bin", None)
ui_home_screen_imgbtn_5.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_5_label = lv.label(ui_home_screen_imgbtn_5)
ui_home_screen_imgbtn_5_label.set_text("")
ui_home_screen_imgbtn_5_label.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_imgbtn_5_label.set_width(lv.pct(100))
ui_home_screen_imgbtn_5_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_imgbtn_5.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_imgbtn_5.set_pos(250, 30)
ui_home_screen_imgbtn_5.set_size(48, 48)
# Set style for ui_home_screen_imgbtn_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_imgbtn_5.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_5.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_5.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_5.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_imgbtn_5, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
ui_home_screen_imgbtn_5.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_5.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_5.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for ui_home_screen_imgbtn_5, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
ui_home_screen_imgbtn_5.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_5.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_5.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for ui_home_screen_imgbtn_5, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
ui_home_screen_imgbtn_5.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create ui_home_screen_label_28
ui_home_screen_label_28 = lv.label(ui_home_screen_cont_19)
ui_home_screen_label_28.set_text("空  调")
ui_home_screen_label_28.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_28.set_width(lv.pct(100))
ui_home_screen_label_28.set_pos(20, 135)
ui_home_screen_label_28.set_size(86, 35)
# Set style for ui_home_screen_label_28, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_28.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_28.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_28.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_28.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_28.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_28.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_28.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_28.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_28.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_28.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_28.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_28.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_28.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_28.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_27
ui_home_screen_label_27 = lv.label(ui_home_screen_cont_19)
ui_home_screen_label_27.set_text("16℃")
ui_home_screen_label_27.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_27.set_width(lv.pct(100))
ui_home_screen_label_27.set_pos(213, 142)
ui_home_screen_label_27.set_size(100, 32)
# Set style for ui_home_screen_label_27, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_27.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_27.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_27.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_27.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_27.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_27.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_27.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_27.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_27.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_27.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_27.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_27.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_27.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_27.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_26
ui_home_screen_label_26 = lv.label(ui_home_screen_cont_19)
ui_home_screen_label_26.set_text("关")
ui_home_screen_label_26.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_26.set_width(lv.pct(100))
ui_home_screen_label_26.set_pos(123, 33)
ui_home_screen_label_26.set_size(61, 37)
# Set style for ui_home_screen_label_26, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_26.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_26.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_26.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_26.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_26.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_26.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_26.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_26.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_26.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_26.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_26.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_26.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_26.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_26.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_25
ui_home_screen_label_25 = lv.label(ui_home_screen_cont_19)
ui_home_screen_label_25.set_text("送风")
ui_home_screen_label_25.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_25.set_width(lv.pct(100))
ui_home_screen_label_25.set_pos(123, 33)
ui_home_screen_label_25.set_size(61, 37)
# Set style for ui_home_screen_label_25, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_25.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_25.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_25.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_25.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_25.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_25.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_25.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_25.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_25.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_25.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_25.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_25.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_25.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_25.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_37
ui_home_screen_img_37 = lv.img(ui_home_screen_cont_19)
ui_home_screen_img_37.set_src("B:MicroPython/_sVACimg_alpha_77x49.bin")
ui_home_screen_img_37.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_37.set_pivot(50,50)
ui_home_screen_img_37.set_angle(0)
ui_home_screen_img_37.set_pos(17, 37)
ui_home_screen_img_37.set_size(77, 49)
# Set style for ui_home_screen_img_37, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_37.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_37.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_37.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_36
ui_home_screen_img_36 = lv.img(ui_home_screen_cont_19)
ui_home_screen_img_36.set_src("B:MicroPython/_sAC_alpha_77x49.bin")
ui_home_screen_img_36.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_36.set_pivot(50,50)
ui_home_screen_img_36.set_angle(0)
ui_home_screen_img_36.set_pos(17, 37)
ui_home_screen_img_36.set_size(77, 49)
# Set style for ui_home_screen_img_36, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_36.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_36.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_36.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_24
ui_home_screen_label_24 = lv.label(ui_home_screen_cont_19)
ui_home_screen_label_24.set_text("制冷")
ui_home_screen_label_24.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_24.set_width(lv.pct(100))
ui_home_screen_label_24.set_pos(123, 33)
ui_home_screen_label_24.set_size(61, 37)
# Set style for ui_home_screen_label_24, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_24.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_24.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_24.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_24.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_24.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_24.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_24.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_24.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_24.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_24.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_24.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_24.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_24.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_24.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_23
ui_home_screen_label_23 = lv.label(ui_home_screen_cont_19)
ui_home_screen_label_23.set_text("制热")
ui_home_screen_label_23.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_23.set_width(lv.pct(100))
ui_home_screen_label_23.set_pos(123, 33)
ui_home_screen_label_23.set_size(61, 37)
# Set style for ui_home_screen_label_23, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_23.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_23.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_23.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_23.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_23.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_23.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_23.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_23.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_23.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_23.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_23.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_23.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_23.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_23.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_22
ui_home_screen_label_22 = lv.label(ui_home_screen_cont_19)
ui_home_screen_label_22.set_text("除湿")
ui_home_screen_label_22.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_22.set_width(lv.pct(100))
ui_home_screen_label_22.set_pos(123, 33)
ui_home_screen_label_22.set_size(61, 37)
# Set style for ui_home_screen_label_22, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_22.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_22.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_22.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_22.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_22.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_22.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_22.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_22.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_22.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_22.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_22.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_22.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_22.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_22.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_18
ui_home_screen_cont_18 = lv.obj(ui_home_screen_tabview_3_tab_1)
ui_home_screen_cont_18.set_pos(344, 840)
ui_home_screen_cont_18.set_size(330, 195)
ui_home_screen_cont_18.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_18, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_18.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_18.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_18.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_18.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_18.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_18.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_18.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_18.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_18.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_18.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_35
ui_home_screen_img_35 = lv.img(ui_home_screen_cont_18)
ui_home_screen_img_35.set_src("B:MicroPython/_small_disc_alpha_51x51.bin")
ui_home_screen_img_35.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_35.set_pivot(50,50)
ui_home_screen_img_35.set_angle(0)
ui_home_screen_img_35.set_pos(23, 34)
ui_home_screen_img_35.set_size(51, 51)
# Set style for ui_home_screen_img_35, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_35.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_35.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_35.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_34
ui_home_screen_img_34 = lv.img(ui_home_screen_cont_18)
ui_home_screen_img_34.set_src("B:MicroPython/_srack_alpha_20x31.bin")
ui_home_screen_img_34.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_34.set_pivot(50,50)
ui_home_screen_img_34.set_angle(0)
ui_home_screen_img_34.set_pos(66, 26)
ui_home_screen_img_34.set_size(20, 31)
# Set style for ui_home_screen_img_34, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_34.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_34.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_34.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_imgbtn_4
ui_home_screen_imgbtn_4 = lv.imgbtn(ui_home_screen_cont_18)
ui_home_screen_imgbtn_4.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_4.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_small_play_alpha_60x60.bin", None)
ui_home_screen_imgbtn_4.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_small_pause_alpha_60x60.bin", None)
ui_home_screen_imgbtn_4.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_4_label = lv.label(ui_home_screen_imgbtn_4)
ui_home_screen_imgbtn_4_label.set_text("")
ui_home_screen_imgbtn_4_label.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_imgbtn_4_label.set_width(lv.pct(100))
ui_home_screen_imgbtn_4_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_imgbtn_4.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_imgbtn_4.set_pos(250, 30)
ui_home_screen_imgbtn_4.set_size(60, 60)
# Set style for ui_home_screen_imgbtn_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_imgbtn_4.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_4.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_4.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_imgbtn_4, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
ui_home_screen_imgbtn_4.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_4.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_4.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for ui_home_screen_imgbtn_4, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
ui_home_screen_imgbtn_4.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_4.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_4.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for ui_home_screen_imgbtn_4, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
ui_home_screen_imgbtn_4.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create ui_home_screen_label_21
ui_home_screen_label_21 = lv.label(ui_home_screen_cont_18)
ui_home_screen_label_21.set_text("音  乐")
ui_home_screen_label_21.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_21.set_width(lv.pct(100))
ui_home_screen_label_21.set_pos(20, 135)
ui_home_screen_label_21.set_size(91, 35)
# Set style for ui_home_screen_label_21, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_21.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_21.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_21.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_21.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_21.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_21.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_21.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_21.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_21.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_21.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_21.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_21.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_21.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_21.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_17
ui_home_screen_cont_17 = lv.obj(ui_home_screen_tabview_3_tab_1)
ui_home_screen_cont_17.set_pos(0, 1050)
ui_home_screen_cont_17.set_size(330, 195)
ui_home_screen_cont_17.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_17, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_17.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_17.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_17.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_17.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_17.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_17.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_17.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_17.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_17.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_17.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_33
ui_home_screen_img_33 = lv.img(ui_home_screen_cont_17)
ui_home_screen_img_33.set_src("B:MicroPython/_sDryRackOn_alpha_104x58.bin")
ui_home_screen_img_33.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_33.set_pivot(50,50)
ui_home_screen_img_33.set_angle(0)
ui_home_screen_img_33.set_pos(24, 16)
ui_home_screen_img_33.set_size(104, 58)
# Set style for ui_home_screen_img_33, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_33.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_33.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_33.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_32
ui_home_screen_img_32 = lv.img(ui_home_screen_cont_17)
ui_home_screen_img_32.set_src("B:MicroPython/_sDryRackOff_alpha_104x27.bin")
ui_home_screen_img_32.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_32.set_pivot(50,50)
ui_home_screen_img_32.set_angle(0)
ui_home_screen_img_32.set_pos(24, 16)
ui_home_screen_img_32.set_size(104, 27)
# Set style for ui_home_screen_img_32, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_32.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_32.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_32.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_20
ui_home_screen_label_20 = lv.label(ui_home_screen_cont_17)
ui_home_screen_label_20.set_text("晾衣机")
ui_home_screen_label_20.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_20.set_width(lv.pct(100))
ui_home_screen_label_20.set_pos(20, 135)
ui_home_screen_label_20.set_size(90, 35)
# Set style for ui_home_screen_label_20, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_20.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_20.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_20.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_20.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_20.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_20.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_20.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_20.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_20.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_20.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_20.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_20.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_20.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_20.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_31
ui_home_screen_img_31 = lv.img(ui_home_screen_cont_17)
ui_home_screen_img_31.set_src("B:MicroPython/_sDown_alpha_60x60.bin")
ui_home_screen_img_31.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_31.set_pivot(50,50)
ui_home_screen_img_31.set_angle(0)
ui_home_screen_img_31.set_pos(250, 110)
ui_home_screen_img_31.set_size(60, 60)
# Set style for ui_home_screen_img_31, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_31.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_31.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_31.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_30
ui_home_screen_img_30 = lv.img(ui_home_screen_cont_17)
ui_home_screen_img_30.set_src("B:MicroPython/_sUp_alpha_60x60.bin")
ui_home_screen_img_30.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_30.set_pivot(50,50)
ui_home_screen_img_30.set_angle(0)
ui_home_screen_img_30.set_pos(250, 20)
ui_home_screen_img_30.set_size(60, 60)
# Set style for ui_home_screen_img_30, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_30.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_30.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_30.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_19
ui_home_screen_img_19 = lv.img(ui_home_screen_cont_17)
ui_home_screen_img_19.set_src("B:MicroPython/_sDryRackL_alpha_21x5.bin")
ui_home_screen_img_19.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_19.set_pivot(50,50)
ui_home_screen_img_19.set_angle(0)
ui_home_screen_img_19.set_pos(63, 20)
ui_home_screen_img_19.set_size(21, 5)
# Set style for ui_home_screen_img_19, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_19.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_19.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_19.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_16
ui_home_screen_cont_16 = lv.obj(ui_home_screen_tabview_3_tab_1)
ui_home_screen_cont_16.set_pos(344, 1048)
ui_home_screen_cont_16.set_size(330, 195)
ui_home_screen_cont_16.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_16, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_16.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_16.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_16.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_16.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_16.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_16.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_16.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_16.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_16.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_16.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_img_29
ui_home_screen_img_29 = lv.img(ui_home_screen_cont_16)
ui_home_screen_img_29.set_src("B:MicroPython/_sFanAndLTon_alpha_60x60.bin")
ui_home_screen_img_29.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_29.set_pivot(50,50)
ui_home_screen_img_29.set_angle(0)
ui_home_screen_img_29.set_pos(19, 27)
ui_home_screen_img_29.set_size(60, 60)
# Set style for ui_home_screen_img_29, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_29.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_29.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_29.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_28
ui_home_screen_img_28 = lv.img(ui_home_screen_cont_16)
ui_home_screen_img_28.set_src("B:MicroPython/_sFanAndLToff_alpha_60x60.bin")
ui_home_screen_img_28.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_28.set_pivot(50,50)
ui_home_screen_img_28.set_angle(0)
ui_home_screen_img_28.set_pos(19, 27)
ui_home_screen_img_28.set_size(60, 60)
# Set style for ui_home_screen_img_28, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_28.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_28.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_28.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_imgbtn_3
ui_home_screen_imgbtn_3 = lv.imgbtn(ui_home_screen_cont_16)
ui_home_screen_imgbtn_3.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_3.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_sFanOff_alpha_60x60.bin", None)
ui_home_screen_imgbtn_3.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_sFanOn_alpha_60x60.bin", None)
ui_home_screen_imgbtn_3.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_3_label = lv.label(ui_home_screen_imgbtn_3)
ui_home_screen_imgbtn_3_label.set_text("")
ui_home_screen_imgbtn_3_label.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_imgbtn_3_label.set_width(lv.pct(100))
ui_home_screen_imgbtn_3_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_imgbtn_3.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_imgbtn_3.set_pos(250, 20)
ui_home_screen_imgbtn_3.set_size(60, 60)
# Set style for ui_home_screen_imgbtn_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_imgbtn_3.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_3.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_imgbtn_3, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
ui_home_screen_imgbtn_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_3.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_3.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for ui_home_screen_imgbtn_3, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
ui_home_screen_imgbtn_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_3.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_3.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for ui_home_screen_imgbtn_3, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
ui_home_screen_imgbtn_3.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create ui_home_screen_label_19
ui_home_screen_label_19 = lv.label(ui_home_screen_cont_16)
ui_home_screen_label_19.set_text("风扇灯")
ui_home_screen_label_19.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_19.set_width(lv.pct(100))
ui_home_screen_label_19.set_pos(20, 135)
ui_home_screen_label_19.set_size(91, 35)
# Set style for ui_home_screen_label_19, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_19.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_19.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_19.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_19.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_19.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_19.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_19.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_19.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_19.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_19.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_19.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_19.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_19.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_19.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_imgbtn_2
ui_home_screen_imgbtn_2 = lv.imgbtn(ui_home_screen_cont_16)
ui_home_screen_imgbtn_2.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_2.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_slightOff_alpha_60x60.bin", None)
ui_home_screen_imgbtn_2.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_slightOn_alpha_60x60.bin", None)
ui_home_screen_imgbtn_2.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_2_label = lv.label(ui_home_screen_imgbtn_2)
ui_home_screen_imgbtn_2_label.set_text("")
ui_home_screen_imgbtn_2_label.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_imgbtn_2_label.set_width(lv.pct(100))
ui_home_screen_imgbtn_2_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_imgbtn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_imgbtn_2.set_pos(160, 20)
ui_home_screen_imgbtn_2.set_size(60, 60)
# Set style for ui_home_screen_imgbtn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_imgbtn_2.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_2.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_imgbtn_2, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
ui_home_screen_imgbtn_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_2.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_2.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for ui_home_screen_imgbtn_2, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
ui_home_screen_imgbtn_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_2.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_2.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for ui_home_screen_imgbtn_2, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
ui_home_screen_imgbtn_2.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create ui_home_screen_cont_15
ui_home_screen_cont_15 = lv.obj(ui_home_screen_tabview_3_tab_1)
ui_home_screen_cont_15.set_pos(0, 1260)
ui_home_screen_cont_15.set_size(330, 195)
ui_home_screen_cont_15.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_15, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_15.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_15.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_15.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_15.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_15.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_15.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_15.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_15.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_15.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_15.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_label_18
ui_home_screen_label_18 = lv.label(ui_home_screen_cont_15)
ui_home_screen_label_18.set_text("浴  霸")
ui_home_screen_label_18.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_18.set_width(lv.pct(100))
ui_home_screen_label_18.set_pos(20, 135)
ui_home_screen_label_18.set_size(86, 35)
# Set style for ui_home_screen_label_18, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_18.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_18.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_18.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_18.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_18.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_18.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_18.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_18.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_18.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_18.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_18.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_18.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_18.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_18.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_27
ui_home_screen_img_27 = lv.img(ui_home_screen_cont_15)
ui_home_screen_img_27.set_src("B:MicroPython/_sIdleBtn_alpha_60x60.bin")
ui_home_screen_img_27.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_27.set_pivot(50,50)
ui_home_screen_img_27.set_angle(0)
ui_home_screen_img_27.set_pos(250, 30)
ui_home_screen_img_27.set_size(60, 60)
# Set style for ui_home_screen_img_27, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_27.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_27.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_27.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_26
ui_home_screen_img_26 = lv.img(ui_home_screen_cont_15)
ui_home_screen_img_26.set_src("B:MicroPython/_sHlight_alpha_65x43.bin")
ui_home_screen_img_26.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_26.set_pivot(50,50)
ui_home_screen_img_26.set_angle(0)
ui_home_screen_img_26.set_pos(22, 32)
ui_home_screen_img_26.set_size(65, 43)
# Set style for ui_home_screen_img_26, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_26.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_26.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_26.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_imgbtn_1
ui_home_screen_imgbtn_1 = lv.imgbtn(ui_home_screen_cont_15)
ui_home_screen_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_1.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_slightOff_alpha_60x60.bin", None)
ui_home_screen_imgbtn_1.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_slightOn_alpha_60x60.bin", None)
ui_home_screen_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
ui_home_screen_imgbtn_1_label = lv.label(ui_home_screen_imgbtn_1)
ui_home_screen_imgbtn_1_label.set_text("")
ui_home_screen_imgbtn_1_label.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_imgbtn_1_label.set_width(lv.pct(100))
ui_home_screen_imgbtn_1_label.align(lv.ALIGN.CENTER, 0, 0)
ui_home_screen_imgbtn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
ui_home_screen_imgbtn_1.set_pos(160, 30)
ui_home_screen_imgbtn_1.set_size(60, 60)
# Set style for ui_home_screen_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_imgbtn_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
ui_home_screen_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
ui_home_screen_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for ui_home_screen_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
ui_home_screen_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
ui_home_screen_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for ui_home_screen_imgbtn_1, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
ui_home_screen_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create ui_home_screen_img_25
ui_home_screen_img_25 = lv.img(ui_home_screen_cont_15)
ui_home_screen_img_25.set_src("B:MicroPython/_sLowHeatMode_alpha_65x43.bin")
ui_home_screen_img_25.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_25.set_pivot(50,50)
ui_home_screen_img_25.set_angle(0)
ui_home_screen_img_25.set_pos(23, 33)
ui_home_screen_img_25.set_size(65, 43)
# Set style for ui_home_screen_img_25, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_25.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_25.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_25.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_24
ui_home_screen_img_24 = lv.img(ui_home_screen_cont_15)
ui_home_screen_img_24.set_src("B:MicroPython/_sHeatMode_alpha_65x43.bin")
ui_home_screen_img_24.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_24.set_pivot(50,50)
ui_home_screen_img_24.set_angle(0)
ui_home_screen_img_24.set_pos(23, 33)
ui_home_screen_img_24.set_size(65, 43)
# Set style for ui_home_screen_img_24, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_24.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_24.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_24.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_23
ui_home_screen_img_23 = lv.img(ui_home_screen_cont_15)
ui_home_screen_img_23.set_src("B:MicroPython/_sventilate_alpha_65x43.bin")
ui_home_screen_img_23.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_23.set_pivot(50,50)
ui_home_screen_img_23.set_angle(0)
ui_home_screen_img_23.set_pos(23, 33)
ui_home_screen_img_23.set_size(65, 43)
# Set style for ui_home_screen_img_23, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_23.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_23.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_23.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_22
ui_home_screen_img_22 = lv.img(ui_home_screen_cont_15)
ui_home_screen_img_22.set_src("B:MicroPython/_sFanMode_alpha_65x43.bin")
ui_home_screen_img_22.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_22.set_pivot(50,50)
ui_home_screen_img_22.set_angle(0)
ui_home_screen_img_22.set_pos(23, 33)
ui_home_screen_img_22.set_size(65, 43)
# Set style for ui_home_screen_img_22, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_22.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_22.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_22.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_21
ui_home_screen_img_21 = lv.img(ui_home_screen_cont_15)
ui_home_screen_img_21.set_src("B:MicroPython/_sDev_alpha_65x43.bin")
ui_home_screen_img_21.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_21.set_pivot(50,50)
ui_home_screen_img_21.set_angle(0)
ui_home_screen_img_21.set_pos(23, 33)
ui_home_screen_img_21.set_size(65, 43)
# Set style for ui_home_screen_img_21, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_21.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_21.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_21.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_20
ui_home_screen_img_20 = lv.img(ui_home_screen_cont_15)
ui_home_screen_img_20.set_src("B:MicroPython/_sIdleMode_alpha_65x43.bin")
ui_home_screen_img_20.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_20.set_pivot(50,50)
ui_home_screen_img_20.set_angle(0)
ui_home_screen_img_20.set_pos(23, 33)
ui_home_screen_img_20.set_size(65, 43)
# Set style for ui_home_screen_img_20, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_20.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_20.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_20.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_17
ui_home_screen_label_17 = lv.label(ui_home_screen_tileview_1_tile_4)
ui_home_screen_label_17.set_text("设备管理")
ui_home_screen_label_17.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_17.set_width(lv.pct(100))
ui_home_screen_label_17.set_pos(40, 25)
ui_home_screen_label_17.set_size(120, 33)
# Set style for ui_home_screen_label_17, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_17.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_17.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_17.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_17.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_17.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_17.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_17.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_17.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_17.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_17.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_17.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_17.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_17.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_17.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_tabview_1
ui_home_screen_tabview_1 = lv.tabview(ui_home_screen_tileview_1_tile_5, lv.DIR.TOP, 85)
ui_home_screen_tabview_1.set_pos(0, 0)
ui_home_screen_tabview_1.set_size(720, 720)
ui_home_screen_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for ui_home_screen_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_ui_home_screen_tabview_1_extra_btnm_main_default = lv.style_t()
style_ui_home_screen_tabview_1_extra_btnm_main_default.init()
style_ui_home_screen_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_ui_home_screen_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_ui_home_screen_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_ui_home_screen_tabview_1_extra_btnm_main_default.set_border_width(0)
style_ui_home_screen_tabview_1_extra_btnm_main_default.set_radius(0)
ui_home_screen_tabview_1.get_tab_btns().add_style(style_ui_home_screen_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_ui_home_screen_tabview_1_extra_btnm_items_default = lv.style_t()
style_ui_home_screen_tabview_1_extra_btnm_items_default.init()
style_ui_home_screen_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_ui_home_screen_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_ui_home_screen_tabview_1_extra_btnm_items_default.set_text_opa(255)
ui_home_screen_tabview_1.get_tab_btns().add_style(style_ui_home_screen_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for ui_home_screen_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_ui_home_screen_tabview_1_extra_btnm_items_checked = lv.style_t()
style_ui_home_screen_tabview_1_extra_btnm_items_checked.init()
style_ui_home_screen_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_ui_home_screen_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_ui_home_screen_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_ui_home_screen_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_ui_home_screen_tabview_1_extra_btnm_items_checked.set_radius(0)
style_ui_home_screen_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_ui_home_screen_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_ui_home_screen_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
ui_home_screen_tabview_1.get_tab_btns().add_style(style_ui_home_screen_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
ui_home_screen_tabview_1_tab_1 = ui_home_screen_tabview_1.add_tab("")
ui_home_screen_tabview_1_tab_1_label = lv.label(ui_home_screen_tabview_1_tab_1)
ui_home_screen_tabview_1_tab_1_label.set_text("")

# Create ui_home_screen_cont_8
ui_home_screen_cont_8 = lv.obj(ui_home_screen_tabview_1_tab_1)
ui_home_screen_cont_8.set_pos(345, 400)
ui_home_screen_cont_8.set_size(330, 185)
ui_home_screen_cont_8.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_8.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_8.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_8.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_8.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_8.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_8.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_8.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_8.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_8.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_label_9
ui_home_screen_label_9 = lv.label(ui_home_screen_cont_8)
ui_home_screen_label_9.set_text("情景模式4")
ui_home_screen_label_9.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_9.set_width(lv.pct(100))
ui_home_screen_label_9.set_pos(85, 128)
ui_home_screen_label_9.set_size(160, 35)
# Set style for ui_home_screen_label_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_9.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_9.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_9.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_9.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_9.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_9.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_9.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_9.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_9.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_9.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_9.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_9.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_9.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_9.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_12
ui_home_screen_img_12 = lv.img(ui_home_screen_cont_8)
ui_home_screen_img_12.set_src("B:MicroPython/_LightScene4_alpha_48x48.bin")
ui_home_screen_img_12.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_12.set_pivot(50,50)
ui_home_screen_img_12.set_angle(0)
ui_home_screen_img_12.set_pos(135, 40)
ui_home_screen_img_12.set_size(48, 48)
# Set style for ui_home_screen_img_12, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_12.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_12.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_12.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_7
ui_home_screen_cont_7 = lv.obj(ui_home_screen_tabview_1_tab_1)
ui_home_screen_cont_7.set_pos(0, 400)
ui_home_screen_cont_7.set_size(330, 185)
ui_home_screen_cont_7.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_7.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_7.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_7.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_7.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_7.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_7.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_7.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_7.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_label_8
ui_home_screen_label_8 = lv.label(ui_home_screen_cont_7)
ui_home_screen_label_8.set_text("情景模式3")
ui_home_screen_label_8.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_8.set_width(lv.pct(100))
ui_home_screen_label_8.set_pos(85, 122)
ui_home_screen_label_8.set_size(150, 40)
# Set style for ui_home_screen_label_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_8.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_8.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_8.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_8.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_8.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_8.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_8.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_8.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_8.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_8.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_8.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_8.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_8.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_11
ui_home_screen_img_11 = lv.img(ui_home_screen_cont_7)
ui_home_screen_img_11.set_src("B:MicroPython/_LightScene3_alpha_48x48.bin")
ui_home_screen_img_11.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_11.set_pivot(50,50)
ui_home_screen_img_11.set_angle(0)
ui_home_screen_img_11.set_pos(135, 40)
ui_home_screen_img_11.set_size(48, 48)
# Set style for ui_home_screen_img_11, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_11.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_11.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_11.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_6
ui_home_screen_cont_6 = lv.obj(ui_home_screen_tabview_1_tab_1)
ui_home_screen_cont_6.set_pos(0, 200)
ui_home_screen_cont_6.set_size(330, 185)
ui_home_screen_cont_6.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_6.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_6.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_6.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_6.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_6.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_6.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_6.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_6.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_label_7
ui_home_screen_label_7 = lv.label(ui_home_screen_cont_6)
ui_home_screen_label_7.set_text("情景模式1")
ui_home_screen_label_7.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_7.set_width(lv.pct(100))
ui_home_screen_label_7.set_pos(85, 134)
ui_home_screen_label_7.set_size(150, 40)
# Set style for ui_home_screen_label_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_7.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_7.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_7.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_7.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_7.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_7.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_7.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_7.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_7.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_7.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_7.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_10
ui_home_screen_img_10 = lv.img(ui_home_screen_cont_6)
ui_home_screen_img_10.set_src("B:MicroPython/_LightScene1_alpha_48x48.bin")
ui_home_screen_img_10.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_10.set_pivot(50,50)
ui_home_screen_img_10.set_angle(0)
ui_home_screen_img_10.set_pos(135, 40)
ui_home_screen_img_10.set_size(48, 48)
# Set style for ui_home_screen_img_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_10.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_10.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_10.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_5
ui_home_screen_cont_5 = lv.obj(ui_home_screen_tabview_1_tab_1)
ui_home_screen_cont_5.set_pos(344, 200)
ui_home_screen_cont_5.set_size(330, 185)
ui_home_screen_cont_5.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_5.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_5.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_5.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_5.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_5.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_5.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_5.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_label_6
ui_home_screen_label_6 = lv.label(ui_home_screen_cont_5)
ui_home_screen_label_6.set_text("情景模式2")
ui_home_screen_label_6.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_6.set_width(lv.pct(100))
ui_home_screen_label_6.set_pos(85, 130)
ui_home_screen_label_6.set_size(150, 40)
# Set style for ui_home_screen_label_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_6.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_6.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_6.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_6.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_6.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_6.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_6.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_6.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_6.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_6.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_6.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_9
ui_home_screen_img_9 = lv.img(ui_home_screen_cont_5)
ui_home_screen_img_9.set_src("B:MicroPython/_LightScene2_alpha_48x48.bin")
ui_home_screen_img_9.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_9.set_pivot(50,50)
ui_home_screen_img_9.set_angle(0)
ui_home_screen_img_9.set_pos(135, 40)
ui_home_screen_img_9.set_size(48, 48)
# Set style for ui_home_screen_img_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_9.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_9.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_9.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_4
ui_home_screen_cont_4 = lv.obj(ui_home_screen_tabview_1_tab_1)
ui_home_screen_cont_4.set_pos(344, 1)
ui_home_screen_cont_4.set_size(330, 185)
ui_home_screen_cont_4.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_4.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_4.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_4.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_4.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_4.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_4.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_4.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_4.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_label_5
ui_home_screen_label_5 = lv.label(ui_home_screen_cont_4)
ui_home_screen_label_5.set_text("灯光全关")
ui_home_screen_label_5.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_5.set_width(lv.pct(100))
ui_home_screen_label_5.set_pos(85, 127)
ui_home_screen_label_5.set_size(150, 40)
# Set style for ui_home_screen_label_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_5.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_5.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_5.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_5.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_5.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_5.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_5.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_5.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_5.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_5.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_8
ui_home_screen_img_8 = lv.img(ui_home_screen_cont_4)
ui_home_screen_img_8.set_src("B:MicroPython/_onoff_off_alpha_48x48.bin")
ui_home_screen_img_8.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_8.set_pivot(50,50)
ui_home_screen_img_8.set_angle(0)
ui_home_screen_img_8.set_pos(135, 40)
ui_home_screen_img_8.set_size(48, 48)
# Set style for ui_home_screen_img_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_8.set_style_img_recolor_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_8.set_style_img_recolor(lv.color_hex(0xc62a2a), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_8.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_8.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_8.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_3
ui_home_screen_cont_3 = lv.obj(ui_home_screen_tabview_1_tab_1)
ui_home_screen_cont_3.set_pos(0, 1)
ui_home_screen_cont_3.set_size(330, 185)
ui_home_screen_cont_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_3.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_3.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_label_4
ui_home_screen_label_4 = lv.label(ui_home_screen_cont_3)
ui_home_screen_label_4.set_text("灯光全开")
ui_home_screen_label_4.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_4.set_width(lv.pct(100))
ui_home_screen_label_4.set_pos(85, 130)
ui_home_screen_label_4.set_size(150, 40)
# Set style for ui_home_screen_label_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_4.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_4.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_4.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_4.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_4.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_4.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_4.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_7
ui_home_screen_img_7 = lv.img(ui_home_screen_cont_3)
ui_home_screen_img_7.set_src("B:MicroPython/_onoff_on_alpha_48x48.bin")
ui_home_screen_img_7.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_7.set_pivot(50,50)
ui_home_screen_img_7.set_angle(0)
ui_home_screen_img_7.set_pos(135, 40)
ui_home_screen_img_7.set_size(48, 48)
# Set style for ui_home_screen_img_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_7.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_7.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_7.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_3
ui_home_screen_label_3 = lv.label(ui_home_screen_tileview_1_tile_5)
ui_home_screen_label_3.set_text("灯光情景")
ui_home_screen_label_3.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_3.set_width(lv.pct(100))
ui_home_screen_label_3.set_pos(43, 25)
ui_home_screen_label_3.set_size(125, 32)
# Set style for ui_home_screen_label_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_3.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_3.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_tabview_2
ui_home_screen_tabview_2 = lv.tabview(ui_home_screen_tileview_1_tile_6, lv.DIR.TOP, 85)
ui_home_screen_tabview_2.set_pos(0, 0)
ui_home_screen_tabview_2.set_size(720, 720)
ui_home_screen_tabview_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for ui_home_screen_tabview_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_tabview_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_2.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_2.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_2.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_2.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_tabview_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_tabview_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_ui_home_screen_tabview_2_extra_btnm_main_default = lv.style_t()
style_ui_home_screen_tabview_2_extra_btnm_main_default.init()
style_ui_home_screen_tabview_2_extra_btnm_main_default.set_bg_opa(255)
style_ui_home_screen_tabview_2_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_ui_home_screen_tabview_2_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_ui_home_screen_tabview_2_extra_btnm_main_default.set_border_width(0)
style_ui_home_screen_tabview_2_extra_btnm_main_default.set_radius(0)
ui_home_screen_tabview_2.get_tab_btns().add_style(style_ui_home_screen_tabview_2_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for ui_home_screen_tabview_2, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_ui_home_screen_tabview_2_extra_btnm_items_default = lv.style_t()
style_ui_home_screen_tabview_2_extra_btnm_items_default.init()
style_ui_home_screen_tabview_2_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_ui_home_screen_tabview_2_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_ui_home_screen_tabview_2_extra_btnm_items_default.set_text_opa(255)
ui_home_screen_tabview_2.get_tab_btns().add_style(style_ui_home_screen_tabview_2_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for ui_home_screen_tabview_2, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_ui_home_screen_tabview_2_extra_btnm_items_checked = lv.style_t()
style_ui_home_screen_tabview_2_extra_btnm_items_checked.init()
style_ui_home_screen_tabview_2_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_ui_home_screen_tabview_2_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_ui_home_screen_tabview_2_extra_btnm_items_checked.set_text_opa(255)
style_ui_home_screen_tabview_2_extra_btnm_items_checked.set_border_width(0)
style_ui_home_screen_tabview_2_extra_btnm_items_checked.set_radius(0)
style_ui_home_screen_tabview_2_extra_btnm_items_checked.set_bg_opa(255)
style_ui_home_screen_tabview_2_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_ui_home_screen_tabview_2_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
ui_home_screen_tabview_2.get_tab_btns().add_style(style_ui_home_screen_tabview_2_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
ui_home_screen_tabview_2_tab_1 = ui_home_screen_tabview_2.add_tab("")
ui_home_screen_tabview_2_tab_1_label = lv.label(ui_home_screen_tabview_2_tab_1)
ui_home_screen_tabview_2_tab_1_label.set_text("")

# Create ui_home_screen_cont_14
ui_home_screen_cont_14 = lv.obj(ui_home_screen_tabview_2_tab_1)
ui_home_screen_cont_14.set_pos(345, 400)
ui_home_screen_cont_14.set_size(330, 185)
ui_home_screen_cont_14.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_14, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_14.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_14.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_14.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_14.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_14.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_14.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_14.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_14.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_14.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_14.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_label_16
ui_home_screen_label_16 = lv.label(ui_home_screen_cont_14)
ui_home_screen_label_16.set_text("80%")
ui_home_screen_label_16.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_16.set_width(lv.pct(100))
ui_home_screen_label_16.set_pos(140, 130)
ui_home_screen_label_16.set_size(70, 35)
# Set style for ui_home_screen_label_16, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_16.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_16.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_16.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_16.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_16.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_16.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_16.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_16.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_16.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_16.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_16.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_16.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_16.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_16.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_18
ui_home_screen_img_18 = lv.img(ui_home_screen_cont_14)
ui_home_screen_img_18.set_src("B:MicroPython/_CuratianS4_alpha_59x31.bin")
ui_home_screen_img_18.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_18.set_pivot(50,50)
ui_home_screen_img_18.set_angle(0)
ui_home_screen_img_18.set_pos(135, 40)
ui_home_screen_img_18.set_size(59, 31)
# Set style for ui_home_screen_img_18, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_18.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_18.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_18.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_13
ui_home_screen_cont_13 = lv.obj(ui_home_screen_tabview_2_tab_1)
ui_home_screen_cont_13.set_pos(0, 400)
ui_home_screen_cont_13.set_size(330, 185)
ui_home_screen_cont_13.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_13, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_13.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_13.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_13.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_13.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_13.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_13.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_13.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_13.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_13.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_13.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_label_15
ui_home_screen_label_15 = lv.label(ui_home_screen_cont_13)
ui_home_screen_label_15.set_text("60%")
ui_home_screen_label_15.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_15.set_width(lv.pct(100))
ui_home_screen_label_15.set_pos(140, 130)
ui_home_screen_label_15.set_size(65, 30)
# Set style for ui_home_screen_label_15, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_15.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_15.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_15.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_15.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_15.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_15.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_15.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_15.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_15.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_15.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_15.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_15.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_15.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_15.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_17
ui_home_screen_img_17 = lv.img(ui_home_screen_cont_13)
ui_home_screen_img_17.set_src("B:MicroPython/_CuratianS3_alpha_59x31.bin")
ui_home_screen_img_17.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_17.set_pivot(50,50)
ui_home_screen_img_17.set_angle(0)
ui_home_screen_img_17.set_pos(135, 40)
ui_home_screen_img_17.set_size(59, 31)
# Set style for ui_home_screen_img_17, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_17.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_17.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_17.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_12
ui_home_screen_cont_12 = lv.obj(ui_home_screen_tabview_2_tab_1)
ui_home_screen_cont_12.set_pos(0, 200)
ui_home_screen_cont_12.set_size(330, 185)
ui_home_screen_cont_12.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_12, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_12.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_12.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_12.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_12.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_12.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_12.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_12.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_12.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_12.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_12.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_label_14
ui_home_screen_label_14 = lv.label(ui_home_screen_cont_12)
ui_home_screen_label_14.set_text("20%")
ui_home_screen_label_14.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_14.set_width(lv.pct(100))
ui_home_screen_label_14.set_pos(140, 130)
ui_home_screen_label_14.set_size(61, 35)
# Set style for ui_home_screen_label_14, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_14.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_14.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_14.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_14.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_14.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_14.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_14.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_14.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_14.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_14.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_14.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_14.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_14.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_14.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_16
ui_home_screen_img_16 = lv.img(ui_home_screen_cont_12)
ui_home_screen_img_16.set_src("B:MicroPython/_CuratianS1_alpha_59x31.bin")
ui_home_screen_img_16.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_16.set_pivot(50,50)
ui_home_screen_img_16.set_angle(0)
ui_home_screen_img_16.set_pos(135, 40)
ui_home_screen_img_16.set_size(59, 31)
# Set style for ui_home_screen_img_16, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_16.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_16.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_16.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_11
ui_home_screen_cont_11 = lv.obj(ui_home_screen_tabview_2_tab_1)
ui_home_screen_cont_11.set_pos(344, 200)
ui_home_screen_cont_11.set_size(330, 185)
ui_home_screen_cont_11.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_11, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_11.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_11.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_11.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_11.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_11.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_11.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_11.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_11.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_11.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_11.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_label_13
ui_home_screen_label_13 = lv.label(ui_home_screen_cont_11)
ui_home_screen_label_13.set_text("40%")
ui_home_screen_label_13.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_13.set_width(lv.pct(100))
ui_home_screen_label_13.set_pos(140, 128)
ui_home_screen_label_13.set_size(67, 40)
# Set style for ui_home_screen_label_13, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_13.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_13.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_13.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_13.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_13.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_13.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_13.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_13.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_13.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_13.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_13.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_13.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_13.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_13.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_15
ui_home_screen_img_15 = lv.img(ui_home_screen_cont_11)
ui_home_screen_img_15.set_src("B:MicroPython/_CuratianS2_alpha_59x31.bin")
ui_home_screen_img_15.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_15.set_pivot(50,50)
ui_home_screen_img_15.set_angle(0)
ui_home_screen_img_15.set_pos(135, 40)
ui_home_screen_img_15.set_size(59, 31)
# Set style for ui_home_screen_img_15, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_15.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_15.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_15.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_10
ui_home_screen_cont_10 = lv.obj(ui_home_screen_tabview_2_tab_1)
ui_home_screen_cont_10.set_pos(344, 1)
ui_home_screen_cont_10.set_size(330, 185)
ui_home_screen_cont_10.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_10.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_10.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_10.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_10.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_10.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_10.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_10.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_10.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_10.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_10.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_label_12
ui_home_screen_label_12 = lv.label(ui_home_screen_cont_10)
ui_home_screen_label_12.set_text("窗帘全关")
ui_home_screen_label_12.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_12.set_width(lv.pct(100))
ui_home_screen_label_12.set_pos(85, 127)
ui_home_screen_label_12.set_size(150, 40)
# Set style for ui_home_screen_label_12, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_12.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_12.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_12.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_12.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_12.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_12.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_12.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_12.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_12.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_12.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_12.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_12.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_12.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_12.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_14
ui_home_screen_img_14 = lv.img(ui_home_screen_cont_10)
ui_home_screen_img_14.set_src("B:MicroPython/_CurAllClose_alpha_53x31.bin")
ui_home_screen_img_14.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_14.set_pivot(50,50)
ui_home_screen_img_14.set_angle(0)
ui_home_screen_img_14.set_pos(135, 40)
ui_home_screen_img_14.set_size(53, 31)
# Set style for ui_home_screen_img_14, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_14.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_14.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_14.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_cont_9
ui_home_screen_cont_9 = lv.obj(ui_home_screen_tabview_2_tab_1)
ui_home_screen_cont_9.set_pos(0, 1)
ui_home_screen_cont_9.set_size(330, 185)
ui_home_screen_cont_9.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for ui_home_screen_cont_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_cont_9.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_9.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_9.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_9.set_style_bg_color(lv.color_hex(0x333641), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_9.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_9.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_9.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_9.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_9.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_cont_9.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create ui_home_screen_label_11
ui_home_screen_label_11 = lv.label(ui_home_screen_cont_9)
ui_home_screen_label_11.set_text("窗帘全开")
ui_home_screen_label_11.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_11.set_width(lv.pct(100))
ui_home_screen_label_11.set_pos(85, 130)
ui_home_screen_label_11.set_size(150, 40)
# Set style for ui_home_screen_label_11, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_11.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_11.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_11.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_11.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_11.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_11.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_11.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_11.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_11.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_11.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_11.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_11.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_11.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_11.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_img_13
ui_home_screen_img_13 = lv.img(ui_home_screen_cont_9)
ui_home_screen_img_13.set_src("B:MicroPython/_CurAllOpen_alpha_53x31.bin")
ui_home_screen_img_13.add_flag(lv.obj.FLAG.CLICKABLE)
ui_home_screen_img_13.set_pivot(50,50)
ui_home_screen_img_13.set_angle(0)
ui_home_screen_img_13.set_pos(135, 40)
ui_home_screen_img_13.set_size(53, 31)
# Set style for ui_home_screen_img_13, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_img_13.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_13.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_img_13.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create ui_home_screen_label_10
ui_home_screen_label_10 = lv.label(ui_home_screen_tileview_1_tile_6)
ui_home_screen_label_10.set_text("窗帘情景")
ui_home_screen_label_10.set_long_mode(lv.label.LONG.WRAP)
ui_home_screen_label_10.set_width(lv.pct(100))
ui_home_screen_label_10.set_pos(43, 25)
ui_home_screen_label_10.set_size(125, 32)
# Set style for ui_home_screen_label_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
ui_home_screen_label_10.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_10.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_10.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_10.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_10.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_10.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_10.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_10.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_10.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_10.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_10.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_10.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_10.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
ui_home_screen_label_10.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

ui_home_screen.update_layout()
# Create light_CT_screen
light_CT_screen = lv.obj()
light_CT_screen.set_size(720, 720)
light_CT_screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for light_CT_screen, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_tabview_1
light_CT_screen_tabview_1 = lv.tabview(light_CT_screen, lv.DIR.TOP, 85)
light_CT_screen_tabview_1.set_pos(0, -1)
light_CT_screen_tabview_1.set_size(720, 720)
light_CT_screen_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for light_CT_screen_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for light_CT_screen_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_light_CT_screen_tabview_1_extra_btnm_main_default = lv.style_t()
style_light_CT_screen_tabview_1_extra_btnm_main_default.init()
style_light_CT_screen_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_light_CT_screen_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_light_CT_screen_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_light_CT_screen_tabview_1_extra_btnm_main_default.set_border_width(0)
style_light_CT_screen_tabview_1_extra_btnm_main_default.set_radius(0)
light_CT_screen_tabview_1.get_tab_btns().add_style(style_light_CT_screen_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for light_CT_screen_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_light_CT_screen_tabview_1_extra_btnm_items_default = lv.style_t()
style_light_CT_screen_tabview_1_extra_btnm_items_default.init()
style_light_CT_screen_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_light_CT_screen_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_light_CT_screen_tabview_1_extra_btnm_items_default.set_text_opa(255)
light_CT_screen_tabview_1.get_tab_btns().add_style(style_light_CT_screen_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for light_CT_screen_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_light_CT_screen_tabview_1_extra_btnm_items_checked = lv.style_t()
style_light_CT_screen_tabview_1_extra_btnm_items_checked.init()
style_light_CT_screen_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_light_CT_screen_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_light_CT_screen_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_light_CT_screen_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_light_CT_screen_tabview_1_extra_btnm_items_checked.set_radius(0)
style_light_CT_screen_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_light_CT_screen_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x243241))
style_light_CT_screen_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
light_CT_screen_tabview_1.get_tab_btns().add_style(style_light_CT_screen_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
light_CT_screen_tabview_1_tab_1 = light_CT_screen_tabview_1.add_tab("")
light_CT_screen_tabview_1_tab_1_label = lv.label(light_CT_screen_tabview_1_tab_1)
light_CT_screen_tabview_1_tab_1_label.set_text("")

# Create light_CT_screen_cont_1
light_CT_screen_cont_1 = lv.obj(light_CT_screen)
light_CT_screen_cont_1.set_pos(0, 88)
light_CT_screen_cont_1.set_size(720, 630)
light_CT_screen_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for light_CT_screen_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_1.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_label_2
light_CT_screen_label_2 = lv.label(light_CT_screen)
light_CT_screen_label_2.set_text("色 温 | 4850K")
light_CT_screen_label_2.set_long_mode(lv.label.LONG.WRAP)
light_CT_screen_label_2.set_width(lv.pct(100))
light_CT_screen_label_2.set_pos(270, 560)
light_CT_screen_label_2.set_size(195, 34)
# Set style for light_CT_screen_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_2.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_ct_bar
light_CT_screen_ct_bar = lv.img(light_CT_screen)
light_CT_screen_ct_bar.set_src("B:MicroPython/_ct_bar_alpha_650x75.bin")
light_CT_screen_ct_bar.add_flag(lv.obj.FLAG.CLICKABLE)
light_CT_screen_ct_bar.set_pivot(50,50)
light_CT_screen_ct_bar.set_angle(0)
light_CT_screen_ct_bar.set_pos(-210, 610)
light_CT_screen_ct_bar.set_size(650, 75)
# Set style for light_CT_screen_ct_bar, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_ct_bar.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_ct_bar.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_ct_bar.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_slider_2
light_CT_screen_slider_2 = lv.slider(light_CT_screen)
light_CT_screen_slider_2.set_range(2700, 6500)
light_CT_screen_slider_2.set_mode(lv.slider.MODE.SYMMETRICAL)
light_CT_screen_slider_2.set_value(4600, lv.ANIM.OFF)
light_CT_screen_slider_2.set_pos(-210, 610)
light_CT_screen_slider_2.set_size(650, 75)
# Set style for light_CT_screen_slider_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_slider_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_slider_2.set_style_radius(60, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_slider_2.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_slider_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for light_CT_screen_slider_2, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
light_CT_screen_slider_2.set_style_bg_opa(0, lv.PART.INDICATOR|lv.STATE.DEFAULT)
light_CT_screen_slider_2.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for light_CT_screen_slider_2, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
light_CT_screen_slider_2.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
light_CT_screen_slider_2.set_style_bg_color(lv.color_hex(0x300208), lv.PART.KNOB|lv.STATE.DEFAULT)
light_CT_screen_slider_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
light_CT_screen_slider_2.set_style_radius(60, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create light_CT_screen_slider_1
light_CT_screen_slider_1 = lv.slider(light_CT_screen)
light_CT_screen_slider_1.set_range(0, 100)
light_CT_screen_slider_1.set_mode(lv.slider.MODE.SYMMETRICAL)
light_CT_screen_slider_1.set_value(50, lv.ANIM.OFF)
light_CT_screen_slider_1.set_pos(-215, 465)
light_CT_screen_slider_1.set_size(650, 70)
# Set style for light_CT_screen_slider_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_slider_1.set_style_bg_opa(60, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_slider_1.set_style_bg_color(lv.color_hex(0xdedfdf), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_slider_1.set_style_radius(60, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_slider_1.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_slider_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for light_CT_screen_slider_1, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
light_CT_screen_slider_1.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
light_CT_screen_slider_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.INDICATOR|lv.STATE.DEFAULT)
light_CT_screen_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.DEFAULT)
light_CT_screen_slider_1.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for light_CT_screen_slider_1, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
light_CT_screen_slider_1.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DEFAULT)
light_CT_screen_slider_1.set_style_radius(60, lv.PART.KNOB|lv.STATE.DEFAULT)

# Set style for light_CT_screen_slider_1, Part: lv.PART.KNOB, State: lv.STATE.DISABLED.
light_CT_screen_slider_1.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DISABLED)
light_CT_screen_slider_1.set_style_radius(50, lv.PART.KNOB|lv.STATE.DISABLED)

# Create light_CT_screen_label_1
light_CT_screen_label_1 = lv.label(light_CT_screen)
light_CT_screen_label_1.set_text("亮 度 | 50%")
light_CT_screen_label_1.set_long_mode(lv.label.LONG.WRAP)
light_CT_screen_label_1.set_width(lv.pct(100))
light_CT_screen_label_1.set_pos(270, 415)
light_CT_screen_label_1.set_size(174, 32)
# Set style for light_CT_screen_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_dev_shell_img
light_CT_screen_dev_shell_img = lv.img(light_CT_screen)
light_CT_screen_dev_shell_img.set_src("B:MicroPython/_dev_shell_alpha_166x190.bin")
light_CT_screen_dev_shell_img.add_flag(lv.obj.FLAG.CLICKABLE)
light_CT_screen_dev_shell_img.set_pivot(50,50)
light_CT_screen_dev_shell_img.set_angle(0)
light_CT_screen_dev_shell_img.set_pos(272, 84)
light_CT_screen_dev_shell_img.set_size(166, 190)
# Set style for light_CT_screen_dev_shell_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_dev_shell_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_dev_shell_img.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_dev_shell_img.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_white_lid
light_CT_screen_white_lid = lv.img(light_CT_screen)
light_CT_screen_white_lid.set_src("B:MicroPython/_white_lid_alpha_286x54.bin")
light_CT_screen_white_lid.add_flag(lv.obj.FLAG.CLICKABLE)
light_CT_screen_white_lid.set_pivot(50,50)
light_CT_screen_white_lid.set_angle(0)
light_CT_screen_white_lid.set_pos(212, 235)
light_CT_screen_white_lid.set_size(286, 54)
# Set style for light_CT_screen_white_lid, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_white_lid.set_style_img_recolor_opa(184, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_white_lid.set_style_img_recolor(lv.color_hex(0x020202), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_white_lid.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_white_lid.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_white_lid.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_dev_orange_img
light_CT_screen_dev_orange_img = lv.img(light_CT_screen)
light_CT_screen_dev_orange_img.set_src("B:MicroPython/_dev_orange_alpha_490x164.bin")
light_CT_screen_dev_orange_img.add_flag(lv.obj.FLAG.CLICKABLE)
light_CT_screen_dev_orange_img.set_pivot(50,50)
light_CT_screen_dev_orange_img.set_angle(0)
light_CT_screen_dev_orange_img.set_pos(110, 246)
light_CT_screen_dev_orange_img.set_size(490, 164)
# Set style for light_CT_screen_dev_orange_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_dev_orange_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_dev_orange_img.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_dev_orange_img.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_dev_white_img
light_CT_screen_dev_white_img = lv.img(light_CT_screen)
light_CT_screen_dev_white_img.set_src("B:MicroPython/_dev_white_alpha_490x164.bin")
light_CT_screen_dev_white_img.add_flag(lv.obj.FLAG.CLICKABLE)
light_CT_screen_dev_white_img.set_pivot(50,50)
light_CT_screen_dev_white_img.set_angle(0)
light_CT_screen_dev_white_img.set_pos(110, 246)
light_CT_screen_dev_white_img.set_size(490, 164)
# Set style for light_CT_screen_dev_white_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_dev_white_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_dev_white_img.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_dev_white_img.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_btn_1
light_CT_screen_btn_1 = lv.btn(light_CT_screen)
light_CT_screen_btn_1_label = lv.label(light_CT_screen_btn_1)
light_CT_screen_btn_1_label.set_text("色温灯")
light_CT_screen_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
light_CT_screen_btn_1_label.set_width(lv.pct(100))
light_CT_screen_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
light_CT_screen_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
light_CT_screen_btn_1.set_pos(70, 25)
light_CT_screen_btn_1.set_size(128, 32)
# Set style for light_CT_screen_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_imgbtn_1
light_CT_screen_imgbtn_1 = lv.imgbtn(light_CT_screen)
light_CT_screen_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
light_CT_screen_imgbtn_1.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_scene_btn_alpha_70x70.bin", None)
light_CT_screen_imgbtn_1.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_btn_close_alpha_70x70.bin", None)
light_CT_screen_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
light_CT_screen_imgbtn_1_label = lv.label(light_CT_screen_imgbtn_1)
light_CT_screen_imgbtn_1_label.set_text("")
light_CT_screen_imgbtn_1_label.set_long_mode(lv.label.LONG.WRAP)
light_CT_screen_imgbtn_1_label.set_width(lv.pct(100))
light_CT_screen_imgbtn_1_label.align(lv.ALIGN.CENTER, 0, 0)
light_CT_screen_imgbtn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
light_CT_screen_imgbtn_1.set_pos(622, 120)
light_CT_screen_imgbtn_1.set_size(70, 70)
# Set style for light_CT_screen_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_imgbtn_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_imgbtn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_imgbtn_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_imgbtn_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for light_CT_screen_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
light_CT_screen_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
light_CT_screen_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
light_CT_screen_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
light_CT_screen_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
light_CT_screen_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for light_CT_screen_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
light_CT_screen_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
light_CT_screen_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
light_CT_screen_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
light_CT_screen_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
light_CT_screen_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for light_CT_screen_imgbtn_1, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
light_CT_screen_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create light_CT_screen_on_off_2_img
light_CT_screen_on_off_2_img = lv.imgbtn(light_CT_screen)
light_CT_screen_on_off_2_img.add_flag(lv.obj.FLAG.CHECKABLE)
light_CT_screen_on_off_2_img.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_onoff_off_alpha_48x48.bin", None)
light_CT_screen_on_off_2_img.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_onoff_on_alpha_48x48.bin", None)
light_CT_screen_on_off_2_img.add_flag(lv.obj.FLAG.CHECKABLE)
light_CT_screen_on_off_2_img_label = lv.label(light_CT_screen_on_off_2_img)
light_CT_screen_on_off_2_img_label.set_text("")
light_CT_screen_on_off_2_img_label.set_long_mode(lv.label.LONG.WRAP)
light_CT_screen_on_off_2_img_label.set_width(lv.pct(100))
light_CT_screen_on_off_2_img_label.align(lv.ALIGN.CENTER, 0, 0)
light_CT_screen_on_off_2_img.set_style_pad_all(0, lv.STATE.DEFAULT)
light_CT_screen_on_off_2_img.set_pos(38, 120)
light_CT_screen_on_off_2_img.set_size(48, 48)
# Set style for light_CT_screen_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_on_off_2_img.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_on_off_2_img.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_on_off_2_img.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_on_off_2_img.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for light_CT_screen_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
light_CT_screen_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
light_CT_screen_on_off_2_img.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
light_CT_screen_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
light_CT_screen_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
light_CT_screen_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for light_CT_screen_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
light_CT_screen_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
light_CT_screen_on_off_2_img.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
light_CT_screen_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
light_CT_screen_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
light_CT_screen_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for light_CT_screen_on_off_2_img, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
light_CT_screen_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create light_CT_screen_img_1
light_CT_screen_img_1 = lv.img(light_CT_screen)
light_CT_screen_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
light_CT_screen_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
light_CT_screen_img_1.set_pivot(50,50)
light_CT_screen_img_1.set_angle(0)
light_CT_screen_img_1.set_pos(43, 28)
light_CT_screen_img_1.set_size(14, 24)
# Set style for light_CT_screen_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_btn_2
light_CT_screen_btn_2 = lv.btn(light_CT_screen)
light_CT_screen_btn_2_label = lv.label(light_CT_screen_btn_2)
light_CT_screen_btn_2_label.set_text("")
light_CT_screen_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
light_CT_screen_btn_2_label.set_width(lv.pct(100))
light_CT_screen_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
light_CT_screen_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
light_CT_screen_btn_2.set_pos(-8, -4)
light_CT_screen_btn_2.set_size(258, 95)
# Set style for light_CT_screen_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_cont_2
light_CT_screen_cont_2 = lv.obj(light_CT_screen)
light_CT_screen_cont_2.set_pos(98, -437)
light_CT_screen_cont_2.set_size(524, 392)
light_CT_screen_cont_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for light_CT_screen_cont_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_cont_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_2.set_style_bg_color(lv.color_hex(0x171717), lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_cont_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create light_CT_screen_LSscene1
light_CT_screen_LSscene1 = lv.img(light_CT_screen_cont_2)
light_CT_screen_LSscene1.set_src("B:MicroPython/_LSscene1_alpha_112x140.bin")
light_CT_screen_LSscene1.add_flag(lv.obj.FLAG.CLICKABLE)
light_CT_screen_LSscene1.set_pivot(50,50)
light_CT_screen_LSscene1.set_angle(0)
light_CT_screen_LSscene1.set_pos(40, 29)
light_CT_screen_LSscene1.set_size(112, 140)
# Set style for light_CT_screen_LSscene1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_LSscene1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_LSscene1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_LSscene1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_img_3
light_CT_screen_img_3 = lv.img(light_CT_screen_cont_2)
light_CT_screen_img_3.set_src("B:MicroPython/_LSscene2_alpha_112x140.bin")
light_CT_screen_img_3.add_flag(lv.obj.FLAG.CLICKABLE)
light_CT_screen_img_3.set_pivot(50,50)
light_CT_screen_img_3.set_angle(0)
light_CT_screen_img_3.set_pos(210, 29)
light_CT_screen_img_3.set_size(112, 140)
# Set style for light_CT_screen_img_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_img_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_img_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_img_3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_img_4
light_CT_screen_img_4 = lv.img(light_CT_screen_cont_2)
light_CT_screen_img_4.set_src("B:MicroPython/_LSscene3_alpha_112x140.bin")
light_CT_screen_img_4.add_flag(lv.obj.FLAG.CLICKABLE)
light_CT_screen_img_4.set_pivot(50,50)
light_CT_screen_img_4.set_angle(0)
light_CT_screen_img_4.set_pos(380, 29)
light_CT_screen_img_4.set_size(112, 140)
# Set style for light_CT_screen_img_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_img_4.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_img_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_img_4.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_img_5
light_CT_screen_img_5 = lv.img(light_CT_screen_cont_2)
light_CT_screen_img_5.set_src("B:MicroPython/_LSscene4_alpha_112x140.bin")
light_CT_screen_img_5.add_flag(lv.obj.FLAG.CLICKABLE)
light_CT_screen_img_5.set_pivot(50,50)
light_CT_screen_img_5.set_angle(0)
light_CT_screen_img_5.set_pos(40, 204)
light_CT_screen_img_5.set_size(112, 140)
# Set style for light_CT_screen_img_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_img_5.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_img_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_img_5.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_img_6
light_CT_screen_img_6 = lv.img(light_CT_screen_cont_2)
light_CT_screen_img_6.set_src("B:MicroPython/_LSscene5_alpha_112x140.bin")
light_CT_screen_img_6.add_flag(lv.obj.FLAG.CLICKABLE)
light_CT_screen_img_6.set_pivot(50,50)
light_CT_screen_img_6.set_angle(0)
light_CT_screen_img_6.set_pos(210, 204)
light_CT_screen_img_6.set_size(112, 140)
# Set style for light_CT_screen_img_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_img_6.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_img_6.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_img_6.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create light_CT_screen_img_7
light_CT_screen_img_7 = lv.img(light_CT_screen_cont_2)
light_CT_screen_img_7.set_src("B:MicroPython/_LSscene6_alpha_112x140.bin")
light_CT_screen_img_7.add_flag(lv.obj.FLAG.CLICKABLE)
light_CT_screen_img_7.set_pivot(50,50)
light_CT_screen_img_7.set_angle(0)
light_CT_screen_img_7.set_pos(380, 204)
light_CT_screen_img_7.set_size(112, 140)
# Set style for light_CT_screen_img_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
light_CT_screen_img_7.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_img_7.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
light_CT_screen_img_7.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

light_CT_screen.update_layout()
# Create LedStrip
LedStrip = lv.obj()
LedStrip.set_size(720, 720)
LedStrip.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for LedStrip, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_tabview_1
LedStrip_tabview_1 = lv.tabview(LedStrip, lv.DIR.TOP, 85)
LedStrip_tabview_1.set_pos(0, 0)
LedStrip_tabview_1.set_size(720, 720)
LedStrip_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for LedStrip_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for LedStrip_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_LedStrip_tabview_1_extra_btnm_main_default = lv.style_t()
style_LedStrip_tabview_1_extra_btnm_main_default.init()
style_LedStrip_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_LedStrip_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_LedStrip_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_LedStrip_tabview_1_extra_btnm_main_default.set_border_width(0)
style_LedStrip_tabview_1_extra_btnm_main_default.set_radius(0)
LedStrip_tabview_1.get_tab_btns().add_style(style_LedStrip_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for LedStrip_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_LedStrip_tabview_1_extra_btnm_items_default = lv.style_t()
style_LedStrip_tabview_1_extra_btnm_items_default.init()
style_LedStrip_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_LedStrip_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_LedStrip_tabview_1_extra_btnm_items_default.set_text_opa(255)
LedStrip_tabview_1.get_tab_btns().add_style(style_LedStrip_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for LedStrip_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_LedStrip_tabview_1_extra_btnm_items_checked = lv.style_t()
style_LedStrip_tabview_1_extra_btnm_items_checked.init()
style_LedStrip_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_LedStrip_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_LedStrip_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_LedStrip_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_LedStrip_tabview_1_extra_btnm_items_checked.set_radius(0)
style_LedStrip_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_LedStrip_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x243241))
style_LedStrip_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
LedStrip_tabview_1.get_tab_btns().add_style(style_LedStrip_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
LedStrip_tabview_1_tab_1 = LedStrip_tabview_1.add_tab("")
LedStrip_tabview_1_tab_1_label = lv.label(LedStrip_tabview_1_tab_1)
LedStrip_tabview_1_tab_1_label.set_text("")

# Create LedStrip_btn_2
LedStrip_btn_2 = lv.btn(LedStrip_tabview_1_tab_1)
LedStrip_btn_2_label = lv.label(LedStrip_btn_2)
LedStrip_btn_2_label.set_text("")
LedStrip_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
LedStrip_btn_2_label.set_width(lv.pct(100))
LedStrip_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
LedStrip_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
LedStrip_btn_2.set_pos(4, 4)
LedStrip_btn_2.set_size(229, 82)
# Set style for LedStrip_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_btn_3
LedStrip_btn_3 = lv.btn(LedStrip_tabview_1_tab_1)
LedStrip_btn_3_label = lv.label(LedStrip_btn_3)
LedStrip_btn_3_label.set_text("")
LedStrip_btn_3_label.set_long_mode(lv.label.LONG.WRAP)
LedStrip_btn_3_label.set_width(lv.pct(100))
LedStrip_btn_3_label.align(lv.ALIGN.CENTER, 0, 0)
LedStrip_btn_3.set_style_pad_all(0, lv.STATE.DEFAULT)
LedStrip_btn_3.set_pos(4, 4)
LedStrip_btn_3.set_size(229, 82)
# Set style for LedStrip_btn_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_btn_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_cont_1
LedStrip_cont_1 = lv.obj(LedStrip)
LedStrip_cont_1.set_pos(0, 87)
LedStrip_cont_1.set_size(720, 630)
LedStrip_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for LedStrip_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_1.set_style_bg_opa(107, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_label_2
LedStrip_label_2 = lv.label(LedStrip)
LedStrip_label_2.set_text("色 温 | 4850K")
LedStrip_label_2.set_long_mode(lv.label.LONG.WRAP)
LedStrip_label_2.set_width(lv.pct(100))
LedStrip_label_2.set_pos(270, 560)
LedStrip_label_2.set_size(195, 34)
# Set style for LedStrip_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_2.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_ct_bar
LedStrip_ct_bar = lv.img(LedStrip)
LedStrip_ct_bar.set_src("B:MicroPython/_ct_bar_alpha_650x75.bin")
LedStrip_ct_bar.add_flag(lv.obj.FLAG.CLICKABLE)
LedStrip_ct_bar.set_pivot(50,50)
LedStrip_ct_bar.set_angle(0)
LedStrip_ct_bar.set_pos(-210, 610)
LedStrip_ct_bar.set_size(650, 75)
# Set style for LedStrip_ct_bar, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_ct_bar.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_ct_bar.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_ct_bar.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_slider_2
LedStrip_slider_2 = lv.slider(LedStrip)
LedStrip_slider_2.set_range(2700, 6500)
LedStrip_slider_2.set_mode(lv.slider.MODE.SYMMETRICAL)
LedStrip_slider_2.set_value(4600, lv.ANIM.OFF)
LedStrip_slider_2.set_pos(-210, 610)
LedStrip_slider_2.set_size(650, 75)
# Set style for LedStrip_slider_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_slider_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_slider_2.set_style_radius(60, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_slider_2.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_slider_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for LedStrip_slider_2, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
LedStrip_slider_2.set_style_bg_opa(0, lv.PART.INDICATOR|lv.STATE.DEFAULT)
LedStrip_slider_2.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for LedStrip_slider_2, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
LedStrip_slider_2.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
LedStrip_slider_2.set_style_bg_color(lv.color_hex(0x300208), lv.PART.KNOB|lv.STATE.DEFAULT)
LedStrip_slider_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
LedStrip_slider_2.set_style_radius(60, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create LedStrip_slider_1
LedStrip_slider_1 = lv.slider(LedStrip)
LedStrip_slider_1.set_range(0, 100)
LedStrip_slider_1.set_mode(lv.slider.MODE.SYMMETRICAL)
LedStrip_slider_1.set_value(50, lv.ANIM.OFF)
LedStrip_slider_1.set_pos(-215, 465)
LedStrip_slider_1.set_size(650, 75)
# Set style for LedStrip_slider_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_slider_1.set_style_bg_opa(60, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_slider_1.set_style_bg_color(lv.color_hex(0xdedfdf), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_slider_1.set_style_radius(60, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_slider_1.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_slider_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for LedStrip_slider_1, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
LedStrip_slider_1.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
LedStrip_slider_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.INDICATOR|lv.STATE.DEFAULT)
LedStrip_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.DEFAULT)
LedStrip_slider_1.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for LedStrip_slider_1, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
LedStrip_slider_1.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DEFAULT)
LedStrip_slider_1.set_style_radius(60, lv.PART.KNOB|lv.STATE.DEFAULT)

# Set style for LedStrip_slider_1, Part: lv.PART.KNOB, State: lv.STATE.DISABLED.
LedStrip_slider_1.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DISABLED)
LedStrip_slider_1.set_style_radius(50, lv.PART.KNOB|lv.STATE.DISABLED)

# Create LedStrip_label_1
LedStrip_label_1 = lv.label(LedStrip)
LedStrip_label_1.set_text("亮 度 | 50%")
LedStrip_label_1.set_long_mode(lv.label.LONG.WRAP)
LedStrip_label_1.set_width(lv.pct(100))
LedStrip_label_1.set_pos(270, 415)
LedStrip_label_1.set_size(166, 39)
# Set style for LedStrip_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_btn_1
LedStrip_btn_1 = lv.btn(LedStrip)
LedStrip_btn_1_label = lv.label(LedStrip_btn_1)
LedStrip_btn_1_label.set_text("灯  带")
LedStrip_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
LedStrip_btn_1_label.set_width(lv.pct(100))
LedStrip_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
LedStrip_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
LedStrip_btn_1.set_pos(70, 25)
LedStrip_btn_1.set_size(110, 32)
# Set style for LedStrip_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_imgbtn_1
LedStrip_imgbtn_1 = lv.imgbtn(LedStrip)
LedStrip_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
LedStrip_imgbtn_1.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_scene_btn_alpha_70x70.bin", None)
LedStrip_imgbtn_1.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_btn_close_alpha_70x70.bin", None)
LedStrip_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
LedStrip_imgbtn_1_label = lv.label(LedStrip_imgbtn_1)
LedStrip_imgbtn_1_label.set_text("")
LedStrip_imgbtn_1_label.set_long_mode(lv.label.LONG.WRAP)
LedStrip_imgbtn_1_label.set_width(lv.pct(100))
LedStrip_imgbtn_1_label.align(lv.ALIGN.CENTER, 0, 0)
LedStrip_imgbtn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
LedStrip_imgbtn_1.set_pos(620, 120)
LedStrip_imgbtn_1.set_size(70, 70)
# Set style for LedStrip_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_imgbtn_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_imgbtn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_imgbtn_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_imgbtn_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for LedStrip_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
LedStrip_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
LedStrip_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
LedStrip_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
LedStrip_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
LedStrip_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for LedStrip_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
LedStrip_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
LedStrip_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
LedStrip_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
LedStrip_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
LedStrip_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for LedStrip_imgbtn_1, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
LedStrip_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create LedStrip_on_off_2_img
LedStrip_on_off_2_img = lv.imgbtn(LedStrip)
LedStrip_on_off_2_img.add_flag(lv.obj.FLAG.CHECKABLE)
LedStrip_on_off_2_img.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_onoff_off_alpha_48x48.bin", None)
LedStrip_on_off_2_img.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_onoff_on_alpha_48x48.bin", None)
LedStrip_on_off_2_img.add_flag(lv.obj.FLAG.CHECKABLE)
LedStrip_on_off_2_img_label = lv.label(LedStrip_on_off_2_img)
LedStrip_on_off_2_img_label.set_text("")
LedStrip_on_off_2_img_label.set_long_mode(lv.label.LONG.WRAP)
LedStrip_on_off_2_img_label.set_width(lv.pct(100))
LedStrip_on_off_2_img_label.align(lv.ALIGN.CENTER, 0, 0)
LedStrip_on_off_2_img.set_style_pad_all(0, lv.STATE.DEFAULT)
LedStrip_on_off_2_img.set_pos(40, 120)
LedStrip_on_off_2_img.set_size(48, 48)
# Set style for LedStrip_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_on_off_2_img.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_on_off_2_img.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_on_off_2_img.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_on_off_2_img.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for LedStrip_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
LedStrip_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
LedStrip_on_off_2_img.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
LedStrip_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
LedStrip_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
LedStrip_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for LedStrip_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
LedStrip_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
LedStrip_on_off_2_img.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
LedStrip_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
LedStrip_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
LedStrip_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for LedStrip_on_off_2_img, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
LedStrip_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create LedStrip_LSOn
LedStrip_LSOn = lv.img(LedStrip)
LedStrip_LSOn.set_src("B:MicroPython/_LedStripOn_alpha_300x196.bin")
LedStrip_LSOn.add_flag(lv.obj.FLAG.CLICKABLE)
LedStrip_LSOn.set_pivot(50,50)
LedStrip_LSOn.set_angle(0)
LedStrip_LSOn.set_pos(208, 149)
LedStrip_LSOn.set_size(300, 196)
# Set style for LedStrip_LSOn, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_LSOn.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_LSOn.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_LSOn.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_LSOff
LedStrip_LSOff = lv.img(LedStrip)
LedStrip_LSOff.set_src("B:MicroPython/_LedStripOff_alpha_300x196.bin")
LedStrip_LSOff.add_flag(lv.obj.FLAG.CLICKABLE)
LedStrip_LSOff.set_pivot(50,50)
LedStrip_LSOff.set_angle(0)
LedStrip_LSOff.set_pos(208, 149)
LedStrip_LSOff.set_size(300, 196)
# Set style for LedStrip_LSOff, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_LSOff.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_LSOff.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_LSOff.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_img_1
LedStrip_img_1 = lv.img(LedStrip)
LedStrip_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
LedStrip_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
LedStrip_img_1.set_pivot(50,50)
LedStrip_img_1.set_angle(0)
LedStrip_img_1.set_pos(43, 28)
LedStrip_img_1.set_size(14, 24)
# Set style for LedStrip_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_btn_4
LedStrip_btn_4 = lv.btn(LedStrip)
LedStrip_btn_4_label = lv.label(LedStrip_btn_4)
LedStrip_btn_4_label.set_text("")
LedStrip_btn_4_label.set_long_mode(lv.label.LONG.WRAP)
LedStrip_btn_4_label.set_width(lv.pct(100))
LedStrip_btn_4_label.align(lv.ALIGN.CENTER, 0, 0)
LedStrip_btn_4.set_style_pad_all(0, lv.STATE.DEFAULT)
LedStrip_btn_4.set_pos(-7, -5)
LedStrip_btn_4.set_size(249, 96)
# Set style for LedStrip_btn_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_btn_4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_4.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_btn_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_cont_2
LedStrip_cont_2 = lv.obj(LedStrip)
LedStrip_cont_2.set_pos(98, -509)
LedStrip_cont_2.set_size(524, 392)
LedStrip_cont_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for LedStrip_cont_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_cont_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_2.set_style_bg_color(lv.color_hex(0x171717), lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_cont_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create LedStrip_img_7
LedStrip_img_7 = lv.img(LedStrip_cont_2)
LedStrip_img_7.set_src("B:MicroPython/_LSscene1_alpha_112x140.bin")
LedStrip_img_7.add_flag(lv.obj.FLAG.CLICKABLE)
LedStrip_img_7.set_pivot(50,50)
LedStrip_img_7.set_angle(0)
LedStrip_img_7.set_pos(40, 29)
LedStrip_img_7.set_size(112, 140)
# Set style for LedStrip_img_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_img_7.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_img_7.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_img_7.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_img_6
LedStrip_img_6 = lv.img(LedStrip_cont_2)
LedStrip_img_6.set_src("B:MicroPython/_LSscene2_alpha_112x140.bin")
LedStrip_img_6.add_flag(lv.obj.FLAG.CLICKABLE)
LedStrip_img_6.set_pivot(50,50)
LedStrip_img_6.set_angle(0)
LedStrip_img_6.set_pos(210, 29)
LedStrip_img_6.set_size(112, 140)
# Set style for LedStrip_img_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_img_6.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_img_6.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_img_6.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_img_5
LedStrip_img_5 = lv.img(LedStrip_cont_2)
LedStrip_img_5.set_src("B:MicroPython/_LSscene3_alpha_112x140.bin")
LedStrip_img_5.add_flag(lv.obj.FLAG.CLICKABLE)
LedStrip_img_5.set_pivot(50,50)
LedStrip_img_5.set_angle(0)
LedStrip_img_5.set_pos(380, 29)
LedStrip_img_5.set_size(112, 140)
# Set style for LedStrip_img_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_img_5.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_img_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_img_5.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_img_4
LedStrip_img_4 = lv.img(LedStrip_cont_2)
LedStrip_img_4.set_src("B:MicroPython/_LSscene4_alpha_112x140.bin")
LedStrip_img_4.add_flag(lv.obj.FLAG.CLICKABLE)
LedStrip_img_4.set_pivot(50,50)
LedStrip_img_4.set_angle(0)
LedStrip_img_4.set_pos(40, 204)
LedStrip_img_4.set_size(112, 140)
# Set style for LedStrip_img_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_img_4.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_img_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_img_4.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_img_3
LedStrip_img_3 = lv.img(LedStrip_cont_2)
LedStrip_img_3.set_src("B:MicroPython/_LSscene5_alpha_112x140.bin")
LedStrip_img_3.add_flag(lv.obj.FLAG.CLICKABLE)
LedStrip_img_3.set_pivot(50,50)
LedStrip_img_3.set_angle(0)
LedStrip_img_3.set_pos(210, 204)
LedStrip_img_3.set_size(112, 140)
# Set style for LedStrip_img_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_img_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_img_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_img_3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create LedStrip_img_2
LedStrip_img_2 = lv.img(LedStrip_cont_2)
LedStrip_img_2.set_src("B:MicroPython/_LSscene6_alpha_112x140.bin")
LedStrip_img_2.add_flag(lv.obj.FLAG.CLICKABLE)
LedStrip_img_2.set_pivot(50,50)
LedStrip_img_2.set_angle(0)
LedStrip_img_2.set_pos(380, 204)
LedStrip_img_2.set_size(112, 140)
# Set style for LedStrip_img_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
LedStrip_img_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_img_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
LedStrip_img_2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

LedStrip.update_layout()
# Create RGBLight
RGBLight = lv.obj()
RGBLight.set_size(720, 720)
RGBLight.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for RGBLight, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_tabview_1
RGBLight_tabview_1 = lv.tabview(RGBLight, lv.DIR.TOP, 85)
RGBLight_tabview_1.set_pos(0, 0)
RGBLight_tabview_1.set_size(720, 720)
RGBLight_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for RGBLight_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for RGBLight_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_RGBLight_tabview_1_extra_btnm_main_default = lv.style_t()
style_RGBLight_tabview_1_extra_btnm_main_default.init()
style_RGBLight_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_RGBLight_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_RGBLight_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_RGBLight_tabview_1_extra_btnm_main_default.set_border_width(0)
style_RGBLight_tabview_1_extra_btnm_main_default.set_radius(0)
RGBLight_tabview_1.get_tab_btns().add_style(style_RGBLight_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for RGBLight_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_RGBLight_tabview_1_extra_btnm_items_default = lv.style_t()
style_RGBLight_tabview_1_extra_btnm_items_default.init()
style_RGBLight_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_RGBLight_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_RGBLight_tabview_1_extra_btnm_items_default.set_text_opa(255)
RGBLight_tabview_1.get_tab_btns().add_style(style_RGBLight_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for RGBLight_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_RGBLight_tabview_1_extra_btnm_items_checked = lv.style_t()
style_RGBLight_tabview_1_extra_btnm_items_checked.init()
style_RGBLight_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_RGBLight_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_RGBLight_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_RGBLight_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_RGBLight_tabview_1_extra_btnm_items_checked.set_radius(0)
style_RGBLight_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_RGBLight_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x243241))
style_RGBLight_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
RGBLight_tabview_1.get_tab_btns().add_style(style_RGBLight_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
RGBLight_tabview_1_tab_1 = RGBLight_tabview_1.add_tab("")
RGBLight_tabview_1_tab_1_label = lv.label(RGBLight_tabview_1_tab_1)
RGBLight_tabview_1_tab_1_label.set_text("")

# Create RGBLight_cont_1
RGBLight_cont_1 = lv.obj(RGBLight)
RGBLight_cont_1.set_pos(0, 85)
RGBLight_cont_1.set_size(720, 630)
RGBLight_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for RGBLight_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_1.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_label_2
RGBLight_label_2 = lv.label(RGBLight)
RGBLight_label_2.set_text("颜 色 | #00718D")
RGBLight_label_2.set_long_mode(lv.label.LONG.WRAP)
RGBLight_label_2.set_width(lv.pct(100))
RGBLight_label_2.set_pos(270, 560)
RGBLight_label_2.set_size(257, 34)
# Set style for RGBLight_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_2.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_ct_bar
RGBLight_ct_bar = lv.img(RGBLight)
RGBLight_ct_bar.set_src("B:MicroPython/_rgb_bar_alpha_650x75.bin")
RGBLight_ct_bar.add_flag(lv.obj.FLAG.CLICKABLE)
RGBLight_ct_bar.set_pivot(50,50)
RGBLight_ct_bar.set_angle(0)
RGBLight_ct_bar.set_pos(-221, 610)
RGBLight_ct_bar.set_size(650, 75)
# Set style for RGBLight_ct_bar, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_ct_bar.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_ct_bar.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_ct_bar.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_slider_2
RGBLight_slider_2 = lv.slider(RGBLight)
RGBLight_slider_2.set_range(2700, 6500)
RGBLight_slider_2.set_mode(lv.slider.MODE.SYMMETRICAL)
RGBLight_slider_2.set_value(4600, lv.ANIM.OFF)
RGBLight_slider_2.set_pos(-220, 610)
RGBLight_slider_2.set_size(650, 75)
# Set style for RGBLight_slider_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_slider_2.set_style_bg_opa(40, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_slider_2.set_style_bg_color(lv.color_hex(0x495661), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_slider_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_slider_2.set_style_radius(60, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_slider_2.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_slider_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for RGBLight_slider_2, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
RGBLight_slider_2.set_style_bg_opa(0, lv.PART.INDICATOR|lv.STATE.DEFAULT)
RGBLight_slider_2.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for RGBLight_slider_2, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
RGBLight_slider_2.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
RGBLight_slider_2.set_style_bg_color(lv.color_hex(0x300208), lv.PART.KNOB|lv.STATE.DEFAULT)
RGBLight_slider_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
RGBLight_slider_2.set_style_radius(60, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create RGBLight_slider_1
RGBLight_slider_1 = lv.slider(RGBLight)
RGBLight_slider_1.set_range(0, 100)
RGBLight_slider_1.set_mode(lv.slider.MODE.SYMMETRICAL)
RGBLight_slider_1.set_value(50, lv.ANIM.OFF)
RGBLight_slider_1.set_pos(-215, 465)
RGBLight_slider_1.set_size(650, 75)
# Set style for RGBLight_slider_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_slider_1.set_style_bg_opa(60, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_slider_1.set_style_bg_color(lv.color_hex(0xdedfdf), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_slider_1.set_style_radius(60, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_slider_1.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_slider_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for RGBLight_slider_1, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
RGBLight_slider_1.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
RGBLight_slider_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.INDICATOR|lv.STATE.DEFAULT)
RGBLight_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.DEFAULT)
RGBLight_slider_1.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for RGBLight_slider_1, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
RGBLight_slider_1.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DEFAULT)
RGBLight_slider_1.set_style_radius(60, lv.PART.KNOB|lv.STATE.DEFAULT)

# Set style for RGBLight_slider_1, Part: lv.PART.KNOB, State: lv.STATE.DISABLED.
RGBLight_slider_1.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DISABLED)
RGBLight_slider_1.set_style_radius(50, lv.PART.KNOB|lv.STATE.DISABLED)

# Create RGBLight_label_1
RGBLight_label_1 = lv.label(RGBLight)
RGBLight_label_1.set_text("亮 度 | 50%")
RGBLight_label_1.set_long_mode(lv.label.LONG.WRAP)
RGBLight_label_1.set_width(lv.pct(100))
RGBLight_label_1.set_pos(271, 415)
RGBLight_label_1.set_size(227, 39)
# Set style for RGBLight_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_btn_1
RGBLight_btn_1 = lv.btn(RGBLight)
RGBLight_btn_1_label = lv.label(RGBLight_btn_1)
RGBLight_btn_1_label.set_text("彩色灯")
RGBLight_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
RGBLight_btn_1_label.set_width(lv.pct(100))
RGBLight_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
RGBLight_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
RGBLight_btn_1.set_pos(70, 25)
RGBLight_btn_1.set_size(122, 32)
# Set style for RGBLight_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_imgbtn_1
RGBLight_imgbtn_1 = lv.imgbtn(RGBLight)
RGBLight_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
RGBLight_imgbtn_1.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_scene_btn_alpha_70x70.bin", None)
RGBLight_imgbtn_1.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_btn_close_alpha_70x70.bin", None)
RGBLight_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
RGBLight_imgbtn_1_label = lv.label(RGBLight_imgbtn_1)
RGBLight_imgbtn_1_label.set_text("")
RGBLight_imgbtn_1_label.set_long_mode(lv.label.LONG.WRAP)
RGBLight_imgbtn_1_label.set_width(lv.pct(100))
RGBLight_imgbtn_1_label.align(lv.ALIGN.CENTER, 0, 0)
RGBLight_imgbtn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
RGBLight_imgbtn_1.set_pos(620, 120)
RGBLight_imgbtn_1.set_size(70, 70)
# Set style for RGBLight_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_imgbtn_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_imgbtn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_imgbtn_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_imgbtn_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for RGBLight_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
RGBLight_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
RGBLight_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
RGBLight_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
RGBLight_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
RGBLight_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for RGBLight_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
RGBLight_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
RGBLight_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
RGBLight_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
RGBLight_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
RGBLight_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for RGBLight_imgbtn_1, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
RGBLight_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create RGBLight_on_off_2_img
RGBLight_on_off_2_img = lv.imgbtn(RGBLight)
RGBLight_on_off_2_img.add_flag(lv.obj.FLAG.CHECKABLE)
RGBLight_on_off_2_img.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_onoff_off_alpha_48x48.bin", None)
RGBLight_on_off_2_img.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_onoff_on_alpha_48x48.bin", None)
RGBLight_on_off_2_img.add_flag(lv.obj.FLAG.CHECKABLE)
RGBLight_on_off_2_img_label = lv.label(RGBLight_on_off_2_img)
RGBLight_on_off_2_img_label.set_text("")
RGBLight_on_off_2_img_label.set_long_mode(lv.label.LONG.WRAP)
RGBLight_on_off_2_img_label.set_width(lv.pct(100))
RGBLight_on_off_2_img_label.align(lv.ALIGN.CENTER, 0, 0)
RGBLight_on_off_2_img.set_style_pad_all(0, lv.STATE.DEFAULT)
RGBLight_on_off_2_img.set_pos(40, 120)
RGBLight_on_off_2_img.set_size(48, 48)
# Set style for RGBLight_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_on_off_2_img.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_on_off_2_img.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_on_off_2_img.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_on_off_2_img.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for RGBLight_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
RGBLight_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
RGBLight_on_off_2_img.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
RGBLight_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
RGBLight_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
RGBLight_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for RGBLight_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
RGBLight_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
RGBLight_on_off_2_img.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
RGBLight_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
RGBLight_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
RGBLight_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for RGBLight_on_off_2_img, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
RGBLight_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create RGBLight_RGBCover
RGBLight_RGBCover = lv.img(RGBLight)
RGBLight_RGBCover.set_src("B:MicroPython/_RGBCover_alpha_196x190.bin")
RGBLight_RGBCover.add_flag(lv.obj.FLAG.CLICKABLE)
RGBLight_RGBCover.set_pivot(50,50)
RGBLight_RGBCover.set_angle(0)
RGBLight_RGBCover.set_pos(233, 85)
RGBLight_RGBCover.set_size(196, 190)
# Set style for RGBLight_RGBCover, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_RGBCover.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_RGBCover.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_RGBCover.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_Blue
RGBLight_Blue = lv.img(RGBLight)
RGBLight_Blue.set_src("B:MicroPython/_RGBblue_alpha_537x170.bin")
RGBLight_Blue.add_flag(lv.obj.FLAG.CLICKABLE)
RGBLight_Blue.set_pivot(50,50)
RGBLight_Blue.set_angle(0)
RGBLight_Blue.set_pos(64, 249)
RGBLight_Blue.set_size(537, 170)
# Set style for RGBLight_Blue, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_Blue.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_Blue.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_Blue.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_Red
RGBLight_Red = lv.img(RGBLight)
RGBLight_Red.set_src("B:MicroPython/_RGBRed_alpha_537x170.bin")
RGBLight_Red.add_flag(lv.obj.FLAG.CLICKABLE)
RGBLight_Red.set_pivot(50,50)
RGBLight_Red.set_angle(0)
RGBLight_Red.set_pos(64, 249)
RGBLight_Red.set_size(537, 170)
# Set style for RGBLight_Red, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_Red.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_Red.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_Red.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_Green
RGBLight_Green = lv.img(RGBLight)
RGBLight_Green.set_src("B:MicroPython/_RGBGreen_alpha_537x170.bin")
RGBLight_Green.add_flag(lv.obj.FLAG.CLICKABLE)
RGBLight_Green.set_pivot(50,50)
RGBLight_Green.set_angle(0)
RGBLight_Green.set_pos(64, 249)
RGBLight_Green.set_size(537, 170)
# Set style for RGBLight_Green, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_Green.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_Green.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_Green.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_img_1
RGBLight_img_1 = lv.img(RGBLight)
RGBLight_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
RGBLight_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
RGBLight_img_1.set_pivot(50,50)
RGBLight_img_1.set_angle(0)
RGBLight_img_1.set_pos(43, 28)
RGBLight_img_1.set_size(14, 24)
# Set style for RGBLight_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_btn_2
RGBLight_btn_2 = lv.btn(RGBLight)
RGBLight_btn_2_label = lv.label(RGBLight_btn_2)
RGBLight_btn_2_label.set_text("")
RGBLight_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
RGBLight_btn_2_label.set_width(lv.pct(100))
RGBLight_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
RGBLight_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
RGBLight_btn_2.set_pos(-6, -7)
RGBLight_btn_2.set_size(238, 99)
# Set style for RGBLight_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_cont_2
RGBLight_cont_2 = lv.obj(RGBLight)
RGBLight_cont_2.set_pos(98, -457)
RGBLight_cont_2.set_size(524, 392)
RGBLight_cont_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for RGBLight_cont_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_cont_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_2.set_style_bg_color(lv.color_hex(0x171717), lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_cont_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create RGBLight_img_7
RGBLight_img_7 = lv.img(RGBLight_cont_2)
RGBLight_img_7.set_src("B:MicroPython/_RGBscene1_alpha_112x140.bin")
RGBLight_img_7.add_flag(lv.obj.FLAG.CLICKABLE)
RGBLight_img_7.set_pivot(50,50)
RGBLight_img_7.set_angle(0)
RGBLight_img_7.set_pos(40, 29)
RGBLight_img_7.set_size(112, 140)
# Set style for RGBLight_img_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_img_7.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_img_7.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_img_7.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_img_6
RGBLight_img_6 = lv.img(RGBLight_cont_2)
RGBLight_img_6.set_src("B:MicroPython/_RGBscene2_alpha_112x140.bin")
RGBLight_img_6.add_flag(lv.obj.FLAG.CLICKABLE)
RGBLight_img_6.set_pivot(50,50)
RGBLight_img_6.set_angle(0)
RGBLight_img_6.set_pos(210, 29)
RGBLight_img_6.set_size(112, 140)
# Set style for RGBLight_img_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_img_6.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_img_6.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_img_6.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_img_5
RGBLight_img_5 = lv.img(RGBLight_cont_2)
RGBLight_img_5.set_src("B:MicroPython/_RGBscene3_alpha_112x140.bin")
RGBLight_img_5.add_flag(lv.obj.FLAG.CLICKABLE)
RGBLight_img_5.set_pivot(50,50)
RGBLight_img_5.set_angle(0)
RGBLight_img_5.set_pos(380, 29)
RGBLight_img_5.set_size(112, 140)
# Set style for RGBLight_img_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_img_5.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_img_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_img_5.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_img_4
RGBLight_img_4 = lv.img(RGBLight_cont_2)
RGBLight_img_4.set_src("B:MicroPython/_RGBscene4_alpha_112x140.bin")
RGBLight_img_4.add_flag(lv.obj.FLAG.CLICKABLE)
RGBLight_img_4.set_pivot(50,50)
RGBLight_img_4.set_angle(0)
RGBLight_img_4.set_pos(40, 204)
RGBLight_img_4.set_size(112, 140)
# Set style for RGBLight_img_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_img_4.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_img_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_img_4.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_img_3
RGBLight_img_3 = lv.img(RGBLight_cont_2)
RGBLight_img_3.set_src("B:MicroPython/_RGBscene5_alpha_112x140.bin")
RGBLight_img_3.add_flag(lv.obj.FLAG.CLICKABLE)
RGBLight_img_3.set_pivot(50,50)
RGBLight_img_3.set_angle(0)
RGBLight_img_3.set_pos(210, 204)
RGBLight_img_3.set_size(112, 140)
# Set style for RGBLight_img_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_img_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_img_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_img_3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RGBLight_img_2
RGBLight_img_2 = lv.img(RGBLight_cont_2)
RGBLight_img_2.set_src("B:MicroPython/_RGBscene6_alpha_112x140.bin")
RGBLight_img_2.add_flag(lv.obj.FLAG.CLICKABLE)
RGBLight_img_2.set_pivot(50,50)
RGBLight_img_2.set_angle(0)
RGBLight_img_2.set_pos(380, 204)
RGBLight_img_2.set_size(112, 140)
# Set style for RGBLight_img_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RGBLight_img_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_img_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RGBLight_img_2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

RGBLight.update_layout()
# Create MagLight
MagLight = lv.obj()
MagLight.set_size(720, 720)
MagLight.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MagLight, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_tabview_1
MagLight_tabview_1 = lv.tabview(MagLight, lv.DIR.TOP, 85)
MagLight_tabview_1.set_pos(0, 0)
MagLight_tabview_1.set_size(720, 720)
MagLight_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for MagLight_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MagLight_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_MagLight_tabview_1_extra_btnm_main_default = lv.style_t()
style_MagLight_tabview_1_extra_btnm_main_default.init()
style_MagLight_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_MagLight_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_MagLight_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_MagLight_tabview_1_extra_btnm_main_default.set_border_width(0)
style_MagLight_tabview_1_extra_btnm_main_default.set_radius(0)
MagLight_tabview_1.get_tab_btns().add_style(style_MagLight_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MagLight_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_MagLight_tabview_1_extra_btnm_items_default = lv.style_t()
style_MagLight_tabview_1_extra_btnm_items_default.init()
style_MagLight_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_MagLight_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_MagLight_tabview_1_extra_btnm_items_default.set_text_opa(255)
MagLight_tabview_1.get_tab_btns().add_style(style_MagLight_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for MagLight_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_MagLight_tabview_1_extra_btnm_items_checked = lv.style_t()
style_MagLight_tabview_1_extra_btnm_items_checked.init()
style_MagLight_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_MagLight_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_MagLight_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_MagLight_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_MagLight_tabview_1_extra_btnm_items_checked.set_radius(0)
style_MagLight_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_MagLight_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_MagLight_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
MagLight_tabview_1.get_tab_btns().add_style(style_MagLight_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
MagLight_tabview_1_tab_1 = MagLight_tabview_1.add_tab("")
MagLight_tabview_1_tab_1_label = lv.label(MagLight_tabview_1_tab_1)
MagLight_tabview_1_tab_1_label.set_text("")

# Create MagLight_cont_1
MagLight_cont_1 = lv.obj(MagLight)
MagLight_cont_1.set_pos(0, 85)
MagLight_cont_1.set_size(720, 630)
MagLight_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MagLight_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_1.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_label_2
MagLight_label_2 = lv.label(MagLight)
MagLight_label_2.set_text("色 温 | 4850K")
MagLight_label_2.set_long_mode(lv.label.LONG.WRAP)
MagLight_label_2.set_width(lv.pct(100))
MagLight_label_2.set_pos(270, 560)
MagLight_label_2.set_size(211, 34)
# Set style for MagLight_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_2.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_ct_bar
MagLight_ct_bar = lv.img(MagLight)
MagLight_ct_bar.set_src("B:MicroPython/_ct_bar_alpha_650x75.bin")
MagLight_ct_bar.add_flag(lv.obj.FLAG.CLICKABLE)
MagLight_ct_bar.set_pivot(50,50)
MagLight_ct_bar.set_angle(0)
MagLight_ct_bar.set_pos(-210, 610)
MagLight_ct_bar.set_size(650, 75)
# Set style for MagLight_ct_bar, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_ct_bar.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_ct_bar.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_ct_bar.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_slider_2
MagLight_slider_2 = lv.slider(MagLight)
MagLight_slider_2.set_range(2700, 6500)
MagLight_slider_2.set_mode(lv.slider.MODE.SYMMETRICAL)
MagLight_slider_2.set_value(4600, lv.ANIM.OFF)
MagLight_slider_2.set_pos(-210, 610)
MagLight_slider_2.set_size(650, 75)
# Set style for MagLight_slider_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_slider_2.set_style_bg_opa(40, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_slider_2.set_style_bg_color(lv.color_hex(0x495661), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_slider_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_slider_2.set_style_radius(60, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_slider_2.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_slider_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for MagLight_slider_2, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
MagLight_slider_2.set_style_bg_opa(0, lv.PART.INDICATOR|lv.STATE.DEFAULT)
MagLight_slider_2.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for MagLight_slider_2, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
MagLight_slider_2.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
MagLight_slider_2.set_style_bg_color(lv.color_hex(0x300208), lv.PART.KNOB|lv.STATE.DEFAULT)
MagLight_slider_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
MagLight_slider_2.set_style_radius(60, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create MagLight_slider_1
MagLight_slider_1 = lv.slider(MagLight)
MagLight_slider_1.set_range(0, 100)
MagLight_slider_1.set_mode(lv.slider.MODE.SYMMETRICAL)
MagLight_slider_1.set_value(50, lv.ANIM.OFF)
MagLight_slider_1.set_pos(-215, 465)
MagLight_slider_1.set_size(650, 75)
# Set style for MagLight_slider_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_slider_1.set_style_bg_opa(60, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_slider_1.set_style_bg_color(lv.color_hex(0xdedfdf), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_slider_1.set_style_radius(60, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_slider_1.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_slider_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for MagLight_slider_1, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
MagLight_slider_1.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
MagLight_slider_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.INDICATOR|lv.STATE.DEFAULT)
MagLight_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.DEFAULT)
MagLight_slider_1.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for MagLight_slider_1, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
MagLight_slider_1.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DEFAULT)
MagLight_slider_1.set_style_radius(60, lv.PART.KNOB|lv.STATE.DEFAULT)

# Set style for MagLight_slider_1, Part: lv.PART.KNOB, State: lv.STATE.DISABLED.
MagLight_slider_1.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DISABLED)
MagLight_slider_1.set_style_radius(50, lv.PART.KNOB|lv.STATE.DISABLED)

# Create MagLight_label_1
MagLight_label_1 = lv.label(MagLight)
MagLight_label_1.set_text("亮 度 | 50%")
MagLight_label_1.set_long_mode(lv.label.LONG.WRAP)
MagLight_label_1.set_width(lv.pct(100))
MagLight_label_1.set_pos(270, 415)
MagLight_label_1.set_size(227, 39)
# Set style for MagLight_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_btn_1
MagLight_btn_1 = lv.btn(MagLight)
MagLight_btn_1_label = lv.label(MagLight_btn_1)
MagLight_btn_1_label.set_text("磁吸灯")
MagLight_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
MagLight_btn_1_label.set_width(lv.pct(100))
MagLight_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
MagLight_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
MagLight_btn_1.set_pos(70, 25)
MagLight_btn_1.set_size(123, 33)
# Set style for MagLight_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_imgbtn_1
MagLight_imgbtn_1 = lv.imgbtn(MagLight)
MagLight_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
MagLight_imgbtn_1.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_scene_btn_alpha_70x70.bin", None)
MagLight_imgbtn_1.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_btn_close_alpha_70x70.bin", None)
MagLight_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
MagLight_imgbtn_1_label = lv.label(MagLight_imgbtn_1)
MagLight_imgbtn_1_label.set_text("")
MagLight_imgbtn_1_label.set_long_mode(lv.label.LONG.WRAP)
MagLight_imgbtn_1_label.set_width(lv.pct(100))
MagLight_imgbtn_1_label.align(lv.ALIGN.CENTER, 0, 0)
MagLight_imgbtn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
MagLight_imgbtn_1.set_pos(620, 120)
MagLight_imgbtn_1.set_size(70, 70)
# Set style for MagLight_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_imgbtn_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_imgbtn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_imgbtn_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_imgbtn_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MagLight_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
MagLight_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
MagLight_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
MagLight_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
MagLight_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
MagLight_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for MagLight_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
MagLight_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
MagLight_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
MagLight_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
MagLight_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
MagLight_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for MagLight_imgbtn_1, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
MagLight_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create MagLight_on_off_2_img
MagLight_on_off_2_img = lv.imgbtn(MagLight)
MagLight_on_off_2_img.add_flag(lv.obj.FLAG.CHECKABLE)
MagLight_on_off_2_img.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_onoff_off_alpha_48x48.bin", None)
MagLight_on_off_2_img.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_onoff_on_alpha_48x48.bin", None)
MagLight_on_off_2_img.add_flag(lv.obj.FLAG.CHECKABLE)
MagLight_on_off_2_img_label = lv.label(MagLight_on_off_2_img)
MagLight_on_off_2_img_label.set_text("")
MagLight_on_off_2_img_label.set_long_mode(lv.label.LONG.WRAP)
MagLight_on_off_2_img_label.set_width(lv.pct(100))
MagLight_on_off_2_img_label.align(lv.ALIGN.CENTER, 0, 0)
MagLight_on_off_2_img.set_style_pad_all(0, lv.STATE.DEFAULT)
MagLight_on_off_2_img.set_pos(40, 120)
MagLight_on_off_2_img.set_size(48, 48)
# Set style for MagLight_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_on_off_2_img.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_on_off_2_img.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_on_off_2_img.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_on_off_2_img.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MagLight_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
MagLight_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
MagLight_on_off_2_img.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
MagLight_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
MagLight_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
MagLight_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for MagLight_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
MagLight_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
MagLight_on_off_2_img.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
MagLight_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
MagLight_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
MagLight_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for MagLight_on_off_2_img, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
MagLight_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create MagLight_MagPole
MagLight_MagPole = lv.img(MagLight)
MagLight_MagPole.set_src("B:MicroPython/_MagPole_alpha_453x13.bin")
MagLight_MagPole.add_flag(lv.obj.FLAG.CLICKABLE)
MagLight_MagPole.set_pivot(50,50)
MagLight_MagPole.set_angle(0)
MagLight_MagPole.set_pos(123, 259)
MagLight_MagPole.set_size(453, 13)
# Set style for MagLight_MagPole, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_MagPole.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_MagPole.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_MagPole.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_Orange
MagLight_Orange = lv.img(MagLight)
MagLight_Orange.set_src("B:MicroPython/_MagOrg_alpha_453x13.bin")
MagLight_Orange.add_flag(lv.obj.FLAG.CLICKABLE)
MagLight_Orange.set_pivot(50,50)
MagLight_Orange.set_angle(0)
MagLight_Orange.set_pos(123, 259)
MagLight_Orange.set_size(453, 13)
# Set style for MagLight_Orange, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_Orange.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_Orange.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_Orange.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_white
MagLight_white = lv.img(MagLight)
MagLight_white.set_src("B:MicroPython/_MagWhi_alpha_453x13.bin")
MagLight_white.add_flag(lv.obj.FLAG.CLICKABLE)
MagLight_white.set_pivot(50,50)
MagLight_white.set_angle(0)
MagLight_white.set_pos(123, 259)
MagLight_white.set_size(453, 13)
# Set style for MagLight_white, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_white.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_white.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_white.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_img_1
MagLight_img_1 = lv.img(MagLight)
MagLight_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
MagLight_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
MagLight_img_1.set_pivot(50,50)
MagLight_img_1.set_angle(0)
MagLight_img_1.set_pos(43, 28)
MagLight_img_1.set_size(14, 24)
# Set style for MagLight_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_btn_2
MagLight_btn_2 = lv.btn(MagLight)
MagLight_btn_2_label = lv.label(MagLight_btn_2)
MagLight_btn_2_label.set_text("")
MagLight_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
MagLight_btn_2_label.set_width(lv.pct(100))
MagLight_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
MagLight_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
MagLight_btn_2.set_pos(-8, -9)
MagLight_btn_2.set_size(243, 100)
# Set style for MagLight_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_cont_2
MagLight_cont_2 = lv.obj(MagLight)
MagLight_cont_2.set_pos(98, -509)
MagLight_cont_2.set_size(524, 392)
MagLight_cont_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MagLight_cont_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_cont_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_2.set_style_bg_color(lv.color_hex(0x171717), lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_cont_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create MagLight_img_7
MagLight_img_7 = lv.img(MagLight_cont_2)
MagLight_img_7.set_src("B:MicroPython/_LSscene1_alpha_112x140.bin")
MagLight_img_7.add_flag(lv.obj.FLAG.CLICKABLE)
MagLight_img_7.set_pivot(50,50)
MagLight_img_7.set_angle(0)
MagLight_img_7.set_pos(40, 29)
MagLight_img_7.set_size(112, 140)
# Set style for MagLight_img_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_img_7.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_img_7.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_img_7.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_img_6
MagLight_img_6 = lv.img(MagLight_cont_2)
MagLight_img_6.set_src("B:MicroPython/_LSscene2_alpha_112x140.bin")
MagLight_img_6.add_flag(lv.obj.FLAG.CLICKABLE)
MagLight_img_6.set_pivot(50,50)
MagLight_img_6.set_angle(0)
MagLight_img_6.set_pos(210, 29)
MagLight_img_6.set_size(112, 140)
# Set style for MagLight_img_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_img_6.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_img_6.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_img_6.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_img_5
MagLight_img_5 = lv.img(MagLight_cont_2)
MagLight_img_5.set_src("B:MicroPython/_LSscene3_alpha_112x140.bin")
MagLight_img_5.add_flag(lv.obj.FLAG.CLICKABLE)
MagLight_img_5.set_pivot(50,50)
MagLight_img_5.set_angle(0)
MagLight_img_5.set_pos(380, 29)
MagLight_img_5.set_size(112, 140)
# Set style for MagLight_img_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_img_5.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_img_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_img_5.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_img_4
MagLight_img_4 = lv.img(MagLight_cont_2)
MagLight_img_4.set_src("B:MicroPython/_LSscene4_alpha_112x140.bin")
MagLight_img_4.add_flag(lv.obj.FLAG.CLICKABLE)
MagLight_img_4.set_pivot(50,50)
MagLight_img_4.set_angle(0)
MagLight_img_4.set_pos(40, 204)
MagLight_img_4.set_size(112, 140)
# Set style for MagLight_img_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_img_4.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_img_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_img_4.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_img_3
MagLight_img_3 = lv.img(MagLight_cont_2)
MagLight_img_3.set_src("B:MicroPython/_LSscene5_alpha_112x140.bin")
MagLight_img_3.add_flag(lv.obj.FLAG.CLICKABLE)
MagLight_img_3.set_pivot(50,50)
MagLight_img_3.set_angle(0)
MagLight_img_3.set_pos(210, 204)
MagLight_img_3.set_size(112, 140)
# Set style for MagLight_img_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_img_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_img_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_img_3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MagLight_img_2
MagLight_img_2 = lv.img(MagLight_cont_2)
MagLight_img_2.set_src("B:MicroPython/_LSscene6_alpha_112x140.bin")
MagLight_img_2.add_flag(lv.obj.FLAG.CLICKABLE)
MagLight_img_2.set_pivot(50,50)
MagLight_img_2.set_angle(0)
MagLight_img_2.set_pos(380, 204)
MagLight_img_2.set_size(112, 140)
# Set style for MagLight_img_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MagLight_img_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_img_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MagLight_img_2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

MagLight.update_layout()
# Create FabricCurtian
FabricCurtian = lv.obj()
FabricCurtian.set_size(720, 720)
FabricCurtian.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for FabricCurtian, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_tabview_1
FabricCurtian_tabview_1 = lv.tabview(FabricCurtian, lv.DIR.TOP, 85)
FabricCurtian_tabview_1.set_pos(0, 0)
FabricCurtian_tabview_1.set_size(720, 720)
FabricCurtian_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for FabricCurtian_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for FabricCurtian_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_FabricCurtian_tabview_1_extra_btnm_main_default = lv.style_t()
style_FabricCurtian_tabview_1_extra_btnm_main_default.init()
style_FabricCurtian_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_FabricCurtian_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_FabricCurtian_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_FabricCurtian_tabview_1_extra_btnm_main_default.set_border_width(0)
style_FabricCurtian_tabview_1_extra_btnm_main_default.set_radius(0)
FabricCurtian_tabview_1.get_tab_btns().add_style(style_FabricCurtian_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for FabricCurtian_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_FabricCurtian_tabview_1_extra_btnm_items_default = lv.style_t()
style_FabricCurtian_tabview_1_extra_btnm_items_default.init()
style_FabricCurtian_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_FabricCurtian_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_FabricCurtian_tabview_1_extra_btnm_items_default.set_text_opa(255)
FabricCurtian_tabview_1.get_tab_btns().add_style(style_FabricCurtian_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for FabricCurtian_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_FabricCurtian_tabview_1_extra_btnm_items_checked = lv.style_t()
style_FabricCurtian_tabview_1_extra_btnm_items_checked.init()
style_FabricCurtian_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_FabricCurtian_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_FabricCurtian_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_FabricCurtian_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_FabricCurtian_tabview_1_extra_btnm_items_checked.set_radius(0)
style_FabricCurtian_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_FabricCurtian_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_FabricCurtian_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
FabricCurtian_tabview_1.get_tab_btns().add_style(style_FabricCurtian_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
FabricCurtian_tabview_1_tab_1 = FabricCurtian_tabview_1.add_tab("")
FabricCurtian_tabview_1_tab_1_label = lv.label(FabricCurtian_tabview_1_tab_1)
FabricCurtian_tabview_1_tab_1_label.set_text("")

# Create FabricCurtian_cont_1
FabricCurtian_cont_1 = lv.obj(FabricCurtian)
FabricCurtian_cont_1.set_pos(0, 85)
FabricCurtian_cont_1.set_size(720, 630)
FabricCurtian_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for FabricCurtian_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_1.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_btn_1
FabricCurtian_btn_1 = lv.btn(FabricCurtian)
FabricCurtian_btn_1_label = lv.label(FabricCurtian_btn_1)
FabricCurtian_btn_1_label.set_text("布  帘")
FabricCurtian_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
FabricCurtian_btn_1_label.set_width(lv.pct(100))
FabricCurtian_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
FabricCurtian_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
FabricCurtian_btn_1.set_pos(70, 25)
FabricCurtian_btn_1.set_size(94, 33)
# Set style for FabricCurtian_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_FabCurtianOpen
FabricCurtian_FabCurtianOpen = lv.img(FabricCurtian)
FabricCurtian_FabCurtianOpen.set_src("B:MicroPython/_FCOpen_alpha_94x95.bin")
FabricCurtian_FabCurtianOpen.add_flag(lv.obj.FLAG.CLICKABLE)
FabricCurtian_FabCurtianOpen.set_pivot(50,50)
FabricCurtian_FabCurtianOpen.set_angle(0)
FabricCurtian_FabCurtianOpen.set_pos(70, 678)
FabricCurtian_FabCurtianOpen.set_size(94, 95)
# Set style for FabricCurtian_FabCurtianOpen, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_FabCurtianOpen.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianOpen.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianOpen.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_FabCurtianClose
FabricCurtian_FabCurtianClose = lv.img(FabricCurtian)
FabricCurtian_FabCurtianClose.set_src("B:MicroPython/_FCClose_alpha_95x95.bin")
FabricCurtian_FabCurtianClose.add_flag(lv.obj.FLAG.CLICKABLE)
FabricCurtian_FabCurtianClose.set_pivot(50,50)
FabricCurtian_FabCurtianClose.set_angle(0)
FabricCurtian_FabCurtianClose.set_pos(557, 678)
FabricCurtian_FabCurtianClose.set_size(95, 95)
# Set style for FabricCurtian_FabCurtianClose, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_FabCurtianClose.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianClose.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianClose.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_FabCurtianPause
FabricCurtian_FabCurtianPause = lv.img(FabricCurtian)
FabricCurtian_FabCurtianPause.set_src("B:MicroPython/_FCPause_alpha_109x110.bin")
FabricCurtian_FabCurtianPause.add_flag(lv.obj.FLAG.CLICKABLE)
FabricCurtian_FabCurtianPause.set_pivot(50,50)
FabricCurtian_FabCurtianPause.set_angle(0)
FabricCurtian_FabCurtianPause.set_pos(311, 678)
FabricCurtian_FabCurtianPause.set_size(109, 110)
# Set style for FabricCurtian_FabCurtianPause, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_FabCurtianPause.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPause.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPause.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_FabCurtianBg1
FabricCurtian_FabCurtianBg1 = lv.img(FabricCurtian)
FabricCurtian_FabCurtianBg1.set_src("B:MicroPython/_FCBg1_alpha_62x60.bin")
FabricCurtian_FabCurtianBg1.add_flag(lv.obj.FLAG.CLICKABLE)
FabricCurtian_FabCurtianBg1.set_pivot(50,50)
FabricCurtian_FabCurtianBg1.set_angle(0)
FabricCurtian_FabCurtianBg1.set_pos(232, 255)
FabricCurtian_FabCurtianBg1.set_size(62, 60)
# Set style for FabricCurtian_FabCurtianBg1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_FabCurtianBg1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianBg1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianBg1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_FabCurtianBg2
FabricCurtian_FabCurtianBg2 = lv.img(FabricCurtian)
FabricCurtian_FabCurtianBg2.set_src("B:MicroPython/_FCBg2_alpha_34x73.bin")
FabricCurtian_FabCurtianBg2.add_flag(lv.obj.FLAG.CLICKABLE)
FabricCurtian_FabCurtianBg2.set_pivot(50,50)
FabricCurtian_FabCurtianBg2.set_angle(0)
FabricCurtian_FabCurtianBg2.set_pos(415, 272)
FabricCurtian_FabCurtianBg2.set_size(34, 73)
# Set style for FabricCurtian_FabCurtianBg2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_FabCurtianBg2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianBg2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianBg2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_FabCurtianBg3
FabricCurtian_FabCurtianBg3 = lv.img(FabricCurtian)
FabricCurtian_FabCurtianBg3.set_src("B:MicroPython/_FCBg3_alpha_42x14.bin")
FabricCurtian_FabCurtianBg3.add_flag(lv.obj.FLAG.CLICKABLE)
FabricCurtian_FabCurtianBg3.set_pivot(50,50)
FabricCurtian_FabCurtianBg3.set_angle(0)
FabricCurtian_FabCurtianBg3.set_pos(252, 384)
FabricCurtian_FabCurtianBg3.set_size(42, 14)
# Set style for FabricCurtian_FabCurtianBg3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_FabCurtianBg3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianBg3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianBg3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_FabCurtianLeft
FabricCurtian_FabCurtianLeft = lv.img(FabricCurtian)
FabricCurtian_FabCurtianLeft.set_src("B:MicroPython/_FCLeft_alpha_231x287.bin")
FabricCurtian_FabCurtianLeft.add_flag(lv.obj.FLAG.CLICKABLE)
FabricCurtian_FabCurtianLeft.set_pivot(50,50)
FabricCurtian_FabCurtianLeft.set_angle(0)
FabricCurtian_FabCurtianLeft.set_pos(129, 193)
FabricCurtian_FabCurtianLeft.set_size(231, 287)
# Set style for FabricCurtian_FabCurtianLeft, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_FabCurtianLeft.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianLeft.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianLeft.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_FabCurtianright
FabricCurtian_FabCurtianright = lv.img(FabricCurtian)
FabricCurtian_FabCurtianright.set_src("B:MicroPython/_FCright_alpha_231x287.bin")
FabricCurtian_FabCurtianright.add_flag(lv.obj.FLAG.CLICKABLE)
FabricCurtian_FabCurtianright.set_pivot(50,50)
FabricCurtian_FabCurtianright.set_angle(0)
FabricCurtian_FabCurtianright.set_pos(360, 193)
FabricCurtian_FabCurtianright.set_size(231, 287)
# Set style for FabricCurtian_FabCurtianright, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_FabCurtianright.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianright.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianright.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_cont_2
FabricCurtian_cont_2 = lv.obj(FabricCurtian)
FabricCurtian_cont_2.set_pos(-9, 170)
FabricCurtian_cont_2.set_size(137, 324)
FabricCurtian_cont_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for FabricCurtian_cont_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_cont_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_2.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_cont_3
FabricCurtian_cont_3 = lv.obj(FabricCurtian)
FabricCurtian_cont_3.set_pos(590, 164)
FabricCurtian_cont_3.set_size(132, 324)
FabricCurtian_cont_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for FabricCurtian_cont_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_cont_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_3.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_cont_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_FabCurtianPull2
FabricCurtian_FabCurtianPull2 = lv.img(FabricCurtian)
FabricCurtian_FabCurtianPull2.set_src("B:MicroPython/_FCPull_alpha_45x45.bin")
FabricCurtian_FabCurtianPull2.add_flag(lv.obj.FLAG.CLICKABLE)
FabricCurtian_FabCurtianPull2.set_pivot(50,50)
FabricCurtian_FabCurtianPull2.set_angle(0)
FabricCurtian_FabCurtianPull2.set_pos(367, 314)
FabricCurtian_FabCurtianPull2.set_size(45, 45)
# Set style for FabricCurtian_FabCurtianPull2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_FabCurtianPull2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_FabCurtianPull1
FabricCurtian_FabCurtianPull1 = lv.img(FabricCurtian)
FabricCurtian_FabCurtianPull1.set_src("B:MicroPython/_FCPull_alpha_45x45.bin")
FabricCurtian_FabCurtianPull1.add_flag(lv.obj.FLAG.CLICKABLE)
FabricCurtian_FabCurtianPull1.set_pivot(50,50)
FabricCurtian_FabCurtianPull1.set_angle(0)
FabricCurtian_FabCurtianPull1.set_pos(302, 315)
FabricCurtian_FabCurtianPull1.set_size(45, 45)
# Set style for FabricCurtian_FabCurtianPull1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_FabCurtianPull1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_FabCurtianPole
FabricCurtian_FabCurtianPole = lv.img(FabricCurtian)
FabricCurtian_FabCurtianPole.set_src("B:MicroPython/_FCPole_alpha_494x34.bin")
FabricCurtian_FabCurtianPole.add_flag(lv.obj.FLAG.CLICKABLE)
FabricCurtian_FabCurtianPole.set_pivot(50,50)
FabricCurtian_FabCurtianPole.set_angle(0)
FabricCurtian_FabCurtianPole.set_pos(112, 178)
FabricCurtian_FabCurtianPole.set_size(494, 34)
# Set style for FabricCurtian_FabCurtianPole, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_FabCurtianPole.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPole.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPole.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_label_1
FabricCurtian_label_1 = lv.label(FabricCurtian)
FabricCurtian_label_1.set_text("0%")
FabricCurtian_label_1.set_long_mode(lv.label.LONG.WRAP)
FabricCurtian_label_1.set_width(lv.pct(100))
FabricCurtian_label_1.set_pos(316, 503)
FabricCurtian_label_1.set_size(87, 30)
# Set style for FabricCurtian_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_label_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_img_1
FabricCurtian_img_1 = lv.img(FabricCurtian)
FabricCurtian_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
FabricCurtian_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
FabricCurtian_img_1.set_pivot(50,50)
FabricCurtian_img_1.set_angle(0)
FabricCurtian_img_1.set_pos(43, 28)
FabricCurtian_img_1.set_size(14, 24)
# Set style for FabricCurtian_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_btn_2
FabricCurtian_btn_2 = lv.btn(FabricCurtian)
FabricCurtian_btn_2_label = lv.label(FabricCurtian_btn_2)
FabricCurtian_btn_2_label.set_text("")
FabricCurtian_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
FabricCurtian_btn_2_label.set_width(lv.pct(100))
FabricCurtian_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
FabricCurtian_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
FabricCurtian_btn_2.set_pos(-8, -11)
FabricCurtian_btn_2.set_size(240, 101)
# Set style for FabricCurtian_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_FabCurtianPull3
FabricCurtian_FabCurtianPull3 = lv.btn(FabricCurtian)
FabricCurtian_FabCurtianPull3_label = lv.label(FabricCurtian_FabCurtianPull3)
FabricCurtian_FabCurtianPull3_label.set_text("")
FabricCurtian_FabCurtianPull3_label.set_long_mode(lv.label.LONG.WRAP)
FabricCurtian_FabCurtianPull3_label.set_width(lv.pct(100))
FabricCurtian_FabCurtianPull3_label.align(lv.ALIGN.CENTER, 0, 0)
FabricCurtian_FabCurtianPull3.set_style_pad_all(0, lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull3.set_pos(290, 205)
FabricCurtian_FabCurtianPull3.set_size(65, 300)
# Set style for FabricCurtian_FabCurtianPull3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_FabCurtianPull3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FabricCurtian_FabCurtianPull4
FabricCurtian_FabCurtianPull4 = lv.btn(FabricCurtian)
FabricCurtian_FabCurtianPull4_label = lv.label(FabricCurtian_FabCurtianPull4)
FabricCurtian_FabCurtianPull4_label.set_text("")
FabricCurtian_FabCurtianPull4_label.set_long_mode(lv.label.LONG.WRAP)
FabricCurtian_FabCurtianPull4_label.set_width(lv.pct(100))
FabricCurtian_FabCurtianPull4_label.align(lv.ALIGN.CENTER, 0, 0)
FabricCurtian_FabCurtianPull4.set_style_pad_all(0, lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull4.set_pos(362, 205)
FabricCurtian_FabCurtianPull4.set_size(65, 300)
# Set style for FabricCurtian_FabCurtianPull4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FabricCurtian_FabCurtianPull4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull4.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FabricCurtian_FabCurtianPull4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

FabricCurtian.update_layout()
# Create Sheers
Sheers = lv.obj()
Sheers.set_size(720, 720)
Sheers.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Sheers, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_tabview_1
Sheers_tabview_1 = lv.tabview(Sheers, lv.DIR.TOP, 85)
Sheers_tabview_1.set_pos(0, 0)
Sheers_tabview_1.set_size(720, 720)
Sheers_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for Sheers_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for Sheers_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_Sheers_tabview_1_extra_btnm_main_default = lv.style_t()
style_Sheers_tabview_1_extra_btnm_main_default.init()
style_Sheers_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_Sheers_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_Sheers_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_Sheers_tabview_1_extra_btnm_main_default.set_border_width(0)
style_Sheers_tabview_1_extra_btnm_main_default.set_radius(0)
Sheers_tabview_1.get_tab_btns().add_style(style_Sheers_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for Sheers_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_Sheers_tabview_1_extra_btnm_items_default = lv.style_t()
style_Sheers_tabview_1_extra_btnm_items_default.init()
style_Sheers_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_Sheers_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_Sheers_tabview_1_extra_btnm_items_default.set_text_opa(255)
Sheers_tabview_1.get_tab_btns().add_style(style_Sheers_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for Sheers_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_Sheers_tabview_1_extra_btnm_items_checked = lv.style_t()
style_Sheers_tabview_1_extra_btnm_items_checked.init()
style_Sheers_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_Sheers_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_Sheers_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_Sheers_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_Sheers_tabview_1_extra_btnm_items_checked.set_radius(0)
style_Sheers_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_Sheers_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_Sheers_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
Sheers_tabview_1.get_tab_btns().add_style(style_Sheers_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
Sheers_tabview_1_tab_1 = Sheers_tabview_1.add_tab("")
Sheers_tabview_1_tab_1_label = lv.label(Sheers_tabview_1_tab_1)
Sheers_tabview_1_tab_1_label.set_text("")

# Create Sheers_cont_1
Sheers_cont_1 = lv.obj(Sheers)
Sheers_cont_1.set_pos(0, 85)
Sheers_cont_1.set_size(720, 630)
Sheers_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Sheers_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_1.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_btn_1
Sheers_btn_1 = lv.btn(Sheers)
Sheers_btn_1_label = lv.label(Sheers_btn_1)
Sheers_btn_1_label.set_text("纱  帘")
Sheers_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
Sheers_btn_1_label.set_width(lv.pct(100))
Sheers_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
Sheers_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
Sheers_btn_1.set_pos(70, 25)
Sheers_btn_1.set_size(94, 34)
# Set style for Sheers_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_FabCurtianOpen
Sheers_FabCurtianOpen = lv.img(Sheers)
Sheers_FabCurtianOpen.set_src("B:MicroPython/_FCOpen_alpha_94x95.bin")
Sheers_FabCurtianOpen.add_flag(lv.obj.FLAG.CLICKABLE)
Sheers_FabCurtianOpen.set_pivot(50,50)
Sheers_FabCurtianOpen.set_angle(0)
Sheers_FabCurtianOpen.set_pos(69, 670)
Sheers_FabCurtianOpen.set_size(94, 95)
# Set style for Sheers_FabCurtianOpen, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_FabCurtianOpen.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianOpen.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianOpen.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_FabCurtianClose
Sheers_FabCurtianClose = lv.img(Sheers)
Sheers_FabCurtianClose.set_src("B:MicroPython/_FCClose_alpha_95x95.bin")
Sheers_FabCurtianClose.add_flag(lv.obj.FLAG.CLICKABLE)
Sheers_FabCurtianClose.set_pivot(50,50)
Sheers_FabCurtianClose.set_angle(0)
Sheers_FabCurtianClose.set_pos(567, 670)
Sheers_FabCurtianClose.set_size(95, 95)
# Set style for Sheers_FabCurtianClose, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_FabCurtianClose.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianClose.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianClose.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_FabCurtianPause
Sheers_FabCurtianPause = lv.img(Sheers)
Sheers_FabCurtianPause.set_src("B:MicroPython/_FCPause_alpha_109x110.bin")
Sheers_FabCurtianPause.add_flag(lv.obj.FLAG.CLICKABLE)
Sheers_FabCurtianPause.set_pivot(50,50)
Sheers_FabCurtianPause.set_angle(0)
Sheers_FabCurtianPause.set_pos(317, 670)
Sheers_FabCurtianPause.set_size(109, 110)
# Set style for Sheers_FabCurtianPause, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_FabCurtianPause.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPause.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPause.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_FabCurtianBg1
Sheers_FabCurtianBg1 = lv.img(Sheers)
Sheers_FabCurtianBg1.set_src("B:MicroPython/_FCBg1_alpha_62x60.bin")
Sheers_FabCurtianBg1.add_flag(lv.obj.FLAG.CLICKABLE)
Sheers_FabCurtianBg1.set_pivot(50,50)
Sheers_FabCurtianBg1.set_angle(0)
Sheers_FabCurtianBg1.set_pos(232, 255)
Sheers_FabCurtianBg1.set_size(62, 60)
# Set style for Sheers_FabCurtianBg1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_FabCurtianBg1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianBg1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianBg1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_FabCurtianBg2
Sheers_FabCurtianBg2 = lv.img(Sheers)
Sheers_FabCurtianBg2.set_src("B:MicroPython/_FCBg2_alpha_34x73.bin")
Sheers_FabCurtianBg2.add_flag(lv.obj.FLAG.CLICKABLE)
Sheers_FabCurtianBg2.set_pivot(50,50)
Sheers_FabCurtianBg2.set_angle(0)
Sheers_FabCurtianBg2.set_pos(415, 272)
Sheers_FabCurtianBg2.set_size(34, 73)
# Set style for Sheers_FabCurtianBg2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_FabCurtianBg2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianBg2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianBg2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_FabCurtianBg3
Sheers_FabCurtianBg3 = lv.img(Sheers)
Sheers_FabCurtianBg3.set_src("B:MicroPython/_FCBg3_alpha_42x14.bin")
Sheers_FabCurtianBg3.add_flag(lv.obj.FLAG.CLICKABLE)
Sheers_FabCurtianBg3.set_pivot(50,50)
Sheers_FabCurtianBg3.set_angle(0)
Sheers_FabCurtianBg3.set_pos(252, 384)
Sheers_FabCurtianBg3.set_size(42, 14)
# Set style for Sheers_FabCurtianBg3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_FabCurtianBg3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianBg3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianBg3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_FabCurtianLeft
Sheers_FabCurtianLeft = lv.img(Sheers)
Sheers_FabCurtianLeft.set_src("B:MicroPython/_SheersLeft_alpha_230x282.bin")
Sheers_FabCurtianLeft.add_flag(lv.obj.FLAG.CLICKABLE)
Sheers_FabCurtianLeft.set_pivot(50,50)
Sheers_FabCurtianLeft.set_angle(0)
Sheers_FabCurtianLeft.set_pos(129, 202)
Sheers_FabCurtianLeft.set_size(230, 282)
# Set style for Sheers_FabCurtianLeft, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_FabCurtianLeft.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianLeft.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianLeft.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_FabCurtianright
Sheers_FabCurtianright = lv.img(Sheers)
Sheers_FabCurtianright.set_src("B:MicroPython/_SheersRight_alpha_230x282.bin")
Sheers_FabCurtianright.add_flag(lv.obj.FLAG.CLICKABLE)
Sheers_FabCurtianright.set_pivot(50,50)
Sheers_FabCurtianright.set_angle(0)
Sheers_FabCurtianright.set_pos(359, 202)
Sheers_FabCurtianright.set_size(230, 282)
# Set style for Sheers_FabCurtianright, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_FabCurtianright.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianright.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianright.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_cont_2
Sheers_cont_2 = lv.obj(Sheers)
Sheers_cont_2.set_pos(-2, 164)
Sheers_cont_2.set_size(130, 336)
Sheers_cont_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Sheers_cont_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_cont_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_2.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_cont_3
Sheers_cont_3 = lv.obj(Sheers)
Sheers_cont_3.set_pos(591, 174)
Sheers_cont_3.set_size(130, 336)
Sheers_cont_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Sheers_cont_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_cont_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_3.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_cont_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_FabCurtianPull2
Sheers_FabCurtianPull2 = lv.img(Sheers)
Sheers_FabCurtianPull2.set_src("B:MicroPython/_FCPull_alpha_45x45.bin")
Sheers_FabCurtianPull2.add_flag(lv.obj.FLAG.CLICKABLE)
Sheers_FabCurtianPull2.set_pivot(50,50)
Sheers_FabCurtianPull2.set_angle(0)
Sheers_FabCurtianPull2.set_pos(361, 321)
Sheers_FabCurtianPull2.set_size(45, 45)
# Set style for Sheers_FabCurtianPull2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_FabCurtianPull2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_FabCurtianPull1
Sheers_FabCurtianPull1 = lv.img(Sheers)
Sheers_FabCurtianPull1.set_src("B:MicroPython/_FCPull_alpha_45x45.bin")
Sheers_FabCurtianPull1.add_flag(lv.obj.FLAG.CLICKABLE)
Sheers_FabCurtianPull1.set_pivot(50,50)
Sheers_FabCurtianPull1.set_angle(0)
Sheers_FabCurtianPull1.set_pos(311, 321)
Sheers_FabCurtianPull1.set_size(45, 45)
# Set style for Sheers_FabCurtianPull1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_FabCurtianPull1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_FabCurtianPole
Sheers_FabCurtianPole = lv.img(Sheers)
Sheers_FabCurtianPole.set_src("B:MicroPython/_FCPole_alpha_494x34.bin")
Sheers_FabCurtianPole.add_flag(lv.obj.FLAG.CLICKABLE)
Sheers_FabCurtianPole.set_pivot(50,50)
Sheers_FabCurtianPole.set_angle(0)
Sheers_FabCurtianPole.set_pos(112, 178)
Sheers_FabCurtianPole.set_size(494, 34)
# Set style for Sheers_FabCurtianPole, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_FabCurtianPole.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPole.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPole.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_img_1
Sheers_img_1 = lv.img(Sheers)
Sheers_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
Sheers_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
Sheers_img_1.set_pivot(50,50)
Sheers_img_1.set_angle(0)
Sheers_img_1.set_pos(43, 28)
Sheers_img_1.set_size(14, 24)
# Set style for Sheers_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_btn_2
Sheers_btn_2 = lv.btn(Sheers)
Sheers_btn_2_label = lv.label(Sheers_btn_2)
Sheers_btn_2_label.set_text("")
Sheers_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
Sheers_btn_2_label.set_width(lv.pct(100))
Sheers_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
Sheers_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
Sheers_btn_2.set_pos(-6, -10)
Sheers_btn_2.set_size(232, 103)
# Set style for Sheers_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_FabCurtianPull4
Sheers_FabCurtianPull4 = lv.btn(Sheers)
Sheers_FabCurtianPull4_label = lv.label(Sheers_FabCurtianPull4)
Sheers_FabCurtianPull4_label.set_text("")
Sheers_FabCurtianPull4_label.set_long_mode(lv.label.LONG.WRAP)
Sheers_FabCurtianPull4_label.set_width(lv.pct(100))
Sheers_FabCurtianPull4_label.align(lv.ALIGN.CENTER, 0, 0)
Sheers_FabCurtianPull4.set_style_pad_all(0, lv.STATE.DEFAULT)
Sheers_FabCurtianPull4.set_pos(361, 205)
Sheers_FabCurtianPull4.set_size(65, 300)
# Set style for Sheers_FabCurtianPull4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_FabCurtianPull4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull4.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Sheers_FabCurtianPull3
Sheers_FabCurtianPull3 = lv.btn(Sheers)
Sheers_FabCurtianPull3_label = lv.label(Sheers_FabCurtianPull3)
Sheers_FabCurtianPull3_label.set_text("")
Sheers_FabCurtianPull3_label.set_long_mode(lv.label.LONG.WRAP)
Sheers_FabCurtianPull3_label.set_width(lv.pct(100))
Sheers_FabCurtianPull3_label.align(lv.ALIGN.CENTER, 0, 0)
Sheers_FabCurtianPull3.set_style_pad_all(0, lv.STATE.DEFAULT)
Sheers_FabCurtianPull3.set_pos(292, 205)
Sheers_FabCurtianPull3.set_size(65, 300)
# Set style for Sheers_FabCurtianPull3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Sheers_FabCurtianPull3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Sheers_FabCurtianPull3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

Sheers.update_layout()
# Create RollBlind
RollBlind = lv.obj()
RollBlind.set_size(720, 720)
RollBlind.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for RollBlind, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_tabview_1
RollBlind_tabview_1 = lv.tabview(RollBlind, lv.DIR.TOP, 85)
RollBlind_tabview_1.set_pos(0, 0)
RollBlind_tabview_1.set_size(720, 720)
RollBlind_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for RollBlind_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for RollBlind_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_RollBlind_tabview_1_extra_btnm_main_default = lv.style_t()
style_RollBlind_tabview_1_extra_btnm_main_default.init()
style_RollBlind_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_RollBlind_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x4f3f3f))
style_RollBlind_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_RollBlind_tabview_1_extra_btnm_main_default.set_border_width(0)
style_RollBlind_tabview_1_extra_btnm_main_default.set_radius(0)
RollBlind_tabview_1.get_tab_btns().add_style(style_RollBlind_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for RollBlind_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_RollBlind_tabview_1_extra_btnm_items_default = lv.style_t()
style_RollBlind_tabview_1_extra_btnm_items_default.init()
style_RollBlind_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_RollBlind_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_RollBlind_tabview_1_extra_btnm_items_default.set_text_opa(255)
RollBlind_tabview_1.get_tab_btns().add_style(style_RollBlind_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for RollBlind_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_RollBlind_tabview_1_extra_btnm_items_checked = lv.style_t()
style_RollBlind_tabview_1_extra_btnm_items_checked.init()
style_RollBlind_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_RollBlind_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_RollBlind_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_RollBlind_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_RollBlind_tabview_1_extra_btnm_items_checked.set_radius(0)
style_RollBlind_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_RollBlind_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_RollBlind_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
RollBlind_tabview_1.get_tab_btns().add_style(style_RollBlind_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
RollBlind_tabview_1_tab_1 = RollBlind_tabview_1.add_tab("")
RollBlind_tabview_1_tab_1_label = lv.label(RollBlind_tabview_1_tab_1)
RollBlind_tabview_1_tab_1_label.set_text("")

# Create RollBlind_cont_1
RollBlind_cont_1 = lv.obj(RollBlind)
RollBlind_cont_1.set_pos(0, 72)
RollBlind_cont_1.set_size(720, 645)
RollBlind_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for RollBlind_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_1.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_FabCurtianOpen
RollBlind_FabCurtianOpen = lv.img(RollBlind)
RollBlind_FabCurtianOpen.set_src("B:MicroPython/_RollBlindUp_alpha_94x95.bin")
RollBlind_FabCurtianOpen.add_flag(lv.obj.FLAG.CLICKABLE)
RollBlind_FabCurtianOpen.set_pivot(50,50)
RollBlind_FabCurtianOpen.set_angle(0)
RollBlind_FabCurtianOpen.set_pos(57, 662)
RollBlind_FabCurtianOpen.set_size(94, 95)
# Set style for RollBlind_FabCurtianOpen, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_FabCurtianOpen.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianOpen.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianOpen.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_FabCurtianClose
RollBlind_FabCurtianClose = lv.img(RollBlind)
RollBlind_FabCurtianClose.set_src("B:MicroPython/_RBDown_alpha_94x95.bin")
RollBlind_FabCurtianClose.add_flag(lv.obj.FLAG.CLICKABLE)
RollBlind_FabCurtianClose.set_pivot(50,50)
RollBlind_FabCurtianClose.set_angle(0)
RollBlind_FabCurtianClose.set_pos(554, 662)
RollBlind_FabCurtianClose.set_size(94, 95)
# Set style for RollBlind_FabCurtianClose, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_FabCurtianClose.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianClose.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianClose.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_cont_2
RollBlind_cont_2 = lv.obj(RollBlind)
RollBlind_cont_2.set_pos(147, 112)
RollBlind_cont_2.set_size(435, 353)
RollBlind_cont_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for RollBlind_cont_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_cont_2.set_style_border_width(4, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_2.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_2.set_style_border_color(lv.color_hex(0x2c2424), lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_2.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_FabCurtianPause
RollBlind_FabCurtianPause = lv.img(RollBlind)
RollBlind_FabCurtianPause.set_src("B:MicroPython/_FCPause_alpha_95x95.bin")
RollBlind_FabCurtianPause.add_flag(lv.obj.FLAG.CLICKABLE)
RollBlind_FabCurtianPause.set_pivot(50,50)
RollBlind_FabCurtianPause.set_angle(0)
RollBlind_FabCurtianPause.set_pos(305, 662)
RollBlind_FabCurtianPause.set_size(95, 95)
# Set style for RollBlind_FabCurtianPause, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_FabCurtianPause.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianPause.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianPause.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_FabCurtianBg1
RollBlind_FabCurtianBg1 = lv.img(RollBlind)
RollBlind_FabCurtianBg1.set_src("B:MicroPython/_FCBg1_alpha_62x60.bin")
RollBlind_FabCurtianBg1.add_flag(lv.obj.FLAG.CLICKABLE)
RollBlind_FabCurtianBg1.set_pivot(50,50)
RollBlind_FabCurtianBg1.set_angle(0)
RollBlind_FabCurtianBg1.set_pos(237, 186)
RollBlind_FabCurtianBg1.set_size(62, 60)
# Set style for RollBlind_FabCurtianBg1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_FabCurtianBg1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianBg1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianBg1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_FabCurtianBg2
RollBlind_FabCurtianBg2 = lv.img(RollBlind)
RollBlind_FabCurtianBg2.set_src("B:MicroPython/_FCBg2_alpha_34x73.bin")
RollBlind_FabCurtianBg2.add_flag(lv.obj.FLAG.CLICKABLE)
RollBlind_FabCurtianBg2.set_pivot(50,50)
RollBlind_FabCurtianBg2.set_angle(0)
RollBlind_FabCurtianBg2.set_pos(420, 203)
RollBlind_FabCurtianBg2.set_size(34, 73)
# Set style for RollBlind_FabCurtianBg2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_FabCurtianBg2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianBg2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianBg2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_FabCurtianBg3
RollBlind_FabCurtianBg3 = lv.img(RollBlind)
RollBlind_FabCurtianBg3.set_src("B:MicroPython/_FCBg3_alpha_42x14.bin")
RollBlind_FabCurtianBg3.add_flag(lv.obj.FLAG.CLICKABLE)
RollBlind_FabCurtianBg3.set_pivot(50,50)
RollBlind_FabCurtianBg3.set_angle(0)
RollBlind_FabCurtianBg3.set_pos(257, 315)
RollBlind_FabCurtianBg3.set_size(42, 14)
# Set style for RollBlind_FabCurtianBg3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_FabCurtianBg3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianBg3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianBg3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_FabCurtianLeft
RollBlind_FabCurtianLeft = lv.img(RollBlind)
RollBlind_FabCurtianLeft.set_src("B:MicroPython/_RBCloth_alpha_435x353.bin")
RollBlind_FabCurtianLeft.add_flag(lv.obj.FLAG.CLICKABLE)
RollBlind_FabCurtianLeft.set_pivot(50,50)
RollBlind_FabCurtianLeft.set_angle(0)
RollBlind_FabCurtianLeft.set_pos(147, 112)
RollBlind_FabCurtianLeft.set_size(435, 353)
# Set style for RollBlind_FabCurtianLeft, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_FabCurtianLeft.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianLeft.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianLeft.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_cont_3
RollBlind_cont_3 = lv.obj(RollBlind)
RollBlind_cont_3.set_pos(138, 83)
RollBlind_cont_3.set_size(456, 28)
RollBlind_cont_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for RollBlind_cont_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_cont_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_3.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_cont_4
RollBlind_cont_4 = lv.obj(RollBlind)
RollBlind_cont_4.set_pos(0, 0)
RollBlind_cont_4.set_size(720, 85)
RollBlind_cont_4.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for RollBlind_cont_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_cont_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_4.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_4.set_style_bg_color(lv.color_hex(0x243241), lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_4.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_4.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_4.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_4.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_4.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_cont_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_FabCurtianPull1
RollBlind_FabCurtianPull1 = lv.img(RollBlind)
RollBlind_FabCurtianPull1.set_src("B:MicroPython/_CurtainPull_alpha_39x39.bin")
RollBlind_FabCurtianPull1.add_flag(lv.obj.FLAG.CLICKABLE)
RollBlind_FabCurtianPull1.set_pivot(50,50)
RollBlind_FabCurtianPull1.set_angle(0)
RollBlind_FabCurtianPull1.set_pos(345, 411)
RollBlind_FabCurtianPull1.set_size(39, 39)
# Set style for RollBlind_FabCurtianPull1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_FabCurtianPull1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianPull1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianPull1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_RollBlindPole
RollBlind_RollBlindPole = lv.img(RollBlind)
RollBlind_RollBlindPole.set_src("B:MicroPython/_RBPole_alpha_462x26.bin")
RollBlind_RollBlindPole.add_flag(lv.obj.FLAG.CLICKABLE)
RollBlind_RollBlindPole.set_pivot(50,50)
RollBlind_RollBlindPole.set_angle(0)
RollBlind_RollBlindPole.set_pos(134, 109)
RollBlind_RollBlindPole.set_size(462, 26)
# Set style for RollBlind_RollBlindPole, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_RollBlindPole.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_RollBlindPole.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_RollBlindPole.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_btn_1
RollBlind_btn_1 = lv.btn(RollBlind)
RollBlind_btn_1_label = lv.label(RollBlind_btn_1)
RollBlind_btn_1_label.set_text("卷  帘")
RollBlind_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
RollBlind_btn_1_label.set_width(lv.pct(100))
RollBlind_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
RollBlind_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
RollBlind_btn_1.set_pos(70, 25)
RollBlind_btn_1.set_size(95, 36)
# Set style for RollBlind_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_img_1
RollBlind_img_1 = lv.img(RollBlind)
RollBlind_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
RollBlind_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
RollBlind_img_1.set_pivot(50,50)
RollBlind_img_1.set_angle(0)
RollBlind_img_1.set_pos(43, 28)
RollBlind_img_1.set_size(14, 24)
# Set style for RollBlind_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_btn_2
RollBlind_btn_2 = lv.btn(RollBlind)
RollBlind_btn_2_label = lv.label(RollBlind_btn_2)
RollBlind_btn_2_label.set_text("")
RollBlind_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
RollBlind_btn_2_label.set_width(lv.pct(100))
RollBlind_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
RollBlind_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
RollBlind_btn_2.set_pos(-5, -7)
RollBlind_btn_2.set_size(230, 102)
# Set style for RollBlind_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RollBlind_FabCurtianPull2
RollBlind_FabCurtianPull2 = lv.btn(RollBlind)
RollBlind_FabCurtianPull2_label = lv.label(RollBlind_FabCurtianPull2)
RollBlind_FabCurtianPull2_label.set_text("")
RollBlind_FabCurtianPull2_label.set_long_mode(lv.label.LONG.WRAP)
RollBlind_FabCurtianPull2_label.set_width(lv.pct(100))
RollBlind_FabCurtianPull2_label.align(lv.ALIGN.CENTER, 0, 0)
RollBlind_FabCurtianPull2.set_style_pad_all(0, lv.STATE.DEFAULT)
RollBlind_FabCurtianPull2.set_pos(142, 394)
RollBlind_FabCurtianPull2.set_size(445, 134)
# Set style for RollBlind_FabCurtianPull2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RollBlind_FabCurtianPull2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianPull2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianPull2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianPull2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianPull2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianPull2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianPull2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RollBlind_FabCurtianPull2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

RollBlind.update_layout()
# Create Dream
Dream = lv.obj()
Dream.set_size(720, 720)
Dream.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Dream, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_tabview_1
Dream_tabview_1 = lv.tabview(Dream, lv.DIR.TOP, 85)
Dream_tabview_1.set_pos(0, 0)
Dream_tabview_1.set_size(720, 720)
Dream_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for Dream_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for Dream_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_Dream_tabview_1_extra_btnm_main_default = lv.style_t()
style_Dream_tabview_1_extra_btnm_main_default.init()
style_Dream_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_Dream_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_Dream_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_Dream_tabview_1_extra_btnm_main_default.set_border_width(0)
style_Dream_tabview_1_extra_btnm_main_default.set_radius(0)
Dream_tabview_1.get_tab_btns().add_style(style_Dream_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for Dream_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_Dream_tabview_1_extra_btnm_items_default = lv.style_t()
style_Dream_tabview_1_extra_btnm_items_default.init()
style_Dream_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_Dream_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_Dream_tabview_1_extra_btnm_items_default.set_text_opa(255)
Dream_tabview_1.get_tab_btns().add_style(style_Dream_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for Dream_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_Dream_tabview_1_extra_btnm_items_checked = lv.style_t()
style_Dream_tabview_1_extra_btnm_items_checked.init()
style_Dream_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_Dream_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_Dream_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_Dream_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_Dream_tabview_1_extra_btnm_items_checked.set_radius(0)
style_Dream_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_Dream_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_Dream_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
Dream_tabview_1.get_tab_btns().add_style(style_Dream_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
Dream_tabview_1_tab_1 = Dream_tabview_1.add_tab("")
Dream_tabview_1_tab_1_label = lv.label(Dream_tabview_1_tab_1)
Dream_tabview_1_tab_1_label.set_text("")

# Create Dream_cont_1
Dream_cont_1 = lv.obj(Dream)
Dream_cont_1.set_pos(0, 85)
Dream_cont_1.set_size(720, 630)
Dream_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Dream_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_1.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_btn_1
Dream_btn_1 = lv.btn(Dream)
Dream_btn_1_label = lv.label(Dream_btn_1)
Dream_btn_1_label.set_text("梦幻帘")
Dream_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
Dream_btn_1_label.set_width(lv.pct(100))
Dream_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
Dream_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
Dream_btn_1.set_pos(70, 25)
Dream_btn_1.set_size(125, 38)
# Set style for Dream_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_FabCurtianOpen
Dream_FabCurtianOpen = lv.img(Dream)
Dream_FabCurtianOpen.set_src("B:MicroPython/_FCOpen_alpha_94x95.bin")
Dream_FabCurtianOpen.add_flag(lv.obj.FLAG.CLICKABLE)
Dream_FabCurtianOpen.set_pivot(50,50)
Dream_FabCurtianOpen.set_angle(0)
Dream_FabCurtianOpen.set_pos(63, 660)
Dream_FabCurtianOpen.set_size(94, 95)
# Set style for Dream_FabCurtianOpen, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_FabCurtianOpen.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianOpen.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianOpen.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_FabCurtianClose
Dream_FabCurtianClose = lv.img(Dream)
Dream_FabCurtianClose.set_src("B:MicroPython/_FCClose_alpha_95x95.bin")
Dream_FabCurtianClose.add_flag(lv.obj.FLAG.CLICKABLE)
Dream_FabCurtianClose.set_pivot(50,50)
Dream_FabCurtianClose.set_angle(0)
Dream_FabCurtianClose.set_pos(560, 660)
Dream_FabCurtianClose.set_size(95, 95)
# Set style for Dream_FabCurtianClose, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_FabCurtianClose.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianClose.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianClose.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_FabCurtianPause
Dream_FabCurtianPause = lv.img(Dream)
Dream_FabCurtianPause.set_src("B:MicroPython/_FCPause_alpha_109x110.bin")
Dream_FabCurtianPause.add_flag(lv.obj.FLAG.CLICKABLE)
Dream_FabCurtianPause.set_pivot(50,50)
Dream_FabCurtianPause.set_angle(0)
Dream_FabCurtianPause.set_pos(311, 660)
Dream_FabCurtianPause.set_size(109, 110)
# Set style for Dream_FabCurtianPause, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_FabCurtianPause.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPause.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPause.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_FabCurtianBg1
Dream_FabCurtianBg1 = lv.img(Dream)
Dream_FabCurtianBg1.set_src("B:MicroPython/_FCBg1_alpha_62x60.bin")
Dream_FabCurtianBg1.add_flag(lv.obj.FLAG.CLICKABLE)
Dream_FabCurtianBg1.set_pivot(50,50)
Dream_FabCurtianBg1.set_angle(0)
Dream_FabCurtianBg1.set_pos(232, 255)
Dream_FabCurtianBg1.set_size(62, 60)
# Set style for Dream_FabCurtianBg1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_FabCurtianBg1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianBg1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianBg1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_FabCurtianBg2
Dream_FabCurtianBg2 = lv.img(Dream)
Dream_FabCurtianBg2.set_src("B:MicroPython/_FCBg2_alpha_34x73.bin")
Dream_FabCurtianBg2.add_flag(lv.obj.FLAG.CLICKABLE)
Dream_FabCurtianBg2.set_pivot(50,50)
Dream_FabCurtianBg2.set_angle(0)
Dream_FabCurtianBg2.set_pos(415, 272)
Dream_FabCurtianBg2.set_size(34, 73)
# Set style for Dream_FabCurtianBg2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_FabCurtianBg2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianBg2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianBg2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_FabCurtianBg3
Dream_FabCurtianBg3 = lv.img(Dream)
Dream_FabCurtianBg3.set_src("B:MicroPython/_FCBg3_alpha_42x14.bin")
Dream_FabCurtianBg3.add_flag(lv.obj.FLAG.CLICKABLE)
Dream_FabCurtianBg3.set_pivot(50,50)
Dream_FabCurtianBg3.set_angle(0)
Dream_FabCurtianBg3.set_pos(252, 384)
Dream_FabCurtianBg3.set_size(42, 14)
# Set style for Dream_FabCurtianBg3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_FabCurtianBg3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianBg3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianBg3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_FabCurtianLeft
Dream_FabCurtianLeft = lv.img(Dream)
Dream_FabCurtianLeft.set_src("B:MicroPython/_DreamLeft_alpha_230x249.bin")
Dream_FabCurtianLeft.add_flag(lv.obj.FLAG.CLICKABLE)
Dream_FabCurtianLeft.set_pivot(50,50)
Dream_FabCurtianLeft.set_angle(0)
Dream_FabCurtianLeft.set_pos(129, 193)
Dream_FabCurtianLeft.set_size(230, 249)
# Set style for Dream_FabCurtianLeft, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_FabCurtianLeft.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianLeft.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianLeft.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_FabCurtianright
Dream_FabCurtianright = lv.img(Dream)
Dream_FabCurtianright.set_src("B:MicroPython/_DreamRight_alpha_230x249.bin")
Dream_FabCurtianright.add_flag(lv.obj.FLAG.CLICKABLE)
Dream_FabCurtianright.set_pivot(50,50)
Dream_FabCurtianright.set_angle(0)
Dream_FabCurtianright.set_pos(359, 193)
Dream_FabCurtianright.set_size(230, 249)
# Set style for Dream_FabCurtianright, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_FabCurtianright.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianright.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianright.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_cont_2
Dream_cont_2 = lv.obj(Dream)
Dream_cont_2.set_pos(-8, 148)
Dream_cont_2.set_size(134, 326)
Dream_cont_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Dream_cont_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_cont_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_2.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_cont_3
Dream_cont_3 = lv.obj(Dream)
Dream_cont_3.set_pos(592, 156)
Dream_cont_3.set_size(140, 326)
Dream_cont_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Dream_cont_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_cont_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_3.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_cont_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_FabCurtianPull2
Dream_FabCurtianPull2 = lv.img(Dream)
Dream_FabCurtianPull2.set_src("B:MicroPython/_FCPull_alpha_45x45.bin")
Dream_FabCurtianPull2.add_flag(lv.obj.FLAG.CLICKABLE)
Dream_FabCurtianPull2.set_pivot(50,50)
Dream_FabCurtianPull2.set_angle(0)
Dream_FabCurtianPull2.set_pos(369, 295)
Dream_FabCurtianPull2.set_size(45, 45)
# Set style for Dream_FabCurtianPull2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_FabCurtianPull2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_FabCurtianPull1
Dream_FabCurtianPull1 = lv.img(Dream)
Dream_FabCurtianPull1.set_src("B:MicroPython/_FCPull_alpha_45x45.bin")
Dream_FabCurtianPull1.add_flag(lv.obj.FLAG.CLICKABLE)
Dream_FabCurtianPull1.set_pivot(50,50)
Dream_FabCurtianPull1.set_angle(0)
Dream_FabCurtianPull1.set_pos(304, 295)
Dream_FabCurtianPull1.set_size(45, 45)
# Set style for Dream_FabCurtianPull1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_FabCurtianPull1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_FabCurtianPole
Dream_FabCurtianPole = lv.img(Dream)
Dream_FabCurtianPole.set_src("B:MicroPython/_FCPole_alpha_494x34.bin")
Dream_FabCurtianPole.add_flag(lv.obj.FLAG.CLICKABLE)
Dream_FabCurtianPole.set_pivot(50,50)
Dream_FabCurtianPole.set_angle(0)
Dream_FabCurtianPole.set_pos(112, 178)
Dream_FabCurtianPole.set_size(494, 34)
# Set style for Dream_FabCurtianPole, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_FabCurtianPole.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPole.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPole.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_slider_1
Dream_slider_1 = lv.slider(Dream)
Dream_slider_1.set_range(0, 100)
Dream_slider_1.set_mode(lv.slider.MODE.NORMAL)
Dream_slider_1.set_value(50, lv.ANIM.OFF)
Dream_slider_1.set_pos(191, 502)
Dream_slider_1.set_size(330, 8)
# Set style for Dream_slider_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_slider_1.set_style_bg_opa(60, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_slider_1.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_slider_1.set_style_radius(8, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_slider_1.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_slider_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for Dream_slider_1, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
Dream_slider_1.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
Dream_slider_1.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.INDICATOR|lv.STATE.DEFAULT)
Dream_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.DEFAULT)
Dream_slider_1.set_style_radius(8, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for Dream_slider_1, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
Dream_slider_1.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
Dream_slider_1.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.KNOB|lv.STATE.DEFAULT)
Dream_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
Dream_slider_1.set_style_radius(8, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create Dream_label_1
Dream_label_1 = lv.label(Dream)
Dream_label_1.set_text("0%")
Dream_label_1.set_long_mode(lv.label.LONG.WRAP)
Dream_label_1.set_width(lv.pct(100))
Dream_label_1.set_pos(307, 455)
Dream_label_1.set_size(73, 31)
# Set style for Dream_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_label_2
Dream_label_2 = lv.label(Dream)
Dream_label_2.set_text("0°")
Dream_label_2.set_long_mode(lv.label.LONG.WRAP)
Dream_label_2.set_width(lv.pct(100))
Dream_label_2.set_pos(183, 527)
Dream_label_2.set_size(73, 31)
# Set style for Dream_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_2.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_label_3
Dream_label_3 = lv.label(Dream)
Dream_label_3.set_text("90°")
Dream_label_3.set_long_mode(lv.label.LONG.WRAP)
Dream_label_3.set_width(lv.pct(100))
Dream_label_3.set_pos(307, 527)
Dream_label_3.set_size(73, 31)
# Set style for Dream_label_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_label_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_3.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_3.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_label_4
Dream_label_4 = lv.label(Dream)
Dream_label_4.set_text("180°")
Dream_label_4.set_long_mode(lv.label.LONG.WRAP)
Dream_label_4.set_width(lv.pct(100))
Dream_label_4.set_pos(461, 527)
Dream_label_4.set_size(73, 31)
# Set style for Dream_label_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_label_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_4.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_4.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_4.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_4.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_4.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_4.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_4.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_label_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_img_1
Dream_img_1 = lv.img(Dream)
Dream_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
Dream_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
Dream_img_1.set_pivot(50,50)
Dream_img_1.set_angle(0)
Dream_img_1.set_pos(43, 28)
Dream_img_1.set_size(14, 24)
# Set style for Dream_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_btn_2
Dream_btn_2 = lv.btn(Dream)
Dream_btn_2_label = lv.label(Dream_btn_2)
Dream_btn_2_label.set_text("")
Dream_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
Dream_btn_2_label.set_width(lv.pct(100))
Dream_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
Dream_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
Dream_btn_2.set_pos(-6, -12)
Dream_btn_2.set_size(238, 101)
# Set style for Dream_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_FabCurtianPull3
Dream_FabCurtianPull3 = lv.btn(Dream)
Dream_FabCurtianPull3_label = lv.label(Dream_FabCurtianPull3)
Dream_FabCurtianPull3_label.set_text("")
Dream_FabCurtianPull3_label.set_long_mode(lv.label.LONG.WRAP)
Dream_FabCurtianPull3_label.set_width(lv.pct(100))
Dream_FabCurtianPull3_label.align(lv.ALIGN.CENTER, 0, 0)
Dream_FabCurtianPull3.set_style_pad_all(0, lv.STATE.DEFAULT)
Dream_FabCurtianPull3.set_pos(290, 205)
Dream_FabCurtianPull3.set_size(65, 254)
# Set style for Dream_FabCurtianPull3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_FabCurtianPull3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Dream_FabCurtianPull4
Dream_FabCurtianPull4 = lv.btn(Dream)
Dream_FabCurtianPull4_label = lv.label(Dream_FabCurtianPull4)
Dream_FabCurtianPull4_label.set_text("")
Dream_FabCurtianPull4_label.set_long_mode(lv.label.LONG.WRAP)
Dream_FabCurtianPull4_label.set_width(lv.pct(100))
Dream_FabCurtianPull4_label.align(lv.ALIGN.CENTER, 0, 0)
Dream_FabCurtianPull4.set_style_pad_all(0, lv.STATE.DEFAULT)
Dream_FabCurtianPull4.set_pos(362, 205)
Dream_FabCurtianPull4.set_size(65, 246)
# Set style for Dream_FabCurtianPull4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Dream_FabCurtianPull4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull4.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Dream_FabCurtianPull4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

Dream.update_layout()
# Create AirCondition
AirCondition = lv.obj()
AirCondition.set_size(720, 720)
AirCondition.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for AirCondition, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_tabview_1
AirCondition_tabview_1 = lv.tabview(AirCondition, lv.DIR.TOP, 85)
AirCondition_tabview_1.set_pos(0, 0)
AirCondition_tabview_1.set_size(720, 720)
AirCondition_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for AirCondition_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for AirCondition_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_AirCondition_tabview_1_extra_btnm_main_default = lv.style_t()
style_AirCondition_tabview_1_extra_btnm_main_default.init()
style_AirCondition_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_AirCondition_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_AirCondition_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_AirCondition_tabview_1_extra_btnm_main_default.set_border_width(0)
style_AirCondition_tabview_1_extra_btnm_main_default.set_radius(0)
AirCondition_tabview_1.get_tab_btns().add_style(style_AirCondition_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for AirCondition_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_AirCondition_tabview_1_extra_btnm_items_default = lv.style_t()
style_AirCondition_tabview_1_extra_btnm_items_default.init()
style_AirCondition_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_AirCondition_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_AirCondition_tabview_1_extra_btnm_items_default.set_text_opa(255)
AirCondition_tabview_1.get_tab_btns().add_style(style_AirCondition_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for AirCondition_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_AirCondition_tabview_1_extra_btnm_items_checked = lv.style_t()
style_AirCondition_tabview_1_extra_btnm_items_checked.init()
style_AirCondition_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_AirCondition_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_AirCondition_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_AirCondition_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_AirCondition_tabview_1_extra_btnm_items_checked.set_radius(0)
style_AirCondition_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_AirCondition_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_AirCondition_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
AirCondition_tabview_1.get_tab_btns().add_style(style_AirCondition_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
AirCondition_tabview_1_tab_1 = AirCondition_tabview_1.add_tab("")
AirCondition_tabview_1_tab_1_label = lv.label(AirCondition_tabview_1_tab_1)
AirCondition_tabview_1_tab_1_label.set_text("")

# Create AirCondition_cont_1
AirCondition_cont_1 = lv.obj(AirCondition)
AirCondition_cont_1.set_pos(0, 85)
AirCondition_cont_1.set_size(720, 630)
AirCondition_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for AirCondition_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_cont_1.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_btn_1
AirCondition_btn_1 = lv.btn(AirCondition)
AirCondition_btn_1_label = lv.label(AirCondition_btn_1)
AirCondition_btn_1_label.set_text("空  调")
AirCondition_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
AirCondition_btn_1_label.set_width(lv.pct(100))
AirCondition_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
AirCondition_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
AirCondition_btn_1.set_pos(71, 25)
AirCondition_btn_1.set_size(92, 32)
# Set style for AirCondition_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_FabCurtianLeft
AirCondition_FabCurtianLeft = lv.img(AirCondition)
AirCondition_FabCurtianLeft.set_src("B:MicroPython/_AirCondiImg_alpha_332x140.bin")
AirCondition_FabCurtianLeft.add_flag(lv.obj.FLAG.CLICKABLE)
AirCondition_FabCurtianLeft.set_pivot(50,50)
AirCondition_FabCurtianLeft.set_angle(0)
AirCondition_FabCurtianLeft.set_pos(201, 138)
AirCondition_FabCurtianLeft.set_size(332, 140)
# Set style for AirCondition_FabCurtianLeft, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_FabCurtianLeft.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_FabCurtianLeft.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_FabCurtianLeft.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_ACBtn
AirCondition_ACBtn = lv.imgbtn(AirCondition)
AirCondition_ACBtn.add_flag(lv.obj.FLAG.CHECKABLE)
AirCondition_ACBtn.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_ACOff_alpha_109x109.bin", None)
AirCondition_ACBtn.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_ACOn_alpha_109x109.bin", None)
AirCondition_ACBtn.add_flag(lv.obj.FLAG.CHECKABLE)
AirCondition_ACBtn_label = lv.label(AirCondition_ACBtn)
AirCondition_ACBtn_label.set_text("")
AirCondition_ACBtn_label.set_long_mode(lv.label.LONG.WRAP)
AirCondition_ACBtn_label.set_width(lv.pct(100))
AirCondition_ACBtn_label.align(lv.ALIGN.CENTER, 0, 0)
AirCondition_ACBtn.set_style_pad_all(0, lv.STATE.DEFAULT)
AirCondition_ACBtn.set_pos(310, 534)
AirCondition_ACBtn.set_size(109, 109)
# Set style for AirCondition_ACBtn, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_ACBtn.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACBtn.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACBtn.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACBtn.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACBtn.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for AirCondition_ACBtn, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
AirCondition_ACBtn.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
AirCondition_ACBtn.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
AirCondition_ACBtn.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
AirCondition_ACBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
AirCondition_ACBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for AirCondition_ACBtn, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
AirCondition_ACBtn.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
AirCondition_ACBtn.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
AirCondition_ACBtn.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
AirCondition_ACBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
AirCondition_ACBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for AirCondition_ACBtn, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
AirCondition_ACBtn.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create AirCondition_ACSpeedAuto
AirCondition_ACSpeedAuto = lv.img(AirCondition)
AirCondition_ACSpeedAuto.set_src("B:MicroPython/_ACSpeedAuto_alpha_109x109.bin")
AirCondition_ACSpeedAuto.add_flag(lv.obj.FLAG.CLICKABLE)
AirCondition_ACSpeedAuto.set_pivot(50,50)
AirCondition_ACSpeedAuto.set_angle(0)
AirCondition_ACSpeedAuto.set_pos(574, 534)
AirCondition_ACSpeedAuto.set_size(109, 109)
# Set style for AirCondition_ACSpeedAuto, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_ACSpeedAuto.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACSpeedAuto.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACSpeedAuto.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_ACSpeed3
AirCondition_ACSpeed3 = lv.img(AirCondition)
AirCondition_ACSpeed3.set_src("B:MicroPython/_ACSpeed3_alpha_109x109.bin")
AirCondition_ACSpeed3.add_flag(lv.obj.FLAG.CLICKABLE)
AirCondition_ACSpeed3.set_pivot(50,50)
AirCondition_ACSpeed3.set_angle(0)
AirCondition_ACSpeed3.set_pos(574, 534)
AirCondition_ACSpeed3.set_size(109, 109)
# Set style for AirCondition_ACSpeed3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_ACSpeed3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACSpeed3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACSpeed3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_ACSpeed2
AirCondition_ACSpeed2 = lv.img(AirCondition)
AirCondition_ACSpeed2.set_src("B:MicroPython/_ACSpeed2_alpha_109x109.bin")
AirCondition_ACSpeed2.add_flag(lv.obj.FLAG.CLICKABLE)
AirCondition_ACSpeed2.set_pivot(50,50)
AirCondition_ACSpeed2.set_angle(0)
AirCondition_ACSpeed2.set_pos(574, 534)
AirCondition_ACSpeed2.set_size(109, 109)
# Set style for AirCondition_ACSpeed2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_ACSpeed2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACSpeed2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACSpeed2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_ACSpeed1
AirCondition_ACSpeed1 = lv.img(AirCondition)
AirCondition_ACSpeed1.set_src("B:MicroPython/_ACSpeed1_alpha_109x109.bin")
AirCondition_ACSpeed1.add_flag(lv.obj.FLAG.CLICKABLE)
AirCondition_ACSpeed1.set_pivot(50,50)
AirCondition_ACSpeed1.set_angle(0)
AirCondition_ACSpeed1.set_pos(574, 534)
AirCondition_ACSpeed1.set_size(109, 109)
# Set style for AirCondition_ACSpeed1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_ACSpeed1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACSpeed1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACSpeed1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_AcCool
AirCondition_AcCool = lv.img(AirCondition)
AirCondition_AcCool.set_src("B:MicroPython/_AcCool_alpha_109x109.bin")
AirCondition_AcCool.add_flag(lv.obj.FLAG.CLICKABLE)
AirCondition_AcCool.set_pivot(50,50)
AirCondition_AcCool.set_angle(0)
AirCondition_AcCool.set_pos(50, 538)
AirCondition_AcCool.set_size(109, 109)
# Set style for AirCondition_AcCool, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_AcCool.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_AcCool.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_AcCool.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_ACFan
AirCondition_ACFan = lv.img(AirCondition)
AirCondition_ACFan.set_src("B:MicroPython/_ACFan_alpha_109x109.bin")
AirCondition_ACFan.add_flag(lv.obj.FLAG.CLICKABLE)
AirCondition_ACFan.set_pivot(50,50)
AirCondition_ACFan.set_angle(0)
AirCondition_ACFan.set_pos(50, 538)
AirCondition_ACFan.set_size(109, 109)
# Set style for AirCondition_ACFan, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_ACFan.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACFan.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACFan.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_ACHot
AirCondition_ACHot = lv.img(AirCondition)
AirCondition_ACHot.set_src("B:MicroPython/_ACHot_alpha_109x109.bin")
AirCondition_ACHot.add_flag(lv.obj.FLAG.CLICKABLE)
AirCondition_ACHot.set_pivot(50,50)
AirCondition_ACHot.set_angle(0)
AirCondition_ACHot.set_pos(50, 538)
AirCondition_ACHot.set_size(109, 109)
# Set style for AirCondition_ACHot, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_ACHot.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACHot.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACHot.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_ACDry
AirCondition_ACDry = lv.img(AirCondition)
AirCondition_ACDry.set_src("B:MicroPython/_ACDry_alpha_109x109.bin")
AirCondition_ACDry.add_flag(lv.obj.FLAG.CLICKABLE)
AirCondition_ACDry.set_pivot(50,50)
AirCondition_ACDry.set_angle(0)
AirCondition_ACDry.set_pos(50, 538)
AirCondition_ACDry.set_size(109, 109)
# Set style for AirCondition_ACDry, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_ACDry.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACDry.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_ACDry.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_AcSpd3
AirCondition_AcSpd3 = lv.img(AirCondition)
AirCondition_AcSpd3.set_src("B:MicroPython/_AcSpd3_alpha_349x94.bin")
AirCondition_AcSpd3.add_flag(lv.obj.FLAG.CLICKABLE)
AirCondition_AcSpd3.set_pivot(50,50)
AirCondition_AcSpd3.set_angle(0)
AirCondition_AcSpd3.set_pos(192, 267)
AirCondition_AcSpd3.set_size(349, 94)
# Set style for AirCondition_AcSpd3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_AcSpd3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_AcSpd3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_AcSpd3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_AcSpd2
AirCondition_AcSpd2 = lv.img(AirCondition)
AirCondition_AcSpd2.set_src("B:MicroPython/_AcSpd2_alpha_349x94.bin")
AirCondition_AcSpd2.add_flag(lv.obj.FLAG.CLICKABLE)
AirCondition_AcSpd2.set_pivot(50,50)
AirCondition_AcSpd2.set_angle(0)
AirCondition_AcSpd2.set_pos(192, 267)
AirCondition_AcSpd2.set_size(349, 94)
# Set style for AirCondition_AcSpd2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_AcSpd2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_AcSpd2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_AcSpd2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_AcSpd1
AirCondition_AcSpd1 = lv.img(AirCondition)
AirCondition_AcSpd1.set_src("B:MicroPython/_AcSpd1_alpha_349x94.bin")
AirCondition_AcSpd1.add_flag(lv.obj.FLAG.CLICKABLE)
AirCondition_AcSpd1.set_pivot(50,50)
AirCondition_AcSpd1.set_angle(0)
AirCondition_AcSpd1.set_pos(192, 267)
AirCondition_AcSpd1.set_size(349, 94)
# Set style for AirCondition_AcSpd1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_AcSpd1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_AcSpd1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_AcSpd1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_img_1
AirCondition_img_1 = lv.img(AirCondition)
AirCondition_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
AirCondition_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
AirCondition_img_1.set_pivot(50,50)
AirCondition_img_1.set_angle(0)
AirCondition_img_1.set_pos(43, 28)
AirCondition_img_1.set_size(14, 24)
# Set style for AirCondition_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create AirCondition_btn_2
AirCondition_btn_2 = lv.btn(AirCondition)
AirCondition_btn_2_label = lv.label(AirCondition_btn_2)
AirCondition_btn_2_label.set_text("")
AirCondition_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
AirCondition_btn_2_label.set_width(lv.pct(100))
AirCondition_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
AirCondition_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
AirCondition_btn_2.set_pos(-8, -10)
AirCondition_btn_2.set_size(241, 103)
# Set style for AirCondition_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
AirCondition_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
AirCondition_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

AirCondition.update_layout()
# Create Music
Music = lv.obj()
Music.set_size(720, 720)
Music.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Music, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Music.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Music.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Music.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Music_tabview_1
Music_tabview_1 = lv.tabview(Music, lv.DIR.TOP, 85)
Music_tabview_1.set_pos(0, 0)
Music_tabview_1.set_size(720, 720)
Music_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for Music_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Music_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Music_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
Music_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
Music_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for Music_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_Music_tabview_1_extra_btnm_main_default = lv.style_t()
style_Music_tabview_1_extra_btnm_main_default.init()
style_Music_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_Music_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_Music_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_Music_tabview_1_extra_btnm_main_default.set_border_width(0)
style_Music_tabview_1_extra_btnm_main_default.set_radius(0)
Music_tabview_1.get_tab_btns().add_style(style_Music_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for Music_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_Music_tabview_1_extra_btnm_items_default = lv.style_t()
style_Music_tabview_1_extra_btnm_items_default.init()
style_Music_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_Music_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_Music_tabview_1_extra_btnm_items_default.set_text_opa(255)
Music_tabview_1.get_tab_btns().add_style(style_Music_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for Music_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_Music_tabview_1_extra_btnm_items_checked = lv.style_t()
style_Music_tabview_1_extra_btnm_items_checked.init()
style_Music_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_Music_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_Music_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_Music_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_Music_tabview_1_extra_btnm_items_checked.set_radius(0)
style_Music_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_Music_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_Music_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
Music_tabview_1.get_tab_btns().add_style(style_Music_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
Music_tabview_1_tab_1 = Music_tabview_1.add_tab("")
Music_tabview_1_tab_1_label = lv.label(Music_tabview_1_tab_1)
Music_tabview_1_tab_1_label.set_text("")

# Create Music_cont_1
Music_cont_1 = lv.obj(Music)
Music_cont_1.set_pos(0, 85)
Music_cont_1.set_size(720, 630)
Music_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Music_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Music_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_cont_1.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Music_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Music_btn_1
Music_btn_1 = lv.btn(Music)
Music_btn_1_label = lv.label(Music_btn_1)
Music_btn_1_label.set_text("音  乐")
Music_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
Music_btn_1_label.set_width(lv.pct(100))
Music_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
Music_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
Music_btn_1.set_pos(70, 25)
Music_btn_1.set_size(102, 32)
# Set style for Music_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Music_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Music_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
Music_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Music_prev
Music_prev = lv.img(Music)
Music_prev.set_src("B:MicroPython/_prev_alpha_94x94.bin")
Music_prev.add_flag(lv.obj.FLAG.CLICKABLE)
Music_prev.set_pivot(50,50)
Music_prev.set_angle(0)
Music_prev.set_pos(66, 554)
Music_prev.set_size(94, 94)
# Set style for Music_prev, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Music_prev.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_prev.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_prev.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Music_next
Music_next = lv.img(Music)
Music_next.set_src("B:MicroPython/_next_alpha_94x94.bin")
Music_next.add_flag(lv.obj.FLAG.CLICKABLE)
Music_next.set_pivot(50,50)
Music_next.set_angle(0)
Music_next.set_pos(557, 553)
Music_next.set_size(94, 94)
# Set style for Music_next, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Music_next.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_next.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_next.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Music_volume_dec
Music_volume_dec = lv.img(Music)
Music_volume_dec.set_src("B:MicroPython/_volume_dec_alpha_94x94.bin")
Music_volume_dec.add_flag(lv.obj.FLAG.CLICKABLE)
Music_volume_dec.set_pivot(50,50)
Music_volume_dec.set_angle(0)
Music_volume_dec.set_pos(582, 316)
Music_volume_dec.set_size(94, 94)
# Set style for Music_volume_dec, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Music_volume_dec.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_volume_dec.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_volume_dec.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Music_disc
Music_disc = lv.img(Music)
Music_disc.set_src("B:MicroPython/_disc_alpha_245x245.bin")
Music_disc.add_flag(lv.obj.FLAG.CLICKABLE)
Music_disc.set_pivot(122,122)
Music_disc.set_angle(0)
Music_disc.set_pos(227, 247)
Music_disc.set_size(245, 245)
# Set style for Music_disc, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Music_disc.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_disc.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_disc.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Music_volume_add
Music_volume_add = lv.img(Music)
Music_volume_add.set_src("B:MicroPython/_volume_add_alpha_94x94.bin")
Music_volume_add.add_flag(lv.obj.FLAG.CLICKABLE)
Music_volume_add.set_pivot(50,50)
Music_volume_add.set_angle(0)
Music_volume_add.set_pos(578, 123)
Music_volume_add.set_size(94, 94)
# Set style for Music_volume_add, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Music_volume_add.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_volume_add.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_volume_add.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Music_play
Music_play = lv.imgbtn(Music)
Music_play.add_flag(lv.obj.FLAG.CHECKABLE)
Music_play.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_play_alpha_109x109.bin", None)
Music_play.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_pause_alpha_109x109.bin", None)
Music_play.add_flag(lv.obj.FLAG.CHECKABLE)
Music_play_label = lv.label(Music_play)
Music_play_label.set_text("")
Music_play_label.set_long_mode(lv.label.LONG.WRAP)
Music_play_label.set_width(lv.pct(100))
Music_play_label.align(lv.ALIGN.CENTER, 0, 0)
Music_play.set_style_pad_all(0, lv.STATE.DEFAULT)
Music_play.set_pos(304, 546)
Music_play.set_size(109, 109)
# Set style for Music_play, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Music_play.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Music_play.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
Music_play.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_play.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_play.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_play.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_play.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for Music_play, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
Music_play.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
Music_play.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
Music_play.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
Music_play.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
Music_play.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for Music_play, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
Music_play.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
Music_play.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
Music_play.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
Music_play.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
Music_play.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for Music_play, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
Music_play.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create Music_rack
Music_rack = lv.img(Music)
Music_rack.set_src("B:MicroPython/_rack_alpha_124x195.bin")
Music_rack.add_flag(lv.obj.FLAG.CLICKABLE)
Music_rack.set_pivot(80,40)
Music_rack.set_angle(0)
Music_rack.set_pos(405, 128)
Music_rack.set_size(124, 195)
# Set style for Music_rack, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Music_rack.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_rack.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_rack.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Music_img_1
Music_img_1 = lv.img(Music)
Music_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
Music_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
Music_img_1.set_pivot(50,50)
Music_img_1.set_angle(0)
Music_img_1.set_pos(43, 28)
Music_img_1.set_size(14, 24)
# Set style for Music_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Music_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Music_btn_2
Music_btn_2 = lv.btn(Music)
Music_btn_2_label = lv.label(Music_btn_2)
Music_btn_2_label.set_text("")
Music_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
Music_btn_2_label.set_width(lv.pct(100))
Music_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
Music_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
Music_btn_2.set_pos(-6, -9)
Music_btn_2.set_size(229, 107)
# Set style for Music_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Music_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Music_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Music_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Music_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

Music.update_layout()
# Create DryRack
DryRack = lv.obj()
DryRack.set_size(720, 720)
DryRack.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for DryRack, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create DryRack_tabview_1
DryRack_tabview_1 = lv.tabview(DryRack, lv.DIR.TOP, 70)
DryRack_tabview_1.set_pos(0, 0)
DryRack_tabview_1.set_size(720, 720)
DryRack_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for DryRack_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for DryRack_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_DryRack_tabview_1_extra_btnm_main_default = lv.style_t()
style_DryRack_tabview_1_extra_btnm_main_default.init()
style_DryRack_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_DryRack_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x4f3f3f))
style_DryRack_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_DryRack_tabview_1_extra_btnm_main_default.set_border_width(0)
style_DryRack_tabview_1_extra_btnm_main_default.set_radius(0)
DryRack_tabview_1.get_tab_btns().add_style(style_DryRack_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for DryRack_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_DryRack_tabview_1_extra_btnm_items_default = lv.style_t()
style_DryRack_tabview_1_extra_btnm_items_default.init()
style_DryRack_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_DryRack_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_DryRack_tabview_1_extra_btnm_items_default.set_text_opa(255)
DryRack_tabview_1.get_tab_btns().add_style(style_DryRack_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for DryRack_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_DryRack_tabview_1_extra_btnm_items_checked = lv.style_t()
style_DryRack_tabview_1_extra_btnm_items_checked.init()
style_DryRack_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_DryRack_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_DryRack_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_DryRack_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_DryRack_tabview_1_extra_btnm_items_checked.set_radius(0)
style_DryRack_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_DryRack_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_DryRack_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
DryRack_tabview_1.get_tab_btns().add_style(style_DryRack_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
DryRack_tabview_1_tab_1 = DryRack_tabview_1.add_tab("")
DryRack_tabview_1_tab_1_label = lv.label(DryRack_tabview_1_tab_1)
DryRack_tabview_1_tab_1_label.set_text("")

# Create DryRack_cont_1
DryRack_cont_1 = lv.obj(DryRack)
DryRack_cont_1.set_pos(0, 85)
DryRack_cont_1.set_size(720, 630)
DryRack_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for DryRack_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_1.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create DryRack_FabCurtianOpen
DryRack_FabCurtianOpen = lv.img(DryRack)
DryRack_FabCurtianOpen.set_src("B:MicroPython/_RollBlindUp_alpha_94x95.bin")
DryRack_FabCurtianOpen.add_flag(lv.obj.FLAG.CLICKABLE)
DryRack_FabCurtianOpen.set_pivot(50,50)
DryRack_FabCurtianOpen.set_angle(0)
DryRack_FabCurtianOpen.set_pos(61, 665)
DryRack_FabCurtianOpen.set_size(94, 95)
# Set style for DryRack_FabCurtianOpen, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_FabCurtianOpen.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_FabCurtianOpen.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_FabCurtianOpen.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create DryRack_FabCurtianClose
DryRack_FabCurtianClose = lv.img(DryRack)
DryRack_FabCurtianClose.set_src("B:MicroPython/_RBDown_alpha_94x95.bin")
DryRack_FabCurtianClose.add_flag(lv.obj.FLAG.CLICKABLE)
DryRack_FabCurtianClose.set_pivot(50,50)
DryRack_FabCurtianClose.set_angle(0)
DryRack_FabCurtianClose.set_pos(558, 665)
DryRack_FabCurtianClose.set_size(94, 95)
# Set style for DryRack_FabCurtianClose, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_FabCurtianClose.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_FabCurtianClose.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_FabCurtianClose.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create DryRack_FabCurtianPause
DryRack_FabCurtianPause = lv.img(DryRack)
DryRack_FabCurtianPause.set_src("B:MicroPython/_DRPause_alpha_109x109.bin")
DryRack_FabCurtianPause.add_flag(lv.obj.FLAG.CLICKABLE)
DryRack_FabCurtianPause.set_pivot(50,50)
DryRack_FabCurtianPause.set_angle(0)
DryRack_FabCurtianPause.set_pos(302, 651)
DryRack_FabCurtianPause.set_size(109, 109)
# Set style for DryRack_FabCurtianPause, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_FabCurtianPause.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_FabCurtianPause.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_FabCurtianPause.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create DryRack_img_1
DryRack_img_1 = lv.img(DryRack)
DryRack_img_1.set_src("B:MicroPython/_DryRackPole_alpha_405x319.bin")
DryRack_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
DryRack_img_1.set_pivot(50,50)
DryRack_img_1.set_angle(0)
DryRack_img_1.set_pos(162, -110)
DryRack_img_1.set_size(405, 319)
# Set style for DryRack_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create DryRack_DRLightImg
DryRack_DRLightImg = lv.img(DryRack)
DryRack_DRLightImg.set_src("B:MicroPython/_DryRackL_alpha_163x30.bin")
DryRack_DRLightImg.add_flag(lv.obj.FLAG.CLICKABLE)
DryRack_DRLightImg.set_pivot(50,50)
DryRack_DRLightImg.set_angle(0)
DryRack_DRLightImg.set_pos(284, 154)
DryRack_DRLightImg.set_size(163, 30)
# Set style for DryRack_DRLightImg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_DRLightImg.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_DRLightImg.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_DRLightImg.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create DryRack_RollBlindPole
DryRack_RollBlindPole = lv.img(DryRack)
DryRack_RollBlindPole.set_src("B:MicroPython/_DryRackTop_alpha_272x26.bin")
DryRack_RollBlindPole.add_flag(lv.obj.FLAG.CLICKABLE)
DryRack_RollBlindPole.set_pivot(50,50)
DryRack_RollBlindPole.set_angle(0)
DryRack_RollBlindPole.set_pos(230, 146)
DryRack_RollBlindPole.set_size(272, 26)
# Set style for DryRack_RollBlindPole, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_RollBlindPole.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_RollBlindPole.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_RollBlindPole.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create DryRack_cont_2
DryRack_cont_2 = lv.obj(DryRack)
DryRack_cont_2.set_pos(0, 64)
DryRack_cont_2.set_size(720, 82)
DryRack_cont_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for DryRack_cont_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_cont_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_2.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create DryRack_cont_3
DryRack_cont_3 = lv.obj(DryRack)
DryRack_cont_3.set_pos(0, -5)
DryRack_cont_3.set_size(720, 90)
DryRack_cont_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for DryRack_cont_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_cont_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_3.set_style_bg_color(lv.color_hex(0x243241), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_cont_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create DryRack_imgbtn_1
DryRack_imgbtn_1 = lv.imgbtn(DryRack)
DryRack_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
DryRack_imgbtn_1.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_DRLightOff_alpha_109x109.bin", None)
DryRack_imgbtn_1.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_DRLightOn_alpha_109x109.bin", None)
DryRack_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
DryRack_imgbtn_1_label = lv.label(DryRack_imgbtn_1)
DryRack_imgbtn_1_label.set_text("")
DryRack_imgbtn_1_label.set_long_mode(lv.label.LONG.WRAP)
DryRack_imgbtn_1_label.set_width(lv.pct(100))
DryRack_imgbtn_1_label.align(lv.ALIGN.CENTER, 0, 0)
DryRack_imgbtn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
DryRack_imgbtn_1.set_pos(29, 97)
DryRack_imgbtn_1.set_size(109, 109)
# Set style for DryRack_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_imgbtn_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_imgbtn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_imgbtn_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_imgbtn_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for DryRack_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
DryRack_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
DryRack_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
DryRack_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
DryRack_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
DryRack_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for DryRack_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
DryRack_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
DryRack_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
DryRack_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
DryRack_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
DryRack_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for DryRack_imgbtn_1, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
DryRack_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create DryRack_btn_1
DryRack_btn_1 = lv.btn(DryRack)
DryRack_btn_1_label = lv.label(DryRack_btn_1)
DryRack_btn_1_label.set_text("晾衣机")
DryRack_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
DryRack_btn_1_label.set_width(lv.pct(100))
DryRack_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
DryRack_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
DryRack_btn_1.set_pos(70, 25)
DryRack_btn_1.set_size(123, 36)
# Set style for DryRack_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create DryRack_label_1
DryRack_label_1 = lv.label(DryRack)
DryRack_label_1.set_text("100%")
DryRack_label_1.set_long_mode(lv.label.LONG.WRAP)
DryRack_label_1.set_width(lv.pct(100))
DryRack_label_1.set_pos(314, 230)
DryRack_label_1.set_size(100, 32)
# Set style for DryRack_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_label_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create DryRack_img_2
DryRack_img_2 = lv.img(DryRack)
DryRack_img_2.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
DryRack_img_2.add_flag(lv.obj.FLAG.CLICKABLE)
DryRack_img_2.set_pivot(50,50)
DryRack_img_2.set_angle(0)
DryRack_img_2.set_pos(43, 28)
DryRack_img_2.set_size(14, 24)
# Set style for DryRack_img_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_img_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_img_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_img_2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create DryRack_btn_2
DryRack_btn_2 = lv.btn(DryRack)
DryRack_btn_2_label = lv.label(DryRack_btn_2)
DryRack_btn_2_label.set_text("")
DryRack_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
DryRack_btn_2_label.set_width(lv.pct(100))
DryRack_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
DryRack_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
DryRack_btn_2.set_pos(-5, -15)
DryRack_btn_2.set_size(234, 103)
# Set style for DryRack_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create DryRack_dry_rack_pull
DryRack_dry_rack_pull = lv.btn(DryRack)
DryRack_dry_rack_pull_label = lv.label(DryRack_dry_rack_pull)
DryRack_dry_rack_pull_label.set_text("")
DryRack_dry_rack_pull_label.set_long_mode(lv.label.LONG.WRAP)
DryRack_dry_rack_pull_label.set_width(lv.pct(100))
DryRack_dry_rack_pull_label.align(lv.ALIGN.CENTER, 0, 0)
DryRack_dry_rack_pull.set_style_pad_all(0, lv.STATE.DEFAULT)
DryRack_dry_rack_pull.set_pos(145, 176)
DryRack_dry_rack_pull.set_size(445, 82)
# Set style for DryRack_dry_rack_pull, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
DryRack_dry_rack_pull.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_dry_rack_pull.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_dry_rack_pull.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_dry_rack_pull.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_dry_rack_pull.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_dry_rack_pull.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_dry_rack_pull.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_dry_rack_pull.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_dry_rack_pull.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_dry_rack_pull.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
DryRack_dry_rack_pull.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

DryRack.update_layout()
# Create FanAndLight
FanAndLight = lv.obj()
FanAndLight.set_size(720, 720)
FanAndLight.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for FanAndLight, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_tabview_1
FanAndLight_tabview_1 = lv.tabview(FanAndLight, lv.DIR.TOP, 85)
FanAndLight_tabview_1.set_pos(0, 0)
FanAndLight_tabview_1.set_size(720, 720)
FanAndLight_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for FanAndLight_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for FanAndLight_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_FanAndLight_tabview_1_extra_btnm_main_default = lv.style_t()
style_FanAndLight_tabview_1_extra_btnm_main_default.init()
style_FanAndLight_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_FanAndLight_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_FanAndLight_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_FanAndLight_tabview_1_extra_btnm_main_default.set_border_width(0)
style_FanAndLight_tabview_1_extra_btnm_main_default.set_radius(0)
FanAndLight_tabview_1.get_tab_btns().add_style(style_FanAndLight_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for FanAndLight_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_FanAndLight_tabview_1_extra_btnm_items_default = lv.style_t()
style_FanAndLight_tabview_1_extra_btnm_items_default.init()
style_FanAndLight_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_FanAndLight_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_FanAndLight_tabview_1_extra_btnm_items_default.set_text_opa(255)
FanAndLight_tabview_1.get_tab_btns().add_style(style_FanAndLight_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for FanAndLight_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_FanAndLight_tabview_1_extra_btnm_items_checked = lv.style_t()
style_FanAndLight_tabview_1_extra_btnm_items_checked.init()
style_FanAndLight_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_FanAndLight_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_FanAndLight_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_FanAndLight_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_FanAndLight_tabview_1_extra_btnm_items_checked.set_radius(0)
style_FanAndLight_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_FanAndLight_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_FanAndLight_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
FanAndLight_tabview_1.get_tab_btns().add_style(style_FanAndLight_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
FanAndLight_tabview_1_tab_1 = FanAndLight_tabview_1.add_tab("")
FanAndLight_tabview_1_tab_1_label = lv.label(FanAndLight_tabview_1_tab_1)
FanAndLight_tabview_1_tab_1_label.set_text("")

# Create FanAndLight_cont_1
FanAndLight_cont_1 = lv.obj(FanAndLight)
FanAndLight_cont_1.set_pos(0, 85)
FanAndLight_cont_1.set_size(720, 630)
FanAndLight_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for FanAndLight_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_cont_1.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_fLight_off
FanAndLight_fLight_off = lv.img(FanAndLight)
FanAndLight_fLight_off.set_src("B:MicroPython/_DRLightOff_alpha_109x109.bin")
FanAndLight_fLight_off.add_flag(lv.obj.FLAG.CLICKABLE)
FanAndLight_fLight_off.set_pivot(50,50)
FanAndLight_fLight_off.set_angle(0)
FanAndLight_fLight_off.set_pos(51, 552)
FanAndLight_fLight_off.set_size(109, 109)
# Set style for FanAndLight_fLight_off, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_fLight_off.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_fLight_off.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_fLight_off.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_fLight_on
FanAndLight_fLight_on = lv.img(FanAndLight)
FanAndLight_fLight_on.set_src("B:MicroPython/_DRLightOn_alpha_109x110.bin")
FanAndLight_fLight_on.add_flag(lv.obj.FLAG.CLICKABLE)
FanAndLight_fLight_on.set_pivot(50,50)
FanAndLight_fLight_on.set_angle(0)
FanAndLight_fLight_on.set_pos(51, 552)
FanAndLight_fLight_on.set_size(109, 110)
# Set style for FanAndLight_fLight_on, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_fLight_on.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_fLight_on.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_fLight_on.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_fan
FanAndLight_fan = lv.img(FanAndLight)
FanAndLight_fan.set_src("B:MicroPython/_fan_alpha_206x204.bin")
FanAndLight_fan.add_flag(lv.obj.FLAG.CLICKABLE)
FanAndLight_fan.set_pivot(103,102)
FanAndLight_fan.set_angle(0)
FanAndLight_fan.set_pos(257, 210)
FanAndLight_fan.set_size(206, 204)
# Set style for FanAndLight_fan, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_fan.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_fan.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_fan.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_FanSpeed4
FanAndLight_FanSpeed4 = lv.img(FanAndLight)
FanAndLight_FanSpeed4.set_src("B:MicroPython/_ACSpeed4_alpha_109x109.bin")
FanAndLight_FanSpeed4.add_flag(lv.obj.FLAG.CLICKABLE)
FanAndLight_FanSpeed4.set_pivot(50,50)
FanAndLight_FanSpeed4.set_angle(0)
FanAndLight_FanSpeed4.set_pos(536, 552)
FanAndLight_FanSpeed4.set_size(109, 109)
# Set style for FanAndLight_FanSpeed4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_FanSpeed4.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_FanSpeed4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_FanSpeed4.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_FanSpeed3
FanAndLight_FanSpeed3 = lv.img(FanAndLight)
FanAndLight_FanSpeed3.set_src("B:MicroPython/_ACSpeed3_alpha_109x109.bin")
FanAndLight_FanSpeed3.add_flag(lv.obj.FLAG.CLICKABLE)
FanAndLight_FanSpeed3.set_pivot(50,50)
FanAndLight_FanSpeed3.set_angle(0)
FanAndLight_FanSpeed3.set_pos(536, 552)
FanAndLight_FanSpeed3.set_size(109, 109)
# Set style for FanAndLight_FanSpeed3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_FanSpeed3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_FanSpeed3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_FanSpeed3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_FanSpeed2
FanAndLight_FanSpeed2 = lv.img(FanAndLight)
FanAndLight_FanSpeed2.set_src("B:MicroPython/_ACSpeed2_alpha_109x109.bin")
FanAndLight_FanSpeed2.add_flag(lv.obj.FLAG.CLICKABLE)
FanAndLight_FanSpeed2.set_pivot(50,50)
FanAndLight_FanSpeed2.set_angle(0)
FanAndLight_FanSpeed2.set_pos(536, 552)
FanAndLight_FanSpeed2.set_size(109, 109)
# Set style for FanAndLight_FanSpeed2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_FanSpeed2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_FanSpeed2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_FanSpeed2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_FanSpeed1
FanAndLight_FanSpeed1 = lv.img(FanAndLight)
FanAndLight_FanSpeed1.set_src("B:MicroPython/_ACSpeed1_alpha_109x109.bin")
FanAndLight_FanSpeed1.add_flag(lv.obj.FLAG.CLICKABLE)
FanAndLight_FanSpeed1.set_pivot(50,50)
FanAndLight_FanSpeed1.set_angle(0)
FanAndLight_FanSpeed1.set_pos(536, 552)
FanAndLight_FanSpeed1.set_size(109, 109)
# Set style for FanAndLight_FanSpeed1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_FanSpeed1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_FanSpeed1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_FanSpeed1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_Fan_on
FanAndLight_Fan_on = lv.img(FanAndLight)
FanAndLight_Fan_on.set_src("B:MicroPython/_fanon_alpha_109x109.bin")
FanAndLight_Fan_on.add_flag(lv.obj.FLAG.CLICKABLE)
FanAndLight_Fan_on.set_pivot(50,50)
FanAndLight_Fan_on.set_angle(0)
FanAndLight_Fan_on.set_pos(296, 552)
FanAndLight_Fan_on.set_size(109, 109)
# Set style for FanAndLight_Fan_on, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_Fan_on.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_Fan_on.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_Fan_on.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_Fan_off
FanAndLight_Fan_off = lv.img(FanAndLight)
FanAndLight_Fan_off.set_src("B:MicroPython/_fanoff_alpha_109x109.bin")
FanAndLight_Fan_off.add_flag(lv.obj.FLAG.CLICKABLE)
FanAndLight_Fan_off.set_pivot(50,50)
FanAndLight_Fan_off.set_angle(0)
FanAndLight_Fan_off.set_pos(296, 552)
FanAndLight_Fan_off.set_size(109, 109)
# Set style for FanAndLight_Fan_off, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_Fan_off.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_Fan_off.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_Fan_off.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_FLightOnImg
FanAndLight_FLightOnImg = lv.img(FanAndLight)
FanAndLight_FLightOnImg.set_src("B:MicroPython/_lightOn_alpha_82x82.bin")
FanAndLight_FLightOnImg.add_flag(lv.obj.FLAG.CLICKABLE)
FanAndLight_FLightOnImg.set_pivot(50,50)
FanAndLight_FLightOnImg.set_angle(0)
FanAndLight_FLightOnImg.set_pos(320, 277)
FanAndLight_FLightOnImg.set_size(82, 82)
# Set style for FanAndLight_FLightOnImg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_FLightOnImg.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_FLightOnImg.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_FLightOnImg.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_FLightOffImg
FanAndLight_FLightOffImg = lv.img(FanAndLight)
FanAndLight_FLightOffImg.set_src("B:MicroPython/_lightOff_alpha_82x82.bin")
FanAndLight_FLightOffImg.add_flag(lv.obj.FLAG.CLICKABLE)
FanAndLight_FLightOffImg.set_pivot(50,50)
FanAndLight_FLightOffImg.set_angle(0)
FanAndLight_FLightOffImg.set_pos(320, 277)
FanAndLight_FLightOffImg.set_size(82, 82)
# Set style for FanAndLight_FLightOffImg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_FLightOffImg.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_FLightOffImg.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_FLightOffImg.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_btn_1
FanAndLight_btn_1 = lv.btn(FanAndLight)
FanAndLight_btn_1_label = lv.label(FanAndLight_btn_1)
FanAndLight_btn_1_label.set_text("风扇灯")
FanAndLight_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
FanAndLight_btn_1_label.set_width(lv.pct(100))
FanAndLight_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
FanAndLight_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
FanAndLight_btn_1.set_pos(70, 25)
FanAndLight_btn_1.set_size(124, 32)
# Set style for FanAndLight_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_imgbtn_1
FanAndLight_imgbtn_1 = lv.imgbtn(FanAndLight)
FanAndLight_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
FanAndLight_imgbtn_1.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_ACOff_alpha_100x96.bin", None)
FanAndLight_imgbtn_1.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_ACOn_alpha_100x96.bin", None)
FanAndLight_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
FanAndLight_imgbtn_1_label = lv.label(FanAndLight_imgbtn_1)
FanAndLight_imgbtn_1_label.set_text("")
FanAndLight_imgbtn_1_label.set_long_mode(lv.label.LONG.WRAP)
FanAndLight_imgbtn_1_label.set_width(lv.pct(100))
FanAndLight_imgbtn_1_label.align(lv.ALIGN.CENTER, 0, 0)
FanAndLight_imgbtn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
FanAndLight_imgbtn_1.set_pos(40, 120)
FanAndLight_imgbtn_1.set_size(100, 96)
# Set style for FanAndLight_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_imgbtn_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_imgbtn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_imgbtn_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_imgbtn_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for FanAndLight_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
FanAndLight_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
FanAndLight_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
FanAndLight_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
FanAndLight_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
FanAndLight_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for FanAndLight_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
FanAndLight_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
FanAndLight_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
FanAndLight_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
FanAndLight_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
FanAndLight_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for FanAndLight_imgbtn_1, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
FanAndLight_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create FanAndLight_img_1
FanAndLight_img_1 = lv.img(FanAndLight)
FanAndLight_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
FanAndLight_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
FanAndLight_img_1.set_pivot(50,50)
FanAndLight_img_1.set_angle(0)
FanAndLight_img_1.set_pos(43, 28)
FanAndLight_img_1.set_size(14, 24)
# Set style for FanAndLight_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create FanAndLight_btn_2
FanAndLight_btn_2 = lv.btn(FanAndLight)
FanAndLight_btn_2_label = lv.label(FanAndLight_btn_2)
FanAndLight_btn_2_label.set_text("")
FanAndLight_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
FanAndLight_btn_2_label.set_width(lv.pct(100))
FanAndLight_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
FanAndLight_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
FanAndLight_btn_2.set_pos(-5, -7)
FanAndLight_btn_2.set_size(238, 101)
# Set style for FanAndLight_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
FanAndLight_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
FanAndLight_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

FanAndLight.update_layout()
# Create Heater
Heater = lv.obj()
Heater.set_size(720, 720)
Heater.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Heater, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_tabview_1
Heater_tabview_1 = lv.tabview(Heater, lv.DIR.TOP, 85)
Heater_tabview_1.set_pos(-1, 0)
Heater_tabview_1.set_size(720, 720)
Heater_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for Heater_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for Heater_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_Heater_tabview_1_extra_btnm_main_default = lv.style_t()
style_Heater_tabview_1_extra_btnm_main_default.init()
style_Heater_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_Heater_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_Heater_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_Heater_tabview_1_extra_btnm_main_default.set_border_width(0)
style_Heater_tabview_1_extra_btnm_main_default.set_radius(0)
Heater_tabview_1.get_tab_btns().add_style(style_Heater_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for Heater_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_Heater_tabview_1_extra_btnm_items_default = lv.style_t()
style_Heater_tabview_1_extra_btnm_items_default.init()
style_Heater_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_Heater_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_Heater_tabview_1_extra_btnm_items_default.set_text_opa(255)
Heater_tabview_1.get_tab_btns().add_style(style_Heater_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for Heater_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_Heater_tabview_1_extra_btnm_items_checked = lv.style_t()
style_Heater_tabview_1_extra_btnm_items_checked.init()
style_Heater_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_Heater_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_Heater_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_Heater_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_Heater_tabview_1_extra_btnm_items_checked.set_radius(0)
style_Heater_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_Heater_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_Heater_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
Heater_tabview_1.get_tab_btns().add_style(style_Heater_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
Heater_tabview_1_tab_1 = Heater_tabview_1.add_tab("")
Heater_tabview_1_tab_1_label = lv.label(Heater_tabview_1_tab_1)
Heater_tabview_1_tab_1_label.set_text("")

# Create Heater_btn_1
Heater_btn_1 = lv.btn(Heater)
Heater_btn_1_label = lv.label(Heater_btn_1)
Heater_btn_1_label.set_text("浴  霸")
Heater_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
Heater_btn_1_label.set_width(lv.pct(100))
Heater_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
Heater_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
Heater_btn_1.set_pos(70, 25)
Heater_btn_1.set_size(93, 33)
# Set style for Heater_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_HeatLight
Heater_HeatLight = lv.img(Heater)
Heater_HeatLight.set_src("B:MicroPython/_light_on_alpha_295x164.bin")
Heater_HeatLight.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_HeatLight.set_pivot(50,50)
Heater_HeatLight.set_angle(0)
Heater_HeatLight.set_pos(213, 182)
Heater_HeatLight.set_size(295, 164)
# Set style for Heater_HeatLight, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_HeatLight.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatLight.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatLight.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_HeatDev
Heater_HeatDev = lv.img(Heater)
Heater_HeatDev.set_src("B:MicroPython/_dev_alpha_295x164.bin")
Heater_HeatDev.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_HeatDev.set_pivot(50,50)
Heater_HeatDev.set_angle(0)
Heater_HeatDev.set_pos(213, 182)
Heater_HeatDev.set_size(295, 164)
# Set style for Heater_HeatDev, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_HeatDev.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatDev.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatDev.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_LightBtn
Heater_LightBtn = lv.btn(Heater)
Heater_LightBtn_label = lv.label(Heater_LightBtn)
Heater_LightBtn_label.set_text("")
Heater_LightBtn_label.set_long_mode(lv.label.LONG.WRAP)
Heater_LightBtn_label.set_width(lv.pct(100))
Heater_LightBtn_label.align(lv.ALIGN.CENTER, 0, 0)
Heater_LightBtn.set_style_pad_all(0, lv.STATE.DEFAULT)
Heater_LightBtn.set_pos(40, 569)
Heater_LightBtn.set_size(310, 76)
# Set style for Heater_LightBtn, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_LightBtn.set_style_bg_opa(244, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_LightBtn.set_style_bg_color(lv.color_hex(0x2f2d31), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_LightBtn.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_LightBtn.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_LightBtn.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_LightBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_LightBtn.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_LightBtn.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_LightBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_LightBtn.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_LightOffImg
Heater_LightOffImg = lv.img(Heater)
Heater_LightOffImg.set_src("B:MicroPython/_lightOffBtn_alpha_50x67.bin")
Heater_LightOffImg.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_LightOffImg.set_pivot(50,50)
Heater_LightOffImg.set_angle(0)
Heater_LightOffImg.set_pos(174, 575)
Heater_LightOffImg.set_size(50, 67)
# Set style for Heater_LightOffImg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_LightOffImg.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_LightOffImg.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_LightOffImg.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_LightOnImg
Heater_LightOnImg = lv.img(Heater)
Heater_LightOnImg.set_src("B:MicroPython/_lightOnBtn_alpha_50x67.bin")
Heater_LightOnImg.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_LightOnImg.set_pivot(50,50)
Heater_LightOnImg.set_angle(0)
Heater_LightOnImg.set_pos(174, 575)
Heater_LightOnImg.set_size(50, 67)
# Set style for Heater_LightOnImg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_LightOnImg.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_LightOnImg.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_LightOnImg.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_IdleBtn
Heater_IdleBtn = lv.btn(Heater)
Heater_IdleBtn_label = lv.label(Heater_IdleBtn)
Heater_IdleBtn_label.set_text("")
Heater_IdleBtn_label.set_long_mode(lv.label.LONG.WRAP)
Heater_IdleBtn_label.set_width(lv.pct(100))
Heater_IdleBtn_label.align(lv.ALIGN.CENTER, 0, 0)
Heater_IdleBtn.set_style_pad_all(0, lv.STATE.DEFAULT)
Heater_IdleBtn.set_pos(370, 569)
Heater_IdleBtn.set_size(310, 76)
# Set style for Heater_IdleBtn, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_IdleBtn.set_style_bg_opa(244, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_IdleBtn.set_style_bg_color(lv.color_hex(0x2f2d31), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_IdleBtn.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_IdleBtn.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_IdleBtn.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_IdleBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_IdleBtn.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_IdleBtn.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_IdleBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_IdleBtn.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for Heater_IdleBtn, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
Heater_IdleBtn.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_IdleBtn.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_IdleBtn.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_IdleBtn.set_style_border_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_IdleBtn.set_style_radius(5, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_IdleBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_IdleBtn.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_IdleBtn.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_IdleBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for Heater_IdleBtn, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
Heater_IdleBtn.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
Heater_IdleBtn.set_style_bg_color(lv.color_hex(0x2f2d31), lv.PART.MAIN|lv.STATE.CHECKED)
Heater_IdleBtn.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.CHECKED)
Heater_IdleBtn.set_style_border_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
Heater_IdleBtn.set_style_radius(5, lv.PART.MAIN|lv.STATE.CHECKED)
Heater_IdleBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
Heater_IdleBtn.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.CHECKED)
Heater_IdleBtn.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
Heater_IdleBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)

# Create Heater_IdleImg
Heater_IdleImg = lv.img(Heater)
Heater_IdleImg.set_src("B:MicroPython/_idle_btn_alpha_50x67.bin")
Heater_IdleImg.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_IdleImg.set_pivot(50,50)
Heater_IdleImg.set_angle(0)
Heater_IdleImg.set_pos(501, 569)
Heater_IdleImg.set_size(50, 67)
# Set style for Heater_IdleImg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_IdleImg.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_IdleImg.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_IdleImg.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_VentilateBtn
Heater_VentilateBtn = lv.btn(Heater)
Heater_VentilateBtn_label = lv.label(Heater_VentilateBtn)
Heater_VentilateBtn_label.set_text("")
Heater_VentilateBtn_label.set_long_mode(lv.label.LONG.WRAP)
Heater_VentilateBtn_label.set_width(lv.pct(100))
Heater_VentilateBtn_label.align(lv.ALIGN.CENTER, 0, 0)
Heater_VentilateBtn.set_style_pad_all(0, lv.STATE.DEFAULT)
Heater_VentilateBtn.set_pos(370, 476)
Heater_VentilateBtn.set_size(145, 76)
# Set style for Heater_VentilateBtn, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_VentilateBtn.set_style_bg_opa(244, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_VentilateBtn.set_style_bg_color(lv.color_hex(0x2f2d31), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_VentilateBtn.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_VentilateBtn.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_VentilateBtn.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_VentilateBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_VentilateBtn.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_VentilateBtn.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_VentilateBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_VentilateBtn.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for Heater_VentilateBtn, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
Heater_VentilateBtn.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_VentilateBtn.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_VentilateBtn.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_VentilateBtn.set_style_border_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_VentilateBtn.set_style_radius(5, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_VentilateBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_VentilateBtn.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_VentilateBtn.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_VentilateBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)

# Create Heater_VentilateImg
Heater_VentilateImg = lv.img(Heater)
Heater_VentilateImg.set_src("B:MicroPython/_venBtn_alpha_50x67.bin")
Heater_VentilateImg.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_VentilateImg.set_pivot(50,50)
Heater_VentilateImg.set_angle(0)
Heater_VentilateImg.set_pos(419, 481)
Heater_VentilateImg.set_size(50, 67)
# Set style for Heater_VentilateImg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_VentilateImg.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_VentilateImg.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_VentilateImg.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_HeatLowBtn
Heater_HeatLowBtn = lv.btn(Heater)
Heater_HeatLowBtn_label = lv.label(Heater_HeatLowBtn)
Heater_HeatLowBtn_label.set_text("")
Heater_HeatLowBtn_label.set_long_mode(lv.label.LONG.WRAP)
Heater_HeatLowBtn_label.set_width(lv.pct(100))
Heater_HeatLowBtn_label.align(lv.ALIGN.CENTER, 0, 0)
Heater_HeatLowBtn.set_style_pad_all(0, lv.STATE.DEFAULT)
Heater_HeatLowBtn.set_pos(204, 473)
Heater_HeatLowBtn.set_size(145, 76)
# Set style for Heater_HeatLowBtn, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_HeatLowBtn.set_style_bg_opa(244, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatLowBtn.set_style_bg_color(lv.color_hex(0x2f2d31), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatLowBtn.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatLowBtn.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatLowBtn.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatLowBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatLowBtn.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatLowBtn.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatLowBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatLowBtn.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for Heater_HeatLowBtn, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
Heater_HeatLowBtn.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatLowBtn.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatLowBtn.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatLowBtn.set_style_border_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatLowBtn.set_style_radius(5, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatLowBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatLowBtn.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatLowBtn.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatLowBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)

# Create Heater_HeatLowImg
Heater_HeatLowImg = lv.img(Heater)
Heater_HeatLowImg.set_src("B:MicroPython/_HeatLBtn_alpha_50x67.bin")
Heater_HeatLowImg.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_HeatLowImg.set_pivot(50,50)
Heater_HeatLowImg.set_angle(0)
Heater_HeatLowImg.set_pos(260, 476)
Heater_HeatLowImg.set_size(50, 67)
# Set style for Heater_HeatLowImg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_HeatLowImg.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatLowImg.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatLowImg.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_WindBtn
Heater_WindBtn = lv.btn(Heater)
Heater_WindBtn_label = lv.label(Heater_WindBtn)
Heater_WindBtn_label.set_text("")
Heater_WindBtn_label.set_long_mode(lv.label.LONG.WRAP)
Heater_WindBtn_label.set_width(lv.pct(100))
Heater_WindBtn_label.align(lv.ALIGN.CENTER, 0, 0)
Heater_WindBtn.set_style_pad_all(0, lv.STATE.DEFAULT)
Heater_WindBtn.set_pos(535, 476)
Heater_WindBtn.set_size(145, 76)
# Set style for Heater_WindBtn, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_WindBtn.set_style_bg_opa(244, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_WindBtn.set_style_bg_color(lv.color_hex(0x2f2d31), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_WindBtn.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_WindBtn.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_WindBtn.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_WindBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_WindBtn.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_WindBtn.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_WindBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_WindBtn.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for Heater_WindBtn, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
Heater_WindBtn.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_WindBtn.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_WindBtn.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_WindBtn.set_style_border_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_WindBtn.set_style_radius(5, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_WindBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_WindBtn.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_WindBtn.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_WindBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)

# Create Heater_WindImg
Heater_WindImg = lv.img(Heater)
Heater_WindImg.set_src("B:MicroPython/_fan_btn_alpha_50x67.bin")
Heater_WindImg.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_WindImg.set_pivot(50,50)
Heater_WindImg.set_angle(0)
Heater_WindImg.set_pos(585, 476)
Heater_WindImg.set_size(50, 67)
# Set style for Heater_WindImg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_WindImg.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_WindImg.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_WindImg.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_HeatHighBtn
Heater_HeatHighBtn = lv.btn(Heater)
Heater_HeatHighBtn_label = lv.label(Heater_HeatHighBtn)
Heater_HeatHighBtn_label.set_text("")
Heater_HeatHighBtn_label.set_long_mode(lv.label.LONG.WRAP)
Heater_HeatHighBtn_label.set_width(lv.pct(100))
Heater_HeatHighBtn_label.align(lv.ALIGN.CENTER, 0, 0)
Heater_HeatHighBtn.set_style_pad_all(0, lv.STATE.DEFAULT)
Heater_HeatHighBtn.set_pos(40, 473)
Heater_HeatHighBtn.set_size(145, 76)
# Set style for Heater_HeatHighBtn, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_HeatHighBtn.set_style_bg_opa(244, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatHighBtn.set_style_bg_color(lv.color_hex(0x2f2d31), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatHighBtn.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatHighBtn.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatHighBtn.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatHighBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatHighBtn.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatHighBtn.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatHighBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatHighBtn.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for Heater_HeatHighBtn, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
Heater_HeatHighBtn.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatHighBtn.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatHighBtn.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatHighBtn.set_style_border_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatHighBtn.set_style_radius(5, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatHighBtn.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatHighBtn.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatHighBtn.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.PRESSED)
Heater_HeatHighBtn.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)

# Create Heater_HeatHighImg
Heater_HeatHighImg = lv.img(Heater)
Heater_HeatHighImg.set_src("B:MicroPython/_HeatHbtn_alpha_50x67.bin")
Heater_HeatHighImg.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_HeatHighImg.set_pivot(50,50)
Heater_HeatHighImg.set_angle(0)
Heater_HeatHighImg.set_pos(88, 476)
Heater_HeatHighImg.set_size(50, 67)
# Set style for Heater_HeatHighImg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_HeatHighImg.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatHighImg.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatHighImg.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_VentilateMode
Heater_VentilateMode = lv.img(Heater)
Heater_VentilateMode.set_src("B:MicroPython/_venMode_alpha_295x164.bin")
Heater_VentilateMode.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_VentilateMode.set_pivot(50,50)
Heater_VentilateMode.set_angle(0)
Heater_VentilateMode.set_pos(210, 180)
Heater_VentilateMode.set_size(295, 164)
# Set style for Heater_VentilateMode, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_VentilateMode.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_VentilateMode.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_VentilateMode.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_heaterlowMode
Heater_heaterlowMode = lv.img(Heater)
Heater_heaterlowMode.set_src("B:MicroPython/_HeatLMode_alpha_295x164.bin")
Heater_heaterlowMode.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_heaterlowMode.set_pivot(50,50)
Heater_heaterlowMode.set_angle(0)
Heater_heaterlowMode.set_pos(210, 180)
Heater_heaterlowMode.set_size(295, 164)
# Set style for Heater_heaterlowMode, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_heaterlowMode.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_heaterlowMode.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_heaterlowMode.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_HeatHighMode
Heater_HeatHighMode = lv.img(Heater)
Heater_HeatHighMode.set_src("B:MicroPython/_HeatHMode_alpha_295x164.bin")
Heater_HeatHighMode.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_HeatHighMode.set_pivot(50,50)
Heater_HeatHighMode.set_angle(0)
Heater_HeatHighMode.set_pos(210, 180)
Heater_HeatHighMode.set_size(295, 164)
# Set style for Heater_HeatHighMode, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_HeatHighMode.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatHighMode.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_HeatHighMode.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_WindMode
Heater_WindMode = lv.img(Heater)
Heater_WindMode.set_src("B:MicroPython/_fan_mode_alpha_295x164.bin")
Heater_WindMode.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_WindMode.set_pivot(50,50)
Heater_WindMode.set_angle(0)
Heater_WindMode.set_pos(210, 180)
Heater_WindMode.set_size(295, 164)
# Set style for Heater_WindMode, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_WindMode.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_WindMode.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_WindMode.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_idleMode
Heater_idleMode = lv.img(Heater)
Heater_idleMode.set_src("B:MicroPython/_idle_mode_alpha_295x164.bin")
Heater_idleMode.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_idleMode.set_pivot(50,50)
Heater_idleMode.set_angle(0)
Heater_idleMode.set_pos(210, 180)
Heater_idleMode.set_size(295, 164)
# Set style for Heater_idleMode, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_idleMode.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_idleMode.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_idleMode.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_img_1
Heater_img_1 = lv.img(Heater)
Heater_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
Heater_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
Heater_img_1.set_pivot(50,50)
Heater_img_1.set_angle(0)
Heater_img_1.set_pos(43, 28)
Heater_img_1.set_size(14, 24)
# Set style for Heater_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Heater_btn_2
Heater_btn_2 = lv.btn(Heater)
Heater_btn_2_label = lv.label(Heater_btn_2)
Heater_btn_2_label.set_text("")
Heater_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
Heater_btn_2_label.set_width(lv.pct(100))
Heater_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
Heater_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
Heater_btn_2.set_pos(-8, -11)
Heater_btn_2.set_size(238, 106)
# Set style for Heater_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Heater_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Heater_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

Heater.update_layout()
# Create setting_screen
setting_screen = lv.obj()
setting_screen.set_size(720, 720)
setting_screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for setting_screen, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_tabview_1
setting_screen_tabview_1 = lv.tabview(setting_screen, lv.DIR.TOP, 85)
setting_screen_tabview_1.set_pos(0, 0)
setting_screen_tabview_1.set_size(720, 720)
setting_screen_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for setting_screen_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for setting_screen_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_setting_screen_tabview_1_extra_btnm_main_default = lv.style_t()
style_setting_screen_tabview_1_extra_btnm_main_default.init()
style_setting_screen_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_setting_screen_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_setting_screen_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_setting_screen_tabview_1_extra_btnm_main_default.set_border_width(0)
style_setting_screen_tabview_1_extra_btnm_main_default.set_radius(0)
setting_screen_tabview_1.get_tab_btns().add_style(style_setting_screen_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for setting_screen_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_setting_screen_tabview_1_extra_btnm_items_default = lv.style_t()
style_setting_screen_tabview_1_extra_btnm_items_default.init()
style_setting_screen_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_setting_screen_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_setting_screen_tabview_1_extra_btnm_items_default.set_text_opa(255)
setting_screen_tabview_1.get_tab_btns().add_style(style_setting_screen_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for setting_screen_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_setting_screen_tabview_1_extra_btnm_items_checked = lv.style_t()
style_setting_screen_tabview_1_extra_btnm_items_checked.init()
style_setting_screen_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_setting_screen_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_setting_screen_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_setting_screen_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_setting_screen_tabview_1_extra_btnm_items_checked.set_radius(0)
style_setting_screen_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_setting_screen_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_setting_screen_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
setting_screen_tabview_1.get_tab_btns().add_style(style_setting_screen_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
setting_screen_tabview_1_tab_1 = setting_screen_tabview_1.add_tab("")
setting_screen_tabview_1_tab_1_label = lv.label(setting_screen_tabview_1_tab_1)
setting_screen_tabview_1_tab_1_label.set_text("")

# Create setting_screen_btn_1
setting_screen_btn_1 = lv.btn(setting_screen)
setting_screen_btn_1_label = lv.label(setting_screen_btn_1)
setting_screen_btn_1_label.set_text("设  置")
setting_screen_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
setting_screen_btn_1_label.set_width(lv.pct(100))
setting_screen_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
setting_screen_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
setting_screen_btn_1.set_pos(70, 25)
setting_screen_btn_1.set_size(95, 32)
# Set style for setting_screen_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_img_1
setting_screen_img_1 = lv.img(setting_screen)
setting_screen_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
setting_screen_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_1.set_pivot(50,50)
setting_screen_img_1.set_angle(0)
setting_screen_img_1.set_pos(43, 28)
setting_screen_img_1.set_size(14, 24)
# Set style for setting_screen_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_btn_2
setting_screen_btn_2 = lv.btn(setting_screen)
setting_screen_btn_2_label = lv.label(setting_screen_btn_2)
setting_screen_btn_2_label.set_text("")
setting_screen_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
setting_screen_btn_2_label.set_width(lv.pct(100))
setting_screen_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
setting_screen_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
setting_screen_btn_2.set_pos(-5, -11)
setting_screen_btn_2.set_size(229, 103)
# Set style for setting_screen_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_cont_3
setting_screen_cont_3 = lv.obj(setting_screen)
setting_screen_cont_3.set_pos(35, 85)
setting_screen_cont_3.set_size(650, 90)
setting_screen_cont_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for setting_screen_cont_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_cont_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_3.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_3.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_3.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_3.set_style_border_color(lv.color_hex(0x151313), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_3.set_style_border_side(lv.BORDER_SIDE.BOTTOM, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create setting_screen_img_
setting_screen_img_ = lv.img(setting_screen_cont_3)
setting_screen_img_.set_src("B:MicroPython/_setnet_alpha_43x43.bin")
setting_screen_img_.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_.set_pivot(50,50)
setting_screen_img_.set_angle(0)
setting_screen_img_.set_pos(0, 23)
setting_screen_img_.set_size(43, 43)
# Set style for setting_screen_img_, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_label_1
setting_screen_label_1 = lv.label(setting_screen_cont_3)
setting_screen_label_1.set_text("网络设置")
setting_screen_label_1.set_long_mode(lv.label.LONG.WRAP)
setting_screen_label_1.set_width(lv.pct(100))
setting_screen_label_1.set_pos(53, 30)
setting_screen_label_1.set_size(148, 32)
# Set style for setting_screen_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_img_2
setting_screen_img_2 = lv.img(setting_screen_cont_3)
setting_screen_img_2.set_src(load_image(r"D:\7.NXP-GUI-PROJECT\4_inch_screen_tileview\generated\MicroPython\spageback_14_24.png"))
setting_screen_img_2.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_2.set_pivot(0,0)
setting_screen_img_2.set_angle(1800)
setting_screen_img_2.set_pos(632, 59)
setting_screen_img_2.set_size(14, 24)
# Set style for setting_screen_img_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_cont_4
setting_screen_cont_4 = lv.obj(setting_screen)
setting_screen_cont_4.set_pos(35, 175)
setting_screen_cont_4.set_size(650, 90)
setting_screen_cont_4.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for setting_screen_cont_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_cont_4.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_4.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_4.set_style_border_color(lv.color_hex(0x151313), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_4.set_style_border_side(lv.BORDER_SIDE.BOTTOM, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_4.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_4.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_4.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_4.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_4.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_4.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_4.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create setting_screen_img_4
setting_screen_img_4 = lv.img(setting_screen_cont_4)
setting_screen_img_4.set_src("B:MicroPython/_setdisp_alpha_43x43.bin")
setting_screen_img_4.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_4.set_pivot(50,50)
setting_screen_img_4.set_angle(0)
setting_screen_img_4.set_pos(0, 23)
setting_screen_img_4.set_size(43, 43)
# Set style for setting_screen_img_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_4.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_4.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_label_2
setting_screen_label_2 = lv.label(setting_screen_cont_4)
setting_screen_label_2.set_text("显示设置")
setting_screen_label_2.set_long_mode(lv.label.LONG.WRAP)
setting_screen_label_2.set_width(lv.pct(100))
setting_screen_label_2.set_pos(54, 30)
setting_screen_label_2.set_size(148, 32)
# Set style for setting_screen_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_2.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_img_3
setting_screen_img_3 = lv.img(setting_screen_cont_4)
setting_screen_img_3.set_src(load_image(r"D:\7.NXP-GUI-PROJECT\4_inch_screen_tileview\generated\MicroPython\spageback_14_24.png"))
setting_screen_img_3.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_3.set_pivot(0,0)
setting_screen_img_3.set_angle(1800)
setting_screen_img_3.set_pos(632, 59)
setting_screen_img_3.set_size(14, 24)
# Set style for setting_screen_img_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_cont_5
setting_screen_cont_5 = lv.obj(setting_screen)
setting_screen_cont_5.set_pos(35, 265)
setting_screen_cont_5.set_size(650, 90)
setting_screen_cont_5.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for setting_screen_cont_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_cont_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_5.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_5.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_5.set_style_border_color(lv.color_hex(0x151313), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_5.set_style_border_side(lv.BORDER_SIDE.BOTTOM, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_5.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_5.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_5.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_5.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_5.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_5.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create setting_screen_img_6
setting_screen_img_6 = lv.img(setting_screen_cont_5)
setting_screen_img_6.set_src("B:MicroPython/_setswitch_alpha_43x43.bin")
setting_screen_img_6.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_6.set_pivot(50,50)
setting_screen_img_6.set_angle(0)
setting_screen_img_6.set_pos(0, 23)
setting_screen_img_6.set_size(43, 43)
# Set style for setting_screen_img_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_6.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_6.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_6.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_label_3
setting_screen_label_3 = lv.label(setting_screen_cont_5)
setting_screen_label_3.set_text("开关配置")
setting_screen_label_3.set_long_mode(lv.label.LONG.WRAP)
setting_screen_label_3.set_width(lv.pct(100))
setting_screen_label_3.set_pos(54, 30)
setting_screen_label_3.set_size(148, 32)
# Set style for setting_screen_label_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_label_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_3.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_3.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_3.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_img_5
setting_screen_img_5 = lv.img(setting_screen_cont_5)
setting_screen_img_5.set_src(load_image(r"D:\7.NXP-GUI-PROJECT\4_inch_screen_tileview\generated\MicroPython\spageback_14_24.png"))
setting_screen_img_5.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_5.set_pivot(0,0)
setting_screen_img_5.set_angle(1800)
setting_screen_img_5.set_pos(632, 59)
setting_screen_img_5.set_size(14, 24)
# Set style for setting_screen_img_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_5.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_5.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_cont_6
setting_screen_cont_6 = lv.obj(setting_screen)
setting_screen_cont_6.set_pos(35, 355)
setting_screen_cont_6.set_size(650, 90)
setting_screen_cont_6.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for setting_screen_cont_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_cont_6.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_6.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_6.set_style_border_color(lv.color_hex(0x151313), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_6.set_style_border_side(lv.BORDER_SIDE.BOTTOM, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_6.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_6.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_6.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_6.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_6.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_6.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_6.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_6.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create setting_screen_img_8
setting_screen_img_8 = lv.img(setting_screen_cont_6)
setting_screen_img_8.set_src("B:MicroPython/_setsensor_alpha_43x43.bin")
setting_screen_img_8.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_8.set_pivot(50,50)
setting_screen_img_8.set_angle(0)
setting_screen_img_8.set_pos(0, 23)
setting_screen_img_8.set_size(43, 43)
# Set style for setting_screen_img_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_8.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_8.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_8.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_label_4
setting_screen_label_4 = lv.label(setting_screen_cont_6)
setting_screen_label_4.set_text("传感器配置")
setting_screen_label_4.set_long_mode(lv.label.LONG.WRAP)
setting_screen_label_4.set_width(lv.pct(100))
setting_screen_label_4.set_pos(54, 30)
setting_screen_label_4.set_size(148, 32)
# Set style for setting_screen_label_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_label_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_4.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_4.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_4.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_4.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_4.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_4.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_4.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_4.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_img_7
setting_screen_img_7 = lv.img(setting_screen_cont_6)
setting_screen_img_7.set_src(load_image(r"D:\7.NXP-GUI-PROJECT\4_inch_screen_tileview\generated\MicroPython\spageback_14_24.png"))
setting_screen_img_7.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_7.set_pivot(0,0)
setting_screen_img_7.set_angle(1800)
setting_screen_img_7.set_pos(632, 59)
setting_screen_img_7.set_size(14, 24)
# Set style for setting_screen_img_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_7.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_7.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_7.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_cont_7
setting_screen_cont_7 = lv.obj(setting_screen)
setting_screen_cont_7.set_pos(35, 445)
setting_screen_cont_7.set_size(650, 90)
setting_screen_cont_7.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for setting_screen_cont_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_cont_7.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_7.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_7.set_style_border_color(lv.color_hex(0x151313), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_7.set_style_border_side(lv.BORDER_SIDE.BOTTOM, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_7.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_7.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_7.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_7.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_7.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_7.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_7.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_7.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create setting_screen_img_10
setting_screen_img_10 = lv.img(setting_screen_cont_7)
setting_screen_img_10.set_src("B:MicroPython/_setreboot_alpha_43x43.bin")
setting_screen_img_10.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_10.set_pivot(50,50)
setting_screen_img_10.set_angle(0)
setting_screen_img_10.set_pos(0, 23)
setting_screen_img_10.set_size(43, 43)
# Set style for setting_screen_img_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_10.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_10.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_10.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_label_5
setting_screen_label_5 = lv.label(setting_screen_cont_7)
setting_screen_label_5.set_text("设备重启")
setting_screen_label_5.set_long_mode(lv.label.LONG.WRAP)
setting_screen_label_5.set_width(lv.pct(100))
setting_screen_label_5.set_pos(54, 30)
setting_screen_label_5.set_size(148, 32)
# Set style for setting_screen_label_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_label_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_5.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_5.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_5.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_5.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_5.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_5.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_5.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_5.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_5.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_5.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_img_9
setting_screen_img_9 = lv.img(setting_screen_cont_7)
setting_screen_img_9.set_src(load_image(r"D:\7.NXP-GUI-PROJECT\4_inch_screen_tileview\generated\MicroPython\spageback_14_24.png"))
setting_screen_img_9.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_9.set_pivot(0,0)
setting_screen_img_9.set_angle(1800)
setting_screen_img_9.set_pos(632, 59)
setting_screen_img_9.set_size(14, 24)
# Set style for setting_screen_img_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_9.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_9.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_9.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_cont_8
setting_screen_cont_8 = lv.obj(setting_screen)
setting_screen_cont_8.set_pos(35, 535)
setting_screen_cont_8.set_size(650, 90)
setting_screen_cont_8.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for setting_screen_cont_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_cont_8.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_8.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_8.set_style_border_color(lv.color_hex(0x151313), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_8.set_style_border_side(lv.BORDER_SIDE.BOTTOM, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_8.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_8.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_8.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_8.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_8.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_8.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_8.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_8.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create setting_screen_img_12
setting_screen_img_12 = lv.img(setting_screen_cont_8)
setting_screen_img_12.set_src("B:MicroPython/_setrestore_alpha_43x43.bin")
setting_screen_img_12.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_12.set_pivot(50,50)
setting_screen_img_12.set_angle(0)
setting_screen_img_12.set_pos(0, 23)
setting_screen_img_12.set_size(43, 43)
# Set style for setting_screen_img_12, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_12.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_12.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_12.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_label_6
setting_screen_label_6 = lv.label(setting_screen_cont_8)
setting_screen_label_6.set_text("恢复出厂")
setting_screen_label_6.set_long_mode(lv.label.LONG.WRAP)
setting_screen_label_6.set_width(lv.pct(100))
setting_screen_label_6.set_pos(54, 30)
setting_screen_label_6.set_size(148, 32)
# Set style for setting_screen_label_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_label_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_6.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_6.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_6.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_6.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_6.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_6.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_6.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_6.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_6.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_6.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_6.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_img_11
setting_screen_img_11 = lv.img(setting_screen_cont_8)
setting_screen_img_11.set_src(load_image(r"D:\7.NXP-GUI-PROJECT\4_inch_screen_tileview\generated\MicroPython\spageback_14_24.png"))
setting_screen_img_11.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_11.set_pivot(0,0)
setting_screen_img_11.set_angle(1800)
setting_screen_img_11.set_pos(632, 59)
setting_screen_img_11.set_size(14, 24)
# Set style for setting_screen_img_11, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_11.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_11.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_11.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_cont_9
setting_screen_cont_9 = lv.obj(setting_screen)
setting_screen_cont_9.set_pos(35, 625)
setting_screen_cont_9.set_size(650, 90)
setting_screen_cont_9.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for setting_screen_cont_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_cont_9.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_9.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_9.set_style_border_color(lv.color_hex(0x151313), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_9.set_style_border_side(lv.BORDER_SIDE.BOTTOM, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_9.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_9.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_9.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_9.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_9.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_9.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_9.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_9.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_cont_9.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create setting_screen_img_14
setting_screen_img_14 = lv.img(setting_screen_cont_9)
setting_screen_img_14.set_src("B:MicroPython/_setabout_alpha_43x43.bin")
setting_screen_img_14.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_14.set_pivot(50,50)
setting_screen_img_14.set_angle(0)
setting_screen_img_14.set_pos(0, 23)
setting_screen_img_14.set_size(43, 43)
# Set style for setting_screen_img_14, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_14.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_14.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_14.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_label_7
setting_screen_label_7 = lv.label(setting_screen_cont_9)
setting_screen_label_7.set_text("关于产品")
setting_screen_label_7.set_long_mode(lv.label.LONG.WRAP)
setting_screen_label_7.set_width(lv.pct(100))
setting_screen_label_7.set_pos(54, 30)
setting_screen_label_7.set_size(148, 32)
# Set style for setting_screen_label_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_label_7.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_7.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_7.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_7.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_7.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_7.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_7.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_7.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_7.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_7.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_7.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_label_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create setting_screen_img_13
setting_screen_img_13 = lv.img(setting_screen_cont_9)
setting_screen_img_13.set_src(load_image(r"D:\7.NXP-GUI-PROJECT\4_inch_screen_tileview\generated\MicroPython\spageback_14_24.png"))
setting_screen_img_13.add_flag(lv.obj.FLAG.CLICKABLE)
setting_screen_img_13.set_pivot(0,0)
setting_screen_img_13.set_angle(1800)
setting_screen_img_13.set_pos(632, 59)
setting_screen_img_13.set_size(14, 24)
# Set style for setting_screen_img_13, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
setting_screen_img_13.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_13.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
setting_screen_img_13.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

setting_screen.update_layout()
# Create NetSetting
NetSetting = lv.obj()
NetSetting.set_size(720, 720)
NetSetting.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for NetSetting, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
NetSetting.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create NetSetting_tabview_1
NetSetting_tabview_1 = lv.tabview(NetSetting, lv.DIR.TOP, 85)
NetSetting_tabview_1.set_pos(0, 0)
NetSetting_tabview_1.set_size(720, 720)
NetSetting_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for NetSetting_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
NetSetting_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_tabview_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for NetSetting_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_NetSetting_tabview_1_extra_btnm_main_default = lv.style_t()
style_NetSetting_tabview_1_extra_btnm_main_default.init()
style_NetSetting_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_NetSetting_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_NetSetting_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_NetSetting_tabview_1_extra_btnm_main_default.set_border_width(0)
style_NetSetting_tabview_1_extra_btnm_main_default.set_radius(0)
NetSetting_tabview_1.get_tab_btns().add_style(style_NetSetting_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for NetSetting_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_NetSetting_tabview_1_extra_btnm_items_default = lv.style_t()
style_NetSetting_tabview_1_extra_btnm_items_default.init()
style_NetSetting_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_NetSetting_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_NetSetting_tabview_1_extra_btnm_items_default.set_text_opa(255)
NetSetting_tabview_1.get_tab_btns().add_style(style_NetSetting_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for NetSetting_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_NetSetting_tabview_1_extra_btnm_items_checked = lv.style_t()
style_NetSetting_tabview_1_extra_btnm_items_checked.init()
style_NetSetting_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_NetSetting_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_NetSetting_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_NetSetting_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_NetSetting_tabview_1_extra_btnm_items_checked.set_radius(0)
style_NetSetting_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_NetSetting_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_NetSetting_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
NetSetting_tabview_1.get_tab_btns().add_style(style_NetSetting_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
NetSetting_tabview_1_tab_1 = NetSetting_tabview_1.add_tab("")
NetSetting_tabview_1_tab_1_label = lv.label(NetSetting_tabview_1_tab_1)
NetSetting_tabview_1_tab_1_label.set_text("")

# Create NetSetting_NetSet
NetSetting_NetSet = lv.btn(NetSetting)
NetSetting_NetSet_label = lv.label(NetSetting_NetSet)
NetSetting_NetSet_label.set_text("网络设置")
NetSetting_NetSet_label.set_long_mode(lv.label.LONG.WRAP)
NetSetting_NetSet_label.set_width(lv.pct(100))
NetSetting_NetSet_label.align(lv.ALIGN.LEFT_MID, 0, 0)
NetSetting_NetSet.set_style_pad_all(0, lv.STATE.DEFAULT)
NetSetting_NetSet.set_pos(70, 25)
NetSetting_NetSet.set_size(156, 32)
# Set style for NetSetting_NetSet, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
NetSetting_NetSet.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_NetSet.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_NetSet.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_NetSet.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_NetSet.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_NetSet.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_NetSet.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_NetSet.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create NetSetting_img_1
NetSetting_img_1 = lv.img(NetSetting)
NetSetting_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
NetSetting_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
NetSetting_img_1.set_pivot(50,50)
NetSetting_img_1.set_angle(0)
NetSetting_img_1.set_pos(43, 28)
NetSetting_img_1.set_size(14, 24)
# Set style for NetSetting_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
NetSetting_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create NetSetting_btn_1
NetSetting_btn_1 = lv.btn(NetSetting)
NetSetting_btn_1_label = lv.label(NetSetting_btn_1)
NetSetting_btn_1_label.set_text("")
NetSetting_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
NetSetting_btn_1_label.set_width(lv.pct(100))
NetSetting_btn_1_label.align(lv.ALIGN.CENTER, 0, 0)
NetSetting_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
NetSetting_btn_1.set_pos(-5, -11)
NetSetting_btn_1.set_size(261, 107)
# Set style for NetSetting_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
NetSetting_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create NetSetting_img_5
NetSetting_img_5 = lv.img(NetSetting)
NetSetting_img_5.set_src("B:MicroPython/_Sbind_alpha_71x71.bin")
NetSetting_img_5.add_flag(lv.obj.FLAG.CLICKABLE)
NetSetting_img_5.set_pivot(50,50)
NetSetting_img_5.set_angle(0)
NetSetting_img_5.set_pos(307, 296)
NetSetting_img_5.set_size(71, 71)
# Set style for NetSetting_img_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
NetSetting_img_5.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_img_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_img_5.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create NetSetting_btn_5
NetSetting_btn_5 = lv.btn(NetSetting)
NetSetting_btn_5_label = lv.label(NetSetting_btn_5)
NetSetting_btn_5_label.set_text("解除设备")
NetSetting_btn_5_label.set_long_mode(lv.label.LONG.WRAP)
NetSetting_btn_5_label.set_width(lv.pct(100))
NetSetting_btn_5_label.align(lv.ALIGN.CENTER, 0, 0)
NetSetting_btn_5.set_style_pad_all(0, lv.STATE.DEFAULT)
NetSetting_btn_5.set_pos(207, 578)
NetSetting_btn_5.set_size(306, 50)
# Set style for NetSetting_btn_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
NetSetting_btn_5.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_5.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_5.set_style_radius(14, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_5.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_5.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_5.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create NetSetting_label_4
NetSetting_label_4 = lv.label(NetSetting)
NetSetting_label_4.set_text("设备已经绑定米家App")
NetSetting_label_4.set_long_mode(lv.label.LONG.WRAP)
NetSetting_label_4.set_width(lv.pct(100))
NetSetting_label_4.set_pos(193, 152)
NetSetting_label_4.set_size(334, 32)
# Set style for NetSetting_label_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
NetSetting_label_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_4.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_4.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_4.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_4.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_4.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_4.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_4.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_4.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create NetSetting_img_4
NetSetting_img_4 = lv.img(NetSetting)
NetSetting_img_4.set_src("B:MicroPython/_SQRCode_alpha_300x300.bin")
NetSetting_img_4.add_flag(lv.obj.FLAG.CLICKABLE)
NetSetting_img_4.set_pivot(50,50)
NetSetting_img_4.set_angle(0)
NetSetting_img_4.set_pos(210, 210)
NetSetting_img_4.set_size(300, 300)
# Set style for NetSetting_img_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
NetSetting_img_4.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_img_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_img_4.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create NetSetting_img_3
NetSetting_img_3 = lv.img(NetSetting)
NetSetting_img_3.set_src("B:MicroPython/_Sstartbind_alpha_136x145.bin")
NetSetting_img_3.add_flag(lv.obj.FLAG.CLICKABLE)
NetSetting_img_3.set_pivot(50,50)
NetSetting_img_3.set_angle(0)
NetSetting_img_3.set_pos(292, 287)
NetSetting_img_3.set_size(136, 145)
# Set style for NetSetting_img_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
NetSetting_img_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_img_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_img_3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create NetSetting_btn_3
NetSetting_btn_3 = lv.btn(NetSetting)
NetSetting_btn_3_label = lv.label(NetSetting_btn_3)
NetSetting_btn_3_label.set_text("开始绑定")
NetSetting_btn_3_label.set_long_mode(lv.label.LONG.WRAP)
NetSetting_btn_3_label.set_width(lv.pct(100))
NetSetting_btn_3_label.align(lv.ALIGN.CENTER, 0, 0)
NetSetting_btn_3.set_style_pad_all(0, lv.STATE.DEFAULT)
NetSetting_btn_3.set_pos(207, 578)
NetSetting_btn_3.set_size(306, 50)
# Set style for NetSetting_btn_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
NetSetting_btn_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_3.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_3.set_style_radius(14, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_3.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_btn_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create NetSetting_label_3
NetSetting_label_3 = lv.label(NetSetting)
NetSetting_label_3.set_text("设备未绑定米家")
NetSetting_label_3.set_long_mode(lv.label.LONG.WRAP)
NetSetting_label_3.set_width(lv.pct(100))
NetSetting_label_3.set_pos(193, 152)
NetSetting_label_3.set_size(334, 32)
# Set style for NetSetting_label_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
NetSetting_label_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_3.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_3.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_3.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
NetSetting_label_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

NetSetting.update_layout()
# Create PlaySet
PlaySet = lv.obj()
PlaySet.set_size(720, 720)
PlaySet.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for PlaySet, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_tabview_1
PlaySet_tabview_1 = lv.tabview(PlaySet, lv.DIR.TOP, 85)
PlaySet_tabview_1.set_pos(0, 0)
PlaySet_tabview_1.set_size(720, 720)
PlaySet_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for PlaySet_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for PlaySet_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_PlaySet_tabview_1_extra_btnm_main_default = lv.style_t()
style_PlaySet_tabview_1_extra_btnm_main_default.init()
style_PlaySet_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_PlaySet_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_PlaySet_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_PlaySet_tabview_1_extra_btnm_main_default.set_border_width(0)
style_PlaySet_tabview_1_extra_btnm_main_default.set_radius(0)
PlaySet_tabview_1.get_tab_btns().add_style(style_PlaySet_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for PlaySet_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_PlaySet_tabview_1_extra_btnm_items_default = lv.style_t()
style_PlaySet_tabview_1_extra_btnm_items_default.init()
style_PlaySet_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_PlaySet_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_PlaySet_tabview_1_extra_btnm_items_default.set_text_opa(255)
PlaySet_tabview_1.get_tab_btns().add_style(style_PlaySet_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for PlaySet_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_PlaySet_tabview_1_extra_btnm_items_checked = lv.style_t()
style_PlaySet_tabview_1_extra_btnm_items_checked.init()
style_PlaySet_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_PlaySet_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_PlaySet_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_PlaySet_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_PlaySet_tabview_1_extra_btnm_items_checked.set_radius(0)
style_PlaySet_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_PlaySet_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_PlaySet_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
PlaySet_tabview_1.get_tab_btns().add_style(style_PlaySet_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
PlaySet_tabview_1_tab_1 = PlaySet_tabview_1.add_tab("")
PlaySet_tabview_1_tab_1_label = lv.label(PlaySet_tabview_1_tab_1)
PlaySet_tabview_1_tab_1_label.set_text("")

# Create PlaySet_btn_1
PlaySet_btn_1 = lv.btn(PlaySet)
PlaySet_btn_1_label = lv.label(PlaySet_btn_1)
PlaySet_btn_1_label.set_text("显示设置")
PlaySet_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_1_label.set_width(lv.pct(100))
PlaySet_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_1.set_pos(70, 25)
PlaySet_btn_1.set_size(152, 32)
# Set style for PlaySet_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_List
PlaySet_List = lv.list(PlaySet)
PlaySet_List_item0 = PlaySet_List.add_text("延时进入待机时间")
PlaySet_List_item1 = PlaySet_List.add_text("待机显示")
PlaySet_List_item2 = PlaySet_List.add_text("接近亮屏")
PlaySet_List.set_pos(21, 91)
PlaySet_List.set_size(665, 585)
PlaySet_List.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for PlaySet_List, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_List.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_List.set_style_pad_left(5, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_List.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_List.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_List.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_List.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_List.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_List.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_List.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_List.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for PlaySet_List, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
PlaySet_List.set_style_radius(3, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
PlaySet_List.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
PlaySet_List.set_style_bg_color(lv.color_hex(0x000000), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
PlaySet_List.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
# Set style for PlaySet_List, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_PlaySet_List_extra_btns_main_default = lv.style_t()
style_PlaySet_List_extra_btns_main_default.init()
style_PlaySet_List_extra_btns_main_default.set_pad_top(5)
style_PlaySet_List_extra_btns_main_default.set_pad_left(5)
style_PlaySet_List_extra_btns_main_default.set_pad_right(5)
style_PlaySet_List_extra_btns_main_default.set_pad_bottom(5)
style_PlaySet_List_extra_btns_main_default.set_border_width(2)
style_PlaySet_List_extra_btns_main_default.set_border_opa(255)
style_PlaySet_List_extra_btns_main_default.set_border_color(lv.color_hex(0xe1e6ee))
style_PlaySet_List_extra_btns_main_default.set_border_side(lv.BORDER_SIDE.BOTTOM)
style_PlaySet_List_extra_btns_main_default.set_text_color(lv.color_hex(0xffffff))
style_PlaySet_List_extra_btns_main_default.set_text_font(test_font("MiSansNormal", 30))
style_PlaySet_List_extra_btns_main_default.set_text_opa(255)
style_PlaySet_List_extra_btns_main_default.set_radius(3)
style_PlaySet_List_extra_btns_main_default.set_bg_opa(255)
style_PlaySet_List_extra_btns_main_default.set_bg_color(lv.color_hex(0x000000))
style_PlaySet_List_extra_btns_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)

# Set style for PlaySet_List, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_PlaySet_List_extra_texts_main_default = lv.style_t()
style_PlaySet_List_extra_texts_main_default.init()
style_PlaySet_List_extra_texts_main_default.set_pad_top(20)
style_PlaySet_List_extra_texts_main_default.set_pad_left(10)
style_PlaySet_List_extra_texts_main_default.set_pad_right(0)
style_PlaySet_List_extra_texts_main_default.set_pad_bottom(24)
style_PlaySet_List_extra_texts_main_default.set_border_width(3)
style_PlaySet_List_extra_texts_main_default.set_border_opa(255)
style_PlaySet_List_extra_texts_main_default.set_border_color(lv.color_hex(0x151313))
style_PlaySet_List_extra_texts_main_default.set_border_side(lv.BORDER_SIDE.BOTTOM)
style_PlaySet_List_extra_texts_main_default.set_text_color(lv.color_hex(0xffffff))
style_PlaySet_List_extra_texts_main_default.set_text_font(test_font("MiSansNormal", 30))
style_PlaySet_List_extra_texts_main_default.set_text_opa(255)
style_PlaySet_List_extra_texts_main_default.set_radius(0)
style_PlaySet_List_extra_texts_main_default.set_transform_width(0)
style_PlaySet_List_extra_texts_main_default.set_bg_opa(255)
style_PlaySet_List_extra_texts_main_default.set_bg_color(lv.color_hex(0x000000))
style_PlaySet_List_extra_texts_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
PlaySet_List_item2.add_style(style_PlaySet_List_extra_texts_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_List_item1.add_style(style_PlaySet_List_extra_texts_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_List_item0.add_style(style_PlaySet_List_extra_texts_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_img_1
PlaySet_img_1 = lv.img(PlaySet)
PlaySet_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
PlaySet_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
PlaySet_img_1.set_pivot(50,50)
PlaySet_img_1.set_angle(0)
PlaySet_img_1.set_pos(43, 28)
PlaySet_img_1.set_size(14, 24)
# Set style for PlaySet_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_2
PlaySet_btn_2 = lv.btn(PlaySet)
PlaySet_btn_2_label = lv.label(PlaySet_btn_2)
PlaySet_btn_2_label.set_text("")
PlaySet_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_2_label.set_width(lv.pct(100))
PlaySet_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
PlaySet_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_2.set_pos(-7, -12)
PlaySet_btn_2.set_size(248, 103)
# Set style for PlaySet_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_img_2
PlaySet_img_2 = lv.img(PlaySet)
PlaySet_img_2.set_src(load_image(r"D:\7.NXP-GUI-PROJECT\4_inch_screen_tileview\generated\MicroPython\spageback_14_24.png"))
PlaySet_img_2.add_flag(lv.obj.FLAG.CLICKABLE)
PlaySet_img_2.set_pivot(0,0)
PlaySet_img_2.set_angle(1800)
PlaySet_img_2.set_pos(667, 142)
PlaySet_img_2.set_size(14, 24)
# Set style for PlaySet_img_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_img_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_img_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_img_2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_img_3
PlaySet_img_3 = lv.img(PlaySet)
PlaySet_img_3.set_src(load_image(r"D:\7.NXP-GUI-PROJECT\4_inch_screen_tileview\generated\MicroPython\spageback_14_24.png"))
PlaySet_img_3.add_flag(lv.obj.FLAG.CLICKABLE)
PlaySet_img_3.set_pivot(0,0)
PlaySet_img_3.set_angle(1800)
PlaySet_img_3.set_pos(670, 322)
PlaySet_img_3.set_size(14, 24)
# Set style for PlaySet_img_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_img_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_img_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_img_3.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_img_4
PlaySet_img_4 = lv.img(PlaySet)
PlaySet_img_4.set_src(load_image(r"D:\7.NXP-GUI-PROJECT\4_inch_screen_tileview\generated\MicroPython\spageback_14_24.png"))
PlaySet_img_4.add_flag(lv.obj.FLAG.CLICKABLE)
PlaySet_img_4.set_pivot(0,0)
PlaySet_img_4.set_angle(1800)
PlaySet_img_4.set_pos(667, 232)
PlaySet_img_4.set_size(14, 24)
# Set style for PlaySet_img_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_img_4.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_img_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_img_4.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_tileview_1
PlaySet_tileview_1 = lv.tileview(PlaySet)
PlaySet_tileview_1_tile = PlaySet_tileview_1.add_tile(0, 0, lv.DIR.RIGHT)
PlaySet_tileview_1.set_pos(916, 0)
PlaySet_tileview_1.set_size(600, 245)
PlaySet_tileview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for PlaySet_tileview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_tileview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tileview_1.set_style_bg_color(lv.color_hex(0xf6f6f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tileview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tileview_1.set_style_radius(10, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tileview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for PlaySet_tileview_1, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
PlaySet_tileview_1.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
PlaySet_tileview_1.set_style_bg_color(lv.color_hex(0xeaeff3), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
PlaySet_tileview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
PlaySet_tileview_1.set_style_radius(0, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create PlaySet_line_5
PlaySet_line_5 = lv.line(PlaySet_tileview_1_tile)
PlaySet_line_5_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_5.set_points(PlaySet_line_5_line_points, 2)
PlaySet_line_5.set_pos(45, 55)
PlaySet_line_5.set_size(505, 22)
# Set style for PlaySet_line_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_5.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_5.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_5.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_5.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_5
PlaySet_label_5 = lv.label(PlaySet_tileview_1_tile)
PlaySet_label_5.set_text("15秒")
PlaySet_label_5.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_5.set_width(lv.pct(100))
PlaySet_label_5.set_pos(50, 18)
PlaySet_label_5.set_size(100, 32)
# Set style for PlaySet_label_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_5.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_5.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_5.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_5.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_5.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_5.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_5.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_5.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_5.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_5.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_5
PlaySet_btn_5 = lv.btn(PlaySet_tileview_1_tile)
PlaySet_btn_5_label = lv.label(PlaySet_btn_5)
PlaySet_btn_5_label.set_text("")
PlaySet_btn_5_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_5_label.set_width(lv.pct(100))
PlaySet_btn_5_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_5.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_5.set_pos(500, 14)
PlaySet_btn_5.set_size(35, 35)
# Set style for PlaySet_btn_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_5.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_5.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_5.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_5.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_5.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_5.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_5.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_5.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_5.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_6
PlaySet_line_6 = lv.line(PlaySet_tileview_1_tile)
PlaySet_line_6_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_6.set_points(PlaySet_line_6_line_points, 2)
PlaySet_line_6.set_pos(45, 131)
PlaySet_line_6.set_size(505, 22)
# Set style for PlaySet_line_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_6.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_6.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_6.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_6.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_6
PlaySet_btn_6 = lv.btn(PlaySet_tileview_1_tile)
PlaySet_btn_6_label = lv.label(PlaySet_btn_6)
PlaySet_btn_6_label.set_text("")
PlaySet_btn_6_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_6_label.set_width(lv.pct(100))
PlaySet_btn_6_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_6.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_6.set_pos(500, 89)
PlaySet_btn_6.set_size(35, 35)
# Set style for PlaySet_btn_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_6.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_6.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_6.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_6.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_6.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_6.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_6.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_6.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_6.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_6
PlaySet_label_6 = lv.label(PlaySet_tileview_1_tile)
PlaySet_label_6.set_text("30秒")
PlaySet_label_6.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_6.set_width(lv.pct(100))
PlaySet_label_6.set_pos(50, 94)
PlaySet_label_6.set_size(100, 32)
# Set style for PlaySet_label_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_6.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_6.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_6.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_6.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_6.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_6.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_6.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_6.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_6.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_6.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_6.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_7
PlaySet_btn_7 = lv.btn(PlaySet_tileview_1_tile)
PlaySet_btn_7_label = lv.label(PlaySet_btn_7)
PlaySet_btn_7_label.set_text("")
PlaySet_btn_7_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_7_label.set_width(lv.pct(100))
PlaySet_btn_7_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_7.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_7.set_pos(500, 164)
PlaySet_btn_7.set_size(35, 35)
# Set style for PlaySet_btn_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_7.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_7.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_7.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_7.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_7.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_7.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_7.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_7.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_7.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_7
PlaySet_line_7 = lv.line(PlaySet_tileview_1_tile)
PlaySet_line_7_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_7.set_points(PlaySet_line_7_line_points, 2)
PlaySet_line_7.set_pos(45, 207)
PlaySet_line_7.set_size(505, 22)
# Set style for PlaySet_line_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_7.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_7.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_7.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_7.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_7
PlaySet_label_7 = lv.label(PlaySet_tileview_1_tile)
PlaySet_label_7.set_text("1分钟")
PlaySet_label_7.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_7.set_width(lv.pct(100))
PlaySet_label_7.set_pos(50, 170)
PlaySet_label_7.set_size(100, 32)
# Set style for PlaySet_label_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_7.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_7.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_7.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_7.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_7.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_7.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_7.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_7.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_7.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_7.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_7.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_8
PlaySet_btn_8 = lv.btn(PlaySet_tileview_1_tile)
PlaySet_btn_8_label = lv.label(PlaySet_btn_8)
PlaySet_btn_8_label.set_text("")
PlaySet_btn_8_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_8_label.set_width(lv.pct(100))
PlaySet_btn_8_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_8.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_8.set_pos(500, 239)
PlaySet_btn_8.set_size(35, 35)
# Set style for PlaySet_btn_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_8.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_8.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_8.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_8.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_8.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_8.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_8.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_8.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_8.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_8.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_8
PlaySet_line_8 = lv.line(PlaySet_tileview_1_tile)
PlaySet_line_8_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_8.set_points(PlaySet_line_8_line_points, 2)
PlaySet_line_8.set_pos(45, 283)
PlaySet_line_8.set_size(505, 22)
# Set style for PlaySet_line_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_8.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_8.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_8.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_8.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_8
PlaySet_label_8 = lv.label(PlaySet_tileview_1_tile)
PlaySet_label_8.set_text("2分钟\n")
PlaySet_label_8.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_8.set_width(lv.pct(100))
PlaySet_label_8.set_pos(50, 246)
PlaySet_label_8.set_size(100, 32)
# Set style for PlaySet_label_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_8.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_8.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_8.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_8.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_8.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_8.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_8.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_8.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_8.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_8.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_8.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_8.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_8.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_9
PlaySet_btn_9 = lv.btn(PlaySet_tileview_1_tile)
PlaySet_btn_9_label = lv.label(PlaySet_btn_9)
PlaySet_btn_9_label.set_text("")
PlaySet_btn_9_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_9_label.set_width(lv.pct(100))
PlaySet_btn_9_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_9.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_9.set_pos(500, 314)
PlaySet_btn_9.set_size(35, 35)
# Set style for PlaySet_btn_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_9.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_9.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_9.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_9.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_9.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_9.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_9.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_9.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_9.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_9.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_9.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_9
PlaySet_line_9 = lv.line(PlaySet_tileview_1_tile)
PlaySet_line_9_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_9.set_points(PlaySet_line_9_line_points, 2)
PlaySet_line_9.set_pos(45, 359)
PlaySet_line_9.set_size(505, 22)
# Set style for PlaySet_line_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_9.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_9.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_9.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_9.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_9
PlaySet_label_9 = lv.label(PlaySet_tileview_1_tile)
PlaySet_label_9.set_text("5分钟")
PlaySet_label_9.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_9.set_width(lv.pct(100))
PlaySet_label_9.set_pos(50, 322)
PlaySet_label_9.set_size(100, 32)
# Set style for PlaySet_label_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_9.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_9.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_9.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_9.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_9.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_9.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_9.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_9.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_9.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_9.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_9.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_9.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_9.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_9.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_10
PlaySet_btn_10 = lv.btn(PlaySet_tileview_1_tile)
PlaySet_btn_10_label = lv.label(PlaySet_btn_10)
PlaySet_btn_10_label.set_text("")
PlaySet_btn_10_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_10_label.set_width(lv.pct(100))
PlaySet_btn_10_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_10.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_10.set_pos(500, 389)
PlaySet_btn_10.set_size(35, 35)
# Set style for PlaySet_btn_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_10.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_10.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_10.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_10.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_10.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_10.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_10.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_10.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_10.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_10.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_10.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_10
PlaySet_line_10 = lv.line(PlaySet_tileview_1_tile)
PlaySet_line_10_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_10.set_points(PlaySet_line_10_line_points, 2)
PlaySet_line_10.set_pos(45, 435)
PlaySet_line_10.set_size(505, 22)
# Set style for PlaySet_line_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_10.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_10.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_10.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_10.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_10
PlaySet_label_10 = lv.label(PlaySet_tileview_1_tile)
PlaySet_label_10.set_text("10分钟")
PlaySet_label_10.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_10.set_width(lv.pct(100))
PlaySet_label_10.set_pos(50, 398)
PlaySet_label_10.set_size(100, 32)
# Set style for PlaySet_label_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_10.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_10.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_10.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_10.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_10.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_10.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_10.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_10.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_10.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_10.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_10.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_10.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_10.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_10.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_11
PlaySet_line_11 = lv.line(PlaySet_tileview_1_tile)
PlaySet_line_11_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_11.set_points(PlaySet_line_11_line_points, 2)
PlaySet_line_11.set_pos(45, 511)
PlaySet_line_11.set_size(505, 22)
# Set style for PlaySet_line_11, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_11.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_11.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_11.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_11.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_11
PlaySet_btn_11 = lv.btn(PlaySet_tileview_1_tile)
PlaySet_btn_11_label = lv.label(PlaySet_btn_11)
PlaySet_btn_11_label.set_text("")
PlaySet_btn_11_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_11_label.set_width(lv.pct(100))
PlaySet_btn_11_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_11.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_11.set_pos(500, 464)
PlaySet_btn_11.set_size(35, 35)
# Set style for PlaySet_btn_11, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_11.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_11.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_11.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_11.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_11.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_11.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_11.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_11.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_11.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_11.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_11.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_11
PlaySet_label_11 = lv.label(PlaySet_tileview_1_tile)
PlaySet_label_11.set_text("永久")
PlaySet_label_11.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_11.set_width(lv.pct(100))
PlaySet_label_11.set_pos(50, 474)
PlaySet_label_11.set_size(100, 32)
# Set style for PlaySet_label_11, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_11.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_11.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_11.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_11.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_11.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_11.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_11.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_11.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_11.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_11.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_11.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_11.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_11.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_11.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_tileview_2
PlaySet_tileview_2 = lv.tileview(PlaySet)
PlaySet_tileview_2_tile = PlaySet_tileview_2.add_tile(0, 0, lv.DIR.RIGHT)
PlaySet_tileview_2.set_pos(1886, 42)
PlaySet_tileview_2.set_size(600, 245)
PlaySet_tileview_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for PlaySet_tileview_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_tileview_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tileview_2.set_style_bg_color(lv.color_hex(0xf6f6f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tileview_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tileview_2.set_style_radius(10, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tileview_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for PlaySet_tileview_2, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
PlaySet_tileview_2.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
PlaySet_tileview_2.set_style_bg_color(lv.color_hex(0xeaeff3), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
PlaySet_tileview_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
PlaySet_tileview_2.set_style_radius(0, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create PlaySet_line_18
PlaySet_line_18 = lv.line(PlaySet_tileview_2_tile)
PlaySet_line_18_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_18.set_points(PlaySet_line_18_line_points, 2)
PlaySet_line_18.set_pos(45, 55)
PlaySet_line_18.set_size(505, 22)
# Set style for PlaySet_line_18, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_18.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_18.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_18.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_18.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_18
PlaySet_label_18 = lv.label(PlaySet_tileview_2_tile)
PlaySet_label_18.set_text("熄屏")
PlaySet_label_18.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_18.set_width(lv.pct(100))
PlaySet_label_18.set_pos(50, 16)
PlaySet_label_18.set_size(100, 32)
# Set style for PlaySet_label_18, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_18.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_18.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_18.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_18.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_18.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_18.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_18.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_18.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_18.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_18.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_18.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_18.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_18.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_18.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_18
PlaySet_btn_18 = lv.btn(PlaySet_tileview_2_tile)
PlaySet_btn_18_label = lv.label(PlaySet_btn_18)
PlaySet_btn_18_label.set_text("")
PlaySet_btn_18_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_18_label.set_width(lv.pct(100))
PlaySet_btn_18_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_18.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_18.set_pos(500, 14)
PlaySet_btn_18.set_size(35, 35)
# Set style for PlaySet_btn_18, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_18.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_18.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_18.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_18.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_18.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_18.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_18.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_18.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_18.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_18.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_18.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_17
PlaySet_line_17 = lv.line(PlaySet_tileview_2_tile)
PlaySet_line_17_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_17.set_points(PlaySet_line_17_line_points, 2)
PlaySet_line_17.set_pos(45, 131)
PlaySet_line_17.set_size(505, 22)
# Set style for PlaySet_line_17, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_17.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_17.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_17.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_17.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_17
PlaySet_btn_17 = lv.btn(PlaySet_tileview_2_tile)
PlaySet_btn_17_label = lv.label(PlaySet_btn_17)
PlaySet_btn_17_label.set_text("")
PlaySet_btn_17_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_17_label.set_width(lv.pct(100))
PlaySet_btn_17_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_17.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_17.set_pos(500, 89)
PlaySet_btn_17.set_size(35, 35)
# Set style for PlaySet_btn_17, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_17.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_17.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_17.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_17.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_17.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_17.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_17.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_17.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_17.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_17.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_17.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_17
PlaySet_label_17 = lv.label(PlaySet_tileview_2_tile)
PlaySet_label_17.set_text("屏保")
PlaySet_label_17.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_17.set_width(lv.pct(100))
PlaySet_label_17.set_pos(50, 94)
PlaySet_label_17.set_size(100, 32)
# Set style for PlaySet_label_17, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_17.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_17.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_17.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_17.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_17.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_17.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_17.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_17.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_17.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_17.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_17.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_17.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_17.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_17.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_16
PlaySet_btn_16 = lv.btn(PlaySet_tileview_2_tile)
PlaySet_btn_16_label = lv.label(PlaySet_btn_16)
PlaySet_btn_16_label.set_text("")
PlaySet_btn_16_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_16_label.set_width(lv.pct(100))
PlaySet_btn_16_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_16.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_16.set_pos(500, 164)
PlaySet_btn_16.set_size(35, 35)
# Set style for PlaySet_btn_16, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_16.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_16.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_16.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_16.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_16.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_16.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_16.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_16.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_16.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_16.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_16.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_16
PlaySet_line_16 = lv.line(PlaySet_tileview_2_tile)
PlaySet_line_16_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_16.set_points(PlaySet_line_16_line_points, 2)
PlaySet_line_16.set_pos(45, 207)
PlaySet_line_16.set_size(505, 22)
# Set style for PlaySet_line_16, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_16.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_16.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_16.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_16.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_16
PlaySet_label_16 = lv.label(PlaySet_tileview_2_tile)
PlaySet_label_16.set_text("场景")
PlaySet_label_16.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_16.set_width(lv.pct(100))
PlaySet_label_16.set_pos(50, 170)
PlaySet_label_16.set_size(100, 32)
# Set style for PlaySet_label_16, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_16.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_16.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_16.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_16.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_16.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_16.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_16.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_16.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_16.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_16.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_16.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_16.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_16.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_16.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_15
PlaySet_btn_15 = lv.btn(PlaySet_tileview_2_tile)
PlaySet_btn_15_label = lv.label(PlaySet_btn_15)
PlaySet_btn_15_label.set_text("")
PlaySet_btn_15_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_15_label.set_width(lv.pct(100))
PlaySet_btn_15_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_15.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_15.set_pos(500, 239)
PlaySet_btn_15.set_size(35, 35)
# Set style for PlaySet_btn_15, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_15.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_15.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_15.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_15.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_15.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_15.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_15.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_15.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_15.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_15.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_15.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_15
PlaySet_line_15 = lv.line(PlaySet_tileview_2_tile)
PlaySet_line_15_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_15.set_points(PlaySet_line_15_line_points, 2)
PlaySet_line_15.set_pos(45, 283)
PlaySet_line_15.set_size(505, 22)
# Set style for PlaySet_line_15, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_15.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_15.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_15.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_15.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_15
PlaySet_label_15 = lv.label(PlaySet_tileview_2_tile)
PlaySet_label_15.set_text("开关\n")
PlaySet_label_15.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_15.set_width(lv.pct(100))
PlaySet_label_15.set_pos(50, 246)
PlaySet_label_15.set_size(100, 32)
# Set style for PlaySet_label_15, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_15.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_15.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_15.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_15.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_15.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_15.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_15.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_15.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_15.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_15.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_15.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_15.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_15.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_15.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_14
PlaySet_btn_14 = lv.btn(PlaySet_tileview_2_tile)
PlaySet_btn_14_label = lv.label(PlaySet_btn_14)
PlaySet_btn_14_label.set_text("")
PlaySet_btn_14_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_14_label.set_width(lv.pct(100))
PlaySet_btn_14_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_14.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_14.set_pos(500, 314)
PlaySet_btn_14.set_size(35, 35)
# Set style for PlaySet_btn_14, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_14.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_14.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_14.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_14.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_14.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_14.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_14.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_14.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_14.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_14.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_14.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_14
PlaySet_line_14 = lv.line(PlaySet_tileview_2_tile)
PlaySet_line_14_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_14.set_points(PlaySet_line_14_line_points, 2)
PlaySet_line_14.set_pos(45, 359)
PlaySet_line_14.set_size(505, 22)
# Set style for PlaySet_line_14, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_14.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_14.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_14.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_14.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_14
PlaySet_label_14 = lv.label(PlaySet_tileview_2_tile)
PlaySet_label_14.set_text("设备")
PlaySet_label_14.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_14.set_width(lv.pct(100))
PlaySet_label_14.set_pos(50, 322)
PlaySet_label_14.set_size(100, 32)
# Set style for PlaySet_label_14, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_14.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_14.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_14.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_14.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_14.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_14.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_14.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_14.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_14.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_14.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_14.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_14.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_14.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_14.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_13
PlaySet_btn_13 = lv.btn(PlaySet_tileview_2_tile)
PlaySet_btn_13_label = lv.label(PlaySet_btn_13)
PlaySet_btn_13_label.set_text("")
PlaySet_btn_13_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_13_label.set_width(lv.pct(100))
PlaySet_btn_13_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_13.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_13.set_pos(500, 389)
PlaySet_btn_13.set_size(35, 35)
# Set style for PlaySet_btn_13, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_13.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_13.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_13.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_13.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_13.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_13.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_13.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_13.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_13.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_13.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_13.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_13
PlaySet_line_13 = lv.line(PlaySet_tileview_2_tile)
PlaySet_line_13_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_13.set_points(PlaySet_line_13_line_points, 2)
PlaySet_line_13.set_pos(45, 435)
PlaySet_line_13.set_size(505, 22)
# Set style for PlaySet_line_13, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_13.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_13.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_13.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_13.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_13
PlaySet_label_13 = lv.label(PlaySet_tileview_2_tile)
PlaySet_label_13.set_text("灯光")
PlaySet_label_13.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_13.set_width(lv.pct(100))
PlaySet_label_13.set_pos(50, 398)
PlaySet_label_13.set_size(100, 32)
# Set style for PlaySet_label_13, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_13.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_13.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_13.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_13.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_13.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_13.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_13.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_13.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_13.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_13.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_13.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_13.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_13.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_13.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_12
PlaySet_line_12 = lv.line(PlaySet_tileview_2_tile)
PlaySet_line_12_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_12.set_points(PlaySet_line_12_line_points, 2)
PlaySet_line_12.set_pos(45, 511)
PlaySet_line_12.set_size(505, 22)
# Set style for PlaySet_line_12, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_12.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_12.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_12.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_12.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_12
PlaySet_btn_12 = lv.btn(PlaySet_tileview_2_tile)
PlaySet_btn_12_label = lv.label(PlaySet_btn_12)
PlaySet_btn_12_label.set_text("")
PlaySet_btn_12_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_12_label.set_width(lv.pct(100))
PlaySet_btn_12_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_12.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_12.set_pos(500, 464)
PlaySet_btn_12.set_size(35, 35)
# Set style for PlaySet_btn_12, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_12.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_12.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_12.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_12.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_12.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_12.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_12.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_12.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_12.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_12.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_12.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_12
PlaySet_label_12 = lv.label(PlaySet_tileview_2_tile)
PlaySet_label_12.set_text("窗帘")
PlaySet_label_12.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_12.set_width(lv.pct(100))
PlaySet_label_12.set_pos(50, 474)
PlaySet_label_12.set_size(100, 32)
# Set style for PlaySet_label_12, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_12.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_12.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_12.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_12.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_12.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_12.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_12.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_12.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_12.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_12.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_12.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_12.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_12.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_12.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_tileview_3
PlaySet_tileview_3 = lv.tileview(PlaySet)
PlaySet_tileview_3_tile = PlaySet_tileview_3.add_tile(0, 0, lv.DIR.RIGHT)
PlaySet_tileview_3.set_pos(2662, 16)
PlaySet_tileview_3.set_size(600, 245)
PlaySet_tileview_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for PlaySet_tileview_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_tileview_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tileview_3.set_style_bg_color(lv.color_hex(0xf6f6f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tileview_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tileview_3.set_style_radius(10, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_tileview_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for PlaySet_tileview_3, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
PlaySet_tileview_3.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
PlaySet_tileview_3.set_style_bg_color(lv.color_hex(0xeaeff3), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
PlaySet_tileview_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
PlaySet_tileview_3.set_style_radius(0, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create PlaySet_line_25
PlaySet_line_25 = lv.line(PlaySet_tileview_3_tile)
PlaySet_line_25_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_25.set_points(PlaySet_line_25_line_points, 2)
PlaySet_line_25.set_pos(45, 55)
PlaySet_line_25.set_size(505, 22)
# Set style for PlaySet_line_25, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_25.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_25.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_25.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_25.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_25
PlaySet_label_25 = lv.label(PlaySet_tileview_3_tile)
PlaySet_label_25.set_text("关闭")
PlaySet_label_25.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_25.set_width(lv.pct(100))
PlaySet_label_25.set_pos(50, 18)
PlaySet_label_25.set_size(100, 32)
# Set style for PlaySet_label_25, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_25.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_25.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_25.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_25.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_25.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_25.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_25.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_25.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_25.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_25.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_25.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_25.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_25.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_25.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_25
PlaySet_btn_25 = lv.btn(PlaySet_tileview_3_tile)
PlaySet_btn_25_label = lv.label(PlaySet_btn_25)
PlaySet_btn_25_label.set_text("")
PlaySet_btn_25_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_25_label.set_width(lv.pct(100))
PlaySet_btn_25_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_25.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_25.set_pos(500, 14)
PlaySet_btn_25.set_size(35, 35)
# Set style for PlaySet_btn_25, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_25.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_25.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_25.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_25.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_25.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_25.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_25.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_25.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_25.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_25.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_25.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_24
PlaySet_line_24 = lv.line(PlaySet_tileview_3_tile)
PlaySet_line_24_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_24.set_points(PlaySet_line_24_line_points, 2)
PlaySet_line_24.set_pos(45, 131)
PlaySet_line_24.set_size(505, 22)
# Set style for PlaySet_line_24, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_24.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_24.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_24.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_24.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_24
PlaySet_btn_24 = lv.btn(PlaySet_tileview_3_tile)
PlaySet_btn_24_label = lv.label(PlaySet_btn_24)
PlaySet_btn_24_label.set_text("")
PlaySet_btn_24_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_24_label.set_width(lv.pct(100))
PlaySet_btn_24_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_24.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_24.set_pos(500, 89)
PlaySet_btn_24.set_size(35, 35)
# Set style for PlaySet_btn_24, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_24.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_24.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_24.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_24.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_24.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_24.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_24.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_24.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_24.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_24.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_24.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_24
PlaySet_label_24 = lv.label(PlaySet_tileview_3_tile)
PlaySet_label_24.set_text("近")
PlaySet_label_24.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_24.set_width(lv.pct(100))
PlaySet_label_24.set_pos(50, 94)
PlaySet_label_24.set_size(100, 32)
# Set style for PlaySet_label_24, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_24.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_24.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_24.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_24.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_24.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_24.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_24.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_24.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_24.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_24.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_24.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_24.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_24.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_24.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_23
PlaySet_btn_23 = lv.btn(PlaySet_tileview_3_tile)
PlaySet_btn_23_label = lv.label(PlaySet_btn_23)
PlaySet_btn_23_label.set_text("")
PlaySet_btn_23_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_23_label.set_width(lv.pct(100))
PlaySet_btn_23_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_23.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_23.set_pos(500, 164)
PlaySet_btn_23.set_size(35, 35)
# Set style for PlaySet_btn_23, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_23.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_23.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_23.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_23.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_23.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_23.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_23.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_23.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_23.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_23.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_23.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_23
PlaySet_line_23 = lv.line(PlaySet_tileview_3_tile)
PlaySet_line_23_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_23.set_points(PlaySet_line_23_line_points, 2)
PlaySet_line_23.set_pos(45, 207)
PlaySet_line_23.set_size(505, 22)
# Set style for PlaySet_line_23, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_23.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_23.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_23.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_23.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_23
PlaySet_label_23 = lv.label(PlaySet_tileview_3_tile)
PlaySet_label_23.set_text("中")
PlaySet_label_23.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_23.set_width(lv.pct(100))
PlaySet_label_23.set_pos(50, 170)
PlaySet_label_23.set_size(100, 32)
# Set style for PlaySet_label_23, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_23.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_23.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_23.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_23.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_23.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_23.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_23.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_23.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_23.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_23.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_23.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_23.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_23.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_23.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_btn_22
PlaySet_btn_22 = lv.btn(PlaySet_tileview_3_tile)
PlaySet_btn_22_label = lv.label(PlaySet_btn_22)
PlaySet_btn_22_label.set_text("")
PlaySet_btn_22_label.set_long_mode(lv.label.LONG.WRAP)
PlaySet_btn_22_label.set_width(lv.pct(100))
PlaySet_btn_22_label.align(lv.ALIGN.LEFT_MID, 0, 0)
PlaySet_btn_22.set_style_pad_all(0, lv.STATE.DEFAULT)
PlaySet_btn_22.set_pos(500, 239)
PlaySet_btn_22.set_size(35, 35)
# Set style for PlaySet_btn_22, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_btn_22.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_22.set_style_border_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_22.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_22.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_22.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_22.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_22.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_22.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_22.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_22.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_btn_22.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_line_22
PlaySet_line_22 = lv.line(PlaySet_tileview_3_tile)
PlaySet_line_22_line_points = [{"x":500, "y":0},{"x":0, "y":0},]
PlaySet_line_22.set_points(PlaySet_line_22_line_points, 2)
PlaySet_line_22.set_pos(45, 283)
PlaySet_line_22.set_size(505, 22)
# Set style for PlaySet_line_22, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_line_22.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_22.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_22.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_line_22.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_22
PlaySet_label_22 = lv.label(PlaySet_tileview_3_tile)
PlaySet_label_22.set_text("远\n")
PlaySet_label_22.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_22.set_width(lv.pct(100))
PlaySet_label_22.set_pos(50, 246)
PlaySet_label_22.set_size(100, 32)
# Set style for PlaySet_label_22, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_22.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_22.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_22.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_22.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_22.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_22.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_22.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_22.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_22.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_22.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_22.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_22.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_22.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_22.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_1
PlaySet_label_1 = lv.label(PlaySet)
PlaySet_label_1.set_text("30秒")
PlaySet_label_1.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_1.set_width(lv.pct(100))
PlaySet_label_1.set_pos(533, 114)
PlaySet_label_1.set_size(100, 32)
# Set style for PlaySet_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_2
PlaySet_label_2 = lv.label(PlaySet)
PlaySet_label_2.set_text("熄屏")
PlaySet_label_2.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_2.set_width(lv.pct(100))
PlaySet_label_2.set_pos(533, 203)
PlaySet_label_2.set_size(100, 32)
# Set style for PlaySet_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_2.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create PlaySet_label_3
PlaySet_label_3 = lv.label(PlaySet)
PlaySet_label_3.set_text("关闭")
PlaySet_label_3.set_long_mode(lv.label.LONG.WRAP)
PlaySet_label_3.set_width(lv.pct(100))
PlaySet_label_3.set_pos(533, 292)
PlaySet_label_3.set_size(100, 32)
# Set style for PlaySet_label_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
PlaySet_label_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_3.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_3.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_3.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
PlaySet_label_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

PlaySet.update_layout()
# Create SwitchSet
SwitchSet = lv.obj()
SwitchSet.set_size(720, 720)
SwitchSet.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for SwitchSet, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SwitchSet_tabview_1
SwitchSet_tabview_1 = lv.tabview(SwitchSet, lv.DIR.TOP, 85)
SwitchSet_tabview_1.set_pos(0, 0)
SwitchSet_tabview_1.set_size(720, 720)
SwitchSet_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for SwitchSet_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for SwitchSet_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_SwitchSet_tabview_1_extra_btnm_main_default = lv.style_t()
style_SwitchSet_tabview_1_extra_btnm_main_default.init()
style_SwitchSet_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_SwitchSet_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_SwitchSet_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_SwitchSet_tabview_1_extra_btnm_main_default.set_border_width(0)
style_SwitchSet_tabview_1_extra_btnm_main_default.set_radius(0)
SwitchSet_tabview_1.get_tab_btns().add_style(style_SwitchSet_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for SwitchSet_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_SwitchSet_tabview_1_extra_btnm_items_default = lv.style_t()
style_SwitchSet_tabview_1_extra_btnm_items_default.init()
style_SwitchSet_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_SwitchSet_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_SwitchSet_tabview_1_extra_btnm_items_default.set_text_opa(255)
SwitchSet_tabview_1.get_tab_btns().add_style(style_SwitchSet_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for SwitchSet_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_SwitchSet_tabview_1_extra_btnm_items_checked = lv.style_t()
style_SwitchSet_tabview_1_extra_btnm_items_checked.init()
style_SwitchSet_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_SwitchSet_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_SwitchSet_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_SwitchSet_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_SwitchSet_tabview_1_extra_btnm_items_checked.set_radius(0)
style_SwitchSet_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_SwitchSet_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_SwitchSet_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
SwitchSet_tabview_1.get_tab_btns().add_style(style_SwitchSet_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
SwitchSet_tabview_1_tab_1 = SwitchSet_tabview_1.add_tab("")
SwitchSet_tabview_1_tab_1_label = lv.label(SwitchSet_tabview_1_tab_1)
SwitchSet_tabview_1_tab_1_label.set_text("")

# Create SwitchSet_cont_2
SwitchSet_cont_2 = lv.obj(SwitchSet)
SwitchSet_cont_2.set_pos(-1, 516)
SwitchSet_cont_2.set_size(720, 201)
SwitchSet_cont_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for SwitchSet_cont_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_cont_2.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_2.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_2.set_style_border_color(lv.color_hex(0x151313), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_2.set_style_border_side(lv.BORDER_SIDE.BOTTOM, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_2.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_2.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create SwitchSet_btn_5
SwitchSet_btn_5 = lv.btn(SwitchSet_cont_2)
SwitchSet_btn_5_label = lv.label(SwitchSet_btn_5)
SwitchSet_btn_5_label.set_text("清除已学")
SwitchSet_btn_5_label.set_long_mode(lv.label.LONG.WRAP)
SwitchSet_btn_5_label.set_width(lv.pct(100))
SwitchSet_btn_5_label.align(lv.ALIGN.CENTER, 0, 0)
SwitchSet_btn_5.set_style_pad_all(0, lv.STATE.DEFAULT)
SwitchSet_btn_5.set_pos(490, 25)
SwitchSet_btn_5.set_size(180, 50)
# Set style for SwitchSet_btn_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_btn_5.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_5.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_5.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_5.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_5.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_5.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SwitchSet_btn_4
SwitchSet_btn_4 = lv.btn(SwitchSet_cont_2)
SwitchSet_btn_4_label = lv.label(SwitchSet_btn_4)
SwitchSet_btn_4_label.set_text("开始学码")
SwitchSet_btn_4_label.set_long_mode(lv.label.LONG.WRAP)
SwitchSet_btn_4_label.set_width(lv.pct(100))
SwitchSet_btn_4_label.align(lv.ALIGN.CENTER, 0, 0)
SwitchSet_btn_4.set_style_pad_all(0, lv.STATE.DEFAULT)
SwitchSet_btn_4.set_pos(490, 121)
SwitchSet_btn_4.set_size(180, 50)
# Set style for SwitchSet_btn_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_btn_4.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_4.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_4.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_4.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_4.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SwitchSet_label_2
SwitchSet_label_2 = lv.label(SwitchSet_cont_2)
SwitchSet_label_2.set_text("按键3  互控")
SwitchSet_label_2.set_long_mode(lv.label.LONG.WRAP)
SwitchSet_label_2.set_width(lv.pct(100))
SwitchSet_label_2.set_pos(14, 86)
SwitchSet_label_2.set_size(170, 40)
# Set style for SwitchSet_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_2.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SwitchSet_cont_1
SwitchSet_cont_1 = lv.obj(SwitchSet)
SwitchSet_cont_1.set_pos(-1, 85)
SwitchSet_cont_1.set_size(720, 215)
SwitchSet_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for SwitchSet_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_cont_1.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_1.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_1.set_style_border_color(lv.color_hex(0x151313), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_1.set_style_border_side(lv.BORDER_SIDE.BOTTOM, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_1.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create SwitchSet_btn_2
SwitchSet_btn_2 = lv.btn(SwitchSet_cont_1)
SwitchSet_btn_2_label = lv.label(SwitchSet_btn_2)
SwitchSet_btn_2_label.set_text("清除已学")
SwitchSet_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
SwitchSet_btn_2_label.set_width(lv.pct(100))
SwitchSet_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
SwitchSet_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
SwitchSet_btn_2.set_pos(490, 26)
SwitchSet_btn_2.set_size(180, 50)
# Set style for SwitchSet_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_btn_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_2.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_2.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_2.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SwitchSet_btn_3
SwitchSet_btn_3 = lv.btn(SwitchSet_cont_1)
SwitchSet_btn_3_label = lv.label(SwitchSet_btn_3)
SwitchSet_btn_3_label.set_text("开始学码")
SwitchSet_btn_3_label.set_long_mode(lv.label.LONG.WRAP)
SwitchSet_btn_3_label.set_width(lv.pct(100))
SwitchSet_btn_3_label.align(lv.ALIGN.CENTER, 0, 0)
SwitchSet_btn_3.set_style_pad_all(0, lv.STATE.DEFAULT)
SwitchSet_btn_3.set_pos(490, 122)
SwitchSet_btn_3.set_size(180, 50)
# Set style for SwitchSet_btn_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_btn_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_3.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_3.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_3.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SwitchSet_label_1
SwitchSet_label_1 = lv.label(SwitchSet_cont_1)
SwitchSet_label_1.set_text("按键1  互控")
SwitchSet_label_1.set_long_mode(lv.label.LONG.WRAP)
SwitchSet_label_1.set_width(lv.pct(100))
SwitchSet_label_1.set_pos(12, 79)
SwitchSet_label_1.set_size(170, 40)
# Set style for SwitchSet_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SwitchSet_cont_3
SwitchSet_cont_3 = lv.obj(SwitchSet)
SwitchSet_cont_3.set_pos(-2, 302)
SwitchSet_cont_3.set_size(720, 215)
SwitchSet_cont_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for SwitchSet_cont_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_cont_3.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_3.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_3.set_style_border_color(lv.color_hex(0x151313), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_3.set_style_border_side(lv.BORDER_SIDE.BOTTOM, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_3.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_3.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_cont_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create SwitchSet_btn_7
SwitchSet_btn_7 = lv.btn(SwitchSet_cont_3)
SwitchSet_btn_7_label = lv.label(SwitchSet_btn_7)
SwitchSet_btn_7_label.set_text("清除已学")
SwitchSet_btn_7_label.set_long_mode(lv.label.LONG.WRAP)
SwitchSet_btn_7_label.set_width(lv.pct(100))
SwitchSet_btn_7_label.align(lv.ALIGN.CENTER, 0, 0)
SwitchSet_btn_7.set_style_pad_all(0, lv.STATE.DEFAULT)
SwitchSet_btn_7.set_pos(490, 26)
SwitchSet_btn_7.set_size(180, 50)
# Set style for SwitchSet_btn_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_btn_7.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_7.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_7.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_7.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_7.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_7.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_7.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SwitchSet_btn_6
SwitchSet_btn_6 = lv.btn(SwitchSet_cont_3)
SwitchSet_btn_6_label = lv.label(SwitchSet_btn_6)
SwitchSet_btn_6_label.set_text("开始学码")
SwitchSet_btn_6_label.set_long_mode(lv.label.LONG.WRAP)
SwitchSet_btn_6_label.set_width(lv.pct(100))
SwitchSet_btn_6_label.align(lv.ALIGN.CENTER, 0, 0)
SwitchSet_btn_6.set_style_pad_all(0, lv.STATE.DEFAULT)
SwitchSet_btn_6.set_pos(490, 117)
SwitchSet_btn_6.set_size(180, 50)
# Set style for SwitchSet_btn_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_btn_6.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_6.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_6.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_6.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_6.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_6.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_6.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SwitchSet_label_3
SwitchSet_label_3 = lv.label(SwitchSet_cont_3)
SwitchSet_label_3.set_text("按键2  互控")
SwitchSet_label_3.set_long_mode(lv.label.LONG.WRAP)
SwitchSet_label_3.set_width(lv.pct(100))
SwitchSet_label_3.set_pos(10, 84)
SwitchSet_label_3.set_size(170, 40)
# Set style for SwitchSet_label_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_label_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_3.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_3.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_label_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SwitchSet_btn_1
SwitchSet_btn_1 = lv.btn(SwitchSet)
SwitchSet_btn_1_label = lv.label(SwitchSet_btn_1)
SwitchSet_btn_1_label.set_text("开关配置")
SwitchSet_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
SwitchSet_btn_1_label.set_width(lv.pct(100))
SwitchSet_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
SwitchSet_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
SwitchSet_btn_1.set_pos(68, 24)
SwitchSet_btn_1.set_size(152, 32)
# Set style for SwitchSet_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SwitchSet_img_1
SwitchSet_img_1 = lv.img(SwitchSet)
SwitchSet_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
SwitchSet_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
SwitchSet_img_1.set_pivot(50,50)
SwitchSet_img_1.set_angle(0)
SwitchSet_img_1.set_pos(43, 28)
SwitchSet_img_1.set_size(14, 24)
# Set style for SwitchSet_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SwitchSet_btn_8
SwitchSet_btn_8 = lv.btn(SwitchSet)
SwitchSet_btn_8_label = lv.label(SwitchSet_btn_8)
SwitchSet_btn_8_label.set_text("")
SwitchSet_btn_8_label.set_long_mode(lv.label.LONG.WRAP)
SwitchSet_btn_8_label.set_width(lv.pct(100))
SwitchSet_btn_8_label.align(lv.ALIGN.CENTER, 0, 0)
SwitchSet_btn_8.set_style_pad_all(0, lv.STATE.DEFAULT)
SwitchSet_btn_8.set_pos(-9, -13)
SwitchSet_btn_8.set_size(251, 107)
# Set style for SwitchSet_btn_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SwitchSet_btn_8.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_8.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_8.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_8.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_8.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_8.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SwitchSet_btn_8.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

SwitchSet.update_layout()
# Create SensorSet
SensorSet = lv.obj()
SensorSet.set_size(720, 720)
SensorSet.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for SensorSet, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SensorSet_tabview_1
SensorSet_tabview_1 = lv.tabview(SensorSet, lv.DIR.TOP, 85)
SensorSet_tabview_1.set_pos(0, 0)
SensorSet_tabview_1.set_size(720, 720)
SensorSet_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for SensorSet_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for SensorSet_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_SensorSet_tabview_1_extra_btnm_main_default = lv.style_t()
style_SensorSet_tabview_1_extra_btnm_main_default.init()
style_SensorSet_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_SensorSet_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_SensorSet_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_SensorSet_tabview_1_extra_btnm_main_default.set_border_width(0)
style_SensorSet_tabview_1_extra_btnm_main_default.set_radius(0)
SensorSet_tabview_1.get_tab_btns().add_style(style_SensorSet_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for SensorSet_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_SensorSet_tabview_1_extra_btnm_items_default = lv.style_t()
style_SensorSet_tabview_1_extra_btnm_items_default.init()
style_SensorSet_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_SensorSet_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_SensorSet_tabview_1_extra_btnm_items_default.set_text_opa(255)
SensorSet_tabview_1.get_tab_btns().add_style(style_SensorSet_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for SensorSet_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_SensorSet_tabview_1_extra_btnm_items_checked = lv.style_t()
style_SensorSet_tabview_1_extra_btnm_items_checked.init()
style_SensorSet_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_SensorSet_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_SensorSet_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_SensorSet_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_SensorSet_tabview_1_extra_btnm_items_checked.set_radius(0)
style_SensorSet_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_SensorSet_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_SensorSet_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
SensorSet_tabview_1.get_tab_btns().add_style(style_SensorSet_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
SensorSet_tabview_1_tab_1 = SensorSet_tabview_1.add_tab("")
SensorSet_tabview_1_tab_1_label = lv.label(SensorSet_tabview_1_tab_1)
SensorSet_tabview_1_tab_1_label.set_text("")

# Create SensorSet_cont_2
SensorSet_cont_2 = lv.obj(SensorSet)
SensorSet_cont_2.set_pos(11, 97)
SensorSet_cont_2.set_size(720, 141)
SensorSet_cont_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for SensorSet_cont_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_cont_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_2.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_2.set_style_bg_color(lv.color_hex(0x4a3a3a), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create SensorSet_label_5
SensorSet_label_5 = lv.label(SensorSet_cont_2)
SensorSet_label_5.set_text("温度")
SensorSet_label_5.set_long_mode(lv.label.LONG.WRAP)
SensorSet_label_5.set_width(lv.pct(100))
SensorSet_label_5.set_pos(7, 8)
SensorSet_label_5.set_size(108, 33)
# Set style for SensorSet_label_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_label_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_5.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_5.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_5.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_5.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_5.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_5.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_5.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_5.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_5.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_5.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SensorSet_cont_3
SensorSet_cont_3 = lv.obj(SensorSet_cont_2)
SensorSet_cont_3.set_pos(31, 54)
SensorSet_cont_3.set_size(648, 49)
SensorSet_cont_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for SensorSet_cont_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_cont_3.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_3.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_3.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_3.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_3.set_style_bg_color(lv.color_hex(0x8f8181), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create SensorSet_label_6
SensorSet_label_6 = lv.label(SensorSet_cont_3)
SensorSet_label_6.set_text("型号")
SensorSet_label_6.set_long_mode(lv.label.LONG.WRAP)
SensorSet_label_6.set_width(lv.pct(100))
SensorSet_label_6.set_pos(4, 8)
SensorSet_label_6.set_size(100, 32)
# Set style for SensorSet_label_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_label_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_6.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_6.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_6.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_6.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_6.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_6.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_6.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_6.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_6.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_6.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_6.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SensorSet_btn_11
SensorSet_btn_11 = lv.btn(SensorSet_cont_3)
SensorSet_btn_11_label = lv.label(SensorSet_btn_11)
SensorSet_btn_11_label.set_text("")
SensorSet_btn_11_label.set_long_mode(lv.label.LONG.WRAP)
SensorSet_btn_11_label.set_width(lv.pct(100))
SensorSet_btn_11_label.align(lv.ALIGN.CENTER, 0, 0)
SensorSet_btn_11.set_style_pad_all(0, lv.STATE.DEFAULT)
SensorSet_btn_11.set_pos(586, 11)
SensorSet_btn_11.set_size(26, 24)
# Set style for SensorSet_btn_11, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_btn_11.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_11.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_11.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_11.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_11.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_11.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_11.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_11.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_11.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_11.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SensorSet_label_7
SensorSet_label_7 = lv.label(SensorSet_cont_3)
SensorSet_label_7.set_text("温度")
SensorSet_label_7.set_long_mode(lv.label.LONG.WRAP)
SensorSet_label_7.set_width(lv.pct(100))
SensorSet_label_7.set_pos(487, 13)
SensorSet_label_7.set_size(100, 32)
# Set style for SensorSet_label_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_label_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_7.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_7.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_7.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_7.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_7.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_7.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_7.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_7.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_7.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_7.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_7.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SensorSet_cont_4
SensorSet_cont_4 = lv.obj(SensorSet)
SensorSet_cont_4.set_pos(11, 249)
SensorSet_cont_4.set_size(720, 141)
SensorSet_cont_4.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for SensorSet_cont_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_cont_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_4.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_4.set_style_bg_color(lv.color_hex(0x4a3a3a), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_4.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_4.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_4.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_4.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_4.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create SensorSet_label_10
SensorSet_label_10 = lv.label(SensorSet_cont_4)
SensorSet_label_10.set_text("湿度")
SensorSet_label_10.set_long_mode(lv.label.LONG.WRAP)
SensorSet_label_10.set_width(lv.pct(100))
SensorSet_label_10.set_pos(8, 7)
SensorSet_label_10.set_size(108, 33)
# Set style for SensorSet_label_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_label_10.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_10.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_10.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_10.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_10.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_10.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_10.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_10.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_10.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_10.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_10.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_10.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_10.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_10.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SensorSet_cont_5
SensorSet_cont_5 = lv.obj(SensorSet_cont_4)
SensorSet_cont_5.set_pos(31, 53)
SensorSet_cont_5.set_size(648, 49)
SensorSet_cont_5.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for SensorSet_cont_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_cont_5.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_5.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_5.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_5.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_5.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_5.set_style_bg_color(lv.color_hex(0x8f8181), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_5.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_5.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_5.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_5.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_cont_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create SensorSet_label_9
SensorSet_label_9 = lv.label(SensorSet_cont_5)
SensorSet_label_9.set_text("型号")
SensorSet_label_9.set_long_mode(lv.label.LONG.WRAP)
SensorSet_label_9.set_width(lv.pct(100))
SensorSet_label_9.set_pos(4, 8)
SensorSet_label_9.set_size(100, 32)
# Set style for SensorSet_label_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_label_9.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_9.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_9.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_9.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_9.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_9.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_9.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_9.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_9.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_9.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_9.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_9.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_9.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_9.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SensorSet_btn_12
SensorSet_btn_12 = lv.btn(SensorSet_cont_5)
SensorSet_btn_12_label = lv.label(SensorSet_btn_12)
SensorSet_btn_12_label.set_text("")
SensorSet_btn_12_label.set_long_mode(lv.label.LONG.WRAP)
SensorSet_btn_12_label.set_width(lv.pct(100))
SensorSet_btn_12_label.align(lv.ALIGN.CENTER, 0, 0)
SensorSet_btn_12.set_style_pad_all(0, lv.STATE.DEFAULT)
SensorSet_btn_12.set_pos(586, 11)
SensorSet_btn_12.set_size(26, 24)
# Set style for SensorSet_btn_12, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_btn_12.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_12.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_12.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_12.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_12.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_12.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_12.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_12.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_12.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_12.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SensorSet_label_8
SensorSet_label_8 = lv.label(SensorSet_cont_5)
SensorSet_label_8.set_text("湿度")
SensorSet_label_8.set_long_mode(lv.label.LONG.WRAP)
SensorSet_label_8.set_width(lv.pct(100))
SensorSet_label_8.set_pos(487, 13)
SensorSet_label_8.set_size(100, 32)
# Set style for SensorSet_label_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_label_8.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_8.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_8.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_8.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_8.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_8.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_8.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_8.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_8.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_8.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_8.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_8.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_8.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_label_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SensorSet_btn_1
SensorSet_btn_1 = lv.btn(SensorSet)
SensorSet_btn_1_label = lv.label(SensorSet_btn_1)
SensorSet_btn_1_label.set_text("传感器配置")
SensorSet_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
SensorSet_btn_1_label.set_width(lv.pct(100))
SensorSet_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
SensorSet_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
SensorSet_btn_1.set_pos(70, 24)
SensorSet_btn_1.set_size(186, 32)
# Set style for SensorSet_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SensorSet_img_1
SensorSet_img_1 = lv.img(SensorSet)
SensorSet_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
SensorSet_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
SensorSet_img_1.set_pivot(50,50)
SensorSet_img_1.set_angle(0)
SensorSet_img_1.set_pos(43, 28)
SensorSet_img_1.set_size(14, 24)
# Set style for SensorSet_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create SensorSet_btn_13
SensorSet_btn_13 = lv.btn(SensorSet)
SensorSet_btn_13_label = lv.label(SensorSet_btn_13)
SensorSet_btn_13_label.set_text("")
SensorSet_btn_13_label.set_long_mode(lv.label.LONG.WRAP)
SensorSet_btn_13_label.set_width(lv.pct(100))
SensorSet_btn_13_label.align(lv.ALIGN.CENTER, 0, 0)
SensorSet_btn_13.set_style_pad_all(0, lv.STATE.DEFAULT)
SensorSet_btn_13.set_pos(-6, -15)
SensorSet_btn_13.set_size(272, 111)
# Set style for SensorSet_btn_13, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
SensorSet_btn_13.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_13.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_13.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_13.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_13.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_13.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_13.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
SensorSet_btn_13.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

SensorSet.update_layout()
# Create Reset
Reset = lv.obj()
Reset.set_size(720, 720)
Reset.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Reset, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Reset.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Reset_tile
Reset_tile = lv.tabview(Reset, lv.DIR.TOP, 85)
Reset_tile.set_pos(0, 0)
Reset_tile.set_size(720, 720)
Reset_tile.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for Reset_tile, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Reset_tile.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_tile.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_tile.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_tile.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_tile.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_tile.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_tile.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_tile.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_tile.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_tile.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_tile.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for Reset_tile, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_Reset_tile_extra_btnm_main_default = lv.style_t()
style_Reset_tile_extra_btnm_main_default.init()
style_Reset_tile_extra_btnm_main_default.set_bg_opa(255)
style_Reset_tile_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_Reset_tile_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_Reset_tile_extra_btnm_main_default.set_border_width(0)
style_Reset_tile_extra_btnm_main_default.set_radius(0)
Reset_tile.get_tab_btns().add_style(style_Reset_tile_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for Reset_tile, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_Reset_tile_extra_btnm_items_default = lv.style_t()
style_Reset_tile_extra_btnm_items_default.init()
style_Reset_tile_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_Reset_tile_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_Reset_tile_extra_btnm_items_default.set_text_opa(255)
Reset_tile.get_tab_btns().add_style(style_Reset_tile_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for Reset_tile, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_Reset_tile_extra_btnm_items_checked = lv.style_t()
style_Reset_tile_extra_btnm_items_checked.init()
style_Reset_tile_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_Reset_tile_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_Reset_tile_extra_btnm_items_checked.set_text_opa(255)
style_Reset_tile_extra_btnm_items_checked.set_border_width(0)
style_Reset_tile_extra_btnm_items_checked.set_radius(0)
style_Reset_tile_extra_btnm_items_checked.set_bg_opa(255)
style_Reset_tile_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_Reset_tile_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
Reset_tile.get_tab_btns().add_style(style_Reset_tile_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
Reset_tile_tab_1 = Reset_tile.add_tab("")
Reset_tile_tab_1_label = lv.label(Reset_tile_tab_1)
Reset_tile_tab_1_label.set_text("")

# Create Reset_btn_1
Reset_btn_1 = lv.btn(Reset)
Reset_btn_1_label = lv.label(Reset_btn_1)
Reset_btn_1_label.set_text("设备重启")
Reset_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
Reset_btn_1_label.set_width(lv.pct(100))
Reset_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
Reset_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
Reset_btn_1.set_pos(70, 25)
Reset_btn_1.set_size(152, 32)
# Set style for Reset_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Reset_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Reset_label_1
Reset_label_1 = lv.label(Reset)
Reset_label_1.set_text("是否重启设备?")
Reset_label_1.set_long_mode(lv.label.LONG.WRAP)
Reset_label_1.set_width(lv.pct(100))
Reset_label_1.set_pos(237, 255)
Reset_label_1.set_size(229, 58)
# Set style for Reset_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Reset_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_label_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Reset_btn_2
Reset_btn_2 = lv.btn(Reset)
Reset_btn_2_label = lv.label(Reset_btn_2)
Reset_btn_2_label.set_text("取消")
Reset_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
Reset_btn_2_label.set_width(lv.pct(100))
Reset_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
Reset_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
Reset_btn_2.set_pos(30, 600)
Reset_btn_2.set_size(290, 70)
# Set style for Reset_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Reset_btn_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_2.set_style_bg_color(lv.color_hex(0x232425), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_2.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_2.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Reset_btn_5
Reset_btn_5 = lv.btn(Reset)
Reset_btn_5_label = lv.label(Reset_btn_5)
Reset_btn_5_label.set_text("重启")
Reset_btn_5_label.set_long_mode(lv.label.LONG.WRAP)
Reset_btn_5_label.set_width(lv.pct(100))
Reset_btn_5_label.align(lv.ALIGN.CENTER, 0, 0)
Reset_btn_5.set_style_pad_all(0, lv.STATE.DEFAULT)
Reset_btn_5.set_pos(400, 600)
Reset_btn_5.set_size(290, 70)
# Set style for Reset_btn_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Reset_btn_5.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_5.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_5.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_5.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_5.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_5.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Reset_img_1
Reset_img_1 = lv.img(Reset)
Reset_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
Reset_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
Reset_img_1.set_pivot(50,50)
Reset_img_1.set_angle(0)
Reset_img_1.set_pos(43, 28)
Reset_img_1.set_size(14, 24)
# Set style for Reset_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Reset_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Reset_btn_4
Reset_btn_4 = lv.btn(Reset)
Reset_btn_4_label = lv.label(Reset_btn_4)
Reset_btn_4_label.set_text("")
Reset_btn_4_label.set_long_mode(lv.label.LONG.WRAP)
Reset_btn_4_label.set_width(lv.pct(100))
Reset_btn_4_label.align(lv.ALIGN.CENTER, 0, 0)
Reset_btn_4.set_style_pad_all(0, lv.STATE.DEFAULT)
Reset_btn_4.set_pos(-6, -15)
Reset_btn_4.set_size(241, 108)
# Set style for Reset_btn_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Reset_btn_4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_4.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Reset_btn_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

Reset.update_layout()
# Create huifuchuchangshezhi
huifuchuchangshezhi = lv.obj()
huifuchuchangshezhi.set_size(720, 720)
huifuchuchangshezhi.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for huifuchuchangshezhi, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
huifuchuchangshezhi.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create huifuchuchangshezhi_tile
huifuchuchangshezhi_tile = lv.tabview(huifuchuchangshezhi, lv.DIR.TOP, 85)
huifuchuchangshezhi_tile.set_pos(0, 0)
huifuchuchangshezhi_tile.set_size(720, 720)
huifuchuchangshezhi_tile.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for huifuchuchangshezhi_tile, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
huifuchuchangshezhi_tile.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_tile.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_tile.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_tile.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_tile.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_tile.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_tile.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_tile.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_tile.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_tile.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_tile.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for huifuchuchangshezhi_tile, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_huifuchuchangshezhi_tile_extra_btnm_main_default = lv.style_t()
style_huifuchuchangshezhi_tile_extra_btnm_main_default.init()
style_huifuchuchangshezhi_tile_extra_btnm_main_default.set_bg_opa(255)
style_huifuchuchangshezhi_tile_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_huifuchuchangshezhi_tile_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_huifuchuchangshezhi_tile_extra_btnm_main_default.set_border_width(0)
style_huifuchuchangshezhi_tile_extra_btnm_main_default.set_radius(0)
huifuchuchangshezhi_tile.get_tab_btns().add_style(style_huifuchuchangshezhi_tile_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for huifuchuchangshezhi_tile, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_huifuchuchangshezhi_tile_extra_btnm_items_default = lv.style_t()
style_huifuchuchangshezhi_tile_extra_btnm_items_default.init()
style_huifuchuchangshezhi_tile_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_huifuchuchangshezhi_tile_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_huifuchuchangshezhi_tile_extra_btnm_items_default.set_text_opa(255)
huifuchuchangshezhi_tile.get_tab_btns().add_style(style_huifuchuchangshezhi_tile_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for huifuchuchangshezhi_tile, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_huifuchuchangshezhi_tile_extra_btnm_items_checked = lv.style_t()
style_huifuchuchangshezhi_tile_extra_btnm_items_checked.init()
style_huifuchuchangshezhi_tile_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_huifuchuchangshezhi_tile_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_huifuchuchangshezhi_tile_extra_btnm_items_checked.set_text_opa(255)
style_huifuchuchangshezhi_tile_extra_btnm_items_checked.set_border_width(0)
style_huifuchuchangshezhi_tile_extra_btnm_items_checked.set_radius(0)
style_huifuchuchangshezhi_tile_extra_btnm_items_checked.set_bg_opa(255)
style_huifuchuchangshezhi_tile_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_huifuchuchangshezhi_tile_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
huifuchuchangshezhi_tile.get_tab_btns().add_style(style_huifuchuchangshezhi_tile_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
huifuchuchangshezhi_tile_tab_1 = huifuchuchangshezhi_tile.add_tab("")
huifuchuchangshezhi_tile_tab_1_label = lv.label(huifuchuchangshezhi_tile_tab_1)
huifuchuchangshezhi_tile_tab_1_label.set_text("")

# Create huifuchuchangshezhi_btn_1
huifuchuchangshezhi_btn_1 = lv.btn(huifuchuchangshezhi)
huifuchuchangshezhi_btn_1_label = lv.label(huifuchuchangshezhi_btn_1)
huifuchuchangshezhi_btn_1_label.set_text("恢复出厂")
huifuchuchangshezhi_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
huifuchuchangshezhi_btn_1_label.set_width(lv.pct(100))
huifuchuchangshezhi_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
huifuchuchangshezhi_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_1.set_pos(70, 25)
huifuchuchangshezhi_btn_1.set_size(153, 32)
# Set style for huifuchuchangshezhi_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
huifuchuchangshezhi_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create huifuchuchangshezhi_label_1
huifuchuchangshezhi_label_1 = lv.label(huifuchuchangshezhi)
huifuchuchangshezhi_label_1.set_text("清除所有数据,请谨慎确认!")
huifuchuchangshezhi_label_1.set_long_mode(lv.label.LONG.WRAP)
huifuchuchangshezhi_label_1.set_width(lv.pct(100))
huifuchuchangshezhi_label_1.set_pos(176, 297)
huifuchuchangshezhi_label_1.set_size(368, 58)
# Set style for huifuchuchangshezhi_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
huifuchuchangshezhi_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_label_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create huifuchuchangshezhi_btn_2
huifuchuchangshezhi_btn_2 = lv.btn(huifuchuchangshezhi)
huifuchuchangshezhi_btn_2_label = lv.label(huifuchuchangshezhi_btn_2)
huifuchuchangshezhi_btn_2_label.set_text("取消")
huifuchuchangshezhi_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
huifuchuchangshezhi_btn_2_label.set_width(lv.pct(100))
huifuchuchangshezhi_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
huifuchuchangshezhi_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_2.set_pos(30, 600)
huifuchuchangshezhi_btn_2.set_size(290, 70)
# Set style for huifuchuchangshezhi_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
huifuchuchangshezhi_btn_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_2.set_style_bg_color(lv.color_hex(0x232425), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_2.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_2.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create huifuchuchangshezhi_btn_3
huifuchuchangshezhi_btn_3 = lv.btn(huifuchuchangshezhi)
huifuchuchangshezhi_btn_3_label = lv.label(huifuchuchangshezhi_btn_3)
huifuchuchangshezhi_btn_3_label.set_text("重置")
huifuchuchangshezhi_btn_3_label.set_long_mode(lv.label.LONG.WRAP)
huifuchuchangshezhi_btn_3_label.set_width(lv.pct(100))
huifuchuchangshezhi_btn_3_label.align(lv.ALIGN.CENTER, 0, 0)
huifuchuchangshezhi_btn_3.set_style_pad_all(0, lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_3.set_pos(400, 600)
huifuchuchangshezhi_btn_3.set_size(290, 70)
# Set style for huifuchuchangshezhi_btn_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
huifuchuchangshezhi_btn_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_3.set_style_bg_color(lv.color_hex(0xc1031e), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_3.set_style_radius(15, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_3.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create huifuchuchangshezhi_img_1
huifuchuchangshezhi_img_1 = lv.img(huifuchuchangshezhi)
huifuchuchangshezhi_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
huifuchuchangshezhi_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
huifuchuchangshezhi_img_1.set_pivot(50,50)
huifuchuchangshezhi_img_1.set_angle(0)
huifuchuchangshezhi_img_1.set_pos(43, 28)
huifuchuchangshezhi_img_1.set_size(14, 24)
# Set style for huifuchuchangshezhi_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
huifuchuchangshezhi_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create huifuchuchangshezhi_btn_4
huifuchuchangshezhi_btn_4 = lv.btn(huifuchuchangshezhi)
huifuchuchangshezhi_btn_4_label = lv.label(huifuchuchangshezhi_btn_4)
huifuchuchangshezhi_btn_4_label.set_text("")
huifuchuchangshezhi_btn_4_label.set_long_mode(lv.label.LONG.WRAP)
huifuchuchangshezhi_btn_4_label.set_width(lv.pct(100))
huifuchuchangshezhi_btn_4_label.align(lv.ALIGN.CENTER, 0, 0)
huifuchuchangshezhi_btn_4.set_style_pad_all(0, lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_4.set_pos(-5, -11)
huifuchuchangshezhi_btn_4.set_size(261, 107)
# Set style for huifuchuchangshezhi_btn_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
huifuchuchangshezhi_btn_4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_4.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
huifuchuchangshezhi_btn_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

huifuchuchangshezhi.update_layout()
# Create RelativeProduct
RelativeProduct = lv.obj()
RelativeProduct.set_size(720, 720)
RelativeProduct.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for RelativeProduct, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RelativeProduct.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RelativeProduct_tile
RelativeProduct_tile = lv.tabview(RelativeProduct, lv.DIR.TOP, 85)
RelativeProduct_tile.set_pos(2, -1)
RelativeProduct_tile.set_size(720, 720)
RelativeProduct_tile.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for RelativeProduct_tile, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RelativeProduct_tile.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_tile.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_tile.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_tile.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_tile.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_tile.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_tile.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_tile.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_tile.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_tile.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_tile.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for RelativeProduct_tile, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_RelativeProduct_tile_extra_btnm_main_default = lv.style_t()
style_RelativeProduct_tile_extra_btnm_main_default.init()
style_RelativeProduct_tile_extra_btnm_main_default.set_bg_opa(255)
style_RelativeProduct_tile_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_RelativeProduct_tile_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_RelativeProduct_tile_extra_btnm_main_default.set_border_width(0)
style_RelativeProduct_tile_extra_btnm_main_default.set_radius(0)
RelativeProduct_tile.get_tab_btns().add_style(style_RelativeProduct_tile_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for RelativeProduct_tile, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_RelativeProduct_tile_extra_btnm_items_default = lv.style_t()
style_RelativeProduct_tile_extra_btnm_items_default.init()
style_RelativeProduct_tile_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_RelativeProduct_tile_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_RelativeProduct_tile_extra_btnm_items_default.set_text_opa(255)
RelativeProduct_tile.get_tab_btns().add_style(style_RelativeProduct_tile_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for RelativeProduct_tile, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_RelativeProduct_tile_extra_btnm_items_checked = lv.style_t()
style_RelativeProduct_tile_extra_btnm_items_checked.init()
style_RelativeProduct_tile_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_RelativeProduct_tile_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_RelativeProduct_tile_extra_btnm_items_checked.set_text_opa(255)
style_RelativeProduct_tile_extra_btnm_items_checked.set_border_width(0)
style_RelativeProduct_tile_extra_btnm_items_checked.set_radius(0)
style_RelativeProduct_tile_extra_btnm_items_checked.set_bg_opa(255)
style_RelativeProduct_tile_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_RelativeProduct_tile_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
RelativeProduct_tile.get_tab_btns().add_style(style_RelativeProduct_tile_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
RelativeProduct_tile_tab_1 = RelativeProduct_tile.add_tab("")
RelativeProduct_tile_tab_1_label = lv.label(RelativeProduct_tile_tab_1)
RelativeProduct_tile_tab_1_label.set_text("")

# Create RelativeProduct_list_1
RelativeProduct_list_1 = lv.list(RelativeProduct)
RelativeProduct_list_1_item0 = RelativeProduct_list_1.add_text("产品型号")
RelativeProduct_list_1_item1 = RelativeProduct_list_1.add_text("固件版本")
RelativeProduct_list_1_item2 = RelativeProduct_list_1.add_text("硬件版本")
RelativeProduct_list_1_item3 = RelativeProduct_list_1.add_text("MAC")
RelativeProduct_list_1.set_pos(23, 85)
RelativeProduct_list_1.set_size(665, 635)
RelativeProduct_list_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for RelativeProduct_list_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RelativeProduct_list_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_list_1.set_style_pad_left(5, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_list_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_list_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_list_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_list_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_list_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_list_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_list_1.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_list_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for RelativeProduct_list_1, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
RelativeProduct_list_1.set_style_radius(3, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
RelativeProduct_list_1.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
RelativeProduct_list_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
RelativeProduct_list_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
# Set style for RelativeProduct_list_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_RelativeProduct_list_1_extra_btns_main_default = lv.style_t()
style_RelativeProduct_list_1_extra_btns_main_default.init()
style_RelativeProduct_list_1_extra_btns_main_default.set_pad_top(5)
style_RelativeProduct_list_1_extra_btns_main_default.set_pad_left(5)
style_RelativeProduct_list_1_extra_btns_main_default.set_pad_right(5)
style_RelativeProduct_list_1_extra_btns_main_default.set_pad_bottom(5)
style_RelativeProduct_list_1_extra_btns_main_default.set_border_width(2)
style_RelativeProduct_list_1_extra_btns_main_default.set_border_opa(255)
style_RelativeProduct_list_1_extra_btns_main_default.set_border_color(lv.color_hex(0xe1e6ee))
style_RelativeProduct_list_1_extra_btns_main_default.set_border_side(lv.BORDER_SIDE.BOTTOM)
style_RelativeProduct_list_1_extra_btns_main_default.set_text_color(lv.color_hex(0xffffff))
style_RelativeProduct_list_1_extra_btns_main_default.set_text_font(test_font("MiSansNormal", 30))
style_RelativeProduct_list_1_extra_btns_main_default.set_text_opa(255)
style_RelativeProduct_list_1_extra_btns_main_default.set_radius(3)
style_RelativeProduct_list_1_extra_btns_main_default.set_bg_opa(255)
style_RelativeProduct_list_1_extra_btns_main_default.set_bg_color(lv.color_hex(0x000000))
style_RelativeProduct_list_1_extra_btns_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)

# Set style for RelativeProduct_list_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_RelativeProduct_list_1_extra_texts_main_default = lv.style_t()
style_RelativeProduct_list_1_extra_texts_main_default.init()
style_RelativeProduct_list_1_extra_texts_main_default.set_pad_top(20)
style_RelativeProduct_list_1_extra_texts_main_default.set_pad_left(10)
style_RelativeProduct_list_1_extra_texts_main_default.set_pad_right(0)
style_RelativeProduct_list_1_extra_texts_main_default.set_pad_bottom(24)
style_RelativeProduct_list_1_extra_texts_main_default.set_border_width(3)
style_RelativeProduct_list_1_extra_texts_main_default.set_border_opa(255)
style_RelativeProduct_list_1_extra_texts_main_default.set_border_color(lv.color_hex(0x151313))
style_RelativeProduct_list_1_extra_texts_main_default.set_border_side(lv.BORDER_SIDE.BOTTOM)
style_RelativeProduct_list_1_extra_texts_main_default.set_text_color(lv.color_hex(0xffffff))
style_RelativeProduct_list_1_extra_texts_main_default.set_text_font(test_font("MiSansNormal", 30))
style_RelativeProduct_list_1_extra_texts_main_default.set_text_opa(255)
style_RelativeProduct_list_1_extra_texts_main_default.set_radius(0)
style_RelativeProduct_list_1_extra_texts_main_default.set_transform_width(0)
style_RelativeProduct_list_1_extra_texts_main_default.set_bg_opa(255)
style_RelativeProduct_list_1_extra_texts_main_default.set_bg_color(lv.color_hex(0x000000))
style_RelativeProduct_list_1_extra_texts_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
RelativeProduct_list_1_item3.add_style(style_RelativeProduct_list_1_extra_texts_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_list_1_item2.add_style(style_RelativeProduct_list_1_extra_texts_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_list_1_item1.add_style(style_RelativeProduct_list_1_extra_texts_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_list_1_item0.add_style(style_RelativeProduct_list_1_extra_texts_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RelativeProduct_btn_1
RelativeProduct_btn_1 = lv.btn(RelativeProduct)
RelativeProduct_btn_1_label = lv.label(RelativeProduct_btn_1)
RelativeProduct_btn_1_label.set_text("设备重启")
RelativeProduct_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
RelativeProduct_btn_1_label.set_width(lv.pct(100))
RelativeProduct_btn_1_label.align(lv.ALIGN.LEFT_MID, 0, 0)
RelativeProduct_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
RelativeProduct_btn_1.set_pos(70, 25)
RelativeProduct_btn_1.set_size(152, 32)
# Set style for RelativeProduct_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RelativeProduct_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_btn_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_btn_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RelativeProduct_img_1
RelativeProduct_img_1 = lv.img(RelativeProduct)
RelativeProduct_img_1.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
RelativeProduct_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
RelativeProduct_img_1.set_pivot(50,50)
RelativeProduct_img_1.set_angle(0)
RelativeProduct_img_1.set_pos(43, 28)
RelativeProduct_img_1.set_size(14, 24)
# Set style for RelativeProduct_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RelativeProduct_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RelativeProduct_label_1
RelativeProduct_label_1 = lv.label(RelativeProduct)
RelativeProduct_label_1.set_text("LDZNZK-YS-4")
RelativeProduct_label_1.set_long_mode(lv.label.LONG.WRAP)
RelativeProduct_label_1.set_width(lv.pct(100))
RelativeProduct_label_1.set_pos(440, 110)
RelativeProduct_label_1.set_size(230, 32)
# Set style for RelativeProduct_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RelativeProduct_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_1.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RelativeProduct_label_2
RelativeProduct_label_2 = lv.label(RelativeProduct)
RelativeProduct_label_2.set_text("LDZNZK-YS-4")
RelativeProduct_label_2.set_long_mode(lv.label.LONG.WRAP)
RelativeProduct_label_2.set_width(lv.pct(100))
RelativeProduct_label_2.set_pos(440, 196)
RelativeProduct_label_2.set_size(230, 32)
# Set style for RelativeProduct_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RelativeProduct_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_2.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RelativeProduct_label_3
RelativeProduct_label_3 = lv.label(RelativeProduct)
RelativeProduct_label_3.set_text("LDZNZK-YS-4")
RelativeProduct_label_3.set_long_mode(lv.label.LONG.WRAP)
RelativeProduct_label_3.set_width(lv.pct(100))
RelativeProduct_label_3.set_pos(440, 282)
RelativeProduct_label_3.set_size(230, 32)
# Set style for RelativeProduct_label_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RelativeProduct_label_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_3.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_3.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_3.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RelativeProduct_label_4
RelativeProduct_label_4 = lv.label(RelativeProduct)
RelativeProduct_label_4.set_text("LDZNZK-YS-4")
RelativeProduct_label_4.set_long_mode(lv.label.LONG.WRAP)
RelativeProduct_label_4.set_width(lv.pct(100))
RelativeProduct_label_4.set_pos(440, 367)
RelativeProduct_label_4.set_size(230, 32)
# Set style for RelativeProduct_label_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RelativeProduct_label_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_4.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_4.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_4.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_4.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_4.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_4.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_4.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_4.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_label_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create RelativeProduct_btn_4
RelativeProduct_btn_4 = lv.btn(RelativeProduct)
RelativeProduct_btn_4_label = lv.label(RelativeProduct_btn_4)
RelativeProduct_btn_4_label.set_text("")
RelativeProduct_btn_4_label.set_long_mode(lv.label.LONG.WRAP)
RelativeProduct_btn_4_label.set_width(lv.pct(100))
RelativeProduct_btn_4_label.align(lv.ALIGN.CENTER, 0, 0)
RelativeProduct_btn_4.set_style_pad_all(0, lv.STATE.DEFAULT)
RelativeProduct_btn_4.set_pos(-6, -15)
RelativeProduct_btn_4.set_size(241, 108)
# Set style for RelativeProduct_btn_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
RelativeProduct_btn_4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_btn_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_btn_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_btn_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_btn_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_btn_4.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_btn_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
RelativeProduct_btn_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

RelativeProduct.update_layout()
# Create Helper
Helper = lv.obj()
Helper.set_size(720, 720)
Helper.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Helper, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Helper.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Helper.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Helper_tabview_1
Helper_tabview_1 = lv.tabview(Helper, lv.DIR.TOP, 85)
Helper_tabview_1.set_pos(0, 0)
Helper_tabview_1.set_size(720, 720)
Helper_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for Helper_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Helper_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_tabview_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for Helper_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_Helper_tabview_1_extra_btnm_main_default = lv.style_t()
style_Helper_tabview_1_extra_btnm_main_default.init()
style_Helper_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_Helper_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x243241))
style_Helper_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_Helper_tabview_1_extra_btnm_main_default.set_border_width(0)
style_Helper_tabview_1_extra_btnm_main_default.set_radius(0)
Helper_tabview_1.get_tab_btns().add_style(style_Helper_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for Helper_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_Helper_tabview_1_extra_btnm_items_default = lv.style_t()
style_Helper_tabview_1_extra_btnm_items_default.init()
style_Helper_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_Helper_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_Helper_tabview_1_extra_btnm_items_default.set_text_opa(255)
Helper_tabview_1.get_tab_btns().add_style(style_Helper_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for Helper_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_Helper_tabview_1_extra_btnm_items_checked = lv.style_t()
style_Helper_tabview_1_extra_btnm_items_checked.init()
style_Helper_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_Helper_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_Helper_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_Helper_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_Helper_tabview_1_extra_btnm_items_checked.set_radius(0)
style_Helper_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_Helper_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_Helper_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
Helper_tabview_1.get_tab_btns().add_style(style_Helper_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
Helper_tabview_1_tab_1 = Helper_tabview_1.add_tab("")
Helper_tabview_1_tab_1_label = lv.label(Helper_tabview_1_tab_1)
Helper_tabview_1_tab_1_label.set_text("")

# Create Helper_label_10
Helper_label_10 = lv.label(Helper)
Helper_label_10.set_text("使用说明")
Helper_label_10.set_long_mode(lv.label.LONG.WRAP)
Helper_label_10.set_width(lv.pct(100))
Helper_label_10.set_pos(70, 25)
Helper_label_10.set_size(149, 32)
# Set style for Helper_label_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Helper_label_10.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_label_10.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_label_10.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_label_10.set_style_text_font(test_font("MiSansNormal", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_label_10.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_label_10.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_label_10.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_label_10.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_label_10.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_label_10.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_label_10.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_label_10.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_label_10.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_label_10.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Helper_img_1
Helper_img_1 = lv.img(Helper)
Helper_img_1.set_src("B:MicroPython/_bhelp_alpha_720x635.bin")
Helper_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
Helper_img_1.set_pivot(50,50)
Helper_img_1.set_angle(0)
Helper_img_1.set_pos(0, 85)
Helper_img_1.set_size(720, 635)
# Set style for Helper_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Helper_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Helper_img_2
Helper_img_2 = lv.img(Helper)
Helper_img_2.set_src("B:MicroPython/_spageback_alpha_14x24.bin")
Helper_img_2.add_flag(lv.obj.FLAG.CLICKABLE)
Helper_img_2.set_pivot(50,50)
Helper_img_2.set_angle(0)
Helper_img_2.set_pos(43, 28)
Helper_img_2.set_size(14, 24)
# Set style for Helper_img_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Helper_img_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_img_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_img_2.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Helper_btn_1
Helper_btn_1 = lv.btn(Helper)
Helper_btn_1_label = lv.label(Helper_btn_1)
Helper_btn_1_label.set_text("")
Helper_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
Helper_btn_1_label.set_width(lv.pct(100))
Helper_btn_1_label.align(lv.ALIGN.CENTER, 0, 0)
Helper_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
Helper_btn_1.set_pos(-5, -11)
Helper_btn_1.set_size(263, 107)
# Set style for Helper_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Helper_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_btn_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Helper_btn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

Helper.update_layout()

def ui_home_screen_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        

ui_home_screen.add_event_cb(lambda e: ui_home_screen_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_cont_27_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_cont_27.add_event_cb(lambda e: ui_home_screen_cont_27_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_imgbtn_9_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

ui_home_screen_imgbtn_9.add_event_cb(lambda e: ui_home_screen_imgbtn_9_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_cont_26_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_cont_26.add_event_cb(lambda e: ui_home_screen_cont_26_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_imgbtn_8_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

ui_home_screen_imgbtn_8.add_event_cb(lambda e: ui_home_screen_imgbtn_8_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_cont_25_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_cont_25.add_event_cb(lambda e: ui_home_screen_cont_25_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_imgbtn_7_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

ui_home_screen_imgbtn_7.add_event_cb(lambda e: ui_home_screen_imgbtn_7_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_cont_24_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_cont_24.add_event_cb(lambda e: ui_home_screen_cont_24_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_imgbtn_6_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

ui_home_screen_imgbtn_6.add_event_cb(lambda e: ui_home_screen_imgbtn_6_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_cont_23_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_cont_23.add_event_cb(lambda e: ui_home_screen_cont_23_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_img_51_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_img_51.add_event_cb(lambda e: ui_home_screen_img_51_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_img_50_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_img_50.add_event_cb(lambda e: ui_home_screen_img_50_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_cont_22_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_cont_22.add_event_cb(lambda e: ui_home_screen_cont_22_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_img_47_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_img_47.add_event_cb(lambda e: ui_home_screen_img_47_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_img_46_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_img_46.add_event_cb(lambda e: ui_home_screen_img_46_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_cont_21_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_cont_21.add_event_cb(lambda e: ui_home_screen_cont_21_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_img_43_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_img_43.add_event_cb(lambda e: ui_home_screen_img_43_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_img_42_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_img_42.add_event_cb(lambda e: ui_home_screen_img_42_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_cont_20_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_cont_20.add_event_cb(lambda e: ui_home_screen_cont_20_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_img_39_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_img_39.add_event_cb(lambda e: ui_home_screen_img_39_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_img_38_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_img_38.add_event_cb(lambda e: ui_home_screen_img_38_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_cont_19_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_cont_19.add_event_cb(lambda e: ui_home_screen_cont_19_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_cont_18_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_cont_18.add_event_cb(lambda e: ui_home_screen_cont_18_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_imgbtn_4_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

ui_home_screen_imgbtn_4.add_event_cb(lambda e: ui_home_screen_imgbtn_4_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_cont_17_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_cont_17.add_event_cb(lambda e: ui_home_screen_cont_17_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_img_31_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_img_31.add_event_cb(lambda e: ui_home_screen_img_31_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_img_30_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_img_30.add_event_cb(lambda e: ui_home_screen_img_30_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_cont_16_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_cont_16.add_event_cb(lambda e: ui_home_screen_cont_16_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_imgbtn_3_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

ui_home_screen_imgbtn_3.add_event_cb(lambda e: ui_home_screen_imgbtn_3_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_imgbtn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

ui_home_screen_imgbtn_2.add_event_cb(lambda e: ui_home_screen_imgbtn_2_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_cont_15_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_cont_15.add_event_cb(lambda e: ui_home_screen_cont_15_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_img_27_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

ui_home_screen_img_27.add_event_cb(lambda e: ui_home_screen_img_27_event_handler(e), lv.EVENT.ALL, None)

def ui_home_screen_imgbtn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

ui_home_screen_imgbtn_1.add_event_cb(lambda e: ui_home_screen_imgbtn_1_event_handler(e), lv.EVENT.ALL, None)

def light_CT_screen_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        #Write animation: light_CT_screen_label_2 x
        light_CT_screen_label_2_anim_x = lv.anim_t()
        light_CT_screen_label_2_anim_x.init()
        light_CT_screen_label_2_anim_x.set_var(light_CT_screen_label_2)
        light_CT_screen_label_2_anim_x.set_time(600)
        light_CT_screen_label_2_anim_x.set_delay(0)
        light_CT_screen_label_2_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(light_CT_screen_label_2,val))
        light_CT_screen_label_2_anim_x.set_values(light_CT_screen_label_2.get_x(), 33)
        light_CT_screen_label_2_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        light_CT_screen_label_2_anim_x.set_repeat_count(0)
        light_CT_screen_label_2_anim_x.set_repeat_delay(0)
        light_CT_screen_label_2_anim_x.set_playback_time(0)
        light_CT_screen_label_2_anim_x.set_playback_delay(0)
        light_CT_screen_label_2_anim_x.start()
        #Write animation: light_CT_screen_slider_1 x
        light_CT_screen_slider_1_anim_x = lv.anim_t()
        light_CT_screen_slider_1_anim_x.init()
        light_CT_screen_slider_1_anim_x.set_var(light_CT_screen_slider_1)
        light_CT_screen_slider_1_anim_x.set_time(600)
        light_CT_screen_slider_1_anim_x.set_delay(0)
        light_CT_screen_slider_1_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(light_CT_screen_slider_1,val))
        light_CT_screen_slider_1_anim_x.set_values(light_CT_screen_slider_1.get_x(), 33)
        light_CT_screen_slider_1_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        light_CT_screen_slider_1_anim_x.set_repeat_count(0)
        light_CT_screen_slider_1_anim_x.set_repeat_delay(0)
        light_CT_screen_slider_1_anim_x.set_playback_time(0)
        light_CT_screen_slider_1_anim_x.set_playback_delay(0)
        light_CT_screen_slider_1_anim_x.start()
        #Write animation: light_CT_screen_slider_2 x
        light_CT_screen_slider_2_anim_x = lv.anim_t()
        light_CT_screen_slider_2_anim_x.init()
        light_CT_screen_slider_2_anim_x.set_var(light_CT_screen_slider_2)
        light_CT_screen_slider_2_anim_x.set_time(600)
        light_CT_screen_slider_2_anim_x.set_delay(0)
        light_CT_screen_slider_2_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(light_CT_screen_slider_2,val))
        light_CT_screen_slider_2_anim_x.set_values(light_CT_screen_slider_2.get_x(), 33)
        light_CT_screen_slider_2_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        light_CT_screen_slider_2_anim_x.set_repeat_count(0)
        light_CT_screen_slider_2_anim_x.set_repeat_delay(0)
        light_CT_screen_slider_2_anim_x.set_playback_time(0)
        light_CT_screen_slider_2_anim_x.set_playback_delay(0)
        light_CT_screen_slider_2_anim_x.start()
        #Write animation: light_CT_screen_label_1 x
        light_CT_screen_label_1_anim_x = lv.anim_t()
        light_CT_screen_label_1_anim_x.init()
        light_CT_screen_label_1_anim_x.set_var(light_CT_screen_label_1)
        light_CT_screen_label_1_anim_x.set_time(600)
        light_CT_screen_label_1_anim_x.set_delay(0)
        light_CT_screen_label_1_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(light_CT_screen_label_1,val))
        light_CT_screen_label_1_anim_x.set_values(light_CT_screen_label_1.get_x(), 33)
        light_CT_screen_label_1_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        light_CT_screen_label_1_anim_x.set_repeat_count(0)
        light_CT_screen_label_1_anim_x.set_repeat_delay(0)
        light_CT_screen_label_1_anim_x.set_playback_time(0)
        light_CT_screen_label_1_anim_x.set_playback_delay(0)
        light_CT_screen_label_1_anim_x.start()
        

        #Write animation: light_CT_screen_ct_bar x
        light_CT_screen_ct_bar_anim_x = lv.anim_t()
        light_CT_screen_ct_bar_anim_x.init()
        light_CT_screen_ct_bar_anim_x.set_var(light_CT_screen_ct_bar)
        light_CT_screen_ct_bar_anim_x.set_time(600)
        light_CT_screen_ct_bar_anim_x.set_delay(0)
        light_CT_screen_ct_bar_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(light_CT_screen_ct_bar,val))
        light_CT_screen_ct_bar_anim_x.set_values(light_CT_screen_ct_bar.get_x(), 33)
        light_CT_screen_ct_bar_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        light_CT_screen_ct_bar_anim_x.set_repeat_count(0)
        light_CT_screen_ct_bar_anim_x.set_repeat_delay(0)
        light_CT_screen_ct_bar_anim_x.set_playback_time(0)
        light_CT_screen_ct_bar_anim_x.set_playback_delay(0)
        light_CT_screen_ct_bar_anim_x.start()
light_CT_screen.add_event_cb(lambda e: light_CT_screen_event_handler(e), lv.EVENT.ALL, None)

def light_CT_screen_slider_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

light_CT_screen_slider_2.add_event_cb(lambda e: light_CT_screen_slider_2_event_handler(e), lv.EVENT.ALL, None)

def light_CT_screen_slider_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

light_CT_screen_slider_1.add_event_cb(lambda e: light_CT_screen_slider_1_event_handler(e), lv.EVENT.ALL, None)

def light_CT_screen_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
light_CT_screen_btn_1.add_event_cb(lambda e: light_CT_screen_btn_1_event_handler(e), lv.EVENT.ALL, None)

def light_CT_screen_imgbtn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

light_CT_screen_imgbtn_1.add_event_cb(lambda e: light_CT_screen_imgbtn_1_event_handler(e), lv.EVENT.ALL, None)

def light_CT_screen_on_off_2_img_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

light_CT_screen_on_off_2_img.add_event_cb(lambda e: light_CT_screen_on_off_2_img_event_handler(e), lv.EVENT.ALL, None)

def light_CT_screen_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

light_CT_screen_btn_2.add_event_cb(lambda e: light_CT_screen_btn_2_event_handler(e), lv.EVENT.ALL, None)

def LedStrip_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        #Write animation: LedStrip_label_1 x
        LedStrip_label_1_anim_x = lv.anim_t()
        LedStrip_label_1_anim_x.init()
        LedStrip_label_1_anim_x.set_var(LedStrip_label_1)
        LedStrip_label_1_anim_x.set_time(600)
        LedStrip_label_1_anim_x.set_delay(0)
        LedStrip_label_1_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(LedStrip_label_1,val))
        LedStrip_label_1_anim_x.set_values(LedStrip_label_1.get_x(), 33)
        LedStrip_label_1_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        LedStrip_label_1_anim_x.set_repeat_count(0)
        LedStrip_label_1_anim_x.set_repeat_delay(0)
        LedStrip_label_1_anim_x.set_playback_time(0)
        LedStrip_label_1_anim_x.set_playback_delay(0)
        LedStrip_label_1_anim_x.start()
        #Write animation: LedStrip_slider_1 x
        LedStrip_slider_1_anim_x = lv.anim_t()
        LedStrip_slider_1_anim_x.init()
        LedStrip_slider_1_anim_x.set_var(LedStrip_slider_1)
        LedStrip_slider_1_anim_x.set_time(600)
        LedStrip_slider_1_anim_x.set_delay(0)
        LedStrip_slider_1_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(LedStrip_slider_1,val))
        LedStrip_slider_1_anim_x.set_values(LedStrip_slider_1.get_x(), 33)
        LedStrip_slider_1_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        LedStrip_slider_1_anim_x.set_repeat_count(0)
        LedStrip_slider_1_anim_x.set_repeat_delay(0)
        LedStrip_slider_1_anim_x.set_playback_time(0)
        LedStrip_slider_1_anim_x.set_playback_delay(0)
        LedStrip_slider_1_anim_x.start()
        #Write animation: LedStrip_slider_2 x
        LedStrip_slider_2_anim_x = lv.anim_t()
        LedStrip_slider_2_anim_x.init()
        LedStrip_slider_2_anim_x.set_var(LedStrip_slider_2)
        LedStrip_slider_2_anim_x.set_time(600)
        LedStrip_slider_2_anim_x.set_delay(0)
        LedStrip_slider_2_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(LedStrip_slider_2,val))
        LedStrip_slider_2_anim_x.set_values(LedStrip_slider_2.get_x(), 33)
        LedStrip_slider_2_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        LedStrip_slider_2_anim_x.set_repeat_count(0)
        LedStrip_slider_2_anim_x.set_repeat_delay(0)
        LedStrip_slider_2_anim_x.set_playback_time(0)
        LedStrip_slider_2_anim_x.set_playback_delay(0)
        LedStrip_slider_2_anim_x.start()
        #Write animation: LedStrip_label_2 x
        LedStrip_label_2_anim_x = lv.anim_t()
        LedStrip_label_2_anim_x.init()
        LedStrip_label_2_anim_x.set_var(LedStrip_label_2)
        LedStrip_label_2_anim_x.set_time(600)
        LedStrip_label_2_anim_x.set_delay(0)
        LedStrip_label_2_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(LedStrip_label_2,val))
        LedStrip_label_2_anim_x.set_values(LedStrip_label_2.get_x(), 33)
        LedStrip_label_2_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        LedStrip_label_2_anim_x.set_repeat_count(0)
        LedStrip_label_2_anim_x.set_repeat_delay(0)
        LedStrip_label_2_anim_x.set_playback_time(0)
        LedStrip_label_2_anim_x.set_playback_delay(0)
        LedStrip_label_2_anim_x.start()
        #Write animation: LedStrip_ct_bar x
        LedStrip_ct_bar_anim_x = lv.anim_t()
        LedStrip_ct_bar_anim_x.init()
        LedStrip_ct_bar_anim_x.set_var(LedStrip_ct_bar)
        LedStrip_ct_bar_anim_x.set_time(600)
        LedStrip_ct_bar_anim_x.set_delay(0)
        LedStrip_ct_bar_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(LedStrip_ct_bar,val))
        LedStrip_ct_bar_anim_x.set_values(LedStrip_ct_bar.get_x(), 33)
        LedStrip_ct_bar_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        LedStrip_ct_bar_anim_x.set_repeat_count(0)
        LedStrip_ct_bar_anim_x.set_repeat_delay(0)
        LedStrip_ct_bar_anim_x.set_playback_time(0)
        LedStrip_ct_bar_anim_x.set_playback_delay(0)
        LedStrip_ct_bar_anim_x.start()
        

LedStrip.add_event_cb(lambda e: LedStrip_event_handler(e), lv.EVENT.ALL, None)

def LedStrip_slider_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

LedStrip_slider_2.add_event_cb(lambda e: LedStrip_slider_2_event_handler(e), lv.EVENT.ALL, None)

def LedStrip_slider_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

LedStrip_slider_1.add_event_cb(lambda e: LedStrip_slider_1_event_handler(e), lv.EVENT.ALL, None)

def LedStrip_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
LedStrip_btn_1.add_event_cb(lambda e: LedStrip_btn_1_event_handler(e), lv.EVENT.ALL, None)

def LedStrip_on_off_2_img_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

LedStrip_on_off_2_img.add_event_cb(lambda e: LedStrip_on_off_2_img_event_handler(e), lv.EVENT.ALL, None)

def LedStrip_btn_4_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

LedStrip_btn_4.add_event_cb(lambda e: LedStrip_btn_4_event_handler(e), lv.EVENT.ALL, None)

def RGBLight_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        #Write animation: RGBLight_label_1 x
        RGBLight_label_1_anim_x = lv.anim_t()
        RGBLight_label_1_anim_x.init()
        RGBLight_label_1_anim_x.set_var(RGBLight_label_1)
        RGBLight_label_1_anim_x.set_time(600)
        RGBLight_label_1_anim_x.set_delay(0)
        RGBLight_label_1_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(RGBLight_label_1,val))
        RGBLight_label_1_anim_x.set_values(RGBLight_label_1.get_x(), 33)
        RGBLight_label_1_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        RGBLight_label_1_anim_x.set_repeat_count(0)
        RGBLight_label_1_anim_x.set_repeat_delay(0)
        RGBLight_label_1_anim_x.set_playback_time(0)
        RGBLight_label_1_anim_x.set_playback_delay(0)
        RGBLight_label_1_anim_x.start()
        #Write animation: RGBLight_slider_2 x
        RGBLight_slider_2_anim_x = lv.anim_t()
        RGBLight_slider_2_anim_x.init()
        RGBLight_slider_2_anim_x.set_var(RGBLight_slider_2)
        RGBLight_slider_2_anim_x.set_time(600)
        RGBLight_slider_2_anim_x.set_delay(0)
        RGBLight_slider_2_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(RGBLight_slider_2,val))
        RGBLight_slider_2_anim_x.set_values(RGBLight_slider_2.get_x(), 33)
        RGBLight_slider_2_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        RGBLight_slider_2_anim_x.set_repeat_count(0)
        RGBLight_slider_2_anim_x.set_repeat_delay(0)
        RGBLight_slider_2_anim_x.set_playback_time(0)
        RGBLight_slider_2_anim_x.set_playback_delay(0)
        RGBLight_slider_2_anim_x.start()
        #Write animation: RGBLight_ct_bar x
        RGBLight_ct_bar_anim_x = lv.anim_t()
        RGBLight_ct_bar_anim_x.init()
        RGBLight_ct_bar_anim_x.set_var(RGBLight_ct_bar)
        RGBLight_ct_bar_anim_x.set_time(600)
        RGBLight_ct_bar_anim_x.set_delay(0)
        RGBLight_ct_bar_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(RGBLight_ct_bar,val))
        RGBLight_ct_bar_anim_x.set_values(RGBLight_ct_bar.get_x(), 33)
        RGBLight_ct_bar_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        RGBLight_ct_bar_anim_x.set_repeat_count(0)
        RGBLight_ct_bar_anim_x.set_repeat_delay(0)
        RGBLight_ct_bar_anim_x.set_playback_time(0)
        RGBLight_ct_bar_anim_x.set_playback_delay(0)
        RGBLight_ct_bar_anim_x.start()
        #Write animation: RGBLight_label_2 x
        RGBLight_label_2_anim_x = lv.anim_t()
        RGBLight_label_2_anim_x.init()
        RGBLight_label_2_anim_x.set_var(RGBLight_label_2)
        RGBLight_label_2_anim_x.set_time(600)
        RGBLight_label_2_anim_x.set_delay(0)
        RGBLight_label_2_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(RGBLight_label_2,val))
        RGBLight_label_2_anim_x.set_values(RGBLight_label_2.get_x(), 33)
        RGBLight_label_2_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        RGBLight_label_2_anim_x.set_repeat_count(0)
        RGBLight_label_2_anim_x.set_repeat_delay(0)
        RGBLight_label_2_anim_x.set_playback_time(0)
        RGBLight_label_2_anim_x.set_playback_delay(0)
        RGBLight_label_2_anim_x.start()
        #Write animation: RGBLight_slider_1 x
        RGBLight_slider_1_anim_x = lv.anim_t()
        RGBLight_slider_1_anim_x.init()
        RGBLight_slider_1_anim_x.set_var(RGBLight_slider_1)
        RGBLight_slider_1_anim_x.set_time(600)
        RGBLight_slider_1_anim_x.set_delay(0)
        RGBLight_slider_1_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(RGBLight_slider_1,val))
        RGBLight_slider_1_anim_x.set_values(RGBLight_slider_1.get_x(), 33)
        RGBLight_slider_1_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        RGBLight_slider_1_anim_x.set_repeat_count(0)
        RGBLight_slider_1_anim_x.set_repeat_delay(0)
        RGBLight_slider_1_anim_x.set_playback_time(0)
        RGBLight_slider_1_anim_x.set_playback_delay(0)
        RGBLight_slider_1_anim_x.start()
        

RGBLight.add_event_cb(lambda e: RGBLight_event_handler(e), lv.EVENT.ALL, None)

def RGBLight_slider_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

RGBLight_slider_2.add_event_cb(lambda e: RGBLight_slider_2_event_handler(e), lv.EVENT.ALL, None)

def RGBLight_slider_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

RGBLight_slider_1.add_event_cb(lambda e: RGBLight_slider_1_event_handler(e), lv.EVENT.ALL, None)

def RGBLight_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
RGBLight_btn_1.add_event_cb(lambda e: RGBLight_btn_1_event_handler(e), lv.EVENT.ALL, None)

def RGBLight_on_off_2_img_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

RGBLight_on_off_2_img.add_event_cb(lambda e: RGBLight_on_off_2_img_event_handler(e), lv.EVENT.ALL, None)

def RGBLight_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

RGBLight_btn_2.add_event_cb(lambda e: RGBLight_btn_2_event_handler(e), lv.EVENT.ALL, None)

def MagLight_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        #Write animation: MagLight_label_1 x
        MagLight_label_1_anim_x = lv.anim_t()
        MagLight_label_1_anim_x.init()
        MagLight_label_1_anim_x.set_var(MagLight_label_1)
        MagLight_label_1_anim_x.set_time(600)
        MagLight_label_1_anim_x.set_delay(0)
        MagLight_label_1_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(MagLight_label_1,val))
        MagLight_label_1_anim_x.set_values(MagLight_label_1.get_x(), 33)
        MagLight_label_1_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        MagLight_label_1_anim_x.set_repeat_count(0)
        MagLight_label_1_anim_x.set_repeat_delay(0)
        MagLight_label_1_anim_x.set_playback_time(0)
        MagLight_label_1_anim_x.set_playback_delay(0)
        MagLight_label_1_anim_x.start()
        #Write animation: MagLight_slider_1 x
        MagLight_slider_1_anim_x = lv.anim_t()
        MagLight_slider_1_anim_x.init()
        MagLight_slider_1_anim_x.set_var(MagLight_slider_1)
        MagLight_slider_1_anim_x.set_time(600)
        MagLight_slider_1_anim_x.set_delay(0)
        MagLight_slider_1_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(MagLight_slider_1,val))
        MagLight_slider_1_anim_x.set_values(MagLight_slider_1.get_x(), 33)
        MagLight_slider_1_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        MagLight_slider_1_anim_x.set_repeat_count(0)
        MagLight_slider_1_anim_x.set_repeat_delay(0)
        MagLight_slider_1_anim_x.set_playback_time(0)
        MagLight_slider_1_anim_x.set_playback_delay(0)
        MagLight_slider_1_anim_x.start()
        #Write animation: MagLight_slider_2 x
        MagLight_slider_2_anim_x = lv.anim_t()
        MagLight_slider_2_anim_x.init()
        MagLight_slider_2_anim_x.set_var(MagLight_slider_2)
        MagLight_slider_2_anim_x.set_time(600)
        MagLight_slider_2_anim_x.set_delay(0)
        MagLight_slider_2_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(MagLight_slider_2,val))
        MagLight_slider_2_anim_x.set_values(MagLight_slider_2.get_x(), 33)
        MagLight_slider_2_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        MagLight_slider_2_anim_x.set_repeat_count(0)
        MagLight_slider_2_anim_x.set_repeat_delay(0)
        MagLight_slider_2_anim_x.set_playback_time(0)
        MagLight_slider_2_anim_x.set_playback_delay(0)
        MagLight_slider_2_anim_x.start()
        #Write animation: MagLight_ct_bar x
        MagLight_ct_bar_anim_x = lv.anim_t()
        MagLight_ct_bar_anim_x.init()
        MagLight_ct_bar_anim_x.set_var(MagLight_ct_bar)
        MagLight_ct_bar_anim_x.set_time(600)
        MagLight_ct_bar_anim_x.set_delay(0)
        MagLight_ct_bar_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(MagLight_ct_bar,val))
        MagLight_ct_bar_anim_x.set_values(MagLight_ct_bar.get_x(), 33)
        MagLight_ct_bar_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        MagLight_ct_bar_anim_x.set_repeat_count(0)
        MagLight_ct_bar_anim_x.set_repeat_delay(0)
        MagLight_ct_bar_anim_x.set_playback_time(0)
        MagLight_ct_bar_anim_x.set_playback_delay(0)
        MagLight_ct_bar_anim_x.start()
        #Write animation: MagLight_label_2 x
        MagLight_label_2_anim_x = lv.anim_t()
        MagLight_label_2_anim_x.init()
        MagLight_label_2_anim_x.set_var(MagLight_label_2)
        MagLight_label_2_anim_x.set_time(600)
        MagLight_label_2_anim_x.set_delay(0)
        MagLight_label_2_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(MagLight_label_2,val))
        MagLight_label_2_anim_x.set_values(MagLight_label_2.get_x(), 33)
        MagLight_label_2_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        MagLight_label_2_anim_x.set_repeat_count(0)
        MagLight_label_2_anim_x.set_repeat_delay(0)
        MagLight_label_2_anim_x.set_playback_time(0)
        MagLight_label_2_anim_x.set_playback_delay(0)
        MagLight_label_2_anim_x.start()
        

MagLight.add_event_cb(lambda e: MagLight_event_handler(e), lv.EVENT.ALL, None)

def MagLight_slider_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

MagLight_slider_2.add_event_cb(lambda e: MagLight_slider_2_event_handler(e), lv.EVENT.ALL, None)

def MagLight_slider_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

MagLight_slider_1.add_event_cb(lambda e: MagLight_slider_1_event_handler(e), lv.EVENT.ALL, None)

def MagLight_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
MagLight_btn_1.add_event_cb(lambda e: MagLight_btn_1_event_handler(e), lv.EVENT.ALL, None)

def MagLight_on_off_2_img_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

MagLight_on_off_2_img.add_event_cb(lambda e: MagLight_on_off_2_img_event_handler(e), lv.EVENT.ALL, None)

def MagLight_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

MagLight_btn_2.add_event_cb(lambda e: MagLight_btn_2_event_handler(e), lv.EVENT.ALL, None)

def FabricCurtian_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        #Write animation: FabricCurtian_FabCurtianPause y
        FabricCurtian_FabCurtianPause_anim_y = lv.anim_t()
        FabricCurtian_FabCurtianPause_anim_y.init()
        FabricCurtian_FabCurtianPause_anim_y.set_var(FabricCurtian_FabCurtianPause)
        FabricCurtian_FabCurtianPause_anim_y.set_time(300)
        FabricCurtian_FabCurtianPause_anim_y.set_delay(0)
        FabricCurtian_FabCurtianPause_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(FabricCurtian_FabCurtianPause,val))
        FabricCurtian_FabCurtianPause_anim_y.set_values(FabricCurtian_FabCurtianPause.get_y(), 588)
        FabricCurtian_FabCurtianPause_anim_y.set_path_cb(lv.anim_t.path_linear)
        FabricCurtian_FabCurtianPause_anim_y.set_repeat_count(0)
        FabricCurtian_FabCurtianPause_anim_y.set_repeat_delay(0)
        FabricCurtian_FabCurtianPause_anim_y.set_playback_time(0)
        FabricCurtian_FabCurtianPause_anim_y.set_playback_delay(0)
        FabricCurtian_FabCurtianPause_anim_y.start()
        #Write animation: FabricCurtian_FabCurtianClose y
        FabricCurtian_FabCurtianClose_anim_y = lv.anim_t()
        FabricCurtian_FabCurtianClose_anim_y.init()
        FabricCurtian_FabCurtianClose_anim_y.set_var(FabricCurtian_FabCurtianClose)
        FabricCurtian_FabCurtianClose_anim_y.set_time(300)
        FabricCurtian_FabCurtianClose_anim_y.set_delay(0)
        FabricCurtian_FabCurtianClose_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(FabricCurtian_FabCurtianClose,val))
        FabricCurtian_FabCurtianClose_anim_y.set_values(FabricCurtian_FabCurtianClose.get_y(), 588)
        FabricCurtian_FabCurtianClose_anim_y.set_path_cb(lv.anim_t.path_linear)
        FabricCurtian_FabCurtianClose_anim_y.set_repeat_count(0)
        FabricCurtian_FabCurtianClose_anim_y.set_repeat_delay(0)
        FabricCurtian_FabCurtianClose_anim_y.set_playback_time(0)
        FabricCurtian_FabCurtianClose_anim_y.set_playback_delay(0)
        FabricCurtian_FabCurtianClose_anim_y.start()
        #Write animation: FabricCurtian_FabCurtianOpen y
        FabricCurtian_FabCurtianOpen_anim_y = lv.anim_t()
        FabricCurtian_FabCurtianOpen_anim_y.init()
        FabricCurtian_FabCurtianOpen_anim_y.set_var(FabricCurtian_FabCurtianOpen)
        FabricCurtian_FabCurtianOpen_anim_y.set_time(300)
        FabricCurtian_FabCurtianOpen_anim_y.set_delay(0)
        FabricCurtian_FabCurtianOpen_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(FabricCurtian_FabCurtianOpen,val))
        FabricCurtian_FabCurtianOpen_anim_y.set_values(FabricCurtian_FabCurtianOpen.get_y(), 588)
        FabricCurtian_FabCurtianOpen_anim_y.set_path_cb(lv.anim_t.path_linear)
        FabricCurtian_FabCurtianOpen_anim_y.set_repeat_count(0)
        FabricCurtian_FabCurtianOpen_anim_y.set_repeat_delay(0)
        FabricCurtian_FabCurtianOpen_anim_y.set_playback_time(0)
        FabricCurtian_FabCurtianOpen_anim_y.set_playback_delay(0)
        FabricCurtian_FabCurtianOpen_anim_y.start()
        

FabricCurtian.add_event_cb(lambda e: FabricCurtian_event_handler(e), lv.EVENT.ALL, None)

def FabricCurtian_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
FabricCurtian_btn_1.add_event_cb(lambda e: FabricCurtian_btn_1_event_handler(e), lv.EVENT.ALL, None)

def FabricCurtian_FabCurtianOpen_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

FabricCurtian_FabCurtianOpen.add_event_cb(lambda e: FabricCurtian_FabCurtianOpen_event_handler(e), lv.EVENT.ALL, None)

def FabricCurtian_FabCurtianClose_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

FabricCurtian_FabCurtianClose.add_event_cb(lambda e: FabricCurtian_FabCurtianClose_event_handler(e), lv.EVENT.ALL, None)

def FabricCurtian_FabCurtianPause_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

FabricCurtian_FabCurtianPause.add_event_cb(lambda e: FabricCurtian_FabCurtianPause_event_handler(e), lv.EVENT.ALL, None)

def FabricCurtian_FabCurtianLeft_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSED):
        pass
        

    if (code == lv.EVENT.PRESSING):
        pass
        

FabricCurtian_FabCurtianLeft.add_event_cb(lambda e: FabricCurtian_FabCurtianLeft_event_handler(e), lv.EVENT.ALL, None)

def FabricCurtian_FabCurtianright_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSED):
        pass
        

    if (code == lv.EVENT.PRESSING):
        pass
        

FabricCurtian_FabCurtianright.add_event_cb(lambda e: FabricCurtian_FabCurtianright_event_handler(e), lv.EVENT.ALL, None)

def FabricCurtian_FabCurtianPull2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

    if (code == lv.EVENT.PRESSED):
        pass
        

FabricCurtian_FabCurtianPull2.add_event_cb(lambda e: FabricCurtian_FabCurtianPull2_event_handler(e), lv.EVENT.ALL, None)

def FabricCurtian_FabCurtianPull1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

    if (code == lv.EVENT.PRESSED):
        pass
        

FabricCurtian_FabCurtianPull1.add_event_cb(lambda e: FabricCurtian_FabCurtianPull1_event_handler(e), lv.EVENT.ALL, None)

def FabricCurtian_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

FabricCurtian_btn_2.add_event_cb(lambda e: FabricCurtian_btn_2_event_handler(e), lv.EVENT.ALL, None)

def FabricCurtian_FabCurtianPull3_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

    if (code == lv.EVENT.PRESSED):
        pass
        

FabricCurtian_FabCurtianPull3.add_event_cb(lambda e: FabricCurtian_FabCurtianPull3_event_handler(e), lv.EVENT.ALL, None)

def FabricCurtian_FabCurtianPull4_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

    if (code == lv.EVENT.PRESSED):
        pass
        

FabricCurtian_FabCurtianPull4.add_event_cb(lambda e: FabricCurtian_FabCurtianPull4_event_handler(e), lv.EVENT.ALL, None)

def Sheers_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        #Write animation: Sheers_FabCurtianPause y
        Sheers_FabCurtianPause_anim_y = lv.anim_t()
        Sheers_FabCurtianPause_anim_y.init()
        Sheers_FabCurtianPause_anim_y.set_var(Sheers_FabCurtianPause)
        Sheers_FabCurtianPause_anim_y.set_time(300)
        Sheers_FabCurtianPause_anim_y.set_delay(0)
        Sheers_FabCurtianPause_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(Sheers_FabCurtianPause,val))
        Sheers_FabCurtianPause_anim_y.set_values(Sheers_FabCurtianPause.get_y(), 588)
        Sheers_FabCurtianPause_anim_y.set_path_cb(lv.anim_t.path_linear)
        Sheers_FabCurtianPause_anim_y.set_repeat_count(0)
        Sheers_FabCurtianPause_anim_y.set_repeat_delay(0)
        Sheers_FabCurtianPause_anim_y.set_playback_time(0)
        Sheers_FabCurtianPause_anim_y.set_playback_delay(0)
        Sheers_FabCurtianPause_anim_y.start()
        #Write animation: Sheers_FabCurtianClose y
        Sheers_FabCurtianClose_anim_y = lv.anim_t()
        Sheers_FabCurtianClose_anim_y.init()
        Sheers_FabCurtianClose_anim_y.set_var(Sheers_FabCurtianClose)
        Sheers_FabCurtianClose_anim_y.set_time(300)
        Sheers_FabCurtianClose_anim_y.set_delay(0)
        Sheers_FabCurtianClose_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(Sheers_FabCurtianClose,val))
        Sheers_FabCurtianClose_anim_y.set_values(Sheers_FabCurtianClose.get_y(), 588)
        Sheers_FabCurtianClose_anim_y.set_path_cb(lv.anim_t.path_linear)
        Sheers_FabCurtianClose_anim_y.set_repeat_count(0)
        Sheers_FabCurtianClose_anim_y.set_repeat_delay(0)
        Sheers_FabCurtianClose_anim_y.set_playback_time(0)
        Sheers_FabCurtianClose_anim_y.set_playback_delay(0)
        Sheers_FabCurtianClose_anim_y.start()
        #Write animation: Sheers_FabCurtianOpen y
        Sheers_FabCurtianOpen_anim_y = lv.anim_t()
        Sheers_FabCurtianOpen_anim_y.init()
        Sheers_FabCurtianOpen_anim_y.set_var(Sheers_FabCurtianOpen)
        Sheers_FabCurtianOpen_anim_y.set_time(300)
        Sheers_FabCurtianOpen_anim_y.set_delay(0)
        Sheers_FabCurtianOpen_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(Sheers_FabCurtianOpen,val))
        Sheers_FabCurtianOpen_anim_y.set_values(Sheers_FabCurtianOpen.get_y(), 588)
        Sheers_FabCurtianOpen_anim_y.set_path_cb(lv.anim_t.path_linear)
        Sheers_FabCurtianOpen_anim_y.set_repeat_count(0)
        Sheers_FabCurtianOpen_anim_y.set_repeat_delay(0)
        Sheers_FabCurtianOpen_anim_y.set_playback_time(0)
        Sheers_FabCurtianOpen_anim_y.set_playback_delay(0)
        Sheers_FabCurtianOpen_anim_y.start()
        

Sheers.add_event_cb(lambda e: Sheers_event_handler(e), lv.EVENT.ALL, None)

def Sheers_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
Sheers_btn_1.add_event_cb(lambda e: Sheers_btn_1_event_handler(e), lv.EVENT.ALL, None)

def Sheers_FabCurtianOpen_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Sheers_FabCurtianOpen.add_event_cb(lambda e: Sheers_FabCurtianOpen_event_handler(e), lv.EVENT.ALL, None)

def Sheers_FabCurtianClose_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Sheers_FabCurtianClose.add_event_cb(lambda e: Sheers_FabCurtianClose_event_handler(e), lv.EVENT.ALL, None)

def Sheers_FabCurtianPause_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Sheers_FabCurtianPause.add_event_cb(lambda e: Sheers_FabCurtianPause_event_handler(e), lv.EVENT.ALL, None)

def Sheers_FabCurtianLeft_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSED):
        pass
        

Sheers_FabCurtianLeft.add_event_cb(lambda e: Sheers_FabCurtianLeft_event_handler(e), lv.EVENT.ALL, None)

def Sheers_FabCurtianright_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSED):
        pass
        

Sheers_FabCurtianright.add_event_cb(lambda e: Sheers_FabCurtianright_event_handler(e), lv.EVENT.ALL, None)

def Sheers_FabCurtianPull2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

Sheers_FabCurtianPull2.add_event_cb(lambda e: Sheers_FabCurtianPull2_event_handler(e), lv.EVENT.ALL, None)

def Sheers_FabCurtianPull1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

Sheers_FabCurtianPull1.add_event_cb(lambda e: Sheers_FabCurtianPull1_event_handler(e), lv.EVENT.ALL, None)

def Sheers_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Sheers_btn_2.add_event_cb(lambda e: Sheers_btn_2_event_handler(e), lv.EVENT.ALL, None)

def Sheers_FabCurtianPull4_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

Sheers_FabCurtianPull4.add_event_cb(lambda e: Sheers_FabCurtianPull4_event_handler(e), lv.EVENT.ALL, None)

def Sheers_FabCurtianPull3_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

Sheers_FabCurtianPull3.add_event_cb(lambda e: Sheers_FabCurtianPull3_event_handler(e), lv.EVENT.ALL, None)

def RollBlind_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        #Write animation: RollBlind_FabCurtianPause y
        RollBlind_FabCurtianPause_anim_y = lv.anim_t()
        RollBlind_FabCurtianPause_anim_y.init()
        RollBlind_FabCurtianPause_anim_y.set_var(RollBlind_FabCurtianPause)
        RollBlind_FabCurtianPause_anim_y.set_time(300)
        RollBlind_FabCurtianPause_anim_y.set_delay(0)
        RollBlind_FabCurtianPause_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(RollBlind_FabCurtianPause,val))
        RollBlind_FabCurtianPause_anim_y.set_values(RollBlind_FabCurtianPause.get_y(), 588)
        RollBlind_FabCurtianPause_anim_y.set_path_cb(lv.anim_t.path_linear)
        RollBlind_FabCurtianPause_anim_y.set_repeat_count(0)
        RollBlind_FabCurtianPause_anim_y.set_repeat_delay(0)
        RollBlind_FabCurtianPause_anim_y.set_playback_time(0)
        RollBlind_FabCurtianPause_anim_y.set_playback_delay(0)
        RollBlind_FabCurtianPause_anim_y.start()
        #Write animation: RollBlind_FabCurtianClose y
        RollBlind_FabCurtianClose_anim_y = lv.anim_t()
        RollBlind_FabCurtianClose_anim_y.init()
        RollBlind_FabCurtianClose_anim_y.set_var(RollBlind_FabCurtianClose)
        RollBlind_FabCurtianClose_anim_y.set_time(300)
        RollBlind_FabCurtianClose_anim_y.set_delay(0)
        RollBlind_FabCurtianClose_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(RollBlind_FabCurtianClose,val))
        RollBlind_FabCurtianClose_anim_y.set_values(RollBlind_FabCurtianClose.get_y(), 588)
        RollBlind_FabCurtianClose_anim_y.set_path_cb(lv.anim_t.path_linear)
        RollBlind_FabCurtianClose_anim_y.set_repeat_count(0)
        RollBlind_FabCurtianClose_anim_y.set_repeat_delay(0)
        RollBlind_FabCurtianClose_anim_y.set_playback_time(0)
        RollBlind_FabCurtianClose_anim_y.set_playback_delay(0)
        RollBlind_FabCurtianClose_anim_y.start()
        #Write animation: RollBlind_FabCurtianOpen y
        RollBlind_FabCurtianOpen_anim_y = lv.anim_t()
        RollBlind_FabCurtianOpen_anim_y.init()
        RollBlind_FabCurtianOpen_anim_y.set_var(RollBlind_FabCurtianOpen)
        RollBlind_FabCurtianOpen_anim_y.set_time(300)
        RollBlind_FabCurtianOpen_anim_y.set_delay(0)
        RollBlind_FabCurtianOpen_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(RollBlind_FabCurtianOpen,val))
        RollBlind_FabCurtianOpen_anim_y.set_values(RollBlind_FabCurtianOpen.get_y(), 588)
        RollBlind_FabCurtianOpen_anim_y.set_path_cb(lv.anim_t.path_linear)
        RollBlind_FabCurtianOpen_anim_y.set_repeat_count(0)
        RollBlind_FabCurtianOpen_anim_y.set_repeat_delay(0)
        RollBlind_FabCurtianOpen_anim_y.set_playback_time(0)
        RollBlind_FabCurtianOpen_anim_y.set_playback_delay(0)
        RollBlind_FabCurtianOpen_anim_y.start()
        

RollBlind.add_event_cb(lambda e: RollBlind_event_handler(e), lv.EVENT.ALL, None)

def RollBlind_FabCurtianOpen_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

RollBlind_FabCurtianOpen.add_event_cb(lambda e: RollBlind_FabCurtianOpen_event_handler(e), lv.EVENT.ALL, None)

def RollBlind_FabCurtianClose_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

RollBlind_FabCurtianClose.add_event_cb(lambda e: RollBlind_FabCurtianClose_event_handler(e), lv.EVENT.ALL, None)

def RollBlind_FabCurtianPause_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

RollBlind_FabCurtianPause.add_event_cb(lambda e: RollBlind_FabCurtianPause_event_handler(e), lv.EVENT.ALL, None)

def RollBlind_FabCurtianLeft_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSED):
        pass
        

RollBlind_FabCurtianLeft.add_event_cb(lambda e: RollBlind_FabCurtianLeft_event_handler(e), lv.EVENT.ALL, None)

def RollBlind_FabCurtianPull1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

RollBlind_FabCurtianPull1.add_event_cb(lambda e: RollBlind_FabCurtianPull1_event_handler(e), lv.EVENT.ALL, None)

def RollBlind_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
RollBlind_btn_1.add_event_cb(lambda e: RollBlind_btn_1_event_handler(e), lv.EVENT.ALL, None)

def RollBlind_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

RollBlind_btn_2.add_event_cb(lambda e: RollBlind_btn_2_event_handler(e), lv.EVENT.ALL, None)

def RollBlind_FabCurtianPull2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

RollBlind_FabCurtianPull2.add_event_cb(lambda e: RollBlind_FabCurtianPull2_event_handler(e), lv.EVENT.ALL, None)

def Dream_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        #Write animation: Dream_FabCurtianPause y
        Dream_FabCurtianPause_anim_y = lv.anim_t()
        Dream_FabCurtianPause_anim_y.init()
        Dream_FabCurtianPause_anim_y.set_var(Dream_FabCurtianPause)
        Dream_FabCurtianPause_anim_y.set_time(300)
        Dream_FabCurtianPause_anim_y.set_delay(0)
        Dream_FabCurtianPause_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(Dream_FabCurtianPause,val))
        Dream_FabCurtianPause_anim_y.set_values(Dream_FabCurtianPause.get_y(), 588)
        Dream_FabCurtianPause_anim_y.set_path_cb(lv.anim_t.path_linear)
        Dream_FabCurtianPause_anim_y.set_repeat_count(0)
        Dream_FabCurtianPause_anim_y.set_repeat_delay(0)
        Dream_FabCurtianPause_anim_y.set_playback_time(0)
        Dream_FabCurtianPause_anim_y.set_playback_delay(0)
        Dream_FabCurtianPause_anim_y.start()
        #Write animation: Dream_FabCurtianClose y
        Dream_FabCurtianClose_anim_y = lv.anim_t()
        Dream_FabCurtianClose_anim_y.init()
        Dream_FabCurtianClose_anim_y.set_var(Dream_FabCurtianClose)
        Dream_FabCurtianClose_anim_y.set_time(300)
        Dream_FabCurtianClose_anim_y.set_delay(0)
        Dream_FabCurtianClose_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(Dream_FabCurtianClose,val))
        Dream_FabCurtianClose_anim_y.set_values(Dream_FabCurtianClose.get_y(), 588)
        Dream_FabCurtianClose_anim_y.set_path_cb(lv.anim_t.path_linear)
        Dream_FabCurtianClose_anim_y.set_repeat_count(0)
        Dream_FabCurtianClose_anim_y.set_repeat_delay(0)
        Dream_FabCurtianClose_anim_y.set_playback_time(0)
        Dream_FabCurtianClose_anim_y.set_playback_delay(0)
        Dream_FabCurtianClose_anim_y.start()
        #Write animation: Dream_FabCurtianOpen y
        Dream_FabCurtianOpen_anim_y = lv.anim_t()
        Dream_FabCurtianOpen_anim_y.init()
        Dream_FabCurtianOpen_anim_y.set_var(Dream_FabCurtianOpen)
        Dream_FabCurtianOpen_anim_y.set_time(300)
        Dream_FabCurtianOpen_anim_y.set_delay(0)
        Dream_FabCurtianOpen_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(Dream_FabCurtianOpen,val))
        Dream_FabCurtianOpen_anim_y.set_values(Dream_FabCurtianOpen.get_y(), 588)
        Dream_FabCurtianOpen_anim_y.set_path_cb(lv.anim_t.path_linear)
        Dream_FabCurtianOpen_anim_y.set_repeat_count(0)
        Dream_FabCurtianOpen_anim_y.set_repeat_delay(0)
        Dream_FabCurtianOpen_anim_y.set_playback_time(0)
        Dream_FabCurtianOpen_anim_y.set_playback_delay(0)
        Dream_FabCurtianOpen_anim_y.start()
        

Dream.add_event_cb(lambda e: Dream_event_handler(e), lv.EVENT.ALL, None)

def Dream_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
Dream_btn_1.add_event_cb(lambda e: Dream_btn_1_event_handler(e), lv.EVENT.ALL, None)

def Dream_FabCurtianOpen_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Dream_FabCurtianOpen.add_event_cb(lambda e: Dream_FabCurtianOpen_event_handler(e), lv.EVENT.ALL, None)

def Dream_FabCurtianClose_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Dream_FabCurtianClose.add_event_cb(lambda e: Dream_FabCurtianClose_event_handler(e), lv.EVENT.ALL, None)

def Dream_FabCurtianPause_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Dream_FabCurtianPause.add_event_cb(lambda e: Dream_FabCurtianPause_event_handler(e), lv.EVENT.ALL, None)

def Dream_FabCurtianLeft_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSED):
        pass
        

Dream_FabCurtianLeft.add_event_cb(lambda e: Dream_FabCurtianLeft_event_handler(e), lv.EVENT.ALL, None)

def Dream_FabCurtianright_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSED):
        pass
        

Dream_FabCurtianright.add_event_cb(lambda e: Dream_FabCurtianright_event_handler(e), lv.EVENT.ALL, None)

def Dream_FabCurtianPull2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

Dream_FabCurtianPull2.add_event_cb(lambda e: Dream_FabCurtianPull2_event_handler(e), lv.EVENT.ALL, None)

def Dream_FabCurtianPull1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

Dream_FabCurtianPull1.add_event_cb(lambda e: Dream_FabCurtianPull1_event_handler(e), lv.EVENT.ALL, None)

def Dream_slider_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

Dream_slider_1.add_event_cb(lambda e: Dream_slider_1_event_handler(e), lv.EVENT.ALL, None)

def Dream_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Dream_btn_2.add_event_cb(lambda e: Dream_btn_2_event_handler(e), lv.EVENT.ALL, None)

def Dream_FabCurtianPull3_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

Dream_FabCurtianPull3.add_event_cb(lambda e: Dream_FabCurtianPull3_event_handler(e), lv.EVENT.ALL, None)

def Dream_FabCurtianPull4_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

Dream_FabCurtianPull4.add_event_cb(lambda e: Dream_FabCurtianPull4_event_handler(e), lv.EVENT.ALL, None)

def AirCondition_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        

AirCondition.add_event_cb(lambda e: AirCondition_event_handler(e), lv.EVENT.ALL, None)

def AirCondition_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
AirCondition_btn_1.add_event_cb(lambda e: AirCondition_btn_1_event_handler(e), lv.EVENT.ALL, None)

def AirCondition_ACBtn_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

AirCondition_ACBtn.add_event_cb(lambda e: AirCondition_ACBtn_event_handler(e), lv.EVENT.ALL, None)

def AirCondition_ACSpeedAuto_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

AirCondition_ACSpeedAuto.add_event_cb(lambda e: AirCondition_ACSpeedAuto_event_handler(e), lv.EVENT.ALL, None)

def AirCondition_ACSpeed3_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

AirCondition_ACSpeed3.add_event_cb(lambda e: AirCondition_ACSpeed3_event_handler(e), lv.EVENT.ALL, None)

def AirCondition_ACSpeed2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

AirCondition_ACSpeed2.add_event_cb(lambda e: AirCondition_ACSpeed2_event_handler(e), lv.EVENT.ALL, None)

def AirCondition_ACSpeed1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

AirCondition_ACSpeed1.add_event_cb(lambda e: AirCondition_ACSpeed1_event_handler(e), lv.EVENT.ALL, None)

def AirCondition_AcCool_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

AirCondition_AcCool.add_event_cb(lambda e: AirCondition_AcCool_event_handler(e), lv.EVENT.ALL, None)

def AirCondition_ACFan_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

AirCondition_ACFan.add_event_cb(lambda e: AirCondition_ACFan_event_handler(e), lv.EVENT.ALL, None)

def AirCondition_ACHot_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

AirCondition_ACHot.add_event_cb(lambda e: AirCondition_ACHot_event_handler(e), lv.EVENT.ALL, None)

def AirCondition_ACDry_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

AirCondition_ACDry.add_event_cb(lambda e: AirCondition_ACDry_event_handler(e), lv.EVENT.ALL, None)

def AirCondition_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

AirCondition_btn_2.add_event_cb(lambda e: AirCondition_btn_2_event_handler(e), lv.EVENT.ALL, None)

def Music_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        

Music.add_event_cb(lambda e: Music_event_handler(e), lv.EVENT.ALL, None)

def Music_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
Music_btn_1.add_event_cb(lambda e: Music_btn_1_event_handler(e), lv.EVENT.ALL, None)

def Music_play_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Music_play.add_event_cb(lambda e: Music_play_event_handler(e), lv.EVENT.ALL, None)

def Music_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Music_btn_2.add_event_cb(lambda e: Music_btn_2_event_handler(e), lv.EVENT.ALL, None)

def DryRack_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        #Write animation: DryRack_FabCurtianPause y
        DryRack_FabCurtianPause_anim_y = lv.anim_t()
        DryRack_FabCurtianPause_anim_y.init()
        DryRack_FabCurtianPause_anim_y.set_var(DryRack_FabCurtianPause)
        DryRack_FabCurtianPause_anim_y.set_time(300)
        DryRack_FabCurtianPause_anim_y.set_delay(0)
        DryRack_FabCurtianPause_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(DryRack_FabCurtianPause,val))
        DryRack_FabCurtianPause_anim_y.set_values(DryRack_FabCurtianPause.get_y(), 588)
        DryRack_FabCurtianPause_anim_y.set_path_cb(lv.anim_t.path_linear)
        DryRack_FabCurtianPause_anim_y.set_repeat_count(0)
        DryRack_FabCurtianPause_anim_y.set_repeat_delay(0)
        DryRack_FabCurtianPause_anim_y.set_playback_time(0)
        DryRack_FabCurtianPause_anim_y.set_playback_delay(0)
        DryRack_FabCurtianPause_anim_y.start()
        #Write animation: DryRack_FabCurtianClose y
        DryRack_FabCurtianClose_anim_y = lv.anim_t()
        DryRack_FabCurtianClose_anim_y.init()
        DryRack_FabCurtianClose_anim_y.set_var(DryRack_FabCurtianClose)
        DryRack_FabCurtianClose_anim_y.set_time(300)
        DryRack_FabCurtianClose_anim_y.set_delay(0)
        DryRack_FabCurtianClose_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(DryRack_FabCurtianClose,val))
        DryRack_FabCurtianClose_anim_y.set_values(DryRack_FabCurtianClose.get_y(), 588)
        DryRack_FabCurtianClose_anim_y.set_path_cb(lv.anim_t.path_linear)
        DryRack_FabCurtianClose_anim_y.set_repeat_count(0)
        DryRack_FabCurtianClose_anim_y.set_repeat_delay(0)
        DryRack_FabCurtianClose_anim_y.set_playback_time(0)
        DryRack_FabCurtianClose_anim_y.set_playback_delay(0)
        DryRack_FabCurtianClose_anim_y.start()
        #Write animation: DryRack_FabCurtianOpen y
        DryRack_FabCurtianOpen_anim_y = lv.anim_t()
        DryRack_FabCurtianOpen_anim_y.init()
        DryRack_FabCurtianOpen_anim_y.set_var(DryRack_FabCurtianOpen)
        DryRack_FabCurtianOpen_anim_y.set_time(300)
        DryRack_FabCurtianOpen_anim_y.set_delay(0)
        DryRack_FabCurtianOpen_anim_y.set_custom_exec_cb(lambda e,val: anim_y_cb(DryRack_FabCurtianOpen,val))
        DryRack_FabCurtianOpen_anim_y.set_values(DryRack_FabCurtianOpen.get_y(), 588)
        DryRack_FabCurtianOpen_anim_y.set_path_cb(lv.anim_t.path_linear)
        DryRack_FabCurtianOpen_anim_y.set_repeat_count(0)
        DryRack_FabCurtianOpen_anim_y.set_repeat_delay(0)
        DryRack_FabCurtianOpen_anim_y.set_playback_time(0)
        DryRack_FabCurtianOpen_anim_y.set_playback_delay(0)
        DryRack_FabCurtianOpen_anim_y.start()
        

DryRack.add_event_cb(lambda e: DryRack_event_handler(e), lv.EVENT.ALL, None)

def DryRack_FabCurtianOpen_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

DryRack_FabCurtianOpen.add_event_cb(lambda e: DryRack_FabCurtianOpen_event_handler(e), lv.EVENT.ALL, None)

def DryRack_FabCurtianClose_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

DryRack_FabCurtianClose.add_event_cb(lambda e: DryRack_FabCurtianClose_event_handler(e), lv.EVENT.ALL, None)

def DryRack_FabCurtianPause_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

DryRack_FabCurtianPause.add_event_cb(lambda e: DryRack_FabCurtianPause_event_handler(e), lv.EVENT.ALL, None)

def DryRack_img_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

    if (code == lv.EVENT.PRESSED):
        pass
        

DryRack_img_1.add_event_cb(lambda e: DryRack_img_1_event_handler(e), lv.EVENT.ALL, None)

def DryRack_imgbtn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

DryRack_imgbtn_1.add_event_cb(lambda e: DryRack_imgbtn_1_event_handler(e), lv.EVENT.ALL, None)

def DryRack_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
DryRack_btn_1.add_event_cb(lambda e: DryRack_btn_1_event_handler(e), lv.EVENT.ALL, None)

def DryRack_label_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

DryRack_label_1.add_event_cb(lambda e: DryRack_label_1_event_handler(e), lv.EVENT.ALL, None)

def DryRack_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

DryRack_btn_2.add_event_cb(lambda e: DryRack_btn_2_event_handler(e), lv.EVENT.ALL, None)

def DryRack_dry_rack_pull_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.PRESSING):
        pass
        

    if (code == lv.EVENT.PRESSED):
        pass
        

DryRack_dry_rack_pull.add_event_cb(lambda e: DryRack_dry_rack_pull_event_handler(e), lv.EVENT.ALL, None)

def FanAndLight_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        

FanAndLight.add_event_cb(lambda e: FanAndLight_event_handler(e), lv.EVENT.ALL, None)

def FanAndLight_fLight_off_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

FanAndLight_fLight_off.add_event_cb(lambda e: FanAndLight_fLight_off_event_handler(e), lv.EVENT.ALL, None)

def FanAndLight_fLight_on_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

FanAndLight_fLight_on.add_event_cb(lambda e: FanAndLight_fLight_on_event_handler(e), lv.EVENT.ALL, None)

def FanAndLight_FanSpeed4_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

FanAndLight_FanSpeed4.add_event_cb(lambda e: FanAndLight_FanSpeed4_event_handler(e), lv.EVENT.ALL, None)

def FanAndLight_FanSpeed3_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

FanAndLight_FanSpeed3.add_event_cb(lambda e: FanAndLight_FanSpeed3_event_handler(e), lv.EVENT.ALL, None)

def FanAndLight_FanSpeed2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

FanAndLight_FanSpeed2.add_event_cb(lambda e: FanAndLight_FanSpeed2_event_handler(e), lv.EVENT.ALL, None)

def FanAndLight_FanSpeed1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

FanAndLight_FanSpeed1.add_event_cb(lambda e: FanAndLight_FanSpeed1_event_handler(e), lv.EVENT.ALL, None)

def FanAndLight_Fan_on_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

FanAndLight_Fan_on.add_event_cb(lambda e: FanAndLight_Fan_on_event_handler(e), lv.EVENT.ALL, None)

def FanAndLight_Fan_off_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

FanAndLight_Fan_off.add_event_cb(lambda e: FanAndLight_Fan_off_event_handler(e), lv.EVENT.ALL, None)

def FanAndLight_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
FanAndLight_btn_1.add_event_cb(lambda e: FanAndLight_btn_1_event_handler(e), lv.EVENT.ALL, None)

def FanAndLight_imgbtn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

FanAndLight_imgbtn_1.add_event_cb(lambda e: FanAndLight_imgbtn_1_event_handler(e), lv.EVENT.ALL, None)

def FanAndLight_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

FanAndLight_btn_2.add_event_cb(lambda e: FanAndLight_btn_2_event_handler(e), lv.EVENT.ALL, None)

def Heater_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        

Heater.add_event_cb(lambda e: Heater_event_handler(e), lv.EVENT.ALL, None)

def Heater_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
Heater_btn_1.add_event_cb(lambda e: Heater_btn_1_event_handler(e), lv.EVENT.ALL, None)

def Heater_LightBtn_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Heater_LightBtn.add_event_cb(lambda e: Heater_LightBtn_event_handler(e), lv.EVENT.ALL, None)

def Heater_LightOnImg_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Heater_LightOnImg.add_event_cb(lambda e: Heater_LightOnImg_event_handler(e), lv.EVENT.ALL, None)

def Heater_IdleBtn_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Heater_IdleBtn.add_event_cb(lambda e: Heater_IdleBtn_event_handler(e), lv.EVENT.ALL, None)

def Heater_VentilateBtn_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Heater_VentilateBtn.add_event_cb(lambda e: Heater_VentilateBtn_event_handler(e), lv.EVENT.ALL, None)

def Heater_VentilateImg_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Heater_VentilateImg.add_event_cb(lambda e: Heater_VentilateImg_event_handler(e), lv.EVENT.ALL, None)

def Heater_HeatLowBtn_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Heater_HeatLowBtn.add_event_cb(lambda e: Heater_HeatLowBtn_event_handler(e), lv.EVENT.ALL, None)

def Heater_HeatLowImg_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Heater_HeatLowImg.add_event_cb(lambda e: Heater_HeatLowImg_event_handler(e), lv.EVENT.ALL, None)

def Heater_WindBtn_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Heater_WindBtn.add_event_cb(lambda e: Heater_WindBtn_event_handler(e), lv.EVENT.ALL, None)

def Heater_WindImg_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Heater_WindImg.add_event_cb(lambda e: Heater_WindImg_event_handler(e), lv.EVENT.ALL, None)

def Heater_HeatHighBtn_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Heater_HeatHighBtn.add_event_cb(lambda e: Heater_HeatHighBtn_event_handler(e), lv.EVENT.ALL, None)

def Heater_HeatHighImg_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Heater_HeatHighImg.add_event_cb(lambda e: Heater_HeatHighImg_event_handler(e), lv.EVENT.ALL, None)

def Heater_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Heater_btn_2.add_event_cb(lambda e: Heater_btn_2_event_handler(e), lv.EVENT.ALL, None)

def setting_screen_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        

setting_screen.add_event_cb(lambda e: setting_screen_event_handler(e), lv.EVENT.ALL, None)

def setting_screen_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(ui_home_screen, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
setting_screen_btn_1.add_event_cb(lambda e: setting_screen_btn_1_event_handler(e), lv.EVENT.ALL, None)

def setting_screen_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

setting_screen_btn_2.add_event_cb(lambda e: setting_screen_btn_2_event_handler(e), lv.EVENT.ALL, None)

def setting_screen_cont_3_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(NetSetting, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
setting_screen_cont_3.add_event_cb(lambda e: setting_screen_cont_3_event_handler(e), lv.EVENT.ALL, None)

def NetSetting_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        

NetSetting.add_event_cb(lambda e: NetSetting_event_handler(e), lv.EVENT.ALL, None)

def NetSetting_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(setting_screen, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
NetSetting_btn_1.add_event_cb(lambda e: NetSetting_btn_1_event_handler(e), lv.EVENT.ALL, None)

def PlaySet_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        

PlaySet.add_event_cb(lambda e: PlaySet_event_handler(e), lv.EVENT.ALL, None)

def PlaySet_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(setting_screen, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
PlaySet_btn_2.add_event_cb(lambda e: PlaySet_btn_2_event_handler(e), lv.EVENT.ALL, None)

def SwitchSet_btn_8_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(setting_screen, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
SwitchSet_btn_8.add_event_cb(lambda e: SwitchSet_btn_8_event_handler(e), lv.EVENT.ALL, None)

def SensorSet_btn_13_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(setting_screen, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
SensorSet_btn_13.add_event_cb(lambda e: SensorSet_btn_13_event_handler(e), lv.EVENT.ALL, None)

def Reset_btn_4_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(setting_screen, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
Reset_btn_4.add_event_cb(lambda e: Reset_btn_4_event_handler(e), lv.EVENT.ALL, None)

def huifuchuchangshezhi_btn_4_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(setting_screen, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
huifuchuchangshezhi_btn_4.add_event_cb(lambda e: huifuchuchangshezhi_btn_4_event_handler(e), lv.EVENT.ALL, None)

def RelativeProduct_btn_4_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(setting_screen, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
RelativeProduct_btn_4.add_event_cb(lambda e: RelativeProduct_btn_4_event_handler(e), lv.EVENT.ALL, None)

def Helper_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

Helper_btn_1.add_event_cb(lambda e: Helper_btn_1_event_handler(e), lv.EVENT.ALL, None)

# content from custom.py

# Load the default screen
lv.scr_load(ui_home_screen)

while SDL.check():
    time.sleep_ms(5)

