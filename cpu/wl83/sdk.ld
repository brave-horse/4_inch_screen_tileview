









  memcpy = ABSOLUTE(0xf9f30);
  memmove = ABSOLUTE(0xf9f34);
  memcmp = ABSOLUTE(0xf9f38);
  memset = ABSOLUTE(0xf9f3c);
  strcmp = ABSOLUTE(0xf9f40);
  strcpy = ABSOLUTE(0xf9f44);
  strlen = ABSOLUTE(0xf9f48);
  strncmp = ABSOLUTE(0xf9f4c);
  strstr = ABSOLUTE(0xf9f50);
  strchr = ABSOLUTE(0xf9f54);
  LZ4_setStreamDecode = ABSOLUTE(0xf9fc0);
  LZ4_decompress_safe_continue = ABSOLUTE(0xf9fc4);
  LZ4_decompress_generic = ABSOLUTE(0xf9fc8);
  LZ4_decompress_safe_usingDict = ABSOLUTE(0xf9fcc);
  dec_isd_cfg_ini = ABSOLUTE(0xf9fd0);
  pbkdf2_genkey = ABSOLUTE(0xf9fd4);
  sm4_set_decrypt_key = ABSOLUTE(0xf9fd8);
  sm4_cbc_decrypt = ABSOLUTE(0xf9fdc);
  pbkdf2_hmac_sm3_genkey = ABSOLUTE(0xf9fe0);







EXTERN(
_start

isc0
isc1
csi0
mcv0
mcv1
mcv2
mcv3
isp
imc0
imc1
imc2
imc3
jpeg_enc0
jpeg_enc1
jpeg_enc2
jpeg_dec0
jpeg_dec1
jpeg_dec2
jpeg_dec3
file0
uvc0
uvc1
uvc_dev_ops
rep0
rep1
disp0
disp1
disp2
disp3
disp4
disp5
disp6
disp7
sink0
videosink0
videosink1
videosink2
imagesink0
gp0
virtual0
virtual1
virtual2
virtual3
sft0
sft1
gpu0
gpu1
gpu2
gpu3
dma2d0
dma2d1
yuv0
yuv1
yuv2
yuv3
composite0
composite1
video0
video1
video2
video3
video_dec



fbvirtual_fbops


sdfile_vfs_ops



nor_sdfile_vfs_ops






jl_fat_vfs_ops
video_server_info
video_engine_server_info
vpkg_server_info
vpkg_fsys_ops
avi_pkg_ops
camera_subdev
djpeg_subdev
video_dev_ops

);



BOOT_INFO_SIZE = 68;





TLB_SIZE = 0;
MMU_TAG_ADDR = 0;





OTALOADER_SIZE = 0;





SDRAM_ORIGIN = 0x18000120;
SDRAM_SIZE = (16 * 1024 * 1024) - 0x120 - OTALOADER_SIZE;


VIDEO_RAM_SIZE = 0;
RAM0_SIZE = 0x11fe00 - 0x100000 - TLB_SIZE - BOOT_INFO_SIZE - 128;
UPDATA_BEG = 0x11fe00 - 128;
CODE_BEG = 0x8000120;

FREE_DCACHE_WAY = 0;
FREE_ICACHE0_WAY = 0;
FREE_ICACHE1_WAY = 0;

DCACHE_RAM_SIZE = FREE_DCACHE_WAY*4K;
ICACHE0_RAM_SIZE = FREE_ICACHE0_WAY*4K;
ICACHE1_RAM_SIZE = FREE_ICACHE1_WAY*4K;

