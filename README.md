![image](./png/DarkarchWM.png)

# <p align="center"> With i3wm on Fedora39 </p>

### <p align="center"> Installation: [English](./language/English.md) | [中文](./language/Chinese.md) </p>

## Instructions
- ##### This theme can be built in archlinux
- ##### The operating environment is extremely lightweight

## Build the Environment

  | Standards | x86_64/i686           | Dependence                                                                                        |
  | :--- | :--- | :--- |
  | Kernel    | linux 6.11           | systemd/lvm                                                                                       |
  | Lander    | lxdm                 | gtk3/breeze-gtk                                                                                  |
  | Manager   | i3/i3-blocks/i3lock-color              | gtk/gtk2/gtk3/gtk4/qt5ct/qt6ct                                                                    |
  | Displays  | X11                  | picom/rofi/amdgpu-dkms                                                                      |
  | Shell     | xterm                | bash/zsh/zsh-completions/zsh-syntax-highlighting/zsh-autosuggestions |
  | Files     | ranger/dolphin       | w3m/w3m-img/breeze-gtk                                                                       |
  | Fonts     | Microsoft/MesloLGMNerdFontMono | google-noto/SansMono/others                                                                                            |
  | Text      | vim/nano/code        | vim-molokai                                                                                       |
  | Input     | fcitx5               | simple-dark/fcitx5/fcitx5-qt/fcitx5-gtk/fcitx5-rime/xinput                  |
  | Sound     | alsa-utils             | libXxf86vm                                                                             |
  | Bluetooth | bluez                | bluetoothctl                                                                                      |
  | Light     | brightnessctl        | libinput                                                                                  |

## See

![image](./png/firefox.png)

## Support
- ##### Brightness adjustment
- ##### Volume adjustment
- ##### Touchpad
- ##### Window indicator
- ##### Program Launcher

## Shortcut keys

#### The "Move" keys
``` bash
# h : left
# j : down
# k : up
# l : right
```
##### Example
``` bash
# Win + Shift + 2 : move window to workspace 2
# Alt + l : move window to right
# Win + f : resize window to bigger
```

#### The "Alt" Keys
``` bash
# Alt + F1 :open terminal
# Alt + q :close window
# Alt + p :open screenkey
# Alt + c :open vscode
# Alt + f :open firefox
# Alt + s :open gsettings
# Alt + Shift + r :restart window manager
# Alt + Shift + q :exit window manager
# Alt + mouse_left :move window
# Alt + mouse_right :resize window
```

#### The "WIn/Option" Keys
``` bash
# Win + r : run command
# Win + d : run desktop application
# Win + q : window to lock
# Win + 1 : to workspace 1
# Win + 2 : to workspace 2
# Win + 3 : to workspace 3
# Win + Shift + 1 : take window to workspace 1
# Win + Shift + 2 : take window to workspace 2
# Win + Shift + 3 : take window to workspace 3
```
