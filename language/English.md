# Introduction

### Description: Overwrite a file or directory
- [x] Necessary
- [ ] Matching

| Source files/folder path | Destination files/folder path | Configuration description | Annotation |
| :--- | :--- | :--- | :--- |
| ./etc/lxdm/lxdm.conf | /etc/lxdm/lxdm.conf | The config file of the LXDM | &#9745; | 
| ./etc/pam.d/lxdm | /etc/pam.d/lxdm | User access LXDM permission  | &#9745; |
| ./etc/systemd/logind.conf | /etc/systemd/logind.conf | Disable the laptop lid screen off | ⬜️ |
| ./etc/environment_zh_CN | /etc/environment | Supported for the fcitx input method | &#9745; |
| ./etc/profile | /etc/profile | Supported path for the '~/sbin/' directory | &#9745; |
| ./fcitx5/dark/ | ~/.local/share/fcitx5/themes/dark/ | Supported for the fcitx input method dark theme | ⬜️ |
| ./fluxbox/backgrounds/ | ~/.fluxbox/backgrounds/ | Support for Darkarch-themed wallpapers | &#9745; |
| ./fluxbox/usermenu/ | ~/.fluxbox/usermenu/ | Support for categorical custom menu | ⬜️ |
| ./fluxbox/init_zh_CN | ~/.fluxbox/init | Support for the Darkarch default configuration | &#9745; |
| ./fluxbox/keys | ~/.fluxbox/keys | Support for the Darkarch shortcut key | &#9745; |
| ./fluxbox/lastwallpaper | ~/.fluxbox/lastwallpaper | Darkarch wallpaper configuration takes effect | &#9745; |
| ./fluxbox/menu_zh_CN | ~/.fluxbox/menu | Support for the fluxbox default menu | ⬜️ |
| ./usr/share/fluxbox/styles/* | /usr/share/fluxbox/styles/* | Include Darkarch theme | &#9745; |
| ./usr/share/fonts/* | /usr/share/fonts/* | Include fonts | &#9745; |
| ./usr/share/lxdm/themes/* | /usr/share/lxdm/themes/* | Include LXDM theme | &#9745; |
| ./usr/share/X11/xorg.conf.d/* | /usr/share/X11/xorg.conf.d/* | Support for screen | ⬜️ | 
| ./zsh/ROOT/* | /root/* | zsh/vim/nano support | ⬜️ |
| ./zsh/USER/* | ~/* | Some User support | &#9745; |

#### Note: Please configure the fluxbox theme first
##### Before overwriting and installing, back up the original parameter configuration

