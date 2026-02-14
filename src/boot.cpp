#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
#include <unistd.h>
#include <vector>
#include <sys/stat.h>

namespace fs = std::filesystem;
bool is_root() {
    return geteuid() == 0;
}
std::string get_kernel_version() {
    for (const auto& entry : fs::directory_iterator("/boot")) {
        std::string filename = entry.path().filename();
        if (filename.find("vmlinuz-") == 0) {
            return filename.substr(8);
        }
    }
    return "";
}
std::string get_root_device() {
    std::ifstream mtab("/etc/mtab");
    std::string line;
    while (std::getline(mtab, line)) {
        std::vector<std::string> parts;
        size_t pos = 0;
        while ((pos = line.find(' ')) != std::string::npos) {
            parts.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        parts.push_back(line);
        
        if (parts.size() >= 2 && parts[1] == "/") {
            return parts[0];
        }
    }
    struct stat st;
    if (stat("/", &st) == 0) {
        for (const auto& entry : fs::directory_iterator("/dev")) {
            struct stat dev_st;
            if (stat(entry.path().c_str(), &dev_st) == 0) {
                if (dev_st.st_rdev == st.st_dev) {
                    return entry.path();
                }
            }
        }
    }
    return "";
}
std::pair<std::string, std::string> parse_lvm_device(const std::string& device) {
    if (device.find("/dev/mapper/") == 0) {
        std::string dev_name = device.substr(12);
        size_t dash_pos = dev_name.find('-');
        if (dash_pos != std::string::npos && dash_pos > 0 && dash_pos < dev_name.length() - 1) {
            std::string vg_name = dev_name.substr(0, dash_pos);
            std::string lv_name = dev_name.substr(dash_pos + 1);
            return {vg_name, lv_name};
        }
    }
    return {"", ""};
}
int main() {
    if (!is_root()) {
        std::cerr << "Error: Must be run as root" << std::endl;
        return 1;
    }
    std::string kernel_version = get_kernel_version();
    if (kernel_version.empty()) {
        std::cerr << "Error: No kernel found in /boot" << std::endl;
        return 1;
    }
    std::string root_device = get_root_device();
    if (root_device.empty()) {
        std::cerr << "Error: Could not detect root device" << std::endl;
        return 1;
    }
    auto [vg_name, lv_name] = parse_lvm_device(root_device);
    if (vg_name.empty() || lv_name.empty()) {
        std::cerr << "Error: Could not parse LVM information from " << root_device << std::endl;
        return 1;
    }
    std::string rd_option = "rd.lvm.lv=" + vg_name + "/" + lv_name;
    fs::create_directories("/boot/loader/entries");
    std::ofstream loader_conf("/boot/loader/loader.conf");
    if (!loader_conf) {
        std::cerr << "Error: Cannot create loader.conf" << std::endl;
        return 1;
    }
    loader_conf << "default DarkarchWM.conf\n"
                << "timeout 10\n"
                << "console-mode max\n"
                << "editor no\n";
    loader_conf.close();
    std::ofstream entry_conf("/boot/loader/entries/DarkarchWM.conf");
    if (!entry_conf) {
        std::cerr << "Error: Cannot create entry config" << std::endl;
        return 1;
    }
    entry_conf << "title   DarkarchWM\n"
               << "linux   /vmlinuz-" << kernel_version << "\n"
               << "initrd  /initramfs-" << kernel_version << ".img\n"
               << "options root=" << root_device << " ro " << rd_option << " quiet\n";
    entry_conf.close();
    std::cout << "=== Generated loader.conf ===" << std::endl;
    std::ifstream loader_read("/boot/loader/loader.conf");
    std::cout << loader_read.rdbuf() << std::endl;
    std::cout << "=== Generated DarkarchWM.conf ===" << std::endl;
    std::ifstream entry_read("/boot/loader/entries/DarkarchWM.conf");
    std::cout << entry_read.rdbuf() << std::endl;
    return 0;
}
