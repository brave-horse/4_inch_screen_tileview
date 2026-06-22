#ifndef LOCAL_AVI_H
#define LOCAL_AVI_H

/* 本地文件AVI播放器:音视频同步,播完回调on_end后自动清理 */
int  local_avi_play(const char *path,
                    void (*on_end)(void *priv),
                    void *priv);
void local_avi_stop(void);

#endif
