# 主题安装介绍

### 安装操作：将文件或目录进行覆盖
- [x] 必备
- [ ] 选配

| 源路径 | 目标路径 | 配置说明 | 注 |
| :--- | :--- | :--- | :--- |
| ./etc/lxdm/lxdm.conf | /etc/lxdm/lxdm.conf | 登陆器访问配置文件 | <ul><li>- [x]</li></ul> | 
| ./etc/pam.d/lxdm | /etc/pam.d/lxdm | 登录器访问用户权限设置| <ul><li>- [x]</li></ul> |
| ./etc/systemd/logind.conf | /etc/systemd/logind.conf | 针对笔记本电脑禁用盒盖熄屏设置 | <ul><li>- [ ]</li></ul> |
| ./etc/environment_zh_CN | /etc/environment | 增加对fcitx输入法支持的环境变量 | <ul><li>- [x]</li></ul> |
| ./etc/profile | /etc/profile | 增加对sbin/脚本目录支持的path | <ul><li>- [x]</li></ul> |
| ./fcitx5/dark/ | /home/$USER/.local/share/fcitx5/themes/dark/ | 增加Fcitx5输入法主题Darkarch的支持 | <ul><li>- [ ]</li></ul> |
| ./fluxbox/backgrounds/ | /home/$USER/.fluxbox/backgrounds/ | 增加对Darkarch主题壁纸的支持 | <ul><li>- [x]</li></ul> |
| ./fluxbox/usermenu/ | /home/$USER/.fluxbox/usermenu/ | 增加对Darkarch用户分类自定义菜单的支持 | <ul><li>- [ ]</li></ul> |
| ./fluxbox/init_zh_CN | /home/$USER/.fluxbox/init | 增加Darkarch默认配置的支持 | <ul><li>- [x]</li></ul> |
| ./fluxbox/keys | /home/$USER/.fluxbox/keys | 增加对Darkarch快捷键位的支持 | <ul><li>- [x]</li></ul> |
| ./fluxbox/lastwallpaper | /home/$USER/.fluxbox/lastwallpaper | 使Darkarch默认壁纸配置生效 | &#9745; |
| ./fluxbox/menu_zh_CN | /home/$USER/.fluxbox/menu | 增加对Darkarch默认初始菜单的支持 | &#x2610; |

