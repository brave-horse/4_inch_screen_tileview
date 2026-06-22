@echo off
cd /d e:\4_inch_screen_tileview\AC792_SDK_V3\sdk
echo === 提交中 ===
git commit -m "添加 SDK 源码和 UI 自定义文件"
echo === 切换到 main 分支 ===
git branch -M main
echo === 推送到远程仓库 ===
git push -u origin main
echo === 完成 ===
pause
