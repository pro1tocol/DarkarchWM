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

