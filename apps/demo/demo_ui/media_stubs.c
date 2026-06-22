/* jlstream media框架缺的config/BT/log_tag符号桩(demo_ui专用) */
#include "system/includes.h"

/* BT stub */
const char *bt_get_local_name(void) { return "AC792"; }
void lmp_hci_write_local_name(const char *name, int len) { (void)name; (void)len; }
void lmp_hci_write_local_name_protected(const char *name, int len) { (void)name; (void)len; }

/* jlstream config stub */
const int config_stream_frame_debug = 0;
const int config_jlstream_scene_debug = 0;
const int config_jlstream_fade_time_msec = 0;
const int config_media_24bit_enable = 0;
const int config_jlstream_bind_bt_name_enable = 0;
const int config_dac_cache_msec = 0;
const int config_seamless_recorder_enable = 0;
const int config_jlstream_multi_thread_enable = 0;
const int config_multi_thread_self_adaption_enable = 0;
const int config_jlstream_log_output_enable = 0;

/* audio node 插件桩 */
void source_node_plug_begin(void) {}
void source_node_plug_end(void) {}

/* jlstream LOG tag */
const char log_tag_const_e_JLSTREAM[]  = "JLSTREAM";
const char log_tag_const_w_JLSTREAM[]  = "JLSTREAM";
const char log_tag_const_i_JLSTREAM[]  = "JLSTREAM";
const char log_tag_const_d_JLSTREAM[]  = "JLSTREAM";
const char log_tag_const_v_JLSTREAM[]  = "JLSTREAM";
const char log_tag_const_i_AUDIO_NODE[] = "AUDIO_NODE";
const char log_tag_const_e_AUDIO_NODE[] = "AUDIO_NODE";
