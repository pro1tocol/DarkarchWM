#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <unistd.h>

void update_system(const std::string& kernel_version) {
    std::cout << "Kernel updating..." << std::endl;
    std::system("xbps-install -u -y dracut linux-firmware linux-firmware-intel linux-firmware-amd");
    std::string find_cmd = "find /lib/modules/" + kernel_version + " -name 'tun.ko*'";
    int ret = std::system(find_cmd.c_str());
    if (ret != 0) {
        std::cerr << "ERROR: tun device no found, please check!" << std::endl;
    }
    std::string dracut_cmd = "dracut -f /boot/initramfs-" + kernel_version + ".img " + kernel_version;
    std::system(dracut_cmd.c_str());
    std::string dracut_tun_cmd = "dracut -f --add-drivers \"tun\" /boot/initramfs-" + kernel_version + ".img " + kernel_version;
    std::system(dracut_tun_cmd.c_str());
    std::cout << "Kernel updated successfully" << std::endl;
}

int main(int argc, char* argv[]) {
    if (getuid() != 0) {
        std::cerr << "Error: Must be run as root" << std::endl;
        return 1;
    }
    std::string kernel_version;
    if (argc > 1) {
        kernel_version = argv[1];
    } else {
        FILE* pipe = popen("uname -r", "r");
        if (pipe) {
            char buffer[128];
            if (fgets(buffer, sizeof(buffer), pipe)) {
                kernel_version = buffer;
                kernel_version.erase(kernel_version.find_last_not_of(" \n\r") + 1);
            }
            pclose(pipe);
        } else {
            std::cerr << "ERROR: kernel version no found, please check!" << std::endl;
            return 1;
        }
    }
    std::cout << "Kernel version: " << kernel_version << std::endl;
    update_system(kernel_version);
    return 0;
}
