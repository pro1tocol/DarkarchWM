#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <unistd.h>

bool is_root() {
    return getuid() == 0;
}
int main() {
    if (!is_root()) {
        std::cerr << "Error: Must be run as root" << std::endl;
        return 1;
    }
    const std::string configFile = "/etc/ssh/sshd_config";
    const std::string tempFile = "/tmp/sshd_config.tmp";
    std::string backupCmd = "cp " + configFile + " " + configFile + ".bak";
    system(backupCmd.c_str());
    std::ifstream inFile(configFile);
    std::ofstream outFile(tempFile);
    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return 1;
    }
    std::vector<std::string> targetConfigs = {
        "Port 22",
        "ListenAddress 0.0.0.0", 
        "PermitRootLogin yes",
        "PubkeyAuthentication yes",
        "PasswordAuthentication yes"
    };
    std::string line;
    while (std::getline(inFile, line)) {
        bool lineModified = false;
        for (const auto& config : targetConfigs) {
            std::string key = config.substr(0, config.find(' '));
            if (line.find(key) != std::string::npos) {
                if (line[0] == '#') {
                    std::string uncommented = line.substr(1);
                    while (!uncommented.empty() && uncommented[0] == ' ') {
                        uncommented = uncommented.substr(1);
                    }
                    if (uncommented.substr(0, key.length()) == key) {
                        outFile << config << std::endl;
                        lineModified = true;
                        break;
                    }
                } else {
                    outFile << config << std::endl;
                    lineModified = true;
                    break;
                }
            }
        }
        if (!lineModified) {
            outFile << line << std::endl;
        }
    }
    inFile.close();
    outFile.close();
    std::string moveCmd = "mv " + tempFile + " " + configFile;
    system(moveCmd.c_str());
    std::string chmodCmd = "chmod 600 " + configFile;
    system(chmodCmd.c_str());
    std::cout << "sshd_config updated. Restart SSH service with: sudo sv restart sshd" << std::endl;
    return 0;
}
