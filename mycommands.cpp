#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "mycommands.h"

int cat(char *argv[], int argc) {
    const int end = argc-2;
    for(int i=1; i<end; i++) {
        FILE *fptr;
        char c;
        // Open first file for reading
        fptr = fopen(argv[i], "r");
        if (fptr == NULL) {
            printf("cat: %s: No such file or directory\n", argv[i]);
            return 1;
        }

        c = fgetc(fptr);
        while (c != EOF) {
            printf("%c", c);
            c = fgetc(fptr);
        }

        fclose(fptr);
    }
    return 0;
}

int clear() {
    printf("\033[2J"); //clears terminal for Linux
    return 0;
}

int cp(char *argv[]) {
    FILE *fptr1, *fptr2;
    char c;

    // Open first file for reading
    fptr1 = fopen(argv[1], "r");
    if (fptr1 == NULL) {
        printf("Cannot find file %s \n", argv[1]);
        return 1;
    }

    // Opens other file for writing
    fptr2 = fopen(argv[2], "w");
    if (fptr2 == NULL) {
        printf("Cannot open file %s \n", argv[2]);
        return 1;
    }

    // Read contents from file
    c = fgetc(fptr1);
    while (c != EOF) {
        fputc(c, fptr2);
        c = fgetc(fptr1);
    }

    fclose(fptr1);
    fclose(fptr2);
    return 0;
}

int echo(char *command) {
    printf("%s", command + 5);
    return 0;
}

int grep(char *argv[], int argc) {
    for(int i=2; i<argc; i++) {
        FILE *fp;
        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("File %s not found", argv[i]);
            return 1;
        }

        while ((read = getline(&line, &len, fp)) != -1) {
            if (strstr(line, argv[1])) {
                printf("%s", line);
            }
        }

        fclose(fp);
    }
    return 0;
}

int ls() {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                printf("%s ", dir->d_name);
            }
        }
        closedir(d);
    }
    return 0;
}
