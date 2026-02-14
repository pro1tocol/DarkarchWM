#!/bin/bash

if [ "$(id -u)" -ne 0 ]; then
    echo "Error: Must be run as root" >&2
    exit 1
fi
if [ ! -f /etc/default/libc-locales ]; then
    echo "ERROR：/etc/default/libc-locales no found" >&2
    exit 1
fi
read -p "ENTER HOSTNAME: " HOSTNAME
read -p "ENTER USERNAME: " USERNAME
read -p "ENTER USER HOME PATH(DEFAULT: /home/$USERNAME): " USER_HOME
USER_HOME=${USER_HOME:-/home/$USERNAME}
echo "$HOSTNAME" > /etc/hostname
sed -i 's/^#\s*\(en_US\.UTF-8 UTF-8\)/\1/' /etc/default/libc-locales
sed -i 's/^#\s*\(zh_CN\.GBK GBK\)/\1/' /etc/default/libc-locales
sed -i 's/^#\s*\(zh_CN\.UTF-8 UTF-8\)/\1/' /etc/default/libc-locales
sed -i 's/^#\s*\(zh_CN GB2312\)/\1/' /etc/default/libc-locales
xbps-reconfigure -f glibc-locales
cat > /etc/vconsole.conf << 'EOF'
KEYMAP=us
FONT=lat9u-16
EOF
useradd -m -d "$USER_HOME" -G wheel -s /bin/zsh "$USERNAME"
sed -i 's/^#\s*%wheel\s*ALL=(ALL:ALL)\s*ALL/%wheel ALL=(ALL:ALL) ALL/' /etc/sudoers
echo "DarkarchWM user setup done!"
