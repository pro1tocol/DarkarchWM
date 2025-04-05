#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <sys/stat.h>
#include  <unistd.h>

#define DOCKER_SERVICE "/usr/lib/systemd/system/docker.service"

int dockerservice() {
    // 检查服务文件是否存在
    if (access(DOCKER_SERVICE, F_OK) == 0) {
        // 终止Docker_socket服务
        int result = system("sudo systemctl stop docker.socket");
        
        if (result == 0) {
            printf("\nDocker_socket服务已终止\n");
            // 终止Docker服务
            int result = system ("sudo systemctl stop docker.service");
            
            if (result == 0){
                printf("\nDocker服务已终止\n");
                //终止Container服务
                int result = system ("sudo systemctl stop containerd.service");

                if (result == 0){
                    printf("\nContainer服务已终止\n");
                    return 0;
                } else {
                    printf("\nContainer服务终止报错\n请检查日志信息\n");
                    return 1;
                }
                return 0;
            } else {
                printf("\nDocker服务终止报错\n请检查日志信息\n");
                return 1;
            }
            return 0;
        } else {
            printf("\nDocker_socket终止报错\n请检查日志信息\n");
            return 1;
        }
    } else {
        printf("\nDocker 服务不存在\n请检查路径是否正确\n");
        return 1;
    }
}

int main() {
    while (1) { // 循环
        if (dockerservice() == 0) {
            break; // 成功终止后退出循环
        } else {
            // 终止失败，可以根据需要选择是否重试
            printf("\n尝试重新终止Docker服务...\n或者按Ctrl + C结束进程\n");
            sleep(5); 
        }
    }
    
    return 0;
}
