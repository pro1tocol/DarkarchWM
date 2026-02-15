
![image](/png/DarkarchWM_2026.png)

### <p align="right"> Option: [English](/README.md) </p>

##### <p align="right"> 一个简单高效的桌面环境 </p>

## 构建环境

| 标准版本 | 内核 | 显示 | 窗口管理器 | 终端解释器 | 文本 | 应用管理 |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| DarkarchWM_v4.21.03 | linux6.13-6.13.12_1 | Xorg/X11 | I3wm | zsh/bash | vim-molokai | Flatpak |
## 预览

![image](/png/firefox.png)

## 支持
| 屏幕 | 音量 | 触摸板 | 指示器 | 菜单 | 图形应用 | 虚拟化 | 容器 | 网络 |
| :--- | :--- | :--- | :--- | :--- |  :--- | :--- | :--- | :--- |

---

## 快速开始

# 步骤 1:
#### 安装 DarkarchWM 的先决条件:

- 1.下载 Void Linux [ISO](https://voidlinux.org/) 镜像，并成功从 USB 驱动器启动。
- 2.配置[网络](https://github.com/pro1tocol/DarkarchWM/blob/void/language/Internet.md)连接，并在 USB Live 环境中测试连接。
##### 更换镜像源(可选)
``` shell
mkdir -p /etc/xbps.d && cp /usr/share/xbps.d/*-repository-*.conf /etc/xbps.d/
sed -i 's|https://repo-default.voidlinux.org|https://mirrors.tuna.tsinghua.edu.cn/voidlinux|g' /etc/xbps.d/*-repository-*.conf
```
##### 升级源及包管理工具
``` shell
xbps-install -S && xbps-install -uy xbps && xbps-install -uy vim parted btrfs-progs xfsprogs git
```
- 3.在 USB Live 环境中设置[存储](https://github.com/pro1tocol/DarkarchWM/blob/void/language/Storage.md)分区，确保至少创建一个启动分区和一个根文件系统分区。

---

# 步骤 2:
### 安装经典系统
``` bash
xbps-install -Sy -R https://mirrors.tuna.tsinghua.edu.cn/voidlinux/current -r /mnt base-container-full linux6.13-6.13.12_1 linux6.13-headers-6.13.12_1 base-devel gcc make cmake autoconf automake libtool pkg-config
```
##### 克隆仓库
``` bash
# 生成列表
xgenfstab -U /mnt > /mnt/etc/fstab && cat /mnt/etc/fstab
# 下载 DarkarchWM 仓库
mkdir -p /mnt/data/git && cd /mnt/data/git
git clone -b void --single-branch https://github.com/pro1tocol/DarkarchWM.git && mv DarkarchWM DarkarchWM_void && cd $HOME
```

---

# 步骤 3:
### 进入xchroot环境并构建操作系统
``` shell
xchroot /mnt /bin/bash
gcc --version && g++ --version && make --version
cd /data/git/DarkarchWM_void && make clean && make -j4
```
##### 运行构建脚本
``` shell
chmod +x run.sh setup.sh wakeup.sh copy.sh
mkdir -p /etc/xbps.d && cp /usr/share/xbps.d/*-repository-*.conf /etc/xbps.d/
sed -i 's|https://repo-default.voidlinux.org|https://mirrors.tuna.tsinghua.edu.cn/voidlinux|g' /etc/xbps.d/*-repository-*.conf
./run.sh && ./setup.sh && ./wakeup.sh
bootctl list
bin/sshd_build
chsh -s /bin/zsh
passwd root && passwd $(echo $USER)
```
##### 退出xchroot环境然后重启
``` shell
exit
umount -R /mnt
shutdown -r now
```

---

# 步骤 4:
##### DarkarchWM 重启后执行的配置
### 用户基本设置
``` bash
# $USER 是刚才你创建的
su $USER
sudo bin/fcitx5_build
./copy.sh
# 首次启动 LXDM 登陆器
sudo ln -s /etc/sv/lxdm /etc/runit/runsvdir/default/lxdm
# 启动成功后进行全部配置
cd /data/git/DarkarchWM_void/dotfiles/USER/config
cp -rf ./* $HOME/.config
```

---

### 安装完成
##### 一些已知的问题: [check](https://github.com/pro1tocol/DarkarchWM/blob/void/language/Issues.md)
##### 更多工具: [check](https://github.com/pro1tocol/DarkarchWM/blob/void/language/Tools.md)
