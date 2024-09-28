#!/bin/bash

# 启动中文输入法
fcitx5 -d

# 设置分辨率
/usr/bin/xrandr --output HDMI-A-0 --mode 2560x1440 --rate 60 &

# 壁纸
/usr/bin/feh --bg-fill --randomize /home/laoliu/myconfig/dwm/wallpaper &

# 配置透明
picom -b

