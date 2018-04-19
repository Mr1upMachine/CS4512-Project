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
        else if(!strcmp(argv[0], "cat"))
            cat(argv, *argc, cDir);
        else if(!strcmp(argv[0], "cd"))
            cd(argv, cDir);
        else if(!strcmp(argv[0], "clear"))
            clear();
        else if(!strcmp(argv[0], "cp"))
            cp(argv, cDir);
        else if(!strcmp(argv[0], "diff"))
            diff(argv, *argc, cDir);
        else if(!strcmp(argv[0], "echo"))
            echo(command);
        else if(!strcmp(argv[0], "env"))
            env();
        else if(!strcmp(argv[0], "exit"))
            return 0;
        else if(!strcmp(argv[0], "grep"))
            grep(argv, *argc, cDir);
        else if(!strcmp(argv[0], "help"))
            help();
        else if(!strcmp(argv[0], "kill"))
            kill(argv);
        else if(!strcmp(argv[0], "ls"))
            ls(cDir);
        else if(!strcmp(argv[0], "mkdir"))
            mkdir(argv, *argc, cDir);
        else if(!strcmp(argv[0], "rmdir"))
            rmdir(argv, *argc, cDir);
        else if(!strcmp(argv[0], "sleep"))
            sleep(argv);
        else if(!strcmp(argv[0], "stat"))
            stat(argv, *argc);
        else if(!strcmp(argv[0], "timeout"))
            timeout(argv, *argc);
        else if(!strcmp(argv[0], "wait"))
            wait(argv);
        else
            printf("Command not recognised, type \"help\" for valid commands\n");
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