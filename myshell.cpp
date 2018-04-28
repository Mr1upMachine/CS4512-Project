#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mycommands.h"

char *read_line(void);
char **split_args(char *command, int *argc);

int main() {
    char *command;
    char **argv;
    int *argc;
    char *cDir = getenv("HOME"); //gets home directory

    printf("Welcome to our Shell Program!\n");
    do {
        printf(COLOR_CYAN  "%s"  COLOR_RESET  "> ", cDir);
        command = read_line();
        argv = split_args(command, argc);

        if(*argc == 0)
            continue;
        else
            if (run_command(command, argv, *argc, cDir) == -1) return 0;

    } while(true);
}

char *read_line(void) {
    char *line = (char*)malloc(STR_BUFSIZE);
    fgets(line, STR_BUFSIZE, stdin);
    return line;
}

char **split_args(char *command, int *argc) {
    char *cmdcopy = strdup(command); //deep copy
    int i = 0;
    char **tokens = (char**)malloc(TOKEN_BUFSIZE * sizeof(char*));
    char *token = strtok(cmdcopy, TOKEN_DELIM);
    *argc = 1; //sets arg count to one for initial

    /* walk through other tokens */
    while( token != NULL ) {
        tokens[i] = token;
        //printf("%s", tokens[i]);
        i++;

        token = strtok(NULL, TOKEN_DELIM);
        (*argc)++; //increments value count
    }
    tokens[i] = NULL; //null terminating
    (*argc)--;
    return tokens;
}