# custom 层构建脚本：按需求文档的 6 文件夹结构组织源码。
#   assert/  图片文件系统映射 + DDR 预解码
#   include/ 各模块头文件(只放 .h，加进 -I)
#   widget/  跨单屏的新增控件
#   screen/  单屏控件改动
#   rule/    跨界面 bug 控制(scr_guard / scr_noscroll ...)
#   event/   给 App 提供的接口
# 注：含 .c 的目录列进 CUSTOM_SRC_DIRS；空目录(widget/screen)wildcard 返回空，无害。

CUSTOM_SRC_DIRS := \
		$(PRJ_DIR)/custom \
		$(PRJ_DIR)/custom/assert \
		$(PRJ_DIR)/custom/rule \
		$(PRJ_DIR)/custom/screen \
		$(PRJ_DIR)/custom/widget \
		$(PRJ_DIR)/custom/event \
		$(PRJ_DIR)/class/Soc

CUSTOM_INC_DIRS := \
		$(PRJ_DIR)/custom/include \
		$(PRJ_DIR)/class/Inc \
		$(PRJ_DIR)/task/Inc

GEN_CSRCS += $(notdir $(foreach dir,$(CUSTOM_SRC_DIRS),$(wildcard $(dir)/*.c)))

DEPPATH += $(foreach dir,$(CUSTOM_SRC_DIRS),--dep-path $(dir))
VPATH += $(foreach dir,$(CUSTOM_SRC_DIRS),:$(dir))

CFLAGS += $(foreach dir,$(CUSTOM_INC_DIRS),"-I$(dir)")
