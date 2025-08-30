# 安装介绍

## 安装操作：将文件或目录进行覆盖
- [x] 必备
- [ ] 选配

| 源路径                        | 目标路径                     | 配置说明                           | 注释    |
| :---------------------------- | :--------------------------- | :--------------------------------- | :------ |
| ./etc/lxdm/lxdm.conf          | /etc/lxdm/lxdm.conf          | 登陆器访问配置文件                 | &#9745; |
| ./etc/pam.d/lxdm              | /etc/pam.d/lxdm              | 登录器访问用户权限设置             | &#9745; |
| ./etc/systemd/logind.conf     | /etc/systemd/logind.conf     | 对笔记本电脑禁用盒盖熄屏设置       | ⬜️       |
| ./etc/environment_zh_CN       | /etc/environment             | 对fcitx输入法支持的环境变量        | &#9745; |
| ./etc/profile                 | /etc/profile                 | 对sbin/脚本目录支持的path          | &#9745; |
| ./usr/share/fonts/*           | /usr/share/fonts/*           | 对Darkarch默认中文字体的支持       | &#9745; |
| ./usr/share/lxdm/themes/*     | /usr/share/lxdm/themes/*     | 对Darkarch默认登陆器主题的支持     | &#9745; |
| ./usr/share/gtk*              | /usr/share/gtk*              | 对Darkarch启动应用的默认暗色支持   | &#9745; |
| ./usr/share/rofi              | /usr/share/rofi              | 对Darkarch应用启动器的主题支持     | &#9745; |
| ./usr/share/fcitx5            | /usr/share/fcitx5            | 对Darkarch输入法主题的支持         | &#9745; |
| ./usr/share/X11/xorg.conf.d/* | /usr/share/X11/xorg.conf.d/* | 对屏幕的相关支持                   | ⬜️       |
| ./zsh/ROOT/*                  | /root/*                      | 对zsh/vim/nano的相关支持           | ⬜️       |
| ./zsh/USER/*                  | ~/*                          | 对登录窗口管理器的用户提供配置支持 | &#9745; |

## 系统初始化
### 你需要在全新安装的系统环境下进行配置
``` shell
sudo systemctl stop cockpit.socket && sudo systemctl disable cockpit.socket
sudo systemctl stop cockpit.service && sudo systemctl disable cockpit.service # 禁用服务器网页前端
sudo vim /etc/ssh/sshd_config # 配置远程连接参数
sudo setenforce 0 # 临时关闭selinux
sudo systemctl restart sshd # 重启远程ssh服务
```
### 使用ssh协议连接服务器
``` shell
sudo vim /etc/selinux/config # 修改selinux参数
	SELINUX=disable # 永久关闭selinux端口标准控制
sudo systemctl stop firewalld.service && sudo systemctl disable firewalld.service # 禁用防火墙
```
#### 将文件拷贝至$HOME(root)下
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
#### 将文件拷贝至/etc/yum.repos.d路径下
``` shell
cd etc/yum.repos.d
sudo cp ./* /etc/yum.repos.d
sudo dnf clean all && sudo dnf makecache # 更新包管理器源环境
```
#### 卸载客户端不常用软件包
``` shell
sudo dnf remove -y cockpit systemd-resolved plymouth
sudo touch /etc/resolv.conf && echo "nameserver 223.5.5.5" > /etc/resolv.conf
sudo dnf install -y openssl NetworkManager-tui
```
#### 切换$SHELL环境并更新系统
``` shell
sudo dnf install -y zsh zsh-autosuggestions zsh-syntax-highlighting.noarch && sudo chsh -s /bin/zsh
sudo dnf update -y && reboot # 更新并重启系统
```
### 切换systemd-boot引导环境
``` shell
uname -srm && sudo dnf remove --oldinstallonly -y # 查看当前内核并卸载旧内核
cd /boot/efi
sudo dnf install -y systemd-boot-unsigned
sudo bootctl install # 安装systemd-boot引导
sudo vim loader/loader.conf # 编辑引导配置
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
sudo bootctl status # 查看引导状态
sudo bootctl list # 查看引导列表
reboot # 重启测试
```
---
### 修改主机名及字体
``` shell
# 修改主机名
vim /etc/hostname
# 复制字体包路径
cd /mnt/hgfs/DarkarchWM_fedora39
sudo cp -rf usr/share/fonts/Meslo /usr/share/fonts
sudo cp -rf usr/share/fonts/Windows-to-Linux-Fonts /usr/share/fonts
# 复制默认SHELL字型
sudo cp etc/vconsole.conf /etc
```
### 启用rpmfusion镜像源
``` shell
sudo dnf install -y https://mirrors.ustc.edu.cn/rpmfusion/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm https://mirrors.ustc.edu.cn/rpmfusion/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
sudo dnf clean all && sudo dnf makecache
```
### 建立管理员用户
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
sudo chown alarm:alarm -R $HOME/.vim $HOME/.vimrc $HOME/.nanorc $HOME/.zshrc $HOME/.xprofile $HOME/.Xresources $HOME/.i
```
#### 安装工具及显卡驱动
``` shell
sudo dnf install wget git curl tar zip unzip gzip fastfetch btop iotop iftop nano -y
# AMD核显设置(可选)
sudo dnf install -y https://repo.radeon.com/amdgpu-install/6.4.3/rhel/9.6/amdgpu-install-6.4.60403-1.el9.noarch.rpm
sudo vim /etc/yum.repos.d/amdgpu.repo
	# 将$amdgpudistro修改为9.6
sudo dnf makecache
sudo dnf install -y python3-setuptools python3-wheel gcc tcl
sudo usermod -a -G render,video $LOGNAME
sudo dnf install -y rocm
sudo usermod -aG render,video $USER
	# 退出后重新登录用户使用groups查看分组信息
```
#### 安装设备组件
``` shell
# 蓝牙、ntfs格式以及usb驱动
sudo dnf install -y bluez bluez-tools ntfs-3g usbutils bluedevil bluez-libs bluez-libs-devel
# X11环境下驱动显示器
sudo dnf install -y xorg-x11-server-devel xorg-x11-server-Xorg xorg-x11-font-utils xorg-x11-server-Xwayland xorg-x11-server-common xorg-x11-xinit xorg-x11-xauth xorg-x11-drv-libinput
# X11环境下驱动输入键位、触摸板、声音调节
sudo dnf install -y xinput libXxf86vm alsa-utils xorg-x11-drv-synaptics-devel
# 声卡驱动、背光驱动，频率功耗采集驱动
sudo dnf install -y xrdb brightnessctl xdotool acpi sysstat tk gnuplot
```
#### DarkarchWM必备组件部署
``` shell
sudo dnf install -y plasma-breeze kde-style-breeze breeze-icon-theme breeze-icon-theme-devel breeze-gtk.noarch
sudo dnf install -y breeze-gtk-common.noarch breeze-gtk-gtk2.noarch breeze-gtk-gtk3.noarch breeze-gtk-gtk4.noarch breeze-
sudo dnf install -y xterm dolphin gwenview mpv plasma-desktop plasma-pa plasma-nm plasma-thunderbolt
sudo dnf install -y kscreen powerdevil gnome-screenshot gnome-calculator
sudo dnf install -y kde-gtk-config qt5ct qt6ct adwaita-qt5 adwaita-qt6
sudo dnf install -y bc fzf less picom screenkey slop libappindicator-gtk3
# gnome全局深色
gsettings get org.gnome.desktop.interface color-scheme
gsettings set org.gnome.desktop.interface color-scheme 'prefer-dark'
# 禁用欢迎界面及avahi-daemon组件
sudo dnf remove -y plasma-welcome
sudo systemctl disable avahi-daemon.socket && sudo systemctl disable avahi-daemon.servic
```
#### 安装输入法
``` shell
sudo dnf install -y fcitx5 fcitx5-configtool fcitx5-gtk fcitx5-rime
```
#### DarkarchWM部署
``` shell
sudo dnf install -y lxdm i3 i3blocks rofi ranger w3m w3m-img imlib2 code putty firefox feh
cd /mnt/hgfs/DarkarchWM_fedora39/usr/share
sudo cp -rf ./gtk-* /usr/share
sudo cp -rf ./qt* /usr/share
sudo cp -rf ./lxdm/themes/BlackArch /usr/share/lxdm/themes
sudo cp ./rofi/themes/DarkarchWM.rasi /usr/share/rofi/themes
sudo cp ./X11/xorg.conf.d/* /usr/share/X11/xorg.conf.d
```
#### DarkarchWM配置还原
``` shell
cd etc
sudo cp environment /etc/environment
sudo cp lxdm/lxdm.conf /etc/lxdm
sudo cp pam.d/lxdm /etc/pam.d
sudo cp profile /etc
sudo cp profile.d/offbeep.sh.bak /etc/profile.d
sudo cp systemd/logind.conf /etc/systemd
```
#### DarkarchWM首次载入测试
``` shell
sudo systemctl start lxdm.service
```
### 还原管理员用户配置
``` shell
su alarm
cd zsh/USER/config
cp -rf ./* $HOME/.config
sudo systemctl restart lxdm.service
```
#### 禁用交换分区
``` shell
sudo swapon --show
sudo swapoff -a
sudo systemctl stop swap.target && sudo systemctl disable swap.target
sudo mv /usr/lib/systemd/system/swap.target /usr/lib/systemd/system/swap.target.bak
```
#### 默认图形化启动
``` shell
sudo systemctl get-default # 查看默认启动
	# multi-user.target 默认命令启动模式
sudo systemctl set-default graphical.target # 切换设置默认图形化启动
sudo systemctl enable lxdm.service
```

## [➡ 返回](/README.md)
