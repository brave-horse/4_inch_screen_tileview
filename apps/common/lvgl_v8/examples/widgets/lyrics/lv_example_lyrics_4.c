/*
 * @file lv_example_lyrics_4.c
 *
 * 演示了使用lv_lyrics控件接口,将歌词每个字拆分成独立obj,可以设置换行宽度,对每个字做动画效果
 * 演示了不适用线程外部直接调用接口显示歌词
 */

#include "lvgl.h"
#include "../../lv_examples.h"
#include "app_config.h"
#if LV_USE_LYRICS && LV_BUILD_EXAMPLES

#define CONFIG_UI_RES_PATH CONFIG_ROOT_PATH // SD 路径

#define CONFIG_FONT_TTF_PATH CONFIG_UI_RES_PATH"font/simkai.ttf"    // windows 下完整楷体字库
//#define CONFIG_FONT_TTF_PATH "mnt/sdfile/EXT_RESERVED/uipackres/ui/sub1.ttf" // 龘: flash
//#define CONFIG_FONT_TTF_PATH "mnt/sdfile/EXT_RESERVED/uipackres/ui/sub2.ttf"  // 《生僻字部分歌词》: flash

#define LYRICS_LETTER_NUM_MAX 256

#define FONT_SPACING 10     //字间距,根据实际效果调节

static char lyrics_example4_text[LYRICS_LETTER_NUM_MAX] = "  ";
lv_obj_t *curr_obj_0 = NULL;
lv_obj_t **curr_obj_single = NULL;
int count_of_text = 0;

static void lyrics_example4_play_anim_cb(void *obj, int32_t v)
{
    if (curr_obj_single == NULL) {
        return;
    }

    for (int i = 0; i < count_of_text; i++) {
        lv_lyrics_set_rotation(curr_obj_single[i], 0, 0, v);
        lv_lyrics_fontimg_redarw(curr_obj_single[i]);
    }

}


//释放歌词
void lyrics_example4_clean(void)
{
    for (int i = 0; i < count_of_text; i++) {
        lv_anim_del(curr_obj_single[i], NULL);
        lv_lyrics_destructor(curr_obj_single[i]);
        curr_obj_single[i] = NULL;
    }

    if (curr_obj_single) {
        lv_mem_free(curr_obj_single);
    }

    count_of_text = 0;
}
//创建歌词
void lv_example_lyrics_4_letter(lv_obj_t *dest_scr, const char *text, uint16_t font_size, const char *font_file, uint16_t line_width)
{
    lyrics_example4_clean();

    size_t text_len = strlen(text);
    uint32_t *letter_buf = (uint32_t *)lv_mem_alloc(sizeof(uint32_t) * text_len);    // 空间大小最大不会超过 text_len * 4

    uint16_t letter_num = 0;
    // 解析字符串中的每一个 unicode
    int ofs = 0;
    while (ofs < text_len) {
        uint32_t letter;
        uint32_t letter_next;
        _lv_txt_encoded_letter_next_2(text, &letter, &letter_next, &ofs);
        printf("ofs = %d; letter = 0x%08x; letter_next = 0x%08x.", ofs, letter, letter_next);

        letter_buf[letter_num] = letter;
        printf("info.letter_buf[%d] = 0x%08x.", letter_num, letter_buf[letter_num]);

        letter_num++;
        assert(letter_num < LYRICS_LETTER_NUM_MAX);   // 歌词字符数量过大，有需求再修改
    }
    count_of_text = letter_num;
    printf("letter_num = %d.", letter_num);
    printf("text_len = %d.", text_len);
    curr_obj_single = (lv_obj_t **)lv_mem_alloc(letter_num * sizeof(lv_obj_t *));
    int y = 0;
    int x = 0;
    int xtimes = font_size + FONT_SPACING;

    for (int i = 0; i < letter_num; i++) {

        if (i == 0) {
            x = 0;
        }

        curr_obj_single[i] = lv_lyrics_create(dest_scr, font_file, font_size, 0, letter_buf + i, 1);

        if (x * xtimes >= line_width) {
            x = 0;
            y += xtimes;
            lv_lyrics_set_pos(curr_obj_single[i], 0 + x * xtimes, y);
        } else {
            lv_lyrics_set_pos(curr_obj_single[i], 0 + x * xtimes, y);
        }
        x++;
    }

#if 1
    lv_anim_t lyrics_example4_play_anim0;
    lv_anim_init(&lyrics_example4_play_anim0);  // 初时化动画变量
    lv_anim_set_var(&lyrics_example4_play_anim0, curr_obj_single); //设置动画关联的对象img
    lv_anim_set_exec_cb(&lyrics_example4_play_anim0, lyrics_example4_play_anim_cb); //设置动画执行的回调函数set_angle
    lv_anim_set_values(&lyrics_example4_play_anim0, 0, 3600);
    lv_anim_set_time(&lyrics_example4_play_anim0, 5000);
    lv_anim_set_playback_time(&lyrics_example4_play_anim0, 2000);
    lv_anim_set_repeat_count(&lyrics_example4_play_anim0, LV_ANIM_REPEAT_INFINITE);//设置动画重复次数，这里是无穷次
    lv_anim_start(&lyrics_example4_play_anim0); //启动动画播放
#endif

    lv_mem_free(letter_buf);
    return;
}

/**
 * @brief lv_example_lyrics_4_text_input
 *
 * @Params dest_scr
 * @Params new_text
 * @Params font_size
 * @Params line_width 自动换行宽度，单位为一个像素
 *
 * @return
 */
void lv_example_lyrics_4_text_input(void *dest_scr, char *new_text, uint16_t font_size, uint16_t line_width)
{
    size_t text_len = strlen(new_text);
    if (text_len > LYRICS_LETTER_NUM_MAX) {
        printf("error: new_text is too len. len = %d.", text_len);
        return;
    }

    printf("[%s] new lyrics is [%s]", __func__, new_text);

    memcpy(lyrics_example4_text, new_text, text_len);
    lyrics_example4_text[text_len] = '\0';

    lv_example_lyrics_4_letter(dest_scr, lyrics_example4_text, font_size, CONFIG_FONT_TTF_PATH, line_width);
}



//调用示例
//在lvgl以外线程使用lvgl_rpc_post_func(),如果需要切换页面,歌词建议创建在lv_layer_top()页面自行管理,test_text为输入歌词
//lvgl_rpc_post_func(lv_example_lyrics_4_text_input, 4, lv_layer_top(), test_text, font_size, line_width);



#endif

