#include "img.h"

#include <stdio.h>
#include <string.h>

#define CUSTOM_IMG_EXT_ROOT "mnt/extflash/C"
#define CUSTOM_IMG_PACK_ROOT "mnt/sdfile/EXT_RESERVED/uipackres/ui"
#define CUSTOM_IMG_PATH_MAX_LEN 320
#define CUSTOM_IMG_PATH_BUF_COUNT 4


static char s_img_path_buf[CUSTOM_IMG_PATH_BUF_COUNT][CUSTOM_IMG_PATH_MAX_LEN];
static unsigned int s_img_path_buf_index;

static char *custom_img_next_path_buf(void)
{
    char *buf = s_img_path_buf[s_img_path_buf_index];

    s_img_path_buf_index++;
    if (s_img_path_buf_index >= CUSTOM_IMG_PATH_BUF_COUNT) {
        s_img_path_buf_index = 0;
    }

    buf[0] = '\0';
    return buf;
}

static int custom_img_is_full_path(const char *path)
{
    if (path == NULL || path[0] == '\0') {
        return 0;
    }

    if (path[0] == '/' || path[0] == '\\') {
        return 1;
    }

    if (strchr(path, ':') != NULL) {
        return 1;
    }

    if (strncmp(path, "mnt/", 4) == 0 || strncmp(path, "mnt\\", 4) == 0) {
        return 1;
    }

    return 0;
}

static void custom_img_make_path(char *buf, size_t buf_len, const char *root, const char *name)
{
    size_t root_len;
    int need_slash;

    if (buf == NULL || buf_len == 0) {
        return;
    }

    if (root == NULL) {
        root = "";
    }

    if (name == NULL) {
        name = "";
    }

    root_len = strlen(root);
    need_slash = (root_len > 0) &&
                 (root[root_len - 1] != '/') &&
                 (root[root_len - 1] != '\\') &&
                 (name[0] != '/') &&
                 (name[0] != '\\');

    if (need_slash) {
        snprintf(buf, buf_len, "%s/%s", root, name);
    } else {
        snprintf(buf, buf_len, "%s%s", root, name);
    }

    buf[buf_len - 1] = '\0';
}

static int custom_img_file_exists(const char *path)
{
    FILE *fp;

    if (path == NULL || path[0] == '\0') {
        return 0;
    }

    fp = fopen(path, "rb");
    if (fp == NULL) {
        return 0;
    }

    fclose(fp);
    return 1;
}

const char *custom_img_get_path(const char *name)
{
    char *path;

    if (name == NULL || name[0] == '\0') {
        return NULL;
    }

    if (custom_img_is_full_path(name)) {
        return name;
    }

    path = custom_img_next_path_buf();

    custom_img_make_path(path, CUSTOM_IMG_PATH_MAX_LEN, CUSTOM_IMG_EXT_ROOT, name);
    if (custom_img_file_exists(path)) {
        return path;
    }

    custom_img_make_path(path, CUSTOM_IMG_PATH_MAX_LEN, CUSTOM_IMG_PACK_ROOT, name);
    return path;
}

void custom_img_set_src(lv_obj_t *img, const char *name)
{
#if LV_USE_GUIDER_SIMULATOR
    (void)img;
    (void)name;
#else
    const char *path;

    if (img == NULL) {
        return;
    }

    path = custom_img_get_path(name);
    if (path == NULL) {
        return;
    }

    lv_img_set_src(img, path);
#endif
}

lv_obj_t *custom_img_create(lv_obj_t *parent, const char *name)
{
    lv_obj_t *img = lv_img_create(parent);

    custom_img_set_src(img, name);

    return img;
}
