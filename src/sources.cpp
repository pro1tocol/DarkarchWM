#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/wait.h>

#define SOURCES_DIR "/etc/xbps.d"
#define SOURCE_TEMPLATE_DIR "/usr/share/xbps.d"
#define MIRROR_URL "https://mirrors.tuna.tsinghua.edu.cn/voidlinux"

int create_sources_dir() {
    if (mkdir(SOURCES_DIR, 0755) != 0 && errno != EEXIST) {
        perror("mkdir");
        return 1;
    }
    return 0;
}
int copy_and_modify_configs() {
    DIR *dir = opendir(SOURCE_TEMPLATE_DIR);
    if (!dir) {
        perror("opendir");
        return 1;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, "-repository-") == NULL) 
            continue;
        char src_path[512], dest_path[512];
        snprintf(src_path, sizeof(src_path), "%s/%s", SOURCE_TEMPLATE_DIR, entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", SOURCES_DIR, entry->d_name);
        FILE *src = fopen(src_path, "r");
        FILE *dest = fopen(dest_path, "w");
        if (!src || !dest) {
            perror("fopen");
            closedir(dir);
            return 1;
        }
        char line[1024];
        while (fgets(line, sizeof(line), src)) {
            char *pos = strstr(line, "https://repo-default.voidlinux.org");
            if (pos) {
                int offset = pos - line;
                char new_line[2048];
                snprintf(new_line, sizeof(new_line), "%.*s%s%s", 
                         offset, line, MIRROR_URL, pos + strlen("https://repo-default.voidlinux.org"));
                fputs(new_line, dest);
            } else {
                fputs(line, dest);
            }
        }
        fclose(src);
        fclose(dest);
        chmod(dest_path, 0644);
    }
    closedir(dir);
    return 0;
}
int xbps_command(const char *args[]) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp("xbps-install", (char* const*)args);
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
    printf("Creating DarkarchWM sources...\n");
	const char *update_args[] = {"xbps-install", "-S", NULL};
	if (xbps_command(update_args) == 0) {
		printf("Database updated successfully\n");
		const char *upgrade_args[] = {"xbps-install", "-uy", "xbps", NULL};
		if (xbps_command(upgrade_args) == 0) {
			printf("Xbps upgraded successfully\n");
			const char *upgrade_args[] = {"xbps-install", "-uy", "vim", "fastfetch", "btop", "tzdata", "parted", "git", "wget", NULL};
			if (xbps_command(upgrade_args) == 0) {
				printf("Packages installed successfully\n");
			} else {
				fprintf(stderr, "Packages installed failed\n");
			}
		} else {
			fprintf(stderr, "Xbps update failed\n");
		}
	} else {
		fprintf(stderr, "Database updated failed\n");
	}
    return 0;
}

