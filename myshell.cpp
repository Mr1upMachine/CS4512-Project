#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mycommands.h"

char *read_line(void);
char **split_args(char *command, int *argc);

//#define ANSI_COLOR_RED     "\u001b[31;1m"
//#define ANSI_COLOR_RESET   "\x1b[0m"
int main() {
    char *command;
    char **argv;
    int *argc;

    do {
        //printf(ANSI_COLOR_RED  "This text is RED!"  ANSI_COLOR_RESET  "\n");
        printf("> ");
        command = read_line();
        argv = split_args(command, argc);

        if(strcmp(argv[0], "cat") == 0) {
            cat(argv, argc);
            printf("\n");
        }
        else if(strcmp(argv[0], "clear") == 0) {
            clear();
        }
        else if(strcmp(argv[0], "cp") == 0) {
            cp(argv);
        }
        else if(strcmp(argv[0], "echo") == 0) {
            echo(command);
        }
        else if(strcmp(argv[0], "exit") == 0) {
            return 0;
        }
        else if(strcmp(argv[0], "grep") == 0) {
            grep(argv, *argc);
        }
        else if(strcmp(argv[0], "help") == 0) {
            printf("cat filename\nclear\ncp file1 file2\necho [string]\nexit\ngrep pattern file1 file2 ...\nhelp\nls [-l]\n");
        }
        else if(strcmp(argv[0], "ls") == 0) {
            ls();
            printf("\n");
        }
        else {
            printf("Command not recognised, type help for valid commands\n");
            //printf("%i%s",*argc, argv[4]);
        }
    } while(true);
}

char *read_line(void) {
    char *line = NULL;
    size_t bufsize = 0; // have getline allocate a buffer for us
    getline(&line, &bufsize, stdin);
    return line;
}

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"
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