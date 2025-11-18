#!/bin/bash

pacstrap /mnt zsh zsh-completions zsh-syntax-highlighting zsh-history-substring-search zsh-autosuggestions && \
pacstrap /mnt vim nano curl wget git gzip unzip zip tar iftop btop btrfs-progs xfsprogs xfsdump util-linux && \
pacstrap /mnt dhcpcd iwd openssh openssl networkmanager net-tools lvm2 efibootmgr e2fsprogs less bc fzf && \
pacstrap /mnt bluez bluez-utils bluedevil bluez-obex ntfs-3g usbutils xdotool acpi sysstat tk gnuplot && \
pacstrap /mnt breeze-gtk breeze-plymouth systemsettings kscreen powerdevil gnome-screenshot gnome-calculator && \
pacstrap /mnt alsa-utils pipewire-pulse brightnessctl xterm kitty dolphin gwenview mpv gnome-connections && \
pacstrap /mnt xorg-xbacklight xorg-xrdb xorg-xkbcomp xorg-xmodmap xorg-xdpyinfo plasma-pa plasma-nm && \
pacstrap /mnt sof-firmware xf86-input-synaptics xf86-input-evdev xf86-input-void plasma-thunderbolt && \
pacstrap /mnt fastfetch polybar kde-gtk-config qt5ct qt6ct breeze breeze-icons flatpak && \
pacstrap /mnt picom screenkey slop libappindicator-gtk3 lxdm i3-wm rofi ranger w3m && \
pacstrap /mnt imlib2 vscode putty firefox feh imagemagick vim-molokai xfsprogs xfsdump
