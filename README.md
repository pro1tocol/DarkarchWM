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
| Bright | Volume | Touchpad | Indicator | Launcher | Application | Virtual | Container |
| :--- | :--- | :--- | :--- | :--- |  :--- | :--- |

---

## Step 1:
#### Prerequisites for Installing DarkarchWM:

- 1.Download the Void Linux [ISO](https://voidlinux.org/)) image and successfully boot from a USB drive.
- 2.Configure [network](https://github.com/pro1tocol/DarkarchWM/blob/void/language/Internet.md) connectivity and test the connection within the USB Live Environment.
##### Change mirrors sources(Options)
``` shell
mkdir -p /etc/xbps.d && cp /usr/share/xbps.d/*-repository-*.conf /etc/xbps.d/
sed -i 's|https://repo-default.voidlinux.org|https://mirrors.tuna.tsinghua.edu.cn/voidlinux|g' /etc/xbps.d/*-repository-*.conf
```
##### Update sources and package manager
``` shell
xbps-install -S && xbps-install -uy xbps && xbps-install -uy vim parted btrfs-progs xfsprogs
```
- 3.Set up [storage](https://github.com/pro1tocol/DarkarchWM/blob/void/language/Storage.md) partitions in the USB Live Environment, ensuring at least a boot partition and a root filesystem partition are created.

---

## Step 2:
### Install basic system
``` bash
xbps-install -Sy -R https://mirrors.tuna.tsinghua.edu.cn/voidlinux/current -r /mnt base-container-full linux6.13-6.13.12_1 linux6.13-headers-6.13.12_1 base-devel gcc g++ make cmake autoconf automake libtool pkg-config
```
##### Chroot to system and setup
``` bash
# Generate List
xgenfstab -U /mnt > /mnt/etc/fstab && cat /mnt/etc/fstab
# Download DarkarchWM repository
mkdir -p /mnt/data/git && cd /mnt/data/git
git clone -b void --single-branch https://github.com/pro1tocol/DarkarchWM.git && mv DarkarchWM DarkarchWM_void && cd $HOME
```

---

## Step 3:
### Xchroot and build system
``` shell
xchroot /mnt /bin/bash
gcc --version && g++ --version && make --version
cd /data/git/DarkarchWM_void && make clean && make -j4
```
##### build
``` shell
chown +x run.sh setup.sh wakeup.sh
./run.sh && ./setup.sh && ./wakeup.sh
bootctl list
bin/sshd_build
chsh -s /bin/zsh
passwd root && passwd $(echo $USER)
```
##### Exit xchroot and reboot
``` shell
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

