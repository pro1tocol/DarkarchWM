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
| :--- | :--- | :--- | :--- | :--- |  :--- | :--- | :--- |

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
##### Run the build script
``` shell
chown +x run.sh setup.sh wakeup.sh copy.sh
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

## Step 4:
##### Configuration performed after the DarkarchWM reboot
### User base setup
``` bash
# $USER is the user you just created
su $USER
sudo bin/fcitx5_build
./copy.sh
# First launch test of DarkarchWM's LXDM
sudo ln -s /etc/sv/lxdm /etc/runit/runsvdir/default/lxdm
# Configuration fully copied after successful startup
cd /data/git/DarkarchWM/dotfiles/USER/config
cp -rf ./* $HOME/.config
```

---

### Installation complete
##### Some known issues: [check]()

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

