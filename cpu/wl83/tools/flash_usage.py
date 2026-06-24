#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Print FLASH usage after packing. Called at the end of download.bat.
# Data sources: app.lz4 / UIPACKRES / uboot.boot / cfg_tool.bin file sizes
#               + isd_config.ini partition limits.
import os, re

TOOLS = os.path.dirname(os.path.abspath(__file__))

def fsize(rel):
    p = os.path.join(TOOLS, rel)
    return os.path.getsize(p) if os.path.exists(p) else 0

def mb(n):
    return n / 1024.0 / 1024.0

FLASH = 8 * 1024 * 1024  # FLASH_SIZE = 8M (isd_config)

# read UIPACKRES_LEN from isd_config.ini
uipack_len = 4 * 1024 * 1024
try:
    with open(os.path.join(TOOLS, "isd_config.ini"), encoding="utf-8", errors="ignore") as f:
        for line in f:
            m = re.match(r"\s*UIPACKRES_LEN\s*=\s*(0x[0-9a-fA-F]+)", line)
            if m:
                uipack_len = int(m.group(1), 16)
                break
except Exception:
    pass

uboot  = fsize("uboot.boot")
app    = fsize("app.lz4")
cfg    = fsize("cfg_tool.bin")
uipack = fsize("packres/UIPACKRES")
small  = 32 * 1024 + 0x1000 + 0x1000     # VM 32K + BTIF 4K + USER 4K

app_region = uboot + app + cfg + small   # everything in the app region
used = app_region + uipack               # total real data in flash
free = FLASH - used

print("")
print("========== FLASH usage (total %.2f MB) ==========" % mb(FLASH))
print("  [app region]")
print("    uboot.boot    %6.2f MB" % mb(uboot))
print("    app.lz4       %6.2f MB   (code+const, incl wallpaper C-array)" % mb(app))
print("    cfg_tool.bin  %6.2f MB" % mb(cfg))
print("    VM+BTIF+USER  %6.2f MB" % mb(small))
print("  [UIPACKRES region]   limit %.2f MB" % mb(uipack_len))
print("    UIPACKRES     %6.2f MB   (UI images/avi)" % mb(uipack))
print("  --------------------------------------------")
print("    flash USED    %6.2f MB / %.2f MB  (%.0f%%)" % (mb(used), mb(FLASH), used * 100.0 / FLASH))
print("    flash FREE    %6.2f MB" % mb(free))
if uipack > uipack_len:
    print("    !! UIPACKRES %.2f MB EXCEEDS region limit %.2f MB -> pack will FAIL" % (mb(uipack), mb(uipack_len)))
if free < 0:
    print("    !! FLASH OVERFLOW by %.2f MB" % mb(-free))
print("=================================================")
print("")
