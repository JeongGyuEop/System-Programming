#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void listFilesRecursively(const char *basePath, int depth) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(basePath))) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        for (int i = 0; i < depth; i++) {
            printf("  "); // 디렉토리 깊이에 따라 들여쓰기
        }

        printf("%s\n", entry->d_name);

        if (entry->d_type == DT_DIR) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", basePath, entry->d_name);
            listFilesRecursively(path, depth + 1);
        }
    }
    closedir(dir);
}

int main() {
    const char *basePath = "/home/user/System-Programming/lab3/Practice2";

    printf("%s:\n", basePath);
    listFilesRecursively(basePath, 0);
    return 0;
}

