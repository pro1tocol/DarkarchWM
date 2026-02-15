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
chown $USERNAME:$USERNAME -R /data
cd /data/git/DarkarchWM_void/dotfiles/ROOT && cp -rf ./* $HOME
mv $HOME/inputrc $HOME/.inputrc
mv $HOME/nanorc $HOME/.nanorc
mv $HOME/vim $HOME/.vim
mv $HOME/vimrc $HOME/.vimrc
mv $HOME/zshrc $HOME/.zshrc
ln -s /etc/sv/dbus /etc/runit/runsvdir/default/dbus
ln -s /etc/sv/NetworkManager /etc/runit/runsvdir/default/NetworkManager
ln -s /etc/sv/bluetoothd /etc/runit/runsvdir/default/bluetoothd
ln -s /etc/sv/sshd /etc/runit/runsvdir/default/sshd
echo "DarkarchWM setup done!"
