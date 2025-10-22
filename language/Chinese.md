
![image](/png/DarkarchWM.png)

### <p align="right"> Option: [English](/README.md) </p>

##### <p align="right"> 一个简单高效的桌面环境 </p>

## 构建环境

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

## 预览

![image](/png/firefox.png)

## 支持
- ##### 屏幕背光调节
- ##### 音量调节
- ##### 触摸板
- ##### 窗口指示器
- ##### 程序菜单

---

## 安装向导
### 默认系统(基于 [https://voidlinux.org/](https://voidlinux.org/))
#### 连接设置
``` bash
# 手动设置
ip addr add 192.168.1.2/24 dev eth0
ip route add default via 192.168.1.2 dev eth0
echo 'nameserver 114.114.114.114' > /etc/resolv.conf
# 你需要确认网络状态
ping mirror.sjtu.edu.cn
# 配置远程连接服务并运行
vi /etc/ssh/sshd_config
sv status sshd
sv restart sshd
```
#### 安装一些基础工具在默认系统中
``` bash
# 更换软件包镜像源
mkdir -p /etc/xbps.d
cp /usr/share/xbps.d/*-repository-*.conf /etc/xbps.d/
sed -i 's|https://repo-default.voidlinux.org|https://mirror.sjtu.edu.cn/voidlinux|g' /etc/xbps.d/*-repository-*.conf
xbps-install -S && xbps-install -u xbps 
# 安装工具
xbps-install -u vim fastfetch btop tzdata parted libstdc++-14.2.1+20250405_2
# 你可以使用这个命令搜索一些工具
# xbps-query -Rs nano
```
#### 创建文件系统在存储中
``` bash
# 创建分区
parted /dev/nvme0n1
mklabel gpt
mkpart ESP 4096s 769M
mkpart primary 769M -1
set 1 boot on
p
# "q" 可以退出
# 格式化引导
mkfs.fat -F 32 /dev/nvme0n1p1
# 格式化文件系统并挂载
pvcreate /dev/nvme0n1p2
vgcreate DarkarchWM /dev/nvme0n1p2
lvcreate -l +100%FREE DarkarchWM -n system
# 格式化新的LVM2分区
mkfs.xfs /dev/mapper/DarkarchWM-system
# 挂载文件系统
mount /dev/mapper/DarkarchWM-system /mnt
mount --mkdir /dev/nvme0n1p1 /mnt/boot
# 确认LVM分区状态
lvs 
df -h
```
#### 安装默认系统
``` bash
xbps-install -Sy -R https://mirror.sjtu.edu.cn/voidlinux/current -r /mnt base-system
```
##### 切换到系统环境并进行设置
``` bash
# 生成列表
xgenfstab -U /mnt > /mnt/etc/fstab && cat /mnt/etc/fstab
xchroot /mnt /bin/bash
# 再次切换软件包镜像源
mkdir -p /etc/xbps.d
cp /usr/share/xbps.d/*-repository-*.conf /etc/xbps.d/
sed -i 's|https://repo-default.voidlinux.org|https://mirror.sjtu.edu.cn/voidlinux|g' /etc/xbps.d/*-repository-*.conf
xbps-install -Su && xbps-install -u -y zsh zsh-autosuggestions zsh-completions zsh-history-substring-search zsh-syntax-highlighting wget git
# 下载这个仓库
mkdir -p /data/git && cd /data/git
git clone https://github.com/pro1tocol/DarkarchWM.git && cd DarkarchWM
# 运行这个软件包脚本
chmod +x Install_package && bash Install_package
```
##### 系统初始化
``` bash
vim /etc/hostname # 你需要切换主机名
vim /etc/default/libc-locales # 你需要设置语言
xbps-reconfigure -f glibc-locales
# 设置显示字体
echo "KEYMAP=us" > /etc/vconsole.conf && echo "FONT=lat9u-16" >> /etc/vconsole.conf
# 创建用户并赋予权限
useradd -m -G wheel -s /bin/zsh alarm
EDITOR=vim visudo
```
##### 切换标准内核
``` bash
xbps-query -Rs linux-lts
xbps-install -u -y linux-lts-6.6_1 linux-lts-headers-6.6_1
```
##### 设置系统引导
``` bash
xbps-install -u -y systemd-boot
ls -l /boot # 查看linux内核
cat /etc/fstab # 查看分区 UUID
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
bootctl status # 检查启动有效性
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
# 再次配置远程连接服务
vim /etc/ssh/sshd_config
```
##### 在系统启动时运行的工具
``` bash
echo 'nameserver 114.114.114.114' > /etc/resolv.conf
ln -s /etc/sv/dbus /etc/runit/runsvdir/default/dbus
ln -s /etc/sv/NetworkManager /etc/runit/runsvdir/default/NetworkManager
ln -s /etc/sv/bluetoothd /etc/runit/runsvdir/default/bluetoothd
ln -s /etc/sv/sshd /etc/runit/runsvdir/default/sshd
# 虚拟主机vmware工具
ln -s /etc/sv/vmtoolsd /etc/runit/runsvdir/default/vmtoolsd
ln -s /etc/sv/vmware-vmblock-fuse /etc/runit/runsvdir/default/vmware-vmblock-fuse
```
#### 全部完成并重启系统
``` bash
chsh -s /bin/zsh
# 应用系统字体
xbps-reconfigure -fa
# 设置密码
passwd root
passwd alarm
# 退出并重启
exit
umount -R /mnt
shutdown -r now
```
---

