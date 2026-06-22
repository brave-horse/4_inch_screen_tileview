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

# Create screen
screen = lv.obj()
screen.set_size(720, 720)
screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_img_1
screen_img_1 = lv.img(screen)
screen_img_1.set_src("B:MicroPython/_1_alpha_720x720.bin")
screen_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
screen_img_1.set_pivot(50,50)
screen_img_1.set_angle(0)
screen_img_1.set_pos(-1, 0)
screen_img_1.set_size(720, 720)
# Set style for screen_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_digital_clock_1
screen_digital_clock_1_time = [int(11), int(25), int(50), ""]
screen_digital_clock_1 = lv.dclock(screen, "11:25")
screen_digital_clock_1_timer = lv.timer_create_basic()
screen_digital_clock_1_timer.set_period(1000)
screen_digital_clock_1_timer.set_cb(lambda src: digital_clock_cb(screen_digital_clock_1_timer, screen_digital_clock_1, screen_digital_clock_1_time, False, False ))
screen_digital_clock_1.set_pos(53, 45)
screen_digital_clock_1.set_size(131, 52)
# Set style for screen_digital_clock_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_digital_clock_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_pad_top(7, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_label_1
screen_label_1 = lv.label(screen)
screen_label_1.set_text("2026/06/01")
screen_label_1.set_long_mode(lv.label.LONG.WRAP)
screen_label_1.set_width(lv.pct(100))
screen_label_1.set_pos(66, 111)
screen_label_1.set_size(172, 43)
# Set style for screen_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_label_2
screen_label_2 = lv.label(screen)
screen_label_2.set_text("星期一")
screen_label_2.set_long_mode(lv.label.LONG.WRAP)
screen_label_2.set_width(lv.pct(100))
screen_label_2.set_pos(60, 177)
screen_label_2.set_size(118, 40)
# Set style for screen_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_2.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_btn_1
screen_btn_1 = lv.btn(screen)
screen_btn_1.add_flag(lv.obj.FLAG.CHECKABLE)
screen_btn_1_label = lv.label(screen_btn_1)
screen_btn_1_label.set_text("按键1")
screen_btn_1_label.set_long_mode(lv.label.LONG.CLIP)
screen_btn_1_label.set_width(lv.pct(100))
screen_btn_1_label.align(lv.ALIGN.CENTER, 0, 0)
screen_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_btn_1.set_pos(529, 118)
screen_btn_1.set_size(126, 115)
# Set style for screen_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_btn_1.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_btn_1, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
screen_btn_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
screen_btn_1.set_style_bg_color(lv.color_hex(0x3b3e40), lv.PART.MAIN|lv.STATE.PRESSED)
screen_btn_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.PRESSED)
screen_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
screen_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.PRESSED)
screen_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
screen_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.PRESSED)
screen_btn_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 16), lv.PART.MAIN|lv.STATE.PRESSED)
screen_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for screen_btn_1, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
screen_btn_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
screen_btn_1.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.CHECKED)
screen_btn_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.CHECKED)
screen_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
screen_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.CHECKED)
screen_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
screen_btn_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.CHECKED)
screen_btn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
screen_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for screen_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DISABLED.
screen_btn_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DISABLED)
screen_btn_1.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DISABLED)
screen_btn_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DISABLED)
screen_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DISABLED)
screen_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DISABLED)
screen_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DISABLED)
screen_btn_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DISABLED)
screen_btn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DISABLED)
screen_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DISABLED)

# Create screen_btn_2
screen_btn_2 = lv.btn(screen)
screen_btn_2.add_flag(lv.obj.FLAG.CHECKABLE)
screen_btn_2_label = lv.label(screen_btn_2)
screen_btn_2_label.set_text("按键3")
screen_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
screen_btn_2_label.set_width(lv.pct(100))
screen_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
screen_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_btn_2.set_pos(529, 508)
screen_btn_2.set_size(126, 115)
# Set style for screen_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_btn_2.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_btn_3
screen_btn_3 = lv.btn(screen)
screen_btn_3.add_flag(lv.obj.FLAG.CHECKABLE)
screen_btn_3_label = lv.label(screen_btn_3)
screen_btn_3_label.set_text("按键2")
screen_btn_3_label.set_long_mode(lv.label.LONG.CLIP)
screen_btn_3_label.set_width(lv.pct(100))
screen_btn_3_label.align(lv.ALIGN.CENTER, 0, 0)
screen_btn_3.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_btn_3.set_pos(529, 300)
screen_btn_3.set_size(126, 115)
# Set style for screen_btn_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_btn_3.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_cont_1
screen_cont_1 = lv.obj(screen)
screen_cont_1.set_pos(0, -600)
screen_cont_1.set_size(720, 320)
screen_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

