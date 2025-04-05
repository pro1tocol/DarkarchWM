#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <sys/stat.h>
#include  <unistd.h>

#define OLLAMA_SERVICE "/usr/lib/systemd/system/ollama.service"

int ollamaservice() {
    // 检查服务文件是否存在
    if (access(OLLAMA_SERVICE, F_OK) == 0) {
        // 启动服务
        int result = system("sudo systemctl start ollama");
        
        if (result == 0) {
            printf("\n本地模型服务已启动\n");
            return 0;
        } else {
            printf("\n本地模型服务启动失败\n请检查日志信息\n");
            return 1;
        }
    } else {
        printf("\n本地模型服务不存在\n请检查路径是否正确\n");
        return 1;
    }
}

int main() {
    while (1) { // 循环
        if (ollamaservice() == 0) {
            break; // 成功启动后退出循环
        } else {
            // 启动失败，可以根据需要选择是否重试
            printf("\n尝试重新启动本地模型服务...\n或者按Ctrl + C结束进程\n");
            sleep(5); 
        }
    }
    
    return 0;
}