### 图形化设置
#### 用户配置
``` bash
# 在重启进入系统前
# 卸载内核
xbps-remove -R linux linux-headers
rm -v /boot/loader/entries/void-*
rm -v /boot/config-6.12.53_1
rm -v /boot/initramfs-6.12.53_1.img
rm -v /boot/vmlinuz-6.12.53_1
reboot # 再次运行
# 进入用户设置
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
#### DarkarchWM 首次运行
``` bash
su root
ln -s /etc/sv/lxdm /etc/runit/runsvdir/default/lxdm
```
#### 继续用户设置
``` bash
su alarm
cd /data/git/DarkarchWM/dotfiles/USER/config
cp -rf ./* $HOME/.config
exit
xbps-reconfigure -fa
```
#### 再次进入 DarkarchWM 前
#### 修复相关功能
``` bash
# 修复背光调节
sudo xbps-install -S brightnessctl
brightnessctl # 记录名称
su alarm
groups  # 确认有video组
sudo usermod -aG video $USER
vim $HOME/.config/polybar/config.ini
reboot

# 修复电池
ls -1 /sys/class/power_supply/
vim $HOME/.config/polybar/config.ini

# 修复声音
xbps-install -u pulseaudio
sudo usermod -aG audio $(whoami)
mkdir -p /etc/udev/rules.d
sudo cp app/volume/91-pulseaudio-snd.rules /etc/udev/rules.d
sudo udevadm control --reload
sudo udevadm trigger --subsystem-match=sound
xinput list-props <number> # 检查设备事件编号
sudo vim /usr/share/X11/xorg.conf.d/40-libinput.conf # 变更配置
sudo vim /usr/share/X11/xorg.conf.d/41-libinput.conf # 变更配置
ls -l /dev/snd/ # 确认设备
sudo cp -rf app/volume/udev-trigger-sound /etc/sv
sudo chmod +x /etc/sv/udev-trigger-sound/run
sudo ln -s /etc/sv/udev-trigger-sound /etc/runit/runsvdir/default
sudo reboot

# 修复网络
ip addr # 记录设备
vim $HOME/.config/polybar/config.ini

# 修复固件
sudo xbps-install -u linux-firmware

# 调整时区
ln -sf /usr/share/zoneinfo/Asia/Hong_Kong /etc/localtime
hwclock --systohc
```
### 安装完成
#### 以下是快捷键

---

## 键位

#### "移动" 键位
``` bash
# h : 向左
# j : 向下
# k : 向上
# l : 向右
```
#### "替代" 键位
``` bash
# Alt + F1 : 打开终端
# Alt + q : 关闭窗口
# Alt + p : 打开屏幕键位
# Alt + c : 打开代码编辑器
# Alt + f : 打开火狐浏览器
# Alt + s : 打开设置
# Alt + Shift + r : 刷新窗口
# Alt + Shift + q : 退出窗口管理器
# Alt + mouse_left : 移动窗口
# Alt + mouse_right : 调节窗口大小
```

#### "可选" 键位
``` bash
# Win + r : 运行命令选择器
# Win + d : 运行程序选择器
# Win + q : 锁定
# Win + 1 : 前往工作区 1
# Win + 2 : 前往工作区 2
# Win + 3 : 前往工作区 3
# Win + Shift + 1 : 窗口移动到工作区 1
# Win + Shift + 2 : 窗口移动到工作区 2
# Win + Shift + 3 : 窗口移动到工作区 3
```

##### 示例
``` bash
# Win + Shift + 2 : 窗口移动到工作区 2
# Alt + Shift + l : 向右移动窗口
# Win + f : 全屏窗口
```