MEMORY
{
    rom(rx) : ORIGIN = CODE_BEG, LENGTH = (8 * 1024 * 1024)
    sdram(rwx) : ORIGIN = SDRAM_ORIGIN, LENGTH = SDRAM_SIZE
    ram0(rwx) : ORIGIN = 0x100000 + TLB_SIZE, LENGTH = RAM0_SIZE
    boot_info(rwx) : ORIGIN = 0x100000 + TLB_SIZE + RAM0_SIZE, LENGTH = BOOT_INFO_SIZE
    dcache_ram(rw) : ORIGIN = 0x378000-((FREE_DCACHE_WAY)*4K), LENGTH = FREE_DCACHE_WAY*4K
    icache0_ram(rw) : ORIGIN = 0x3c8000-((FREE_ICACHE0_WAY)*4K), LENGTH = FREE_ICACHE0_WAY*4K
    icache1_ram(rw) : ORIGIN = 0x3d8000-((FREE_ICACHE1_WAY)*4K), LENGTH = FREE_ICACHE1_WAY*4K
    video_ram(rwx) : ORIGIN = 0x7f00000, LENGTH = VIDEO_RAM_SIZE
    dlog0(r) : ORIGIN = 0x20000000, LENGTH = 0x100000
}

SECTIONS
{



    . = ORIGIN(sdram);

    .text ALIGN(4):
    {
        _rom_text_code_begin = .;
        PROVIDE(rom_text_code_begin = .);

        *startup.S.o(.text)
        *(.boot_code)
        *(.dlmalloc_code)
        *(.mem_heap_code)
        *(.os_code)
        *(.os_port_code)



        *(.LOG_TAG_CONST*)

        . = ALIGN(4);
        __VERSION_BEGIN = .;
        KEEP(*(.sys.version))
        __VERSION_END = .;


        . = ALIGN(4);
        _ctors_begin = .;
        PROVIDE(ctors_begin = .);
        KEEP(*(SORT(.ctors.*)))
        KEEP(*(.ctors))
        _ctors_end = .;
        PROVIDE(ctors_end = .);
        . = ALIGN(4);
        . = ALIGN(4);
        _dlog_ops_begin = .;
        PROVIDE(dlog_ops_begin = .);
        KEEP(*(.dlog.0.ops))
        KEEP(*(.dlog.1.ops))
        _dlog_ops_end = .;
        PROVIDE(dlog_ops_end = .);

        _dlog_out_channel_begin = .;
        PROVIDE(dlog_out_channel_begin = .);
        KEEP(*(.dlog_out_channel))
        _dlog_out_channel_end = .;
        PROVIDE(dlog_out_channel_end = .);

        *(*.rf.text.cache.L2.rf_trim)



        *(.power_driver.text)
        *(.power_driver.text.const)

        . = ALIGN(4);
        lp_target_begin = .;
        PROVIDE(lp_target_begin = .);
        KEEP(*(.lp_target))
        lp_target_end = .;
        PROVIDE(lp_target_end = .);

        . = ALIGN(4);
        lp_request_begin = .;
        PROVIDE(lp_request_begin = .);
        KEEP(*(.lp_request))
        lp_request_end = .;
        PROVIDE(lp_request_end = .);

        . = ALIGN(4);
        deepsleep_target_begin = .;
        PROVIDE(deepsleep_target_begin = .);
        KEEP(*(.deepsleep_target))
        deepsleep_target_end = .;
        PROVIDE(deepsleep_target_end = .);

        . = ALIGN(4);
        p2m_msg_handler_begin = .;
        PROVIDE(p2m_msg_handler_begin = .);
        KEEP(*(.p2m_msg_handler))
        PROVIDE(p2m_msg_handler_end = .);
        p2m_msg_handler_end = .;

        . = ALIGN(4);
        soff_busy_dev_close_hdl_begin = .;
        PROVIDE(soff_busy_dev_close_hdl_begin = .);
        KEEP(*(.soff_busy_dev_close_hdl))
        soff_busy_dev_close_hdl_end = .;
        PROVIDE(soff_busy_dev_close_hdl_end = .);







        *(.*.cache.L2.code)
        *(.*.text)
        *(.text*)

        . = ALIGN(4);
        _rom_text_code_end = .;
        PROVIDE(rom_text_code_end = .);

        *(.*.text.const)
        *(.*.cache.L2.const)
        *(.rodata*)


 . = ALIGN(4);
        ui_module_event_handler_begin = .;
        KEEP(*(.ui_module_event_handler))
        ui_module_event_handler_end = .;

        ui_screen_action_handler_begin = .;
        KEEP(*(.ui_screen_action_handler))
        ui_screen_action_handler_end = .;

        ui_varable_reg_tab_begin = .;
        KEEP(*(.ui_varable_reg_tab))
        ui_varable_reg_tab_end = .;

        ui_key_event_handler_begin = .;
        KEEP(*(.ui_key_event_handler))
        ui_key_event_handler_end = .;

        . = ALIGN(4);


    _vfs_ops_begin = .;
    PROVIDE(vfs_ops_begin = .);
        *(.vfs_operations)
    _vfs_ops_end = .;
    PROVIDE(vfs_ops_end = .);

    _initcall_begin = .;
    PROVIDE(initcall_begin = .);
        *(.initcall)
    _initcall_end = .;
    PROVIDE(initcall_end = .);

    _early_initcall_begin = .;
    PROVIDE(early_initcall_begin = .);
       *(.early.initcall)
    _early_initcall_end = .;
    PROVIDE(early_initcall_end = .);

    _late_initcall_begin = .;
    PROVIDE(late_initcall_begin = .);
       *(.late.initcall)
    _late_initcall_end = .;
    PROVIDE(late_initcall_end = .);

    _platform_initcall_begin = .;
    PROVIDE(platform_initcall_begin = .);
       *(.platform.initcall)
    _platform_initcall_end = .;
    PROVIDE(platform_initcall_end = .);

    _module_initcall_begin = .;
    PROVIDE(module_initcall_begin = .);
       *(.module.initcall)
    _module_initcall_end = .;
    PROVIDE(module_initcall_end = .);

    _sys_event_handler_begin = .;
    PROVIDE(sys_event_handler_begin = .);
       *(.sys_event.4.handler)
       *(.sys_event.3.handler)
       *(.sys_event.2.handler)
       *(.sys_event.1.handler)
       *(.sys_event.0.handler)
    _sys_event_handler_end = .;
    PROVIDE(sys_event_handler_end = .);

    _app_event_handler_begin = .;
    PROVIDE(app_event_handler_begin = .);
       *(.app_event_handler)
    _app_event_handler_end = .;
    PROVIDE(app_event_handler_end = .);

    _syscfg_ops_begin = .;
    PROVIDE(syscfg_ops_begin = .);
       *(.syscfg.2.ops)
       *(.syscfg.1.ops)
       *(.syscfg.0.ops)
    _syscfg_ops_end = .;
    PROVIDE(syscfg_ops_end = .);

    _vm_spi_target_begin = .;
    PROVIDE(vm_spi_target_begin = .);
        *(.vm_spi_target)
    _vm_spi_target_end = .;
    PROVIDE(vm_spi_target_end = .);

    _vm_spi_mutex_target_begin = .;
    PROVIDE(vm_spi_mutex_target_begin = .);
        *(.vm_spi_mutex_target)
    _vm_spi_mutex_target_end = .;
    PROVIDE(vm_spi_mutex_target_end = .);

    _key_driver_ops_begin = .;
    PROVIDE(key_driver_ops_begin = .);
        *(.key_operation)
    _key_driver_ops_end = .;
    PROVIDE(key_driver_ops_end = .);

    _server_info_begin = .;
    PROVIDE(server_info_begin = .);
       *(.server_info)
    _server_info_end = .;
    PROVIDE(server_info_end = .);

    _cmd_interface_begin = .;
    PROVIDE(cmd_interface_begin = .);
       *(.eff_cmd)
    _cmd_interface_end = .;
    PROVIDE(cmd_interface_end = .);

    _snap_interface_begin = .;
    PROVIDE(snap_interface_begin = .);
       *(.snap_parm)
    _snap_interface_end = .;
    PROVIDE(snap_interface_end = .);

    _device_node_begin = .;
    PROVIDE(device_node_begin = .);
        *(.device)
    _device_node_end = .;
    PROVIDE(device_node_end = .);

    _ai_sdk_api_begin = .;
    PROVIDE(ai_sdk_api_begin = .);
        *(.ai_sdk)
    _ai_sdk_api_end = .;
    PROVIDE(ai_sdk_api_end = .);

    _tool_interface_begin = .;
    PROVIDE(tool_interface_begin = .);
        *(.tool_interface)
    _tool_interface_end = .;
    PROVIDE(tool_interface_end = .);

    _camera_dev_begin = .;
    PROVIDE(camera_dev_begin = .);
        *(.camera_dev)
    _camera_dev_end = .;
    PROVIDE(camera_dev_end = .);

    _eth_phy_device_begin = .;
    PROVIDE(eth_phy_device_begin = .);
        *(.eth_phy_device)
    _eth_phy_device_end = .;
    PROVIDE(eth_phy_device_end = .);

    _camera1_dev_begin = .;
    PROVIDE(camera1_dev_begin = .);
        *(.camera1_dev)
    _camera1_dev_end = .;
    PROVIDE(camera1_dev_end = .);

    _iic_device_begin = .;
    PROVIDE(iic_device_begin = .);
        *(.iic)
    _iic_device_end = .;
    PROVIDE(iic_device_end = .);

    _video_pkg_sys_begin = .;
    PROVIDE(video_pkg_sys_begin = .);
        *(.video_pkg_sys)
    _video_pkg_sys_end = .;
    PROVIDE(video_pkg_sys_end = .);

    _video_pkg_begin = .;
    PROVIDE(video_pkg_begin = .);
        *(.video_pkg)
    _video_pkg_end = .;
    PROVIDE(video_pkg_end = .);

    _plugin_begin = .;
    PROVIDE(plugin_begin = .);
        *(.pipeline_plugin)
    _plugin_end = .;
    PROVIDE(plugin_end = .);

    _tp_driver_begin = .;
    PROVIDE(tp_driver_begin = .);
     *(.tp_driver)
    _tp_driver_end = .;
    PROVIDE(tp_driver_end = .);

    wireless_trans_ops_begin = .;
    PROVIDE(wireless_trans_ops_begin = .);
    *(.wireless_trans)
    wireless_trans_ops_end = .;
    PROVIDE(wireless_trans_ops_end = .);

    wireless_data_callback_func_begin = .;
    PROVIDE(wireless_data_callback_func_begin = .);
    *(.wireless_call_sync)
    wireless_data_callback_func_end = .;
    PROVIDE(wireless_data_callback_func_end = .);

    wireless_custom_data_trans_stub_begin = .;
    PROVIDE(wireless_custom_data_trans_stub_begin = .);
    *(.wireless_custom_data_trans_stub)
    wireless_custom_data_trans_stub_end = .;
    PROVIDE(wireless_custom_data_trans_stub_end = .);

        . = ALIGN(4);


   _audio_decoder_begin = .;
   PROVIDE(audio_decoder_begin = .);
       *(.audio_decoder)
   _audio_decoder_end = .;
   PROVIDE(audio_decoder_end = .);

   _audio_package_begin = .;
   PROVIDE(audio_package_begin = .);
       *(.audio_package)
   _audio_package_end = .;
   PROVIDE(audio_package_end = .);

   _audio_effect_begin = .;
   PROVIDE(audio_effect_begin = .);
       *(.audio_effect)
   _audio_effect_end = .;
   PROVIDE(audio_effect_end = .);

   _audio_hwaccel_begin = .;
   PROVIDE(audio_hwaccel_begin = .);
       *(.audio_hwaccel)
   _audio_hwaccel_end = .;
   PROVIDE(audio_hwaccel_end = .);

   _audio_output_handler_begin = .;
   PROVIDE(audio_output_handler_begin = .);
       *(.audio_output_handler)
   _audio_output_handler_end = .;
   PROVIDE(audio_output_handler_end = .);

   _audio_input_handler_begin = .;
   PROVIDE(audio_input_handler_begin = .);
       *(.audio_input_handler)
   _audio_input_handler_end = .;
   PROVIDE(audio_input_handler_end = .);

   _audio_subdev_begin = .;
   PROVIDE(audio_subdev_begin = .);
       *(.audio_subdev.0)
       *(.audio_subdev.1)
       *(.audio_subdev.2)
       *(.audio_subdev.3)
   _audio_subdev_end = .;
   PROVIDE(audio_subdev_end = .);

   _fm_dev_begin = .;
   PROVIDE(fm_dev_begin = .);
       *(.fm_dev)
   _fm_dev_end = .;
   PROVIDE(fm_dev_end = .);

    _video_dev_begin = .;
    PROVIDE(video_dev_begin = .);
        *(.video_device)
    _video_dev_end = .;
    PROVIDE(video_dev_end = .);

    _video_subdev_begin = .;
    PROVIDE(video_subdev_begin = .);
        *(.video_subdev.0)
        *(.video_subdev.1)
        *(.video_subdev.2)
        *(.video_subdev.3)
        *(.video_subdev.4)
        *(.video_subdev.5)
    _video_subdev_end = .;
    PROVIDE(video_subdev_end = .);


        . = ALIGN(32);
    }





 > sdram


    .data ALIGN(32):
    {
        _sdram_text_code_begin = .;
        PROVIDE(sdram_text_code_begin = .);
        _sdram_text_code_end = .;
        PROVIDE(sdram_text_code_end = .);

        . = ALIGN(4);

    _app_begin = .;
    PROVIDE(app_begin = .);
        *(.app)
    _app_end = .;
    PROVIDE(app_end = .);

    _static_hi_timer_begin = .;
    PROVIDE(static_hi_timer_begin = .);
        *(.hi_timer)
    _static_hi_timer_end = .;
    PROVIDE(static_hi_timer_end = .);

    _sys_cpu_timer_begin = .;
    PROVIDE(sys_cpu_timer_begin = .);
        *(.sys_cpu_timer)
    _sys_cpu_timer_end = .;
    PROVIDE(sys_cpu_timer_end = .);

    _gsensor_dev_begin = .;
    PROVIDE(gsensor_dev_begin = .);
        *(.gsensor_dev)
    _gsensor_dev_end = .;
    PROVIDE(gsensor_dev_end = .);

    _clock_critical_handler_begin = .;
    PROVIDE(clock_critical_handler_begin = .);
        *(.clock_critical_txt)
    _clock_critical_handler_end = .;
    PROVIDE(clock_critical_handler_end = .);

    _lcd_device_begin = .;
    PROVIDE(lcd_device_begin = .);
        *(.lcd_device)
    _lcd_device_end = .;
    PROVIDE(lcd_device_end = .);

    _lcd_device_drive_begin = .;
    PROVIDE(lcd_device_drive_begin = .);
        *(.lcd_device_drive)
    _lcd_device_drive_end = .;
    PROVIDE(lcd_device_drive_end = .);

        . = ALIGN(4);


  _ctp_mapping_tab_begin = .;
 PROVIDE(ctp_mapping_tab_begin = .);

 _ctp_mapping_tab_system_cmd_begin = .;
 PROVIDE(ctp_mapping_tab_system_cmd_begin = .);
  *(.ctp_system_cmd)
 _ctp_mapping_tab_system_cmd_end = .;
 PROVIDE(ctp_mapping_tab_system_cmd_end = .);

 _ctp_mapping_tab_video_cmd_begin = .;
 PROVIDE(ctp_mapping_tab_video_cmd_begin = .);
  *(.ctp_video_cmd)
 _ctp_mapping_tab_video_cmd_end = .;
 PROVIDE(ctp_mapping_tab_video_cmd_end = .);

 _ctp_mapping_tab_photo_cmd_begin = .;
 PROVIDE(ctp_mapping_tab_photo_cmd_begin = .);
  *(.ctp_photo_cmd)
 _ctp_mapping_tab_photo_cmd_end = .;
 PROVIDE(ctp_mapping_tab_photo_cmd_end = .);

 _ctp_mapping_tab_end = .;
 PROVIDE(ctp_mapping_tab_end = .);

 _net_video_stream_sub_begin = .;
 PROVIDE(net_video_stream_sub_begin = .);
   *(.net_video_stream)
 _net_video_stream_sub_end = .;
 PROVIDE(net_video_stream_sub_end = .);







        *(.dlmalloc_const)
        *(.mem_heap_const)
        *(.os_const)
        *(.os_str)
        *(.os_data)
        *(.os_port_data)
        *(.os_port_const)







        . = ALIGN(4);
        *(.debug_exception.debug_text)
        *(.debug_exception.debug_const)
        *(.debug_exception.data)

        . = ALIGN(4);
        *(.data)

        . = ALIGN(4);
    } > sdram

    .bss ALIGN(32) (NOLOAD):
    {
        . = ALIGN(4);
        *(.debug_exception.data.bss)

        *(.bss)

        *(.bss.*)

        *(COMMON)
        *(.mem_heap)
        *(.memp_memory_x)

        . = ALIGN(4);
        *(.os_port_bss)
        *(.os_bss)

        . = ALIGN(4);
    } > sdram

    _HEAP_BEGIN = ( . + 31 ) / 32 * 32 ;
    PROVIDE(HEAP_BEGIN = (. + 31) / 32 * 32);
    _HEAP_END = SDRAM_ORIGIN + SDRAM_SIZE - 32;
    PROVIDE(HEAP_END = SDRAM_ORIGIN + SDRAM_SIZE - 32);
    _MALLOC_SIZE = _HEAP_END - _HEAP_BEGIN;
    PROVIDE(MALLOC_SIZE = _HEAP_END - _HEAP_BEGIN);


    . =ORIGIN(ram0);
    .ram0_data ALIGN(4):
    {
        _ram_text_code_begin = .;
        PROVIDE(ram_text_code_begin = .);
        . = ALIGN(4);
        _SPI_CODE_START = .;
        *(.spi_code)
        . = ALIGN(4);
        _SPI_CODE_END = .;

        *(.cache_code)
        *(.volatile_ram_code)
        *(.volatile_ram_power)
        . = ALIGN(4);
        _ram_text_code_end = .;
        PROVIDE(ram_text_code_end = .);

        *(.volatile_ram)
        *(.non_volatile_ram)
        *(.fft_data)

        . = ALIGN(4);
        *(.power_driver.data)




        . = ALIGN(4);
    } > ram0

    .ram0_bss ALIGN(4):
    {
        . = ALIGN(4);
        *(.the_debug_isr_stack_c0)
        *(.the_debug_isr_stack_c1)
        *(.stack_magic)
        *(.stack_magic0)

        . = ALIGN(4);
        _stack_info_begin = .;
        PROVIDE(stack_info_begin = .);
        *(.cpu0_ustack)
        _cpu0_sstack_begin = .;
        PROVIDE(cpu0_sstack_begin = .);
        *(.cpu0_sstack)
        _cpu0_sstack_end = .;
        PROVIDE(cpu0_sstack_end = .);
        *(.cpu1_ustack)
        _cpu1_sstack_begin = .;
        PROVIDE(cpu1_sstack_begin = .);
        *(.cpu1_sstack)
        _cpu1_sstack_end = .;
        PROVIDE(cpu1_sstack_end = .);
        _stack_info_end = .;
        PROVIDE(stack_info_end = .);

        . = ALIGN(4);
        *(.power_driver.data.bss)




        *(.sram)

        . = ALIGN(4);


_usb_data_begin = .;
PROVIDE(usb_data_begin = .);
*(.usb_h_bss)
*(.usb_g_bss)
*(.usb_h_dma)
*(.usb_config_var)
*(.usb_msd_dma)
*(.usb_fifo)
*(.mass_storage)
*(.uac_var)
*(.uac_rx)
*(.usb_h_udisk)
*(.cdc_var)
_usb_data_end = .;
PROVIDE(usb_data_end = .);


        . = ALIGN(4);
    } > ram0

    _RAM_HEAP_BEGIN = ( . + 31 ) / 32 * 32;
    PROVIDE(RAM_HEAP_BEGIN = (. + 31) / 32 * 32);
    _RAM_HEAP_END = 0x100000 + TLB_SIZE + RAM0_SIZE - 32;
    PROVIDE(RAM_HEAP_END = 0x100000 + TLB_SIZE + RAM0_SIZE - 32);
    _RAM_MALLOC_SIZE = _RAM_HEAP_END - _RAM_HEAP_BEGIN;
    PROVIDE(RAM_MALLOC_SIZE = _RAM_HEAP_END - _RAM_HEAP_BEGIN);


    . = ORIGIN(boot_info);
    .boot_info ALIGN(4):
    {
        *(.boot_info)
        *(.boot_info_dma)
        . = ALIGN(4);
    } > boot_info


    . = ORIGIN(dlog0);

    .dlog_data :SUBALIGN(4)
    {
        dlog_seg_begin = .;

        KEEP(*(.dlog.rodata.head))

        . = ALIGN(0x100);

        dlog_str_tab_seg_begin = .;
        dlog_str_tab_seg0_begin = .;
        *(.dlog.rodata.str_tab.0)

        dlog_str_tab_seg1_begin = .;
        *(.dlog.rodata.str_tab.1)

        dlog_str_tab_seg2_begin = .;
        *(.dlog.rodata.str_tab.2)

        dlog_str_tab_seg3_begin = .;
        *(.dlog.rodata.str_tab.3)

        dlog_str_tab_seg4_begin = .;
        *(.dlog.rodata.str_tab.4)

        dlog_str_tab_seg5_begin = .;
        *(.dlog.rodata.str_tab.5)

        dlog_str_tab_seg6_begin = .;
        *(.dlog.rodata.str_tab.6)

        dlog_str_tab_seg7_begin = .;
        *(.dlog.rodata.str_tab.7)

        dlog_str_tab_segAll_begin = .;
        *(.dlog.rodata.str_tab*)
        dlog_str_tab_segAll_end = .;
        dlog_str_tab_seg_end = .;

        . = ALIGN(32);
        dlog_str_seg_begin = .;
        dlog_str_seg0_begin = .;
        *(.dlog.rodata.string.0)

        dlog_str_seg1_begin = .;
        *(.dlog.rodata.string.1)

        dlog_str_seg2_begin = .;
        *(.dlog.rodata.string.2)

        dlog_str_seg3_begin = .;
        *(.dlog.rodata.string.3)

        dlog_str_seg4_begin = .;
        *(.dlog.rodata.string.4)

        dlog_str_seg5_begin = .;
        *(.dlog.rodata.string.5)

        dlog_str_seg6_begin = .;
        *(.dlog.rodata.string.6)

        dlog_str_seg7_begin = .;
        *(.dlog.rodata.string.7)

        dlog_str_segAll_begin = .;
        *(.dlog.rodata.string*)
        dlog_str_segAll_end = .;
        dlog_str_seg_end = .;

        dlog_seg_end = .;
    } > dlog0




    . = ORIGIN(dcache_ram);
    .dcache_ram_data ALIGN(4):
    {
        . = ALIGN(4);
    } > dcache_ram

    .dcache_ram_bss ALIGN(4) (NOLOAD):
    {
        . = ALIGN(4);
    } > dcache_ram


    . =ORIGIN(video_ram);
    .video_ram_data ALIGN(4):
    {
        . = ALIGN(4);
    } > video_ram

    .video_ram_bss ALIGN(4) (NOLOAD):
    {
        . = ALIGN(4);
    } > video_ram
}

    text_begin = ADDR(.text);
    text_size = SIZEOF(.text);
    PROVIDE(text_size = SIZEOF(.text));

    bss_begin = ADDR(.bss);
    bss_size = SIZEOF(.bss);
    PROVIDE(bss_size = SIZEOF(.bss));

    _ram0_bss_vma = ADDR(.ram0_bss);
    _ram0_bss_size = SIZEOF(.ram0_bss);
    PROVIDE(ram0_bss_size = SIZEOF(.ram0_bss));

    _dcache_ram_bss_vma = ADDR(.dcache_ram_bss);
    _dcache_ram_bss_size = SIZEOF(.dcache_ram_bss);
    PROVIDE(dcache_ram_bss_size = SIZEOF(.dcache_ram_bss));

    _video_ram_bss_vma = ADDR(.video_ram_bss);
    _video_ram_bss_size = SIZEOF(.video_ram_bss);
    PROVIDE(video_ram_bss_size = SIZEOF(.video_ram_bss));
    data_vma = ADDR(.data);
    data_lma = text_begin + SIZEOF(.text);
    data_size = SIZEOF(.data);
    PROVIDE(data_size = SIZEOF(.data));

    _dcache_ram_data_vma = ADDR(.dcache_ram_data);
    _dcache_ram_data_lma = text_begin + SIZEOF(.text) + SIZEOF(.data);
    _dcache_ram_data_size = SIZEOF(.dcache_ram_data);
    PROVIDE(dcache_ram_data_size = SIZEOF(.dcache_ram_data));

    _video_ram_data_vma = ADDR(.video_ram_data);
    _video_ram_data_lma = text_begin + SIZEOF(.text) + SIZEOF(.data) + SIZEOF(.dcache_ram_data);
    _video_ram_data_size = SIZEOF(.video_ram_data);
    PROVIDE(video_ram_data_size = SIZEOF(.video_ram_data));

    _ram0_data_vma = ADDR(.ram0_data);
    _ram0_data_lma = text_begin + SIZEOF(.text) + SIZEOF(.data) + SIZEOF(.dcache_ram_data) + SIZEOF(.video_ram_data);
    _ram0_data_size = SIZEOF(.ram0_data);
    PROVIDE(ram0_data_size = SIZEOF(.ram0_data));



    bank_code_load_addr = _ram0_data_lma;
    common_code_run_addr = _ram0_data_vma;



