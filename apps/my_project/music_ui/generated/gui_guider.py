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
SDL.init(w=800,h=480)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(800*480*4)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 800
disp_drv.ver_res = 480
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
screen.set_size(800, 480)
screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_cont_1
screen_cont_1 = lv.obj(screen)
screen_cont_1.set_pos(0, 0)
screen_cont_1.set_size(800, 480)
screen_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_cont_1.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_bg_color(lv.color_hex(0x62c90b), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_btn_4
screen_btn_4 = lv.btn(screen_cont_1)
screen_btn_4_label = lv.label(screen_btn_4)
screen_btn_4_label.set_text("Button")
screen_btn_4_label.set_long_mode(lv.label.LONG.WRAP)
screen_btn_4_label.set_width(lv.pct(100))
screen_btn_4_label.align(lv.ALIGN.CENTER, 0, 0)
screen_btn_4.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_btn_4.set_pos(411, 308)
screen_btn_4.set_size(100, 50)
# Set style for screen_btn_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_btn_4.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_4.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_4.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_4.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_4.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_cont_2
screen_cont_2 = lv.obj(screen)
screen_cont_2.set_pos(0, 0)
screen_cont_2.set_size(800, 480)
screen_cont_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_cont_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_cont_2.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_2.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_2.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_2.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_2.set_style_bg_color(lv.color_hex(0x0b4ac9), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_btn_5
screen_btn_5 = lv.btn(screen_cont_2)
screen_btn_5_label = lv.label(screen_btn_5)
screen_btn_5_label.set_text("Button")
screen_btn_5_label.set_long_mode(lv.label.LONG.WRAP)
screen_btn_5_label.set_width(lv.pct(100))
screen_btn_5_label.align(lv.ALIGN.CENTER, 0, 0)
screen_btn_5.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_btn_5.set_pos(372, 143)
screen_btn_5.set_size(100, 50)
# Set style for screen_btn_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_btn_5.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_5.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_5.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_5.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_5.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_5.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_tileview_1
screen_tileview_1 = lv.tileview(screen)
screen_tileview_1_tile = screen_tileview_1.add_tile(0, 0, lv.DIR.RIGHT)
screen_tileview_1_tile_1 = screen_tileview_1.add_tile(1, 0, lv.DIR.LEFT | lv.DIR.RIGHT)
screen_tileview_1_tile_2 = screen_tileview_1.add_tile(2, 0, lv.DIR.LEFT)
screen_tileview_1.set_pos(0, 0)
screen_tileview_1.set_size(800, 480)
screen_tileview_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_tileview_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_tileview_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_tileview_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_tileview_1.set_style_bg_color(lv.color_hex(0x020101), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_tileview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_tileview_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_tileview_1, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
screen_tileview_1.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_tileview_1.set_style_bg_color(lv.color_hex(0xeaeff3), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_tileview_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_tileview_1.set_style_radius(0, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create screen_btn_2
screen_btn_2 = lv.btn(screen_tileview_1_tile)
screen_btn_2_label = lv.label(screen_btn_2)
screen_btn_2_label.set_text("客厅")
screen_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
screen_btn_2_label.set_width(lv.pct(100))
screen_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
screen_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_btn_2.set_pos(661, 182)
screen_btn_2.set_size(100, 50)
# Set style for screen_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_btn_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_btn_6
screen_btn_6 = lv.btn(screen_tileview_1_tile)
screen_btn_6_label = lv.label(screen_btn_6)
screen_btn_6_label.set_text("门厅")
screen_btn_6_label.set_long_mode(lv.label.LONG.WRAP)
screen_btn_6_label.set_width(lv.pct(100))
screen_btn_6_label.align(lv.ALIGN.CENTER, 0, 0)
screen_btn_6.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_btn_6.set_pos(621, 70)
screen_btn_6.set_size(100, 50)
# Set style for screen_btn_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_btn_6.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_6.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_6.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_6.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_6.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_6.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_6.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_btn_1
screen_btn_1 = lv.btn(screen_tileview_1_tile_1)
screen_btn_1_label = lv.label(screen_btn_1)
screen_btn_1_label.set_text("Button1")
screen_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
screen_btn_1_label.set_width(lv.pct(100))
screen_btn_1_label.align(lv.ALIGN.CENTER, 0, 0)
screen_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_btn_1.set_pos(319, 220)
screen_btn_1.set_size(59, 50)
# Set style for screen_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_btn_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_btn_3
screen_btn_3 = lv.btn(screen_tileview_1_tile_2)
screen_btn_3_label = lv.label(screen_btn_3)
screen_btn_3_label.set_text("Button")
screen_btn_3_label.set_long_mode(lv.label.LONG.WRAP)
screen_btn_3_label.set_width(lv.pct(100))
screen_btn_3_label.align(lv.ALIGN.CENTER, 0, 0)
screen_btn_3.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_btn_3.set_pos(350, 215)
screen_btn_3.set_size(100, 50)
# Set style for screen_btn_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_btn_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_digital_clock_1
screen_digital_clock_1_time = [int(13), int(26), int(51), ""]
screen_digital_clock_1 = lv.dclock(screen, "13:26:51")
screen_digital_clock_1_timer = lv.timer_create_basic()
screen_digital_clock_1_timer.set_period(1000)
screen_digital_clock_1_timer.set_cb(lambda src: digital_clock_cb(screen_digital_clock_1_timer, screen_digital_clock_1, screen_digital_clock_1_time, True, False ))
screen_digital_clock_1.set_pos(37, 29)
screen_digital_clock_1.set_size(163, 84)
# Set style for screen_digital_clock_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_digital_clock_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_bg_color(lv.color_hex(0x292929), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_text_font(test_font("Antonio_Regular", 25), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_pad_top(7, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_digital_clock_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_label_1
screen_label_1 = lv.label(screen)
screen_label_1.set_text("Label")
screen_label_1.set_long_mode(lv.label.LONG.WRAP)
screen_label_1.set_width(lv.pct(100))
screen_label_1.set_pos(267, 536)
screen_label_1.set_size(100, 32)
# Set style for screen_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
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
screen_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_img_1
screen_img_1 = lv.img(screen)
screen_img_1.set_src("B:MicroPython/_drop_alpha_354x567.bin")
screen_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
screen_img_1.set_pivot(50,50)
screen_img_1.set_angle(0)
screen_img_1.set_pos(231, -50)
screen_img_1.set_size(354, 567)
# Set style for screen_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_btn_7
screen_btn_7 = lv.btn(screen)
screen_btn_7_label = lv.label(screen_btn_7)
screen_btn_7_label.set_text("餐厅")
screen_btn_7_label.set_long_mode(lv.label.LONG.WRAP)
screen_btn_7_label.set_width(lv.pct(100))
screen_btn_7_label.align(lv.ALIGN.CENTER, 0, 0)
screen_btn_7.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_btn_7.set_pos(623, 294)
screen_btn_7.set_size(100, 50)
# Set style for screen_btn_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_btn_7.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_7.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_7.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_7.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_7.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_7.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_btn_7.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

screen.update_layout()
# Create screen_1
screen_1 = lv.obj()
screen_1.set_size(800, 480)
screen_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_1_btn_1
screen_1_btn_1 = lv.btn(screen_1)
screen_1_btn_1_label = lv.label(screen_1_btn_1)
screen_1_btn_1_label.set_text("Button")
screen_1_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
screen_1_btn_1_label.set_width(lv.pct(100))
screen_1_btn_1_label.align(lv.ALIGN.CENTER, 0, 0)
screen_1_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_1_btn_1.set_pos(65, 66)
screen_1_btn_1.set_size(100, 50)
# Set style for screen_1_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_1_btn_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_1.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_1_btn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_1.update_layout()
# Create screen_2
screen_2 = lv.obj()
screen_2.set_size(800, 480)
screen_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_2.update_layout()
# Create screen_3
screen_3 = lv.obj()
screen_3.set_size(800, 480)
screen_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_3.update_layout()
# Create screen_4
screen_4 = lv.obj()
screen_4.set_size(800, 480)
screen_4.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_4.update_layout()

def screen_btn_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(screen_1, lv.SCR_LOAD_ANIM.NONE, 0, 0, False)
screen_btn_2.add_event_cb(lambda e: screen_btn_2_event_handler(e), lv.EVENT.ALL, None)

def screen_btn_3_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

screen_btn_3.add_event_cb(lambda e: screen_btn_3_event_handler(e), lv.EVENT.ALL, None)

def screen_1_btn_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(screen, lv.SCR_LOAD_ANIM.NONE, 100, 0, False)
screen_1_btn_1.add_event_cb(lambda e: screen_1_btn_1_event_handler(e), lv.EVENT.ALL, None)

# content from custom.py

# Load the default screen
lv.scr_load(screen)

while SDL.check():
    time.sleep_ms(5)

