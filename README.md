![image](./png/DarkarchWM.png)

### <p align="right"> Option: [中文](language/Chinese.md) </p>

##### <p align="right"> A simple and efficient desktop environment </p>

## Build the Environment

| Standards | Kernel | Displays | WM | Shell | Text |
| :--- | :--- | :--- | :--- | :--- | :--- |
| DarkarchWM_v4.21.03 | linux6.13-6.13.12_1 | Xorg/X11 | I3wm | zsh/bash | vim-molokai |
## See

![image](png/firefox.png)

## Support
| Bright | Volume | Touchpad | Indicator | Launcher |
| :--- | :--- | :--- | :--- | :--- |

---

## Installation
#### Prerequisites for Installing DarkarchWM:

- 1.Download the Void Linux [ISO](https://voidlinux.org/)) image and successfully boot from a USB drive.
- 2.Configure [network](https://github.com/pro1tocol/DarkarchWM/blob/void/language/Internet.md) connectivity and test the connection within the USB Live Environment.
- 3.Set up [storage](https://github.com/pro1tocol/DarkarchWM/blob/void/language/Storage.md) partitions in the USB Live Environment, ensuring at least a boot partition and a root filesystem partition are created.

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
``` bash
xbps-install -Sy -R https://mirror.sjtu.edu.cn/voidlinux/current -r /mnt base-system
```
##### Chroot to system and setup
``` bash
# Generate List
xgenfstab -U /mnt > /mnt/etc/fstab && cat /mnt/etc/fstab
xchroot /mnt /bin/bash
# Change mirrors sources again
mkdir -p /etc/xbps.d
cp /usr/share/xbps.d/*-repository-*.conf /etc/xbps.d/
sed -i 's|https://repo-default.voidlinux.org|https://mirror.sjtu.edu.cn/voidlinux|g' /etc/xbps.d/*-repository-*.conf
xbps-install -Su && xbps-install -u -y zsh zsh-autosuggestions zsh-completions zsh-history-substring-search zsh-syntax-highlighting wget git
# Download this repository
mkdir -p /data/git && cd /data/git
git clone https://github.com/pro1tocol/DarkarchWM.git && cd DarkarchWM
# Run this script
chmod +x Install_package && bash Install_package
```
##### System init
``` bash
vim /etc/hostname # You need change hostname
vim /etc/default/libc-locales # You need set language
xbps-reconfigure -f glibc-locales
# Set system display font
echo "KEYMAP=us" > /etc/vconsole.conf && echo "FONT=lat9u-16" >> /etc/vconsole.conf
# Create a user and grant permission
useradd -m -G wheel -s /bin/zsh alarm
EDITOR=vim visudo
```
##### Switch standard kernel
``` bash
xbps-query -Rs linux-lts
xbps-install -u -y linux-lts-6.6_1 linux-lts-headers-6.6_1
```
##### Setup system boot
``` bash
xbps-install -u -y systemd-boot
ls -l /boot # View linux kernel
cat /etc/fstab # View partition UUID
bootctl install
cd /boot
  echo 'default DarkarchWM.conf' > loader/loader.conf
  echo 'timeout 3' >> loader/loader.conf
  echo 'console-mode max' >> loader/loader.conf
  echo 'editor no' >> loader/loader.conf
cat loader/loader.conf
  echo 'title   DarkarchWM' > loader/entries/DarkarchWM.conf
  echo 'linux   /vmlinuz-6.6.111_1' >> loader/entries/DarkarchWM.conf
  echo 'initrd  /initramfs-6.6.111_1.img' >> loader/entries/DarkarchWM.conf
  echo 'options root=/dev/mapper/DarkarchWM-system ro rd.lvm.lv=DarkarchWM/system quiet' >> loader/entries/DarkarchWM.conf
cat loader/entries/DarkarchWM.conf
bootctl status # Check boot effective
```
##### Change repository permission and restore root dotfiles
``` bash
chown alarm:alarm -R /data
cd /data/git/DarkarchWM/dotfiles/ROOT && cp -rf ./* $HOME
mv $HOME/inputrc $HOME/.inputrc
mv $HOME/nanorc $HOME/.nanorc
mv $HOME/vim $HOME/.vim
mv $HOME/vimrc $HOME/.vimrc
mv $HOME/zshrc $HOME/.zshrc
# Configure remote again
vim /etc/ssh/sshd_config
```
##### Run tools at system startup
``` bash
echo 'nameserver 114.114.114.114' > /etc/resolv.conf
ln -s /etc/sv/dbus /etc/runit/runsvdir/default/dbus
ln -s /etc/sv/NetworkManager /etc/runit/runsvdir/default/NetworkManager
ln -s /etc/sv/bluetoothd /etc/runit/runsvdir/default/bluetoothd
ln -s /etc/sv/sshd /etc/runit/runsvdir/default/sshd
# virtual machine vmware tools
ln -s /etc/sv/vmtoolsd /etc/runit/runsvdir/default/vmtoolsd
ln -s /etc/sv/vmware-vmblock-fuse /etc/runit/runsvdir/default/vmware-vmblock-fuse
```
#### All done and restart the system
``` bash
chsh -s /bin/zsh
# Application system font
xbps-reconfigure -fa
# Set Password
passwd root
passwd alarm
# Quit and reboot
exit
umount -R /mnt
shutdown -r now
```
---

### Graphical_settings
#### User configuration
``` bash
# Enter the system after reboot
# Uninstall kernel
xbps-remove -R linux linux-headers
rm -v /boot/loader/entries/void-*
rm -v /boot/config-6.12.53_1
rm -v /boot/initramfs-6.12.53_1.img
rm -v /boot/vmlinuz-6.12.53_1
reboot # again
# Enter user configuration
su alarm
cd /data/git/DarkarchWM/dotfiles/USER
cp inputrc $HOME/.inputrc
cp nanorc $HOME/.nanorc
cp -r vim $HOME/.vim
cp vimrc $HOME/.vimrc
cp xprofile $HOME/.xprofile
cp Xresources $HOME/.Xresources
cp zshrc $HOME/.zshrc
sudo xbps-install -u -y fcitx5 fcitx5-configtool fcitx5-gtk fcitx5-rime fcitx5-gtk+2 fcitx5-gtk+3 fcitx5-gtk-devel fcitx5-gtk4 fcitx5-qt fcitx5-qt5 fcitx5-qt6
cd /data/git/DarkarchWM
sudo cp -rf system/usr/share/fonts/Windows-to-Linux-Fonts /usr/share/fonts && \
sudo cp -rf system/usr/share/fonts/Meslo /usr/share/fonts && \
sudo cp -rf system/usr/share/fcitx5/themes/DarkarchWM /usr/share/fcitx5/themes && \
sudo cp -rf system/usr/share/gtk-* /usr/share && \
sudo cp -rf system/usr/share/qt* /usr/share && \
sudo cp -rf system/usr/share/lxdm/themes/BlackArch /usr/share/lxdm/themes && \
sudo cp system/usr/share/rofi/themes/DarkarchWM.rasi /usr/share/rofi/themes && \
sudo cp system/usr/share/X11/xorg.conf.d/* /usr/share/X11/xorg.conf.d && \
sudo cp system/etc/environment /etc/environment && \
sudo cp system/etc/profile /etc/ && \
sudo cp system/etc/profile.d/offbeep.sh.bak /etc/profile.d && \
sudo cp system/etc/profile.d/append_path.sh /etc/profile.d && \
sudo cp system/etc/lxdm/lxdm.conf /etc/lxdm && \
sudo cp system/etc/pam.d/lxdm /etc/pam.d && \
sudo cp -r system/usr/share/themes/Breeze-Dark /usr/share/themes
```
#### DarkarchWM First run
``` bash
su root
ln -s /etc/sv/lxdm /etc/runit/runsvdir/default/lxdm
```
#### Continue user configuration
``` bash
su alarm
cd /data/git/DarkarchWM/dotfiles/USER/config
cp -rf ./* $HOME/.config
exit
xbps-reconfigure -fa
```
#### After entering DarkarchWM
#### Fix related functions
``` bash
# Fix backlight
sudo xbps-install -S brightnessctl
brightnessctl # record name
su alarm
groups  # check video
sudo usermod -aG video $USER
vim $HOME/.config/polybar/config.ini
reboot

# fix battery
ls -1 /sys/class/power_supply/
vim $HOME/.config/polybar/config.ini

# fix volume
xbps-install -u pulseaudio
sudo usermod -aG audio $(whoami)
mkdir -p /etc/udev/rules.d
sudo cp app/volume/91-pulseaudio-snd.rules /etc/udev/rules.d
sudo udevadm control --reload
sudo udevadm trigger --subsystem-match=sound
xinput list-props <number> # check device event number
sudo vim /usr/share/X11/xorg.conf.d/40-libinput.conf # change conf
ls -l /dev/snd/ # check devices
sudo cp -rf app/volume/udev-trigger-sound /etc/sv
sudo chmod +x /etc/sv/udev-trigger-sound/run
sudo ln -s /etc/sv/udev-trigger-sound /etc/runit/runsvdir/default
sudo reboot

# fix networks
ip addr # record name
vim $HOME/.config/polybar/config.ini

# fix firmware
sudo xbps-install -u linux-firmware

# fix timezone
ln -sf /usr/share/zoneinfo/Asia/Hong_Kong /etc/localtime
hwclock --systohc
```
### Installation complete
#### Below are the system shortcut keys

---

## Keys

#### The "Move" keys
``` bash
# h : left
# j : down
# k : up
# l : right
```
#### The "Alt" Keys
``` bash
# Alt + F1 : open terminal
# Alt + q : close window
# Alt + p : open screenkey
# Alt + c : open vscode
# Alt + f : open firefox
# Alt + s : open gsettings
# Alt + Shift + r : restart window manager
# Alt + Shift + q : exit window manager
# Alt + mouse_left : move window
# Alt + mouse_right : resize window
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
# Alt + Shift + l : move window to right
# Win + f : resize window to bigger
sudo vkpurge rm all #: ro remove all old kernel
```
