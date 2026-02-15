#!/bin/bash

cd /data/git/DarkarchWM_void/dotfiles/USER
cp inputrc $HOME/.inputrc
cp nanorc $HOME/.nanorc
cp -r vim $HOME/.vim
cp vimrc $HOME/.vimrc
cp xprofile $HOME/.xprofile
cp Xresources $HOME/.Xresources
cp zshrc $HOME/.zshrc
cd /data/git/DarkarchWM_void
sudo cp -rf system/usr/share/fonts/Windows /usr/share/fonts && \
sudo cp -rf system/usr/share/fonts/Meslo /usr/share/fonts && \
sudo cp -rf system/usr/share/fonts/UI-Fonts /usr/share/fonts && \
sudo cp -rf system/usr/share/fcitx5/themes/DarkarchWM /usr/share/fcitx5/themes && \
sudo cp -rf system/usr/share/lxdm/themes/BlackArch /usr/share/lxdm/themes && \
sudo cp -rf system/usr/share/themes/Breeze-Dark /usr/share/themes
sudo cp system/usr/share/rofi/themes/DarkarchWM.rasi /usr/share/rofi/themes && \
sudo cp system/usr/share/X11/xorg.conf.d/* /usr/share/X11/xorg.conf.d && \
sudo cp system/etc/profile.d/offbeep.sh.bak /etc/profile.d && \
sudo cp system/etc/profile.d/append_path.sh /etc/profile.d && \
sudo cp system/etc/profile /etc/ && \
sudo cp system/etc/environment /etc/environment && \
sudo cp system/etc/lxdm/lxdm.conf /etc/lxdm && \
sudo cp system/etc/pam.d/lxdm /etc/pam.d
