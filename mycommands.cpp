#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mycommands.h"

int cat(char *argv[], int argc) {
    if(strcmp(argv[argc - 2], ">") == 0) {
        FILE *output;
        output = fopen(argv[argc - 1], "w");
        if (output == NULL) {
            printf("cat: Output file cannot be opened");
            return 1;
        }

        const int end = argc-2;
        for(int i=1; i<end; i++) {
            FILE *input;
            char c;
            // Open first file for reading
            input = fopen(argv[i], "r");
            if (input == NULL) {
                printf("cat: %s: No such file or directory\n", argv[i]);
                return 1;
            }

            c = fgetc(input);
            while (c != EOF) {
                fprintf(output,"%c", c);
                c = fgetc(input);
            }

            fclose(input);
        }
        fclose(output);
    }
    else {
        for(int i=1; i<argc; i++) {
            FILE *input;
            char c;
            // Open first file for reading
            input = fopen(argv[i], "r");
            if (input == NULL) {
                printf("cat: %s: No such file or directory\n", argv[i]);
                return 1;
            }

            c = fgetc(input);
            while (c != EOF) {
                printf("%c", c);
                c = fgetc(input);
            }

            fclose(input);
            printf("\n");
        }
    }
    return 0;
}

int cd(char *argv[], int argc, char *cDir) {
    printf("%s not created yet", argv[0]);
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

int diff(char *argv[], int argc) {
    FILE *fp1, *fp2;
    int MAXLINE = 200;
    char filebuff[MAXLINE];
    char filebuff2[MAXLINE];
    int linecount = 0;

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");

    if(argc != 3)
    {
        printf("Wrong use of diff! Ex: diff File1 File2");
        return 0;
    }

    if (fp1 == NULL)
        printf("File %s not found", argv[1]);

    if (fp2 == NULL)
        printf("File %s not found", argv[2]);


    while (((fgets(filebuff, MAXLINE, fp1)) && (fgets(filebuff2, MAXLINE, fp2)))) { //TODO check if this still works
        if (strcmp(filebuff, filebuff2) != 0){
            printf("The files differ on line: %i\n", linecount);
            printf("File 1: %s\nFile 2: %s", filebuff, filebuff2);
        }
        ++linecount;
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}

int echo(char *command) {
    printf("%s", command + 5);
    return 0;
}

int env(char *argv[], int argc) {
    printf("%s not created yet", argv[0]);
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

int kill(char *argv[], int argc) {
    printf("%s not created yet", argv[0]);
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

int mkdir(char *argv[], int argc) {
    if(mkdir(argv[1], 0777) == 0)
        return 0;
    printf("Directory \"%s\" already exists\n", argv[1]);
    return -1;
}

int rmdir(char *argv[], int argc) {
    printf("%s not created yet", argv[0]);
}

int sleep(char *argv[], int argc) {
    printf("%s not created yet", argv[0]);
}

int stat(char *argv[], int argc) {
    printf("%s not created yet", argv[0]);
}

int timeout(char *argv[], int argc) {
    printf("%s not created yet", argv[0]);
}

int wait(char *argv[], int argc) {
    printf("%s not created yet", argv[0]);
}


//Utility methods
int isValidDir(char path[]) {
    struct stat st = {0};
    if (stat(path, &st) == -1)
        return 0;
    return -1;
}
