# Installation

### Description: Overwrite a file or directory
- [x] Necessary
- [ ] Matching

| Source files/folder path      | Destination files/folder path | Configuration description                  | Annotation |
| :---------------------------- | :---------------------------- | :----------------------------------------- | :--------- |
| ./etc/lxdm/lxdm.conf          | /etc/lxdm/lxdm.conf           | The config file of the LXDM                | &#9745;    |
| ./etc/pam.d/lxdm              | /etc/pam.d/lxdm               | User access LXDM permission                | &#9745;    |
| ./etc/systemd/logind.conf     | /etc/systemd/logind.conf      | Disable the laptop lid screen off          | ⬜️          |
| ./etc/environment_zh_CN       | /etc/environment              | Supported for the fcitx input method       | &#9745;    |
| ./etc/profile                 | /etc/profile                  | Supported path for the '~/sbin/' directory | &#9745;    |
| ./usr/share/fonts/*           | /usr/share/fonts/*            | Include fonts                              | &#9745;    |
| ./usr/share/lxdm/themes/*     | /usr/share/lxdm/themes/*      | Include LXDM theme                         | &#9745;    |
| ./usr/share/gtk*              | /usr/share/gtk*               | Include GTK support                        | &#9745;    |
| ./usr/share/rofi              | /usr/share/rofi               | Applications startup support               | &#9745;    |
| ./usr/share/fcitx5            | /usr/share/fcitx5             | Input methud support                       | &#9745;    |
| ./usr/share/X11/xorg.conf.d/* | /usr/share/X11/xorg.conf.d/*  | Support for screen                         | ⬜️          |
| ./zsh/ROOT/*                  | /root/*                       | zsh/vim/nano support                       | ⬜️          |
| ./zsh/USER/*                  | ~/*                           | Some User's config support                 | &#9745;    |

#### Note: Please configure the i3 theme first
##### The i3 window manager config in path: `$HOME/.config/i3*`, copy `./zsh/USER/config/i3*` as well 
##### Before overwriting and installing, back up the original parameter configuration

## [➡ Back](/README.md)
