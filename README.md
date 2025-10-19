![image](./png/DarkarchWM.png)

### <p align="right"> Option: [中文](./language/Chinese.md) </p>

##### <p align="right"> A simple and efficient desktop environment </p>

## Build the Environment

  | Standards | x86_64           | Dependence                                                                                        |
  | :--- | :--- | :--- |
  | Kernel    | linux 6.6           | runit                                                                                       |
  | Lander    | lxdm                 | breeze-dark                                                                                  |
  | Manager   | i3              | gtk/qt                                                                    |
  | Displays  | Xorg                  | picom/rofi/polybar                                                                      |
  | Shell     | kitty                | bash/zsh |
  | Files     | dolphin       | xfs                                                                       |
  | Fonts     | Microsoft/Meslo | copy                                                                                            |
  | Text      | vim        | vim-molokai                                                                                       |
  | Input     | fcitx5               | simple-dark                  |
  | Sound     | pulseaudio             | xf86audio                                                                             |
  | Bluetooth | bluez                | bluetoothctl                                                                                      |
  | Light     | bright        | libinput                                                                                  |

## See(Option)

![image](png/firefox.png)

## Support
- ##### Bright
- ##### Volume
- ##### Touchpad
- ##### Indicator
- ##### Launcher

---

## Installation
### Basic system(Based on [https://voidlinux.org/](https://voidlinux.org/))
#### Connet setup
``` bash
# Manually network
ip addr add 192.168.1.2/24 dev eth0
ip route add default via 192.168.1.2 dev eth0
echo 'nameserver 114.114.114.114' > /etc/resolv.conf
# You need check network
ping mirror.sjtu.edu.cn
# Configure remote and run service
vi /etc/ssh/sshd_config
sv status sshd
sv restart sshd
```
#### Install some tools on basic system
``` bash
# Change mirrors sources
mkdir -p /etc/xbps.d
cp /usr/share/xbps.d/*-repository-*.conf /etc/xbps.d/
sed -i 's|https://repo-default.voidlinux.org|https://mirror.sjtu.edu.cn/voidlinux|g' /etc/xbps.d/*-repository-*.conf
xbps-install -S && xbps-install -u xbps 
# Install tools
xbps-install -u vim fastfetch btop tzdata parted libstdc++-14.2.1+20250405_2
# You can search some tools in this command
# xbps-query -Rs nano
```
#### Create file system on storage
``` bash
# Create partition
parted /dev/nvme0n1
mklabel gpt
mkpart ESP 4096s 769M
mkpart primary 769M -1
set 1 boot on
p
# "q" to quit
# Format the boot
mkfs.fat -F 32 /dev/nvme0n1p1
# Format the file system and mount
pvcreate /dev/nvme0n1p2
vgcreate DarkarchWM /dev/nvme0n1p2
lvcreate -l +100%FREE DarkarchWM -n system
# Format the new LVM2 partition
mkfs.xfs /dev/mapper/DarkarchWM-system
# Mount file system
mount /dev/mapper/DarkarchWM-system /mnt
mount --mkdir /dev/nvme0n1p1 /mnt/boot
# Check the LVM partition status
lvs 
df -h
```
#### Install basic system

---

## Shortcut keys

#### The "Move" keys
``` bash
# h : left
# j : down
# k : up
# l : right
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

##### Example
``` bash
# Win + Shift + 2 : move window to workspace 2
# Alt + l : move window to right
# Win + f : resize window to bigger
```
