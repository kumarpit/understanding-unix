#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

// basic pwd implementation

ino_t get_inode(char *);
void print_path_to(ino_t);
void inum_to_name(ino_t, char *, int);

int main() {
    print_path_to(get_inode("."));
    printf("\n");
    return 0;
}

void print_path_to(ino_t curr_inode) {
    ino_t parent_inode = get_inode("..");
    char name[BUFSIZ];
    // home dir . == ..
    if (parent_inode != curr_inode) {
        chdir("..");
        inum_to_name(curr_inode, name, BUFSIZ);
        print_path_to(parent_inode);
        printf("%s/", name);
    }
}

void inum_to_name(ino_t inode, char *namebuf, int buflen) {
    DIR *dir_ptr;
    struct dirent *direntp;
    dir_ptr = opendir(".");
    if (dir_ptr == NULL) {
        perror(".");
        exit(1);
    }
    while ((direntp = readdir(dir_ptr)) != NULL) {
        // printf("%d\n", direntp->d_ino);
        // for some reason the inode numbers for my root dir are not correct...
        if (direntp->d_ino == inode) {
            strncpy(namebuf, direntp->d_name, buflen);
            namebuf[buflen-1] = '\0';
            closedir(dir_ptr);
            printf("\n\n");
            return;
        }
    }
    printf("Unable to find inode %d \n", inode);
    strncpy(namebuf, "", buflen);
}

ino_t get_inode(char *fname) {
    struct stat info;
    if (stat(fname, &info) == -1) {
        printf("Cannot stat");
        exit(1);
    }
    return info.st_ino;
}