screen.update_layout()
# Create screen_1
screen_1 = lv.obj()
screen_1.set_size(720, 720)
screen_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_1_tabview_1
screen_1_tabview_1 = lv.tabview(screen_1, lv.DIR.TOP, 85)
screen_1_tabview_1.set_pos(-1, -1)
screen_1_tabview_1.set_size(720, 720)
screen_1_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for screen_1_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_1_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_1_tabview_1_extra_btnm_main_default = lv.style_t()
style_screen_1_tabview_1_extra_btnm_main_default.init()
style_screen_1_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_screen_1_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x201b1b))
style_screen_1_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_1_tabview_1_extra_btnm_main_default.set_border_width(0)
style_screen_1_tabview_1_extra_btnm_main_default.set_radius(0)
screen_1_tabview_1.get_tab_btns().add_style(style_screen_1_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_1_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_screen_1_tabview_1_extra_btnm_items_default = lv.style_t()
style_screen_1_tabview_1_extra_btnm_items_default.init()
style_screen_1_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_screen_1_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_screen_1_tabview_1_extra_btnm_items_default.set_text_opa(255)
screen_1_tabview_1.get_tab_btns().add_style(style_screen_1_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for screen_1_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_screen_1_tabview_1_extra_btnm_items_checked = lv.style_t()
style_screen_1_tabview_1_extra_btnm_items_checked.init()
style_screen_1_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0x2195f6))
style_screen_1_tabview_1_extra_btnm_items_checked.set_text_font(test_font("montserratMedium", 12))
style_screen_1_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_screen_1_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_screen_1_tabview_1_extra_btnm_items_checked.set_radius(0)
style_screen_1_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_screen_1_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x201b1b))
style_screen_1_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
screen_1_tabview_1.get_tab_btns().add_style(style_screen_1_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
screen_1_tabview_1_tab_1 = screen_1_tabview_1.add_tab("")
screen_1_tabview_1_tab_1_label = lv.label(screen_1_tabview_1_tab_1)
screen_1_tabview_1_tab_1_label.set_text("")

# Create screen_1_cont_1
screen_1_cont_1 = lv.obj(screen_1_tabview_1_tab_1)
screen_1_cont_1.set_pos(17, 3)
screen_1_cont_1.set_size(300, 150)
screen_1_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_1_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_cont_1.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_cont_1.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_cont_1.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_cont_1.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_cont_1.set_style_radius(30, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_cont_1.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_cont_1.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_1_Light_CT_on_off_1_img
screen_1_Light_CT_on_off_1_img = lv.imgbtn(screen_1_cont_1)
screen_1_Light_CT_on_off_1_img.add_flag(lv.obj.FLAG.CHECKABLE)
screen_1_Light_CT_on_off_1_img.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_onoff_off_alpha_48x48.bin", None)
screen_1_Light_CT_on_off_1_img.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_onoff_on_alpha_48x48.bin", None)
screen_1_Light_CT_on_off_1_img.add_flag(lv.obj.FLAG.CHECKABLE)
screen_1_Light_CT_on_off_1_img_label = lv.label(screen_1_Light_CT_on_off_1_img)
screen_1_Light_CT_on_off_1_img_label.set_text("")
screen_1_Light_CT_on_off_1_img_label.set_long_mode(lv.label.LONG.WRAP)
screen_1_Light_CT_on_off_1_img_label.set_width(lv.pct(100))
screen_1_Light_CT_on_off_1_img_label.align(lv.ALIGN.CENTER, 0, 0)
screen_1_Light_CT_on_off_1_img.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_1_Light_CT_on_off_1_img.set_pos(211, 24)
screen_1_Light_CT_on_off_1_img.set_size(48, 48)
# Set style for screen_1_Light_CT_on_off_1_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_Light_CT_on_off_1_img.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_Light_CT_on_off_1_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_Light_CT_on_off_1_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_Light_CT_on_off_1_img.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_Light_CT_on_off_1_img.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_Light_CT_on_off_1_img.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_Light_CT_on_off_1_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_1_Light_CT_on_off_1_img, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
screen_1_Light_CT_on_off_1_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
screen_1_Light_CT_on_off_1_img.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
screen_1_Light_CT_on_off_1_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
screen_1_Light_CT_on_off_1_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
screen_1_Light_CT_on_off_1_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for screen_1_Light_CT_on_off_1_img, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
screen_1_Light_CT_on_off_1_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
screen_1_Light_CT_on_off_1_img.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
screen_1_Light_CT_on_off_1_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
screen_1_Light_CT_on_off_1_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
screen_1_Light_CT_on_off_1_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for screen_1_Light_CT_on_off_1_img, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
screen_1_Light_CT_on_off_1_img.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create screen_1_small_dev_on_img
screen_1_small_dev_on_img = lv.img(screen_1_cont_1)
screen_1_small_dev_on_img.set_src("B:MicroPython/_small_dev_on_alpha_50x57.bin")
screen_1_small_dev_on_img.add_flag(lv.obj.FLAG.CLICKABLE)
screen_1_small_dev_on_img.set_pivot(50,50)
screen_1_small_dev_on_img.set_angle(0)
screen_1_small_dev_on_img.set_pos(40, 13)
screen_1_small_dev_on_img.set_size(50, 57)
# Set style for screen_1_small_dev_on_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_small_dev_on_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_small_dev_on_img.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_small_dev_on_img.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_1_small_dev_off_img
screen_1_small_dev_off_img = lv.img(screen_1_cont_1)
screen_1_small_dev_off_img.set_src("B:MicroPython/_small_dev_off_alpha_50x57.bin")
screen_1_small_dev_off_img.add_flag(lv.obj.FLAG.CLICKABLE)
screen_1_small_dev_off_img.set_pivot(50,50)
screen_1_small_dev_off_img.set_angle(0)
screen_1_small_dev_off_img.set_pos(40, 13)
screen_1_small_dev_off_img.set_size(50, 57)
# Set style for screen_1_small_dev_off_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_small_dev_off_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_small_dev_off_img.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_small_dev_off_img.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_1_label_2
screen_1_label_2 = lv.label(screen_1_cont_1)
screen_1_label_2.set_text("色温灯")
screen_1_label_2.set_long_mode(lv.label.LONG.WRAP)
screen_1_label_2.set_width(lv.pct(100))
screen_1_label_2.set_pos(18, 94)
screen_1_label_2.set_size(100, 32)
# Set style for screen_1_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_2.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_1_btn_2
screen_1_btn_2 = lv.btn(screen_1_tabview_1_tab_1)
screen_1_btn_2.add_flag(lv.obj.FLAG.CHECKABLE)
screen_1_btn_2_label = lv.label(screen_1_btn_2)
screen_1_btn_2_label.set_text("按键1")
screen_1_btn_2_label.set_long_mode(lv.label.LONG.CLIP)
screen_1_btn_2_label.set_width(lv.pct(100))
screen_1_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
screen_1_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_1_btn_2.set_pos(373, 3)
screen_1_btn_2.set_size(300, 150)
# Set style for screen_1_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_btn_2.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_2.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_2.set_style_radius(20, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_2.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_1_btn_4
screen_1_btn_4 = lv.btn(screen_1_tabview_1_tab_1)
screen_1_btn_4.add_flag(lv.obj.FLAG.CHECKABLE)
screen_1_btn_4_label = lv.label(screen_1_btn_4)
screen_1_btn_4_label.set_text("按键1")
screen_1_btn_4_label.set_long_mode(lv.label.LONG.CLIP)
screen_1_btn_4_label.set_width(lv.pct(100))
screen_1_btn_4_label.align(lv.ALIGN.CENTER, 0, 0)
screen_1_btn_4.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_1_btn_4.set_pos(376, 211)
screen_1_btn_4.set_size(300, 150)
# Set style for screen_1_btn_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_btn_4.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_4.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_4.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_4.set_style_radius(20, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_4.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_1_btn_3
screen_1_btn_3 = lv.btn(screen_1_tabview_1_tab_1)
screen_1_btn_3.add_flag(lv.obj.FLAG.CHECKABLE)
screen_1_btn_3_label = lv.label(screen_1_btn_3)
screen_1_btn_3_label.set_text("按键1")
screen_1_btn_3_label.set_long_mode(lv.label.LONG.CLIP)
screen_1_btn_3_label.set_width(lv.pct(100))
screen_1_btn_3_label.align(lv.ALIGN.CENTER, 0, 0)
screen_1_btn_3.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_1_btn_3.set_pos(13, 212)
screen_1_btn_3.set_size(300, 150)
# Set style for screen_1_btn_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_btn_3.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_3.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_3.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_3.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_1_btn_6
screen_1_btn_6 = lv.btn(screen_1_tabview_1_tab_1)
screen_1_btn_6.add_flag(lv.obj.FLAG.CHECKABLE)
screen_1_btn_6_label = lv.label(screen_1_btn_6)
screen_1_btn_6_label.set_text("按键1")
screen_1_btn_6_label.set_long_mode(lv.label.LONG.CLIP)
screen_1_btn_6_label.set_width(lv.pct(100))
screen_1_btn_6_label.align(lv.ALIGN.CENTER, 0, 0)
screen_1_btn_6.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_1_btn_6.set_pos(14, 602)
screen_1_btn_6.set_size(300, 150)
# Set style for screen_1_btn_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_btn_6.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_6.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_6.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_6.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_6.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_6.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_6.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_1_btn_5
screen_1_btn_5 = lv.btn(screen_1_tabview_1_tab_1)
screen_1_btn_5.add_flag(lv.obj.FLAG.CHECKABLE)
screen_1_btn_5_label = lv.label(screen_1_btn_5)
screen_1_btn_5_label.set_text("按键1")
screen_1_btn_5_label.set_long_mode(lv.label.LONG.CLIP)
screen_1_btn_5_label.set_width(lv.pct(100))
screen_1_btn_5_label.align(lv.ALIGN.CENTER, 0, 0)
screen_1_btn_5.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_1_btn_5.set_pos(14, 407)
screen_1_btn_5.set_size(300, 150)
# Set style for screen_1_btn_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_btn_5.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_5.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_5.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_5.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_5.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_5.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_1_btn_8
screen_1_btn_8 = lv.btn(screen_1_tabview_1_tab_1)
screen_1_btn_8.add_flag(lv.obj.FLAG.CHECKABLE)
screen_1_btn_8_label = lv.label(screen_1_btn_8)
screen_1_btn_8_label.set_text("按键1")
screen_1_btn_8_label.set_long_mode(lv.label.LONG.CLIP)
screen_1_btn_8_label.set_width(lv.pct(100))
screen_1_btn_8_label.align(lv.ALIGN.CENTER, 0, 0)
screen_1_btn_8.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_1_btn_8.set_pos(376, 599)
screen_1_btn_8.set_size(300, 150)
# Set style for screen_1_btn_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_btn_8.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_8.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_8.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_8.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_8.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_8.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_8.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_8.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_8.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_1_btn_7
screen_1_btn_7 = lv.btn(screen_1_tabview_1_tab_1)
screen_1_btn_7.add_flag(lv.obj.FLAG.CHECKABLE)
screen_1_btn_7_label = lv.label(screen_1_btn_7)
screen_1_btn_7_label.set_text("按键1")
screen_1_btn_7_label.set_long_mode(lv.label.LONG.CLIP)
screen_1_btn_7_label.set_width(lv.pct(100))
screen_1_btn_7_label.align(lv.ALIGN.CENTER, 0, 0)
screen_1_btn_7.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_1_btn_7.set_pos(376, 405)
screen_1_btn_7.set_size(300, 150)
# Set style for screen_1_btn_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_btn_7.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_7.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_7.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_7.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_7.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_7.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_7.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_1_btn_9
screen_1_btn_9 = lv.btn(screen_1_tabview_1_tab_1)
screen_1_btn_9.add_flag(lv.obj.FLAG.CHECKABLE)
screen_1_btn_9_label = lv.label(screen_1_btn_9)
screen_1_btn_9_label.set_text("按键1")
screen_1_btn_9_label.set_long_mode(lv.label.LONG.CLIP)
screen_1_btn_9_label.set_width(lv.pct(100))
screen_1_btn_9_label.align(lv.ALIGN.CENTER, 0, 0)
screen_1_btn_9.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_1_btn_9.set_pos(14, 797)
screen_1_btn_9.set_size(300, 150)
# Set style for screen_1_btn_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_btn_9.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_9.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_9.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_9.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_9.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_9.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_9.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_9.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_9.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_9.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_1_btn_10
screen_1_btn_10 = lv.btn(screen_1_tabview_1_tab_1)
screen_1_btn_10.add_flag(lv.obj.FLAG.CHECKABLE)
screen_1_btn_10_label = lv.label(screen_1_btn_10)
screen_1_btn_10_label.set_text("按键1")
screen_1_btn_10_label.set_long_mode(lv.label.LONG.CLIP)
screen_1_btn_10_label.set_width(lv.pct(100))
screen_1_btn_10_label.align(lv.ALIGN.CENTER, 0, 0)
screen_1_btn_10.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_1_btn_10.set_pos(376, 793)
screen_1_btn_10.set_size(300, 150)
# Set style for screen_1_btn_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_btn_10.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_10.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_10.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_10.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_10.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_10.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_10.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_10.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_10.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_10.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_1_label_1
screen_1_label_1 = lv.label(screen_1)
screen_1_label_1.set_text("设备管理")
screen_1_label_1.set_long_mode(lv.label.LONG.WRAP)
screen_1_label_1.set_width(lv.pct(100))
screen_1_label_1.set_pos(20, 20)
screen_1_label_1.set_size(150, 40)
# Set style for screen_1_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_1.update_layout()
# Create screen_2
screen_2 = lv.obj()
screen_2.set_size(720, 720)
screen_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_2_tabview_1
screen_2_tabview_1 = lv.tabview(screen_2, lv.DIR.TOP, 85)
screen_2_tabview_1.set_pos(-1, -1)
screen_2_tabview_1.set_size(720, 720)
screen_2_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for screen_2_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_2_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_2_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_2_tabview_1_extra_btnm_main_default = lv.style_t()
style_screen_2_tabview_1_extra_btnm_main_default.init()
style_screen_2_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_screen_2_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x201b1b))
style_screen_2_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_2_tabview_1_extra_btnm_main_default.set_border_width(0)
style_screen_2_tabview_1_extra_btnm_main_default.set_radius(0)
screen_2_tabview_1.get_tab_btns().add_style(style_screen_2_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_2_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_screen_2_tabview_1_extra_btnm_items_default = lv.style_t()
style_screen_2_tabview_1_extra_btnm_items_default.init()
style_screen_2_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_screen_2_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_screen_2_tabview_1_extra_btnm_items_default.set_text_opa(255)
screen_2_tabview_1.get_tab_btns().add_style(style_screen_2_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for screen_2_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_screen_2_tabview_1_extra_btnm_items_checked = lv.style_t()
style_screen_2_tabview_1_extra_btnm_items_checked.init()
style_screen_2_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0x2195f6))
style_screen_2_tabview_1_extra_btnm_items_checked.set_text_font(test_font("montserratMedium", 12))
style_screen_2_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_screen_2_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_screen_2_tabview_1_extra_btnm_items_checked.set_radius(0)
style_screen_2_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_screen_2_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x201b1b))
style_screen_2_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
screen_2_tabview_1.get_tab_btns().add_style(style_screen_2_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
screen_2_tabview_1_tab_1 = screen_2_tabview_1.add_tab("")
screen_2_tabview_1_tab_1_label = lv.label(screen_2_tabview_1_tab_1)
screen_2_tabview_1_tab_1_label.set_text("")

# Create screen_2_btn_10
screen_2_btn_10 = lv.btn(screen_2_tabview_1_tab_1)
screen_2_btn_10.add_flag(lv.obj.FLAG.CHECKABLE)
screen_2_btn_10_label = lv.label(screen_2_btn_10)
screen_2_btn_10_label.set_text("按键1")
screen_2_btn_10_label.set_long_mode(lv.label.LONG.CLIP)
screen_2_btn_10_label.set_width(lv.pct(100))
screen_2_btn_10_label.align(lv.ALIGN.CENTER, 0, 0)
screen_2_btn_10.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_2_btn_10.set_pos(14, 17)
screen_2_btn_10.set_size(300, 150)
# Set style for screen_2_btn_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_2_btn_10.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_10.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_10.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_10.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_10.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_10.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_10.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_10.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_10.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_10.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_2_btn_9
screen_2_btn_9 = lv.btn(screen_2_tabview_1_tab_1)
screen_2_btn_9.add_flag(lv.obj.FLAG.CHECKABLE)
screen_2_btn_9_label = lv.label(screen_2_btn_9)
screen_2_btn_9_label.set_text("按键1")
screen_2_btn_9_label.set_long_mode(lv.label.LONG.CLIP)
screen_2_btn_9_label.set_width(lv.pct(100))
screen_2_btn_9_label.align(lv.ALIGN.CENTER, 0, 0)
screen_2_btn_9.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_2_btn_9.set_pos(376, 17)
screen_2_btn_9.set_size(300, 150)
# Set style for screen_2_btn_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_2_btn_9.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_9.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_9.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_9.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_9.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_9.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_9.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_9.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_9.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_9.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_2_btn_8
screen_2_btn_8 = lv.btn(screen_2_tabview_1_tab_1)
screen_2_btn_8.add_flag(lv.obj.FLAG.CHECKABLE)
screen_2_btn_8_label = lv.label(screen_2_btn_8)
screen_2_btn_8_label.set_text("按键1")
screen_2_btn_8_label.set_long_mode(lv.label.LONG.CLIP)
screen_2_btn_8_label.set_width(lv.pct(100))
screen_2_btn_8_label.align(lv.ALIGN.CENTER, 0, 0)
screen_2_btn_8.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_2_btn_8.set_pos(376, 211)
screen_2_btn_8.set_size(300, 150)
# Set style for screen_2_btn_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_2_btn_8.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_8.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_8.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_8.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_8.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_8.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_8.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_8.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_8.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_2_btn_7
screen_2_btn_7 = lv.btn(screen_2_tabview_1_tab_1)
screen_2_btn_7.add_flag(lv.obj.FLAG.CHECKABLE)
screen_2_btn_7_label = lv.label(screen_2_btn_7)
screen_2_btn_7_label.set_text("按键1")
screen_2_btn_7_label.set_long_mode(lv.label.LONG.CLIP)
screen_2_btn_7_label.set_width(lv.pct(100))
screen_2_btn_7_label.align(lv.ALIGN.CENTER, 0, 0)
screen_2_btn_7.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_2_btn_7.set_pos(14, 212)
screen_2_btn_7.set_size(300, 150)
# Set style for screen_2_btn_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_2_btn_7.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_7.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_7.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_7.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_7.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_7.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_7.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_2_btn_6
screen_2_btn_6 = lv.btn(screen_2_tabview_1_tab_1)
screen_2_btn_6.add_flag(lv.obj.FLAG.CHECKABLE)
screen_2_btn_6_label = lv.label(screen_2_btn_6)
screen_2_btn_6_label.set_text("按键1")
screen_2_btn_6_label.set_long_mode(lv.label.LONG.CLIP)
screen_2_btn_6_label.set_width(lv.pct(100))
screen_2_btn_6_label.align(lv.ALIGN.CENTER, 0, 0)
screen_2_btn_6.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_2_btn_6.set_pos(14, 602)
screen_2_btn_6.set_size(300, 150)
# Set style for screen_2_btn_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_2_btn_6.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_6.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_6.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_6.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_6.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_6.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_6.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_2_btn_5
screen_2_btn_5 = lv.btn(screen_2_tabview_1_tab_1)
screen_2_btn_5.add_flag(lv.obj.FLAG.CHECKABLE)
screen_2_btn_5_label = lv.label(screen_2_btn_5)
screen_2_btn_5_label.set_text("按键1")
screen_2_btn_5_label.set_long_mode(lv.label.LONG.CLIP)
screen_2_btn_5_label.set_width(lv.pct(100))
screen_2_btn_5_label.align(lv.ALIGN.CENTER, 0, 0)
screen_2_btn_5.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_2_btn_5.set_pos(14, 407)
screen_2_btn_5.set_size(300, 150)
# Set style for screen_2_btn_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_2_btn_5.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_5.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_5.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_5.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_5.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_5.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_2_btn_4
screen_2_btn_4 = lv.btn(screen_2_tabview_1_tab_1)
screen_2_btn_4.add_flag(lv.obj.FLAG.CHECKABLE)
screen_2_btn_4_label = lv.label(screen_2_btn_4)
screen_2_btn_4_label.set_text("按键1")
screen_2_btn_4_label.set_long_mode(lv.label.LONG.CLIP)
screen_2_btn_4_label.set_width(lv.pct(100))
screen_2_btn_4_label.align(lv.ALIGN.CENTER, 0, 0)
screen_2_btn_4.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_2_btn_4.set_pos(376, 599)
screen_2_btn_4.set_size(300, 150)
# Set style for screen_2_btn_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_2_btn_4.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_4.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_4.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_4.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_4.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_2_btn_3
screen_2_btn_3 = lv.btn(screen_2_tabview_1_tab_1)
screen_2_btn_3.add_flag(lv.obj.FLAG.CHECKABLE)
screen_2_btn_3_label = lv.label(screen_2_btn_3)
screen_2_btn_3_label.set_text("按键1")
screen_2_btn_3_label.set_long_mode(lv.label.LONG.CLIP)
screen_2_btn_3_label.set_width(lv.pct(100))
screen_2_btn_3_label.align(lv.ALIGN.CENTER, 0, 0)
screen_2_btn_3.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_2_btn_3.set_pos(376, 405)
screen_2_btn_3.set_size(300, 150)
# Set style for screen_2_btn_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_2_btn_3.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_3.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_3.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_3.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_2_btn_2
screen_2_btn_2 = lv.btn(screen_2_tabview_1_tab_1)
screen_2_btn_2.add_flag(lv.obj.FLAG.CHECKABLE)
screen_2_btn_2_label = lv.label(screen_2_btn_2)
screen_2_btn_2_label.set_text("按键1")
screen_2_btn_2_label.set_long_mode(lv.label.LONG.CLIP)
screen_2_btn_2_label.set_width(lv.pct(100))
screen_2_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
screen_2_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_2_btn_2.set_pos(14, 797)
screen_2_btn_2.set_size(300, 150)
# Set style for screen_2_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_2_btn_2.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_2.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_2.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_2.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_2_btn_1
screen_2_btn_1 = lv.btn(screen_2_tabview_1_tab_1)
screen_2_btn_1.add_flag(lv.obj.FLAG.CHECKABLE)
screen_2_btn_1_label = lv.label(screen_2_btn_1)
screen_2_btn_1_label.set_text("按键1")
screen_2_btn_1_label.set_long_mode(lv.label.LONG.CLIP)
screen_2_btn_1_label.set_width(lv.pct(100))
screen_2_btn_1_label.align(lv.ALIGN.CENTER, 0, 0)
screen_2_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_2_btn_1.set_pos(376, 793)
screen_2_btn_1.set_size(300, 150)
# Set style for screen_2_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_2_btn_1.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_1.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_btn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_2_label_1
screen_2_label_1 = lv.label(screen_2)
screen_2_label_1.set_text("灯光情景")
screen_2_label_1.set_long_mode(lv.label.LONG.WRAP)
screen_2_label_1.set_width(lv.pct(100))
screen_2_label_1.set_pos(20, 20)
screen_2_label_1.set_size(150, 40)
# Set style for screen_2_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_2_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_label_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_2_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_2.update_layout()
# Create screen_3
screen_3 = lv.obj()
screen_3.set_size(720, 720)
screen_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_3_tabview_1
screen_3_tabview_1 = lv.tabview(screen_3, lv.DIR.TOP, 85)
screen_3_tabview_1.set_pos(-1, -1)
screen_3_tabview_1.set_size(720, 720)
screen_3_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for screen_3_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_3_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_3_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_3_tabview_1_extra_btnm_main_default = lv.style_t()
style_screen_3_tabview_1_extra_btnm_main_default.init()
style_screen_3_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_screen_3_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x201b1b))
style_screen_3_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_3_tabview_1_extra_btnm_main_default.set_border_width(0)
style_screen_3_tabview_1_extra_btnm_main_default.set_radius(0)
screen_3_tabview_1.get_tab_btns().add_style(style_screen_3_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_3_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_screen_3_tabview_1_extra_btnm_items_default = lv.style_t()
style_screen_3_tabview_1_extra_btnm_items_default.init()
style_screen_3_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_screen_3_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_screen_3_tabview_1_extra_btnm_items_default.set_text_opa(255)
screen_3_tabview_1.get_tab_btns().add_style(style_screen_3_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for screen_3_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_screen_3_tabview_1_extra_btnm_items_checked = lv.style_t()
style_screen_3_tabview_1_extra_btnm_items_checked.init()
style_screen_3_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0x2195f6))
style_screen_3_tabview_1_extra_btnm_items_checked.set_text_font(test_font("montserratMedium", 12))
style_screen_3_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_screen_3_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_screen_3_tabview_1_extra_btnm_items_checked.set_radius(0)
style_screen_3_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_screen_3_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x201b1b))
style_screen_3_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
screen_3_tabview_1.get_tab_btns().add_style(style_screen_3_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
screen_3_tabview_1_tab_1 = screen_3_tabview_1.add_tab("")
screen_3_tabview_1_tab_1_label = lv.label(screen_3_tabview_1_tab_1)
screen_3_tabview_1_tab_1_label.set_text("")

# Create screen_3_btn_10
screen_3_btn_10 = lv.btn(screen_3_tabview_1_tab_1)
screen_3_btn_10.add_flag(lv.obj.FLAG.CHECKABLE)
screen_3_btn_10_label = lv.label(screen_3_btn_10)
screen_3_btn_10_label.set_text("按键1")
screen_3_btn_10_label.set_long_mode(lv.label.LONG.CLIP)
screen_3_btn_10_label.set_width(lv.pct(100))
screen_3_btn_10_label.align(lv.ALIGN.CENTER, 0, 0)
screen_3_btn_10.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_3_btn_10.set_pos(14, 17)
screen_3_btn_10.set_size(300, 150)
# Set style for screen_3_btn_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_3_btn_10.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_10.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_10.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_10.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_10.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_10.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_10.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_10.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_10.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_10.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_3_btn_9
screen_3_btn_9 = lv.btn(screen_3_tabview_1_tab_1)
screen_3_btn_9.add_flag(lv.obj.FLAG.CHECKABLE)
screen_3_btn_9_label = lv.label(screen_3_btn_9)
screen_3_btn_9_label.set_text("按键1")
screen_3_btn_9_label.set_long_mode(lv.label.LONG.CLIP)
screen_3_btn_9_label.set_width(lv.pct(100))
screen_3_btn_9_label.align(lv.ALIGN.CENTER, 0, 0)
screen_3_btn_9.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_3_btn_9.set_pos(376, 17)
screen_3_btn_9.set_size(300, 150)
# Set style for screen_3_btn_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_3_btn_9.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_9.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_9.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_9.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_9.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_9.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_9.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_9.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_9.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_9.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_3_btn_8
screen_3_btn_8 = lv.btn(screen_3_tabview_1_tab_1)
screen_3_btn_8.add_flag(lv.obj.FLAG.CHECKABLE)
screen_3_btn_8_label = lv.label(screen_3_btn_8)
screen_3_btn_8_label.set_text("按键1")
screen_3_btn_8_label.set_long_mode(lv.label.LONG.CLIP)
screen_3_btn_8_label.set_width(lv.pct(100))
screen_3_btn_8_label.align(lv.ALIGN.CENTER, 0, 0)
screen_3_btn_8.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_3_btn_8.set_pos(376, 211)
screen_3_btn_8.set_size(300, 150)
# Set style for screen_3_btn_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_3_btn_8.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_8.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_8.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_8.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_8.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_8.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_8.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_8.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_8.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_3_btn_7
screen_3_btn_7 = lv.btn(screen_3_tabview_1_tab_1)
screen_3_btn_7.add_flag(lv.obj.FLAG.CHECKABLE)
screen_3_btn_7_label = lv.label(screen_3_btn_7)
screen_3_btn_7_label.set_text("按键1")
screen_3_btn_7_label.set_long_mode(lv.label.LONG.CLIP)
screen_3_btn_7_label.set_width(lv.pct(100))
screen_3_btn_7_label.align(lv.ALIGN.CENTER, 0, 0)
screen_3_btn_7.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_3_btn_7.set_pos(14, 212)
screen_3_btn_7.set_size(300, 150)
# Set style for screen_3_btn_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_3_btn_7.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_7.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_7.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_7.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_7.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_7.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_7.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_3_btn_6
screen_3_btn_6 = lv.btn(screen_3_tabview_1_tab_1)
screen_3_btn_6.add_flag(lv.obj.FLAG.CHECKABLE)
screen_3_btn_6_label = lv.label(screen_3_btn_6)
screen_3_btn_6_label.set_text("按键1")
screen_3_btn_6_label.set_long_mode(lv.label.LONG.CLIP)
screen_3_btn_6_label.set_width(lv.pct(100))
screen_3_btn_6_label.align(lv.ALIGN.CENTER, 0, 0)
screen_3_btn_6.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_3_btn_6.set_pos(14, 602)
screen_3_btn_6.set_size(300, 150)
# Set style for screen_3_btn_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_3_btn_6.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_6.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_6.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_6.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_6.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_6.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_6.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_3_btn_5
screen_3_btn_5 = lv.btn(screen_3_tabview_1_tab_1)
screen_3_btn_5.add_flag(lv.obj.FLAG.CHECKABLE)
screen_3_btn_5_label = lv.label(screen_3_btn_5)
screen_3_btn_5_label.set_text("按键1")
screen_3_btn_5_label.set_long_mode(lv.label.LONG.CLIP)
screen_3_btn_5_label.set_width(lv.pct(100))
screen_3_btn_5_label.align(lv.ALIGN.CENTER, 0, 0)
screen_3_btn_5.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_3_btn_5.set_pos(14, 407)
screen_3_btn_5.set_size(300, 150)
# Set style for screen_3_btn_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_3_btn_5.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_5.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_5.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_5.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_5.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_5.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_3_btn_4
screen_3_btn_4 = lv.btn(screen_3_tabview_1_tab_1)
screen_3_btn_4.add_flag(lv.obj.FLAG.CHECKABLE)
screen_3_btn_4_label = lv.label(screen_3_btn_4)
screen_3_btn_4_label.set_text("按键1")
screen_3_btn_4_label.set_long_mode(lv.label.LONG.CLIP)
screen_3_btn_4_label.set_width(lv.pct(100))
screen_3_btn_4_label.align(lv.ALIGN.CENTER, 0, 0)
screen_3_btn_4.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_3_btn_4.set_pos(376, 599)
screen_3_btn_4.set_size(300, 150)
# Set style for screen_3_btn_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_3_btn_4.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_4.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_4.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_4.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_4.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_3_btn_3
screen_3_btn_3 = lv.btn(screen_3_tabview_1_tab_1)
screen_3_btn_3.add_flag(lv.obj.FLAG.CHECKABLE)
screen_3_btn_3_label = lv.label(screen_3_btn_3)
screen_3_btn_3_label.set_text("按键1")
screen_3_btn_3_label.set_long_mode(lv.label.LONG.CLIP)
screen_3_btn_3_label.set_width(lv.pct(100))
screen_3_btn_3_label.align(lv.ALIGN.CENTER, 0, 0)
screen_3_btn_3.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_3_btn_3.set_pos(376, 405)
screen_3_btn_3.set_size(300, 150)
# Set style for screen_3_btn_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_3_btn_3.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_3.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_3.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_3.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_3_btn_2
screen_3_btn_2 = lv.btn(screen_3_tabview_1_tab_1)
screen_3_btn_2.add_flag(lv.obj.FLAG.CHECKABLE)
screen_3_btn_2_label = lv.label(screen_3_btn_2)
screen_3_btn_2_label.set_text("按键1")
screen_3_btn_2_label.set_long_mode(lv.label.LONG.CLIP)
screen_3_btn_2_label.set_width(lv.pct(100))
screen_3_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
screen_3_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_3_btn_2.set_pos(14, 797)
screen_3_btn_2.set_size(300, 150)
# Set style for screen_3_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_3_btn_2.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_2.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_2.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_2.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_3_btn_1
screen_3_btn_1 = lv.btn(screen_3_tabview_1_tab_1)
screen_3_btn_1.add_flag(lv.obj.FLAG.CHECKABLE)
screen_3_btn_1_label = lv.label(screen_3_btn_1)
screen_3_btn_1_label.set_text("按键1")
screen_3_btn_1_label.set_long_mode(lv.label.LONG.CLIP)
screen_3_btn_1_label.set_width(lv.pct(100))
screen_3_btn_1_label.align(lv.ALIGN.CENTER, 0, 0)
screen_3_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_3_btn_1.set_pos(376, 793)
screen_3_btn_1.set_size(300, 150)
# Set style for screen_3_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_3_btn_1.set_style_bg_opa(162, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_1.set_style_bg_color(lv.color_hex(0x3a5789), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_btn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_3_label_1
screen_3_label_1 = lv.label(screen_3)
screen_3_label_1.set_text("窗帘情景")
screen_3_label_1.set_long_mode(lv.label.LONG.WRAP)
screen_3_label_1.set_width(lv.pct(100))
screen_3_label_1.set_pos(20, 19)
screen_3_label_1.set_size(150, 40)
# Set style for screen_3_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_3_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_label_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_3_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_3.update_layout()
# Create screen_4
screen_4 = lv.obj()
screen_4.set_size(720, 720)
screen_4.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_4.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_4_tabview_1
screen_4_tabview_1 = lv.tabview(screen_4, lv.DIR.TOP, 70)
screen_4_tabview_1.set_pos(0, 0)
screen_4_tabview_1.set_size(720, 720)
screen_4_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for screen_4_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_4_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_4_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_4_tabview_1_extra_btnm_main_default = lv.style_t()
style_screen_4_tabview_1_extra_btnm_main_default.init()
style_screen_4_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_screen_4_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x4f3f3f))
style_screen_4_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_4_tabview_1_extra_btnm_main_default.set_border_width(0)
style_screen_4_tabview_1_extra_btnm_main_default.set_radius(0)
screen_4_tabview_1.get_tab_btns().add_style(style_screen_4_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_4_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_screen_4_tabview_1_extra_btnm_items_default = lv.style_t()
style_screen_4_tabview_1_extra_btnm_items_default.init()
style_screen_4_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_screen_4_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_screen_4_tabview_1_extra_btnm_items_default.set_text_opa(255)
screen_4_tabview_1.get_tab_btns().add_style(style_screen_4_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for screen_4_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_screen_4_tabview_1_extra_btnm_items_checked = lv.style_t()
style_screen_4_tabview_1_extra_btnm_items_checked.init()
style_screen_4_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_screen_4_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_screen_4_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_screen_4_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_screen_4_tabview_1_extra_btnm_items_checked.set_radius(0)
style_screen_4_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_screen_4_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0c0b0d))
style_screen_4_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
screen_4_tabview_1.get_tab_btns().add_style(style_screen_4_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
screen_4_tabview_1_tab_1 = screen_4_tabview_1.add_tab("")
screen_4_tabview_1_tab_1_label = lv.label(screen_4_tabview_1_tab_1)
screen_4_tabview_1_tab_1_label.set_text("")

# Create screen_4_list_1
screen_4_list_1 = lv.list(screen_4)
screen_4_list_1_item0 = screen_4_list_1.add_btn(lv.SYMBOL.WIFI, "网络设置")
screen_4_list_1_item1 = screen_4_list_1.add_btn(lv.SYMBOL.LOOP, "显示设置")
screen_4_list_1_item2 = screen_4_list_1.add_btn(lv.SYMBOL.SAVE, "开关配置")
screen_4_list_1_item3 = screen_4_list_1.add_btn(lv.SYMBOL.SAVE, "传感器配置")
screen_4_list_1_item4 = screen_4_list_1.add_btn(lv.SYMBOL.SAVE, "设备重启")
screen_4_list_1_item5 = screen_4_list_1.add_btn(lv.SYMBOL.SAVE, "恢复出厂")
screen_4_list_1_item6 = screen_4_list_1.add_btn(lv.SYMBOL.SAVE, "关于产品")
screen_4_list_1.set_pos(0, 71)
screen_4_list_1.set_size(720, 650)
screen_4_list_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for screen_4_list_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_4_list_1.set_style_pad_top(20, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1.set_style_pad_left(, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1.set_style_pad_right(, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1.set_style_pad_bottom(, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_4_list_1, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
screen_4_list_1.set_style_radius(3, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_4_list_1.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_4_list_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_4_list_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
# Set style for screen_4_list_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_4_list_1_extra_btns_main_default = lv.style_t()
style_screen_4_list_1_extra_btns_main_default.init()
style_screen_4_list_1_extra_btns_main_default.set_pad_top(20)
style_screen_4_list_1_extra_btns_main_default.set_pad_left(30)
style_screen_4_list_1_extra_btns_main_default.set_pad_right(10)
style_screen_4_list_1_extra_btns_main_default.set_pad_bottom(20)
style_screen_4_list_1_extra_btns_main_default.set_border_width(2)
style_screen_4_list_1_extra_btns_main_default.set_border_opa(255)
style_screen_4_list_1_extra_btns_main_default.set_border_color(lv.color_hex(0x151313))
style_screen_4_list_1_extra_btns_main_default.set_border_side(lv.BORDER_SIDE.BOTTOM)
style_screen_4_list_1_extra_btns_main_default.set_text_color(lv.color_hex(0xffffff))
style_screen_4_list_1_extra_btns_main_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30))
style_screen_4_list_1_extra_btns_main_default.set_text_opa(255)
style_screen_4_list_1_extra_btns_main_default.set_radius(0)
style_screen_4_list_1_extra_btns_main_default.set_bg_opa(255)
style_screen_4_list_1_extra_btns_main_default.set_bg_color(lv.color_hex(0x000000))
style_screen_4_list_1_extra_btns_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
screen_4_list_1_item6.add_style(style_screen_4_list_1_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1_item5.add_style(style_screen_4_list_1_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1_item4.add_style(style_screen_4_list_1_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1_item3.add_style(style_screen_4_list_1_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1_item2.add_style(style_screen_4_list_1_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1_item1.add_style(style_screen_4_list_1_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_list_1_item0.add_style(style_screen_4_list_1_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_4_list_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_4_list_1_extra_texts_main_default = lv.style_t()
style_screen_4_list_1_extra_texts_main_default.init()
style_screen_4_list_1_extra_texts_main_default.set_pad_top(0)
style_screen_4_list_1_extra_texts_main_default.set_pad_left(30)
style_screen_4_list_1_extra_texts_main_default.set_pad_right(0)
style_screen_4_list_1_extra_texts_main_default.set_pad_bottom(5)
style_screen_4_list_1_extra_texts_main_default.set_border_width(5)
style_screen_4_list_1_extra_texts_main_default.set_border_opa(255)
style_screen_4_list_1_extra_texts_main_default.set_border_color(lv.color_hex(0xfafafa))
style_screen_4_list_1_extra_texts_main_default.set_border_side(lv.BORDER_SIDE.FULL)
style_screen_4_list_1_extra_texts_main_default.set_text_color(lv.color_hex(0xffffff))
style_screen_4_list_1_extra_texts_main_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30))
style_screen_4_list_1_extra_texts_main_default.set_text_opa(255)
style_screen_4_list_1_extra_texts_main_default.set_radius(5)
style_screen_4_list_1_extra_texts_main_default.set_transform_width(0)
style_screen_4_list_1_extra_texts_main_default.set_bg_opa(0)

# Create screen_4_btn_1
screen_4_btn_1 = lv.btn(screen_4)
screen_4_btn_1_label = lv.label(screen_4_btn_1)
screen_4_btn_1_label.set_text("返回")
screen_4_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
screen_4_btn_1_label.set_width(lv.pct(100))
screen_4_btn_1_label.align(lv.ALIGN.CENTER, 0, 0)
screen_4_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_4_btn_1.set_pos(49, 11)
screen_4_btn_1.set_size(100, 50)
# Set style for screen_4_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_4_btn_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_btn_1.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_btn_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_btn_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_4_btn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_4.update_layout()
# Create screen_5
screen_5 = lv.obj()
screen_5.set_size(720, 720)
screen_5.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_5.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_5_tabview_1
screen_5_tabview_1 = lv.tabview(screen_5, lv.DIR.TOP, 70)
screen_5_tabview_1.set_pos(0, 0)
screen_5_tabview_1.set_size(720, 720)
screen_5_tabview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
# Set style for screen_5_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_5_tabview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_tabview_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_tabview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_tabview_1.set_style_text_color(lv.color_hex(0x4d4d4d), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_tabview_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_tabview_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_tabview_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_tabview_1.set_style_text_line_space(16, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_tabview_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_tabview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_tabview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_5_tabview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_5_tabview_1_extra_btnm_main_default = lv.style_t()
style_screen_5_tabview_1_extra_btnm_main_default.init()
style_screen_5_tabview_1_extra_btnm_main_default.set_bg_opa(255)
style_screen_5_tabview_1_extra_btnm_main_default.set_bg_color(lv.color_hex(0x4f3f3f))
style_screen_5_tabview_1_extra_btnm_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_5_tabview_1_extra_btnm_main_default.set_border_width(0)
style_screen_5_tabview_1_extra_btnm_main_default.set_radius(0)
screen_5_tabview_1.get_tab_btns().add_style(style_screen_5_tabview_1_extra_btnm_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_5_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_screen_5_tabview_1_extra_btnm_items_default = lv.style_t()
style_screen_5_tabview_1_extra_btnm_items_default.init()
style_screen_5_tabview_1_extra_btnm_items_default.set_text_color(lv.color_hex(0x4d4d4d))
style_screen_5_tabview_1_extra_btnm_items_default.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 12))
style_screen_5_tabview_1_extra_btnm_items_default.set_text_opa(255)
screen_5_tabview_1.get_tab_btns().add_style(style_screen_5_tabview_1_extra_btnm_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for screen_5_tabview_1, Part: lv.PART.ITEMS, State: lv.STATE.CHECKED.
style_screen_5_tabview_1_extra_btnm_items_checked = lv.style_t()
style_screen_5_tabview_1_extra_btnm_items_checked.init()
style_screen_5_tabview_1_extra_btnm_items_checked.set_text_color(lv.color_hex(0xffffff))
style_screen_5_tabview_1_extra_btnm_items_checked.set_text_font(test_font("ZiTiQuanWeiJunHeiW22", 20))
style_screen_5_tabview_1_extra_btnm_items_checked.set_text_opa(255)
style_screen_5_tabview_1_extra_btnm_items_checked.set_border_width(0)
style_screen_5_tabview_1_extra_btnm_items_checked.set_radius(0)
style_screen_5_tabview_1_extra_btnm_items_checked.set_bg_opa(255)
style_screen_5_tabview_1_extra_btnm_items_checked.set_bg_color(lv.color_hex(0x0f0f12))
style_screen_5_tabview_1_extra_btnm_items_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
screen_5_tabview_1.get_tab_btns().add_style(style_screen_5_tabview_1_extra_btnm_items_checked, lv.PART.ITEMS|lv.STATE.CHECKED)
# Create
screen_5_tabview_1_tab_1 = screen_5_tabview_1.add_tab("")
screen_5_tabview_1_tab_1_label = lv.label(screen_5_tabview_1_tab_1)
screen_5_tabview_1_tab_1_label.set_text("")

# Create screen_5_cont_1
screen_5_cont_1 = lv.obj(screen_5)
screen_5_cont_1.set_pos(0, 75)
screen_5_cont_1.set_size(720, 645)
screen_5_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_5_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_5_cont_1.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_cont_1.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_cont_1.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_cont_1.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_cont_1.set_style_bg_opa(133, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_cont_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_5_label_2
screen_5_label_2 = lv.label(screen_5)
screen_5_label_2.set_text("色 温 | 4850K")
screen_5_label_2.set_long_mode(lv.label.LONG.WRAP)
screen_5_label_2.set_width(lv.pct(100))
screen_5_label_2.set_pos(259, 554)
screen_5_label_2.set_size(211, 34)
# Set style for screen_5_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_5_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_2.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_5_slider_2
screen_5_slider_2 = lv.slider(screen_5)
screen_5_slider_2.set_range(2700, 6500)
screen_5_slider_2.set_mode(lv.slider.MODE.SYMMETRICAL)
screen_5_slider_2.set_value(4600, lv.ANIM.OFF)
screen_5_slider_2.set_pos(-223, 616)
screen_5_slider_2.set_size(600, 70)
# Set style for screen_5_slider_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_5_slider_2.set_style_bg_opa(40, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_slider_2.set_style_bg_color(lv.color_hex(0x495661), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_slider_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_slider_2.set_style_radius(60, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_slider_2.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_slider_2.set_style_bg_img_src("B:MicroPython/_ct_bar_600x70.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_slider_2.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_slider_2.set_style_bg_img_recolor_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_slider_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_5_slider_2, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
screen_5_slider_2.set_style_bg_opa(0, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_5_slider_2.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for screen_5_slider_2, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
screen_5_slider_2.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
screen_5_slider_2.set_style_bg_color(lv.color_hex(0x300208), lv.PART.KNOB|lv.STATE.DEFAULT)
screen_5_slider_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
screen_5_slider_2.set_style_radius(60, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create screen_5_slider_1
screen_5_slider_1 = lv.slider(screen_5)
screen_5_slider_1.set_range(0, 100)
screen_5_slider_1.set_mode(lv.slider.MODE.SYMMETRICAL)
screen_5_slider_1.set_value(50, lv.ANIM.OFF)
screen_5_slider_1.set_pos(-223, 452)
screen_5_slider_1.set_size(600, 70)
# Set style for screen_5_slider_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_5_slider_1.set_style_bg_opa(60, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_slider_1.set_style_bg_color(lv.color_hex(0xdedfdf), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_slider_1.set_style_radius(60, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_slider_1.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_slider_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_5_slider_1, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
screen_5_slider_1.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_5_slider_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_5_slider_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_5_slider_1.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for screen_5_slider_1, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
screen_5_slider_1.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DEFAULT)
screen_5_slider_1.set_style_radius(60, lv.PART.KNOB|lv.STATE.DEFAULT)

# Set style for screen_5_slider_1, Part: lv.PART.KNOB, State: lv.STATE.DISABLED.
screen_5_slider_1.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DISABLED)
screen_5_slider_1.set_style_radius(50, lv.PART.KNOB|lv.STATE.DISABLED)

# Create screen_5_label_1
screen_5_label_1 = lv.label(screen_5)
screen_5_label_1.set_text("亮 度 | 50%")
screen_5_label_1.set_long_mode(lv.label.LONG.WRAP)
screen_5_label_1.set_width(lv.pct(100))
screen_5_label_1.set_pos(239, 394)
screen_5_label_1.set_size(227, 39)
# Set style for screen_5_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_5_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_5_dev_shell_img
screen_5_dev_shell_img = lv.img(screen_5)
screen_5_dev_shell_img.set_src("B:MicroPython/_dev_shell_alpha_100x100.bin")
screen_5_dev_shell_img.add_flag(lv.obj.FLAG.CLICKABLE)
screen_5_dev_shell_img.set_pivot(50,50)
screen_5_dev_shell_img.set_angle(0)
screen_5_dev_shell_img.set_pos(269, 101)
screen_5_dev_shell_img.set_size(100, 100)
# Set style for screen_5_dev_shell_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_5_dev_shell_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_dev_shell_img.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_dev_shell_img.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_5_dev_white_lid
screen_5_dev_white_lid = lv.img(screen_5)
screen_5_dev_white_lid.set_src("B:MicroPython/_dev_white_lid_alpha_174x27.bin")
screen_5_dev_white_lid.add_flag(lv.obj.FLAG.CLICKABLE)
screen_5_dev_white_lid.set_pivot(50,50)
screen_5_dev_white_lid.set_angle(0)
screen_5_dev_white_lid.set_pos(232, 181)
screen_5_dev_white_lid.set_size(174, 27)
# Set style for screen_5_dev_white_lid, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_5_dev_white_lid.set_style_img_recolor_opa(176, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_dev_white_lid.set_style_img_recolor(lv.color_hex(0x0a0a0a), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_dev_white_lid.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_dev_white_lid.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_dev_white_lid.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_5_dev_orange_img
screen_5_dev_orange_img = lv.img(screen_5)
screen_5_dev_orange_img.set_src(load_image(r"D:\7.NXP-GUI-PROJECT\4_inch_screen\generated\MicroPython\dev_orange_280_80.png"))
screen_5_dev_orange_img.add_flag(lv.obj.FLAG.CLICKABLE)
screen_5_dev_orange_img.set_pivot(50,50)
screen_5_dev_orange_img.set_angle(10)
screen_5_dev_orange_img.set_pos(180, 185)
screen_5_dev_orange_img.set_size(280, 80)
# Set style for screen_5_dev_orange_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_5_dev_orange_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_dev_orange_img.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_dev_orange_img.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_5_dev_white_img
screen_5_dev_white_img = lv.img(screen_5)
screen_5_dev_white_img.set_src(load_image(r"D:\7.NXP-GUI-PROJECT\4_inch_screen\generated\MicroPython\dev_white_280_80.png"))
screen_5_dev_white_img.add_flag(lv.obj.FLAG.CLICKABLE)
screen_5_dev_white_img.set_pivot(50,50)
screen_5_dev_white_img.set_angle(10)
screen_5_dev_white_img.set_pos(180, 185)
screen_5_dev_white_img.set_size(280, 80)
# Set style for screen_5_dev_white_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_5_dev_white_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_dev_white_img.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_dev_white_img.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_5_imgbtn_1
screen_5_imgbtn_1 = lv.imgbtn(screen_5)
screen_5_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
screen_5_imgbtn_1.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_scene_btn_alpha_48x48.bin", None)
screen_5_imgbtn_1.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_scene_btn_close_alpha_48x48.bin", None)
screen_5_imgbtn_1.add_flag(lv.obj.FLAG.CHECKABLE)
screen_5_imgbtn_1_label = lv.label(screen_5_imgbtn_1)
screen_5_imgbtn_1_label.set_text("")
screen_5_imgbtn_1_label.set_long_mode(lv.label.LONG.WRAP)
screen_5_imgbtn_1_label.set_width(lv.pct(100))
screen_5_imgbtn_1_label.align(lv.ALIGN.CENTER, 0, 0)
screen_5_imgbtn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_5_imgbtn_1.set_pos(652, 100)
screen_5_imgbtn_1.set_size(48, 48)
# Set style for screen_5_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_5_imgbtn_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_imgbtn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_imgbtn_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_imgbtn_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_5_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
screen_5_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
screen_5_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
screen_5_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
screen_5_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
screen_5_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for screen_5_imgbtn_1, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
screen_5_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
screen_5_imgbtn_1.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
screen_5_imgbtn_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
screen_5_imgbtn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
screen_5_imgbtn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for screen_5_imgbtn_1, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
screen_5_imgbtn_1.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

# Create screen_5_btn_1
screen_5_btn_1 = lv.btn(screen_5)
screen_5_btn_1_label = lv.label(screen_5_btn_1)
screen_5_btn_1_label.set_text("<  色温灯")
screen_5_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
screen_5_btn_1_label.set_width(lv.pct(100))
screen_5_btn_1_label.align(lv.ALIGN.CENTER, 0, 0)
screen_5_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_5_btn_1.set_pos(11, 7)
screen_5_btn_1.set_size(156, 50)
# Set style for screen_5_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_5_btn_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_btn_1.set_style_text_font(test_font("ZiTiQuanWeiJunHeiW22", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_btn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_5_Light_CT_on_off_2_img
screen_5_Light_CT_on_off_2_img = lv.imgbtn(screen_5)
screen_5_Light_CT_on_off_2_img.add_flag(lv.obj.FLAG.CHECKABLE)
screen_5_Light_CT_on_off_2_img.set_src(lv.imgbtn.STATE.RELEASED, None, "B:MicroPython/_onoff_off_alpha_48x48.bin", None)
screen_5_Light_CT_on_off_2_img.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, "B:MicroPython/_onoff_on_alpha_48x48.bin", None)
screen_5_Light_CT_on_off_2_img.add_flag(lv.obj.FLAG.CHECKABLE)
screen_5_Light_CT_on_off_2_img_label = lv.label(screen_5_Light_CT_on_off_2_img)
screen_5_Light_CT_on_off_2_img_label.set_text("")
screen_5_Light_CT_on_off_2_img_label.set_long_mode(lv.label.LONG.WRAP)
screen_5_Light_CT_on_off_2_img_label.set_width(lv.pct(100))
screen_5_Light_CT_on_off_2_img_label.align(lv.ALIGN.CENTER, 0, 0)
screen_5_Light_CT_on_off_2_img.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_5_Light_CT_on_off_2_img.set_pos(20, 101)
screen_5_Light_CT_on_off_2_img.set_size(48, 48)
# Set style for screen_5_Light_CT_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_5_Light_CT_on_off_2_img.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_Light_CT_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_Light_CT_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_Light_CT_on_off_2_img.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_Light_CT_on_off_2_img.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_Light_CT_on_off_2_img.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_5_Light_CT_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_5_Light_CT_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
screen_5_Light_CT_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
screen_5_Light_CT_on_off_2_img.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
screen_5_Light_CT_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
screen_5_Light_CT_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
screen_5_Light_CT_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for screen_5_Light_CT_on_off_2_img, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
screen_5_Light_CT_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
screen_5_Light_CT_on_off_2_img.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
screen_5_Light_CT_on_off_2_img.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
screen_5_Light_CT_on_off_2_img.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
screen_5_Light_CT_on_off_2_img.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for screen_5_Light_CT_on_off_2_img, Part: lv.PART.MAIN, State: LV_IMGBTN_STATE_RELEASED.
screen_5_Light_CT_on_off_2_img.set_style_img_opa(255, lv.PART.MAIN|lv.imgbtn.STATE.RELEASED)

screen_5.update_layout()
# Create screen_6
screen_6 = lv.obj()
screen_6.set_size(720, 720)
screen_6.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_6.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_6_btn_1
screen_6_btn_1 = lv.btn(screen_6)
screen_6_btn_1_label = lv.label(screen_6_btn_1)
screen_6_btn_1_label.set_text("Button")
screen_6_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
screen_6_btn_1_label.set_width(lv.pct(100))
screen_6_btn_1_label.align(lv.ALIGN.CENTER, 0, 0)
screen_6_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_6_btn_1.set_pos(54, 490)
screen_6_btn_1.set_size(100, 50)
# Set style for screen_6_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_6_btn_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_1.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_6_btn_2
screen_6_btn_2 = lv.btn(screen_6)
screen_6_btn_2_label = lv.label(screen_6_btn_2)
screen_6_btn_2_label.set_text("Button")
screen_6_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
screen_6_btn_2_label.set_width(lv.pct(100))
screen_6_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
screen_6_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_6_btn_2.set_pos(224, 490)
screen_6_btn_2.set_size(100, 50)
# Set style for screen_6_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_6_btn_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_2.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_2.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_6_btn_3
screen_6_btn_3 = lv.btn(screen_6)
screen_6_btn_3_label = lv.label(screen_6_btn_3)
screen_6_btn_3_label.set_text("Button")
screen_6_btn_3_label.set_long_mode(lv.label.LONG.WRAP)
screen_6_btn_3_label.set_width(lv.pct(100))
screen_6_btn_3_label.align(lv.ALIGN.CENTER, 0, 0)
screen_6_btn_3.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_6_btn_3.set_pos(457, 490)
screen_6_btn_3.set_size(100, 50)
# Set style for screen_6_btn_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_6_btn_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_3.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_3.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_6_btn_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_6.update_layout()

def screen_event_handler(e):
    code = e.get_code()
    indev = lv.indev_get_act()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.LEFT == gestureDir):
        if indev is not None: indev.wait_release()
        pass
        lv.scr_load_anim(screen_1, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
    if (code == lv.EVENT.PRESSING):
        pass
        

screen.add_event_cb(lambda e: screen_event_handler(e), lv.EVENT.ALL, None)

def screen_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(screen_4, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
screen_btn_1.add_event_cb(lambda e: screen_btn_1_event_handler(e), lv.EVENT.ALL, None)

def screen_1_event_handler(e):
    code = e.get_code()
    indev = lv.indev_get_act()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.LEFT == gestureDir):
        if indev is not None: indev.wait_release()
        pass
        lv.scr_load_anim(screen_2, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
    indev = lv.indev_get_act()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.RIGHT == gestureDir):
        if indev is not None: indev.wait_release()
        pass
        lv.scr_load_anim(screen, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        

screen_1.add_event_cb(lambda e: screen_1_event_handler(e), lv.EVENT.ALL, None)

def screen_1_cont_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(screen_5, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
screen_1_cont_1.add_event_cb(lambda e: screen_1_cont_1_event_handler(e), lv.EVENT.ALL, None)

def screen_1_Light_CT_on_off_1_img_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

screen_1_Light_CT_on_off_1_img.add_event_cb(lambda e: screen_1_Light_CT_on_off_1_img_event_handler(e), lv.EVENT.ALL, None)

def screen_1_small_dev_off_img_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(screen_5, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
screen_1_small_dev_off_img.add_event_cb(lambda e: screen_1_small_dev_off_img_event_handler(e), lv.EVENT.ALL, None)

def screen_1_label_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(screen_5, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
screen_1_label_2.add_event_cb(lambda e: screen_1_label_2_event_handler(e), lv.EVENT.ALL, None)

def screen_2_event_handler(e):
    code = e.get_code()
    indev = lv.indev_get_act()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.LEFT == gestureDir):
        if indev is not None: indev.wait_release()
        pass
        lv.scr_load_anim(screen_3, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
    indev = lv.indev_get_act()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.RIGHT == gestureDir):
        if indev is not None: indev.wait_release()
        pass
        lv.scr_load_anim(screen_1, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
screen_2.add_event_cb(lambda e: screen_2_event_handler(e), lv.EVENT.ALL, None)

def screen_3_event_handler(e):
    code = e.get_code()
    indev = lv.indev_get_act()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.RIGHT == gestureDir):
        if indev is not None: indev.wait_release()
        pass
        lv.scr_load_anim(screen_2, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
screen_3.add_event_cb(lambda e: screen_3_event_handler(e), lv.EVENT.ALL, None)

def screen_4_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(screen, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
screen_4_btn_1.add_event_cb(lambda e: screen_4_btn_1_event_handler(e), lv.EVENT.ALL, None)

def screen_5_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        #Write animation: screen_5_label_2 x
        screen_5_label_2_anim_x = lv.anim_t()
        screen_5_label_2_anim_x.init()
        screen_5_label_2_anim_x.set_var(screen_5_label_2)
        screen_5_label_2_anim_x.set_time(600)
        screen_5_label_2_anim_x.set_delay(0)
        screen_5_label_2_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(screen_5_label_2,val))
        screen_5_label_2_anim_x.set_values(screen_5_label_2.get_x(), 70)
        screen_5_label_2_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        screen_5_label_2_anim_x.set_repeat_count(0)
        screen_5_label_2_anim_x.set_repeat_delay(0)
        screen_5_label_2_anim_x.set_playback_time(0)
        screen_5_label_2_anim_x.set_playback_delay(0)
        screen_5_label_2_anim_x.start()
        #Write animation: screen_5_slider_1 x
        screen_5_slider_1_anim_x = lv.anim_t()
        screen_5_slider_1_anim_x.init()
        screen_5_slider_1_anim_x.set_var(screen_5_slider_1)
        screen_5_slider_1_anim_x.set_time(600)
        screen_5_slider_1_anim_x.set_delay(0)
        screen_5_slider_1_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(screen_5_slider_1,val))
        screen_5_slider_1_anim_x.set_values(screen_5_slider_1.get_x(), 70)
        screen_5_slider_1_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        screen_5_slider_1_anim_x.set_repeat_count(0)
        screen_5_slider_1_anim_x.set_repeat_delay(0)
        screen_5_slider_1_anim_x.set_playback_time(0)
        screen_5_slider_1_anim_x.set_playback_delay(0)
        screen_5_slider_1_anim_x.start()
        #Write animation: screen_5_slider_2 x
        screen_5_slider_2_anim_x = lv.anim_t()
        screen_5_slider_2_anim_x.init()
        screen_5_slider_2_anim_x.set_var(screen_5_slider_2)
        screen_5_slider_2_anim_x.set_time(600)
        screen_5_slider_2_anim_x.set_delay(0)
        screen_5_slider_2_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(screen_5_slider_2,val))
        screen_5_slider_2_anim_x.set_values(screen_5_slider_2.get_x(), 70)
        screen_5_slider_2_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        screen_5_slider_2_anim_x.set_repeat_count(0)
        screen_5_slider_2_anim_x.set_repeat_delay(0)
        screen_5_slider_2_anim_x.set_playback_time(0)
        screen_5_slider_2_anim_x.set_playback_delay(0)
        screen_5_slider_2_anim_x.start()
        #Write animation: screen_5_label_1 x
        screen_5_label_1_anim_x = lv.anim_t()
        screen_5_label_1_anim_x.init()
        screen_5_label_1_anim_x.set_var(screen_5_label_1)
        screen_5_label_1_anim_x.set_time(600)
        screen_5_label_1_anim_x.set_delay(0)
        screen_5_label_1_anim_x.set_custom_exec_cb(lambda e,val: anim_x_cb(screen_5_label_1,val))
        screen_5_label_1_anim_x.set_values(screen_5_label_1.get_x(), 70)
        screen_5_label_1_anim_x.set_path_cb(lv.anim_t.path_overshoot)
        screen_5_label_1_anim_x.set_repeat_count(0)
        screen_5_label_1_anim_x.set_repeat_delay(0)
        screen_5_label_1_anim_x.set_playback_time(0)
        screen_5_label_1_anim_x.set_playback_delay(0)
        screen_5_label_1_anim_x.start()
        

screen_5.add_event_cb(lambda e: screen_5_event_handler(e), lv.EVENT.ALL, None)

def screen_5_slider_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

screen_5_slider_2.add_event_cb(lambda e: screen_5_slider_2_event_handler(e), lv.EVENT.ALL, None)

def screen_5_slider_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

screen_5_slider_1.add_event_cb(lambda e: screen_5_slider_1_event_handler(e), lv.EVENT.ALL, None)

def screen_5_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(screen_1, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
screen_5_btn_1.add_event_cb(lambda e: screen_5_btn_1_event_handler(e), lv.EVENT.ALL, None)

def screen_5_Light_CT_on_off_2_img_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

screen_5_Light_CT_on_off_2_img.add_event_cb(lambda e: screen_5_Light_CT_on_off_2_img_event_handler(e), lv.EVENT.ALL, None)

# content from custom.py

# Load the default screen
lv.scr_load(screen)

while SDL.check():
    time.sleep_ms(5)

