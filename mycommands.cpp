#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "mycommands.h"

int cat(char *args[]) {
    FILE *fptr;
    char c;
    // Open first file for reading
    fptr = fopen(args[1], "r");
    if (fptr == NULL) {
        printf("cat: %s: No such file or directory\n", args[1]);
        return 1;
    }

    c = fgetc(fptr);
    while (c != EOF) {
        printf("%c", c);
        c = fgetc(fptr);
    }

    fclose(fptr);

    return 0;
}

int clear() {
    printf("\033[2J"); //clears terminal for Linux
}

int cp(char *args[]) {
    FILE *fptr1, *fptr2;
    char c;

    // Open first file for reading
    fptr1 = fopen(args[1], "r");
    if (fptr1 == NULL) {
        printf("Cannot find file %s \n", args[1]);
        return 1;
    }

    // Opens other file for writing
    fptr2 = fopen(args[2], "w");
    if (fptr2 == NULL) {
        printf("Cannot open file %s \n", args[2]);
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
}

int grep(char *argv[]) {
    FILE *fp;
    char line[100];
    
    //open the file
    fp = fopen(argv[2],"r");

    //find line with string
    while(fscanf(fp , "%[^\n]\n" , line)!=EOF)
    {
        if(strstr(line , argv[1]) !=NULL)
        {
            //print found line
            printf("%s\n" , line);
        }
        else
        {
            continue;
        }
    }
    fclose(fp);
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
}
