#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <sys/stat.h>
#include  <unistd.h>

#define DOCKER_SERVICE "/usr/lib/systemd/system/docker.service"

int dockerservice() {
    // 检查服务文件是否存在
    if (access(DOCKER_SERVICE, F_OK) == 0) {
        // 启动服务
        int result = system("sudo systemctl start docker.service");
        
        if (result == 0) {
            printf("\nDocker服务已启动\n");
            return 0;
        } else {
            printf("\nDocker服务启动报错\n请检查日志信息\n");
            return 1;
        }
    } else {
        printf("\nDocker服务不存在\n请检查路径是否正确\n");
        return 1;
    }
}

int main() {
    while (1) { // 循环
        if (dockerservice() == 0) {
            break; // 成功启动后退出循环
        } else {
            // 启动失败，可以根据需要选择是否重试
            printf("\n尝试重新启动Docker服务...\n或者按Ctrl + C结束进程\n");
            sleep(5); 
        }
    }
    
    return 0;
}