EXTERN(
    lib_audio_server_version
    lib_system_version
    lib_btstack_version
    lib_btctler_version
    lib_btmesh_version
    lib_cfg_tool_version
    lib_common_version
    lib_crcm_version
    lib_cryto_toolbox_version
    lib_event_version
    lib_finsh_version
    lib_fs_version
    lib_driver_version
    lib_video_dec_version
    lib_video_rec_version
    lib_update_version
    lib_ui_font_version
    lib_wifi_version
    lib_wl83_rf_version
    lib_httpcli_version
    lib_airplay_version
    lib_aliyun_version
    lib_cjson_version
    lib_dcl_version
    lib_wpa_supplicant_version
    lib_device_vad_version
    lib_dlna_version
    lib_dui_version
    lib_echocloud_version
    lib_ftp_client_version
    lib_hsm_version
    lib_http_server_version
    lib_profile_version
    lib_iperf_version
    lib_jl_cloud_version
    lib_json_c_version
    lib_kcp_version
    lib_coap_version
    lib_duer_version
    lib_mpeg_version
    lib_lwip_2_2_0_version
    lib_mbedtls_3_4_0_version
    lib_mdns_version
    lib_mongoose_version
    lib_mqtt_version
    lib_network_download_version
    lib_rtp_version
    lib_net_server_version
    lib_media_server_version
    lib_stupid_ftpd_version
    lib_ftpserver_version
    lib_telecom_version
    lib_tencent_version
    lib_tmallgenie_version
    lib_tunnel_version
    lib_turing_version
    lib_uc_httpc_version
    lib_uip_version
    lib_websocket_version
    lib_wolfmqtt_version
    lib_wolfssl_version
    lib_wt_version
    lib_zliblite_version
    app_wifi_story_machine_version
    app_wifi_camera_version
    app_scan_box_version
    lib_font_version
    lib_res_version
    lib_ui_draw_version
    lib_ui_version
    lib_lvgl_v8_extend_version
    lib_lvgl_v9_extend_version
)

