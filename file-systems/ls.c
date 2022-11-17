#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define COLUMN_SIZE 5

// barebones ls implementation

char *out[1024];
int idx = 0;
int ccount = 0;

void do_ls(char []);
int pstrcmp(const void *a, const void *b);

int main(int ac,  char *av[]) {
    if (ac == 1) {
        do_ls(".");
    } else {
        while (--ac) {
            printf("%s\n", *++av);
            do_ls(*av);
        }
    }
    qsort(out, idx, sizeof(out[0]), pstrcmp);
    for (int i=0; i < idx; i++) {
        if (ccount == COLUMN_SIZE) {
            printf("%s\n", out[i]);
            ccount = 0;
        }
        printf("%s  ", out[i]);
        ccount++;
    }
}

void do_ls(char dirname[]) {
    DIR *dir_ptr;
    struct dirent *direntp;
    dir_ptr = opendir(dirname);
    if (dir_ptr == NULL) {
        perror("err");
        exit(1);
    }
    while ((direntp = readdir(dir_ptr)) != NULL) {
        out[idx++] = direntp->d_name;
    }
}

int pstrcmp( const void* a, const void* b ) {
  return strcmp( *(const char**)a, *(const char**)b );
}