# Fix issues
#### Fix battery collection
``` shell
ls -1 /sys/class/power_supply # Check BAT number
vim $HOME/.config/polybar/config.ini # Replace BAT number
```
#### Fix backlight
``` shell
sudo xbps-install -Sy brightnessctl
brightnessctl # Check backlight number
su $USER
groups  # Check groups
sudo usermod -aG video $USER
vim $HOME/.config/polybar/config.ini # Replace backlight number
reboot
```
#### Fix volume
``` shell
sudo xbps-install -uy pulseaudio
su $USER
sudo usermod -aG audio $(whoami)
```
#### Fix firmware
``` shell
sudo xbps-install -uy linux-firmware
```
#### Fix timezone
``` shell
sudo ln -sf /usr/share/zoneinfo/Asia/Hong_Kong /etc/localtime
sudo hwclock --systohc
```
