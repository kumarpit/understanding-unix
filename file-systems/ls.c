#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

// barebones ls implementation

int main() {
    DIR *dir_ptr;
    struct dirent *direntp;
    dir_ptr = opendir(".");
    if (dir_ptr == NULL) {
        perror(".");
        exit(1);
    }
    while ((direntp = readdir(dir_ptr)) != NULL) {
        printf("%s\n", direntp->d_name);    
    }
}