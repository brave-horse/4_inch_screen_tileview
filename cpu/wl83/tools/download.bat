








@echo off

@echo *********************************************************************
@echo AC792N SDK
@echo *********************************************************************
@echo %date%

cd /d %~dp0

echo %*


set OBJDUMP=C:\JL\pi32\bin\llvm-objdump.exe
set OBJCOPY=C:\JL\pi32\bin\llvm-objcopy.exe
set ELFFILE=sdk.elf
set LZ4_PACKET=lz4_packet.exe

REM %OBJDUMP% -D -address-mask=0x1ffffff -print-dbg %ELFFILE% > sdk.lst
%OBJCOPY% -O binary -j .text %ELFFILE% text.bin
%OBJCOPY% -O binary -j .data %ELFFILE% data.bin
%OBJCOPY% -O binary -j .ram0_data %ELFFILE% ram0_data.bin
%OBJCOPY% -O binary -j .dcache_ram_data %ELFFILE% dcache_ram_data.bin
%OBJCOPY% -O binary -j .video_ram_data %ELFFILE% video_ram_data.bin
%OBJCOPY% -O binary -j .dlog_data %ELFFILE% dlog.bin

%OBJDUMP% -section-headers -address-mask=0x1ffffff %ELFFILE%
%OBJDUMP% -t %ELFFILE% > symbol_tbl.txt





copy /b text.bin+data.bin+dcache_ram_data.bin+video_ram_data.bin+ram0_data.bin app.bin
set UI_RES_PREFIX=demo_
packres\packres.exe -n ui -o packres/UIPACKRES %UI_RES_PREFIX%ui_res
REM set KEY_FILE=-key JL_792N-XXXX.key
REM set KEY_FILE=-key1 JL_792N-XXXX.key1 -mkey JL_792N-XXXX.mkey

set CFG_FILE=cfg

REM 添加新参数-update_files说明
REM 1/normal就是普通的文件目录结构
REM 2/embedded就是每个文件数据前都会有一个头

REM 只生成code + res升级文件
REM -update_files normal
REM 生成的文件名字为：db_update_files_data.bin

REM 只生成预留区资源升级文件
REM -update_files embedded_only $(files) ,其中$(files)为需要添加的资源文件
REM 生成的文件名字为：db_update_files_data.bin

REM 生成code + res + 预留区资源升级文件
REM -update_files embedded $(files) ,其中$(files)为需要添加的资源文件
REM 生成的文件名字为：db_update_files_data.bin
REM 如果不压缩uboot, 需要删除tools目录下的rom.image
REM 先暂时删掉rom.image，会导致不压缩uboot时代码解压出错，后面有需要再加回去
set run_addr=0x103000
set load_addr=0x10B000
set mask_addr=0xf0000
del rom.image
uboot_lz4.exe app.bin app.lz4 %run_addr% %load_addr% rom.image %mask_addr%
REM @@@@@@@@@@@@@@@

isd_download.exe isd_config.ini -gen2 -tonorflash -dev wl83 -boot 0x103000 -div1 -wait 300 -uboot uboot.boot -app app.lz4 cfg_tool.bin -res %AUDIO_RES% %UI_RES% %CFG_FILE% %MEDIA_RES% -reboot 50 %KEY_FILE% %UPDATE_FILES% -extend-bin %EXFLASH_FILES% -output-ufw jl_isd.ufw %FORMAT%



@REM 常用命令说明
@rem -format vm
@rem -format all
@rem -reboot 500

echo %errorlevel%

@REM 删除临时文件
if exist *.mp3 del *.mp3
if exist *.PIX del *.PIX
if exist *.TAB del *.TAB
if exist *.res del *.res
if exist *.sty del *.sty
@REM 生成固件升级文件
fw_add.exe -noenc -fw jl_isd.fw -add ota.bin -type 100 -out jl_isd.fw


@REM 添加配置脚本的版本信息到 FW 文件中
fw_add.exe -noenc -fw jl_isd.fw -add script.ver -out jl_isd.fw

@REM 添加SDK softwate信道到 FW 文件中
fw_add.exe -noenc -fw jl_isd.fw -add version.ver -out jl_isd.fw

ufw_maker.exe -fw_to_ufw jl_isd.fw


@REM 生成配置文件升级文件
rem ufw_maker.exe -chip AC792N %ADD_KEY% -output config.ufw -res bt_cfg.cfg

ping /n 2 127.1>null
IF EXIST null del null

::del app.bin
del video_ram_data.bin
del dcache_ram_data.bin
del data.bin
del ram0_data.bin
del text.bin
::退出当前批处理加返回值(0),才能多个批处理嵌套调用批处理
exit /b 0
