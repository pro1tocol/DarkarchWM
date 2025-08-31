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

## System init
### You need to configure it in a clean system environment
``` shell
sudo systemctl stop cockpit.socket && sudo systemctl disable cockpit.socket
sudo systemctl stop cockpit.service && sudo systemctl disable cockpit.service # stop web connect
sudo vim /etc/ssh/sshd_config
sudo setenforce 0 # disable selinux and reboot restart
sudo systemctl restart sshd
```
### The ssh connect
``` shell
sudo vim /etc/selinux/config # close selinux permanent
	SELINUX=disable
sudo systemctl stop firewalld.service && sudo systemctl disable firewalld.service # stop firewall
```
#### Uninstall packages
``` shell
sudo dnf remove -y cockpit systemd-resolved plymouth
sudo touch /etc/resolv.conf && echo "nameserver 223.5.5.5" > /etc/resolv.conf
```
#### Copy the file to $HOME(root)
``` shell
su root && whoami
cd zsh/ROOT/
sudo cp -rf ./* $HOME
mv $HOME/inputrc $HOME/.inputrc
mv $HOME/nanorc $HOME/.nanorc
mv $HOME/vimrc $HOME/.vimrc
mv $HOME/zshrc $HOME/.zshrc
mv $HOME/vim $HOME/.vim
```
#### Copy the file to path: /etc/yum.repos.d
``` shell
cd etc/yum.repos.d
sudo cp ./* /etc/yum.repos.d
sudo dnf clean all && sudo dnf makecache # update sources
sudo dnf install -y openssl NetworkManager-tui
```
#### Switch the $SHELL and update the system
``` shell
sudo dnf install -y zsh zsh-autosuggestions zsh-syntax-highlighting.noarch && sudo chsh -s /bin/zsh
sudo dnf update -y && reboot # update and restart
```
### Switch systemd-boot environment
``` shell
uname -srm && sudo dnf remove --oldinstallonly -y # uninstall old kernal
cd /boot/efi
sudo dnf install -y systemd-boot-unsigned
sudo bootctl install # install systemd-boot
sudo vim loader/loader.conf
	default DarkarchWM.conf
	timeout 3
    console-mode max
    editor no
sudo vim loader/entries/DarkarchWM.conf
    title   DarkarchWM
    linux   /vmlinuz-6.11.9-100.fc39.x86_64
    initrd  /initramfs-6.11.9-100.fc39.x86_64.img
	options /System.map-6.11.9-100.fc39.x86_64
    options root=/dev/mapper/fedora-root ro rd.lvm.lv=fedora/root rhgb quiet
sudo vim loader/entries/DarkarchWM-fallback.conf
    title   DarkarchWM(fallback)
    linux   /vmlinuz-0-rescue-e2cc20db2f514b85babdae307d927ebf
    initrd  /initramfs-0-rescue-e2cc20db2f514b85babdae307d927ebf.img
    options /System.map-6.11.9-100.fc39.x86_64
    options root=/dev/mapper/fedora-root ro rd.lvm.lv=fedora/root rhgb quiet
sudo cp /boot/initramfs-* /boot/efi
sudo cp /boot/vmlinuz-* /boot/efi
sudo cp /boot/System.map-* /boot/efi
sudo bootctl status # show boot status
sudo bootctl list # show boot list
reboot # test
```
---
### Renew device name
``` shell
# modify the hostname
vim /etc/hostname
# copy the fonts
cd /mnt/hgfs/DarkarchWM_fedora39
sudo cp -rf usr/share/fonts/Meslo /usr/share/fonts
sudo cp -rf usr/share/fonts/Windows-to-Linux-Fonts /usr/share/fonts
# copy the default SHELL font
sudo cp etc/vconsole.conf /etc
```
### Use rpmfusion sources
``` shell
sudo dnf install -y https://mirrors.ustc.edu.cn/rpmfusion/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm 
sudo dnf install -y https://mirrors.ustc.edu.cn/rpmfusion/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
# switch sources(options)
sudo sed -e 's|^metalink=|#metalink=|g' \
         -e 's|^#baseurl=http://download1.rpmfusion.org|baseurl=https://mirrors.ustc.edu.cn/rpmfusion|g' \
         -i.bak \
         /etc/yum.repos.d/rpmfusion*.repo
sudo dnf clean all && sudo dnf makecache
```
### Create an admin user
``` shell
useradd -m -G wheel -s /bin/zsh alarm && passwd alarm
cd /mnt/hgfs/DarkarchWM_fedora39/zsh/USER/
cp inputrc /home/alarm/.inputrc
cp nanorc /home/alarm/.nanorc
cp vimrc /home/alarm/.vimrc
cp -rf vim /home/alarm/.vim
cp xprofile /home/alarm/.xprofile
cp Xresources /home/alarm/.Xresources
cp zshrc /home/alarm/.zshrc
su alarm
sudo chown alarm:alarm -R $HOME/.vim $HOME/.vimrc $HOME/.nanorc $HOME/.zshrc
sudo chown alarm:alarm -R $HOME/.xprofile $HOME/.Xresources $HOME/.inputrc
```
#### Installation tools and graphics card drivers
``` shell
sudo dnf install wget git curl tar zip unzip gzip fastfetch btop iotop iftop nano -y
# AMD graphics settings(options)
sudo dnf install -y https://repo.radeon.com/amdgpu-install/6.4.3/rhel/9.6/amdgpu-install-6.4.60403-1.el9.noarch.rpm
sudo vim /etc/yum.repos.d/amdgpu.repo
	# modify the variable $amdgpudistro to 9.6
sudo dnf makecache
sudo dnf install -y python3-setuptools python3-wheel gcc tcl
sudo usermod -a -G render,video $LOGNAME
sudo dnf install -y rocm
sudo usermod -aG render,video $USER
	# after logging out, users log back in using groups to view group information

# Nvidia独显设置
echo -e "blacklist nouveau\noptions nouveau modeset=0" | sudo tee /etc/modprobe.d/blacklist-nouveau.conf
sudo dracut --force
sudo dnf config-manager --add-repo https://developer.download.nvidia.com/compute/cuda/repos/fedora39/x86_64/cuda-fedora39.repo
sudo dnf makecache
sudo dnf install -y kernel-headers kernel-devel tar bzip2 make automake gcc gcc-c++ pciutils elfutils-libelf-devel libglvnd-opengl libglvnd-glx libglvnd-devel acpid pkgconfig dkms
sudo dnf module list nvidia-driver # show all nvidia driver module
sudo dnf module install nvidia-driver:latest-dkms # install driver
sudo vim xorg.conf.d/10-nvidia.conf
	Option "PrimaryGPU" "no" # the 3D driver setup
cd /boot/efi
sudo cp /boot/initramfs-* /boot/efi
sudo cp /boot/vmlinuz-* /boot/efi
sudo cp /boot/System.map-* /boot/efi

# Intel核显设置
sudo dnf install -y intel-media-driver
sudo lsmod | grep i915
```
#### Install the equipment components
``` shell
# Bluetooth, NTFS format, and USB driver
sudo dnf install -y bluez bluez-tools ntfs-3g usbutils bluedevil bluez-libs bluez-libs-devel
# X11 Environment Drive Display
sudo dnf install -y xorg-x11-server-devel xorg-x11-server-Xorg xorg-x11-font-utils xorg-x11-server-Xwayland
sudo dnf install -y xorg-x11-server-common xorg-x11-xinit xorg-x11-xauth xorg-x11-drv-libinput
# X11 environment drives input keys, touchpad and sound
sudo dnf install -y xinput libXxf86vm alsa-utils xorg-x11-drv-synaptics-devel
# Sound drive, backlight driven, frequency power consumption acquisition driven
sudo dnf install -y xrdb brightnessctl xdotool acpi sysstat tk gnuplot lm_sensors
```
#### DarkarchWM required component
``` shell
sudo dnf install -y plasma-breeze kde-style-breeze breeze-icon-theme breeze-icon-theme-devel breeze-gtk.noarch
sudo dnf install -y breeze-gtk-common.noarch breeze-gtk-gtk2.noarch breeze-gtk-gtk3.noarch breeze-gtk-gtk4.noarch breeze-gtk-gtk4.noarch breeze-cursor-theme.noarch
sudo dnf install -y xterm dolphin gwenview mpv plasma-desktop plasma-pa plasma-nm plasma-thunderbolt
sudo dnf install -y kscreen powerdevil gnome-screenshot gnome-calculator
sudo dnf install -y kde-gtk-config qt5ct qt6ct adwaita-qt5 adwaita-qt6
sudo dnf install -y bc fzf less picom screenkey slop libappindicator-gtk3
# gnome default dark
gsettings get org.gnome.desktop.interface color-scheme
gsettings set org.gnome.desktop.interface color-scheme 'prefer-dark'
# disable plasma-wecom and avahi-daemon
sudo dnf remove -y plasma-welcome
sudo systemctl disable avahi-daemon.socket && sudo systemctl disable avahi-daemon.service
```
#### Install the input method
``` shell
sudo dnf install -y fcitx5 fcitx5-configtool fcitx5-gtk fcitx5-rime
```
#### DarkarchWM deployment
``` shell
sudo dnf install -y lxdm i3 i3blocks rofi ranger w3m w3m-img imlib2 code putty firefox feh
cd /mnt/hgfs/DarkarchWM_fedora39/usr/share
sudo cp -rf ./gtk-* /usr/share
sudo cp -rf ./qt* /usr/share
sudo cp -rf ./lxdm/themes/BlackArch /usr/share/lxdm/themes
sudo cp ./rofi/themes/DarkarchWM.rasi /usr/share/rofi/themes
sudo cp ./X11/xorg.conf.d/* /usr/share/X11/xorg.conf.d
```
#### DarkarchWM configuration restore
``` shell
cd etc
sudo cp environment /etc/environment
sudo cp lxdm/lxdm.conf /etc/lxdm
sudo cp pam.d/lxdm /etc/pam.d
sudo cp profile /etc
sudo cp profile.d/offbeep.sh.bak /etc/profile.d
sudo cp systemd/logind.conf /etc/systemd
```
#### DarkarchWM is loaded for testing
``` shell
sudo systemctl start lxdm.service
```
### Restore the admin user configuration
``` shell
su alarm
cd zsh/USER/config
cp -rf ./* $HOME/.config
sudo systemctl restart lxdm.service
```
#### Disable swap
``` shell
sudo swapon --show
sudo swapoff -a
sudo systemctl stop swap.target && sudo systemctl disable swap.target
sudo mv /usr/lib/systemd/system/swap.target /usr/lib/systemd/system/swap.target.bak
```
#### Default graphical startup
``` shell
sudo systemctl get-default 
	# multi-user.target
sudo systemctl set-default graphical.target # to switch grahical startup
sudo systemctl enable lxdm.service
```

## [➡ Back](/README.md)