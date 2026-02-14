#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int xbps_command(char* const args[]) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp("xbps-install", args);
        perror("execvp");
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    } else {
        perror("fork");
        return -1;
    }
}
int main() {
    if (getuid() != 0) {
        fprintf(stderr, "Error: Must be run as root\n");
        return 1;
    }
    char* const update_args[] = {
        const_cast<char*>("xbps-install"), 
        const_cast<char*>("-S"), 
        NULL
    };
    int update_ret = xbps_command(update_args);
    if (update_ret != 0) {
        fprintf(stderr, "Database update failed (code: %d)\n", update_ret);
        return 1;
    }
    printf("Database updated successfully\n");
    char* const upgrade_args[] = {
        const_cast<char*>("xbps-install"),
        const_cast<char*>("-uy"),
        const_cast<char*>("zsh"),
        const_cast<char*>("zsh-autosuggestions"),
        const_cast<char*>("zsh-completions"),
        const_cast<char*>("zsh-history-substring-search"),
        const_cast<char*>("zsh-syntax-highlighting"),
        NULL
    };
    int upgrade_ret = xbps_command(upgrade_args);
    if (upgrade_ret != 0) {
        fprintf(stderr, "zsh installation failed (code: %d)\n", upgrade_ret);
        return 1;
    }
    printf("zsh installation successful\n");
    return 0;
}
