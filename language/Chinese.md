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

## 安装在Archlinux
### 建立系统存储
``` shell
parted /dev/nvme0n1
mklabel gpt
mkpart ESP 4096s 769M
mkpart primary 769M -1
set 1 boot on
# 查看分区状态
lsblk
fdisk -l
```
### 格式化存储
``` shell
mkfs.fat -F32 /dev/nvme0n1p1
```
### 创建LVM分区并进行挂载
``` shell
pvcreate /dev/nvme0n1p2
vgcreate linux /dev/nvme0n1p2
lvcreate -l +100%FREE linux -n root
# 格式化新建的lvm2分区
mkfs.btrfs /dev/mapper/linux-root
lvs # 查看lvm分区情况
mount /dev/mapper/linux-root /mnt
mkdir -p /mnt/boot
mount /dev/nvme0n1p1 /mnt/boot
df -h # 查看分区挂载情况
```
## 系统初始化
### 安装基础系统
``` shell
# 环境需要提前配置互联网络
echo 'Server = https://mirrors.ustc.edu.cn/archlinux/$repo/os/$arch' > /etc/pacman.d/mirrorlist
sudo pacman-key --init && sudo pacman-key --populate archlinux
sudo pacman -Syy && sudo pacman -S archlinux-keyring
pacstrap /mnt base base-devel linux-lts linux-lts-headers linux-firmware intel-ucode/amd-ucode # 测试部署
bash language/Install
genfstab -U /mnt > /mnt/etc/fstab # 将分区写入fstab
cat /mnt/etc/fstab # 查看分区写入状态
```
### 初始化配置
``` shell
arch-chroot /mnt
vim /etc/hostname # 修改主机名
# 修改系统字体(激活中文)
vim /etc/locale.gen
    en_US.UTF-8 UTF-8
    zh_CN.UTF-8 UTF-8
# 将默认语言写入配置
locale-gen
echo 'LANG=en_US.UTF-8'  > /etc/locale.conf
# 修复字体
echo "KEYMAP=us" > /etc/vconsole.conf
echo "FONT=lat9u-16" >> /etc/vconsole.conf
mkinitcpio -P # 创建内核文件
```
#### 克隆项目
``` shell
mkdir -p /data/git && cd /data/git
git clone -b lts --single-branch https://github.com/pro1tocol/DarkarchWM.git
mv DarkarchWM DarkarchWM_lts && cd DarkarchWM_lts && pwd
```
#### 更新超级用户及更新内核文件(可选)
``` shell
passwd root # 修改超级用户密码
cd zsh/ROOT/
sudo cp -rf ./* $HOME
mv $HOME/inputrc $HOME/.inputrc
mv $HOME/nanorc $HOME/.nanorc
mv $HOME/vimrc $HOME/.vimrc
mv $HOME/zshrc $HOME/.zshrc
echo $SHELL # 修改默认shell环境
    # /bin/bash
chsh -s /bin/zsh # 切换为zsh
# 更新内核文件
vim /etc/mkinitcpio.conf
# ...
	HOOKS=(base systemd udev autodetect microcode modconf kms keyboard keymap consolefont block lvm2 filesystems fsck)
# ...
mkinitcpio -p linux-lts # 更新
```
#### systemd-boot引导启动配置
``` shell
bootctl status # 查看引导启动方式
ls -l /boot # 查看Linux内核文件
cat /etc/fstab # 查看分区(记录UUID)
```
### 切换systemd-boot引导环境
``` shell
bootctl install
cd /boot
sudo vim loader/loader.conf # 编辑引导配置
	default DarkarchWM.conf
	timeout 3
    console-mode max
    editor no
sudo vim loader/entries/DarkarchWM.conf
    title   DarkarchWM
    linux   /vmlinuz-linux-lts
    initrd  /intel-ucode.img
    initrd  /initramfs-linux-lts.img
    options root=/dev/mapper/linux-root ro rd.lvm.lv=linux/root quiet
sudo vim loader/entries/DarkarchWM-fallback.conf
    title   DarkarchWM(fallback)
    linux   /vmlinuz-linux-lts
    initrd  /intel-ucode.img
    initrd  /initramfs-linux-lts-fallback.img
    options root=/dev/mapper/linux-root ro rd.lvm.lv=linux/root quiet
bootctl status
bootctl list # 验证引导
exit
umount -R /mnt && reboot # 重启操作系统验证生效
```
---
### 更新源及密钥
``` shell
# 添加archlinux镜像源
vim /etc/pacman.conf
    [multilib]
    #Inclu...
    [archlinuxcn]
    Server = https://mirrors.ustc.edu.cn/archlinuxcn/$arch
# 更新密钥
pacman-key --init && pacman-key --populate archlinux
pacman -Syy && pacman -Syu
pacman -S archlinux-keyring archlinuxcn-keyring && pacman -S yay
```
### 创建管理员用户
``` shell
useradd -m -G wheel -s /bin/zsh alarm # 创建用户
passwd alarm
# 修改权限
EDITOR=vim visudo
%wheel ALL=(ALL: ALL) ALL
# 调整路径权限
sudo chown alarm:alarm -R /data # 允许管理员用户调整项目
cd /data/git/DarkarchWM_lts/zsh/USER
su alarm
cp inputrc /home/alarm/.inputrc
cp nanorc /home/alarm/.nanorc
cp vimrc /home/alarm/.vimrc
cp xprofile /home/alarm/.xprofile
cp Xresources /home/alarm/.Xresources
cp zshrc /home/alarm/.zshrc
exit
```
### 修复内核模组
``` shell
cd /data/git/DarkarchWM_lts
su alarm
cp -rf zsh/USER/cache/* $HOME/.cache/yay
cd $HOME/.cache/yay
tar -xJvf aic94xx-firmware.tar.xz && \
tar -xJvf ast-firmware.tar.xz && \
tar -xJvf mkinitcpio-firmware.tar.xz && \
tar -xJvf upd72020x-fw.tar.xz && \
tar -xJvf wd719x-firmware.tar.xz
yay -S aic94xx-firmware ast-firmware mkinitcpio-firmware upd72020x-fw wd719x-firmware # 安装模组
yay -S fcitx5 fcitx5-configtool fcitx5-gtk fcitx5-rime # 安装输入法
exit
mkinitcpio -p linux-lts # 修复模组
```
#### 安装工具及显卡驱动
``` shell
su alarm
# intel
yay -S mesa lib32-mesa vulkan-intel lib32-vulkan-intel # 默认驱动已保证基础运行

# amd
yay -S mesa lib32-mesa xf86-video-amdgpu vulkan-radeon  lib32-vulkan-radeon libva-mesa-driver

# Nvidia-open
yay -S nvidia-open-lts nvidia-settings lib32-nvidia-utils nvidia-utils
# 禁用kms模组(可选)
# sudo vim /etc/mkinitcpio.conf

# Nvidia
yay -S nvidia-lts nvidia-settings lib32-nvidia-utils nvidia-utils
```
#### DarkarchWM图形化组件部署
``` shell
# gnome全局深色
gsettings set org.gnome.desktop.interface color-scheme 'prefer-dark' && \ 
gsettings get org.gnome.desktop.interface color-scheme
# 安装字体
su root
sudo cp -rf usr/share/fonts/Windows-to-Linux-Fonts /usr/share/fonts && \
sudo cp -rf usr/share/fonts/Meslo /usr/share/fonts && \
sudo cp -rf usr/share/fcitx5/themes/DarkarchWM /usr/share/fcitx5/themes && \
sudo cp -rf usr/share/gtk-* /usr/share && \
sudo cp -rf usr/share/qt* /usr/share && \
sudo cp -rf usr/share/lxdm/themes/BlackArch /usr/share/lxdm/themes && \
sudo cp usr/share/rofi/themes/DarkarchWM.rasi /usr/share/rofi/themes && \
sudo cp usr/share/X11/xorg.conf.d/* /usr/share/X11/xorg.conf.d && \
sudo cp etc/environment /etc/environment && \
sudo cp etc/lxdm/lxdm.conf /etc/lxdm && \
sudo cp etc/pam.d/lxdm /etc/pam.d && \
sudo cp etc/profile /etc && \
sudo cp etc/profile.d/offbeep.sh.bak /etc/profile.d && \
sudo cp etc/profile.d/append_path.sh /etc/profile.d && \
sudo cp etc/systemd/logind.conf /etc/systemd && \
mkinitcpio -p linux-lts && reboot
```
#### DarkarchWM首次载入测试
``` shell
sudo systemctl start lxdm.service
```
---
### 还原管理员用户配置
``` shell
su alarm
cd /data/git/DarkarchWM_lts/zsh/USER/config
cp -rf ./* $HOME/.config
yay -S docker docker-compose vmware-keymaps
yay -S vmware-workstation zerotier-one
su root
mkinitcpio -p linux-lts
```
#### 安装全部应用(可选)
``` shell
yay -S wps-office-cn wps-office-mui-zh-cn wechat netease-cloud-music
yay -S nvtop intel-gpu-tools obs-studio ollama-cuda notion-app-electron
yay -S nmap wireshark-qt wireshark-cli reaver bully cowpatty macchanger hashcat hcxdumptool hcxtools
yay -S pyrit pixiewps wifite john wireshark-cli ruby
yay -S qt6ct-kde
```

## [➡ 返回](/README.md)