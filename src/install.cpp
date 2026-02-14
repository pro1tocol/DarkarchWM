#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <sys/stat.h>
#include  <unistd.h>

#define RELEASE "/etc/os-release"
#define MAX_RETRIES 3

int install() {
	// check system version
    if (access(RELEASE, F_OK) != 0) {
        printf("\nSystem Error !!! Please Check Path: /etc/os-release\n");
        return 1;
    }
    printf("\nDarkarchWM Applications Installing...\n");
    const char* commands[] = {
        "xbps-install -S",
        "xbps-install -uy void-repo-nonfree vim nano curl git gzip unzip zip tar iftop btop NetworkManager",
        "xbps-install -uy dhcpcd iwd openssh openssl net-tools lvm2 efibootmgr less bc fzf bluez bluedevil bluez-obex",
        "xbps-install -uy ntfs-3g usbutils xbacklight xrdb xkbcomp xmodmap xdpyinfo sof-firmware xf86-input-synaptics",
        "xbps-install -uy xf86-input-evdev alsa-utils pipewire brightnessctl xdotool acpi sysstat tk gnuplot xterm kitty",
        "xbps-install -uy dolphin gwenview mpv plasma-pa plasma-nm plasma-thunderbolt breeze-gtk breeze systemsettings",
        "xbps-install -uy kscreen powerdevil gnome-screenshot gnome-calculator fastfetch kde-gtk-config qt5ct qt6ct",
        "xbps-install -uy breeze-icons polybar picom screenkey slop lxdm i3 rofi ranger w3m w3m-img",
        "xbps-install -uy kde-plasma imlib2 feh xfsprogs xinit xorg tlp flatpak",
        NULL
    };
    for (int i = 0; commands[i] != NULL; i++) {
        int result = system(commands[i]);
        if (result != 0) {
            printf("\nDarkarchWM Applications Install failed: %s\n", commands[i]);
            return 1;
        }
    }
    return 0;
}
int main() {
	if (getuid() != 0) {
        printf("Error: The DarkarchWM applications must be run as root.\n");
        return 1;
    }
    int retry_count = 0;
    while (retry_count < MAX_RETRIES) {
        if (install() == 0) {
            printf("Installation Completed Successfully!\n");
            return 0;
        } else {
            retry_count++;
            printf("\nERROR! Retry %d/%d. Ctrl + C to Stop\n", retry_count, MAX_RETRIES);
            if (retry_count < MAX_RETRIES) {
                sleep(5);
            }
        }
    }
    printf("Installation Failed After %d Attempts\n", MAX_RETRIES);
    return 1;
}
