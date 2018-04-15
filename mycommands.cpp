#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mycommands.h"

struct stat info;

//TODO fix to work with directory support
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

int cd(char *argv[], char *cDir) {
    char *nDir = (char*)malloc(sizeof(char) * STR_BUFSIZE);
    strcpy(nDir, dirBuilder(cDir, argv[1]));

    if( stat( nDir, &info ) != 0 )
        printf( "cannot access %s\n", argv[1] );
    else if( info.st_mode & S_IFDIR )
        strcpy(cDir, nDir);
    else
        printf( "%s is not a directory\n", argv[1] );
}

void clear() {
    printf("\033[2J"); //clears terminal for Linux
}

//TODO fix to work with directory support
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

//TODO fix to work with directory support
int diff(char *argv[], int argc) {
    FILE *fp1, *fp2;
    char filebuff[STR_BUFSIZE];
    char filebuff2[STR_BUFSIZE];
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


    while (((fgets(filebuff, STR_BUFSIZE, fp1)) && (fgets(filebuff2, STR_BUFSIZE, fp2)))) { //TODO check if this still works
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

//TODO fix to work with directory support
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

void help() {
    printf("cat filename\n"
           "cd directory_name\n"
           "clear\n"
           "cp file1 file2\n"
           "diff file1 file2\n"
           "echo [string]\n"
           "env\n"
           "exit\n"
           "grep pattern file1 file2 ...\n"
           "kill signal_number process_id\n"
           "help\n"
           "ls\n"
           "mkdir directory_name\n"
           "rmdir directory_name\n"
           "sleep time\n"
           "stat file_or_directory_name\n"
           "timeout seconds command\n"
           "wait process_id\n");
}

int kill(char *argv[], int argc) {
    printf("%s not created yet", argv[0]);
}

int ls(char *cDir) {
    DIR *d;
    struct dirent *dir;
    d = opendir(cDir);
    printf(COLOR_GREEN_BR);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                printf("%s ", dir->d_name);
            }
        }
        closedir(d);
    }
    printf(COLOR_RESET "\n");
    return 0;
}

//TODO verify if directory support works
int mkdir(char *argv[], int argc, char *cDir) {
    if( mkdir(dirBuilder(cDir, argv[1]), 0777) == 0 )
        return 0;
    printf("Directory \"%s\" already exists\n", argv[1]);
    return -1;
}

int rmdir(char *argv[], int argc, char *cDir) {
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
char* dirBuilder(char *cDir, char *dest) {
    //TODO .. does not work with chaining, create better parsing algo that transforms path all at once
    if(dest[0] == '~') { //home path
        return getenv("HOME");
    }
    else if(dest[0] == '/') { //absolute path
        return dest;
    }

    char *nDir = (char*)malloc(sizeof(char) * STR_BUFSIZE);

    if(dest[0] == '.' && dest[1] == '.') { //parent path
        int index = -1;
        const size_t len = strlen(cDir)-1;
        for (int i = 0; i < len; i++)
            if (cDir[i] == '/')
                index = i;
        if(index == 0)
            strcpy(nDir, "/");
        else
            strncpy(nDir, cDir, index);
        return nDir;
    }
    else {
        if(strcmp(cDir, "/") != 0)
            strcpy(nDir, cDir);
        strcat(nDir, "/");
        strcat(nDir, dest);
        return nDir;
    }

}

int isDirectory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}