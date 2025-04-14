# 安装介绍

### 安装操作：将文件或目录进行覆盖
- [x] 必备
- [ ] 选配

| 源路径 | 目标路径 | 配置说明 | 注释 |
| :--- | :--- | :--- | :--- |
| ./etc/lxdm/lxdm.conf | /etc/lxdm/lxdm.conf | 登陆器访问配置文件 | &#9745; | 
| ./etc/pam.d/lxdm | /etc/pam.d/lxdm | 登录器访问用户权限设置| &#9745; |
| ./etc/systemd/logind.conf | /etc/systemd/logind.conf | 对笔记本电脑禁用盒盖熄屏设置 | ⬜️ |
| ./etc/environment_zh_CN | /etc/environment | 对fcitx输入法支持的环境变量 | &#9745; |
| ./etc/profile | /etc/profile | 对sbin/脚本目录支持的path | &#9745; |
| ./fcitx5/dark/ | ~/.local/share/fcitx5/themes/dark/ | 对Fcitx5输入法暗色主题的支持 | ⬜️ |
| ./fluxbox/backgrounds/ | ~/.fluxbox/backgrounds/ | 对Darkarch主题壁纸的支持 | &#9745; |
| ./fluxbox/usermenu/ | ~/.fluxbox/usermenu/ | 对分类自定义菜单的支持 | ⬜️ |
| ./fluxbox/init_zh_CN | ~/.fluxbox/init | 对Darkarch默认配置的支持 | &#9745; |
| ./fluxbox/keys | ~/.fluxbox/keys | 对Darkarch快捷键位的支持 | &#9745; |
| ./fluxbox/lastwallpaper | ~/.fluxbox/lastwallpaper | 使Darkarch默认壁纸配置生效 | &#9745; |
| ./fluxbox/menu_zh_CN | ~/.fluxbox/menu | 对Darkarch默认初始菜单的支持 | ⬜️ |
| ./usr/share/fluxbox/styles/* | /usr/share/fluxbox/styles/* | 对Darkarch默认主题的支持 | &#9745; |
| ./usr/share/fonts/* | /usr/share/fonts/* | 对Darkarch默认中文字体的支持 | &#9745; |
| ./usr/share/lxdm/themes/* | /usr/share/lxdm/themes/* | 对Darkarch默认登陆器主题的支持 | &#9745; |
| ./usr/share/X11/xorg.conf.d/* | /usr/share/X11/xorg.conf.d/* | 对屏幕的相关支持 | ⬜️ | 

