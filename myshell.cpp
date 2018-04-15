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
        else if(strcmp(argv[0], "cat") == 0)
            cat(argv, *argc);
        else if(strcmp(argv[0], "clear") == 0) 
            clear();
        else if(strcmp(argv[0], "cp") == 0) 
            cp(argv);
        else if(strcmp(argv[0], "diff") == 0) 
            diff(argv, *argc);
        else if(strcmp(argv[0], "echo") == 0) 
            echo(command);
        else if(strcmp(argv[0], "env") == 0) {
            printf("%s not created yet", argv[0]);
            env(argv, *argc);
        }
        else if(strcmp(argv[0], "exit") == 0)
            return 0;
        else if(strcmp(argv[0], "grep") == 0)
            grep(argv, *argc);
        else if(strcmp(argv[0], "help") == 0) {
            //TODO update this
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
        else if(strcmp(argv[0], "kill") == 0) {
            printf("%s not created yet", argv[0]);
            kill(argv, *argc);
        }
        else if(strcmp(argv[0], "ls") == 0)
            ls();
        else if(strcmp(argv[0], "mkdir") == 0)
            mkdir(argv, *argc);
        else if(strcmp(argv[0], "rmdir") == 0) {
            printf("%s not created yet", argv[0]);
            rmdir(argv, *argc);
        }
        else if(strcmp(argv[0], "sleep") == 0) {
            printf("%s not created yet", argv[0]);
            sleep(argv, *argc);
        }
        else if(strcmp(argv[0], "stat") == 0) {
            printf("%s not created yet", argv[0]);
            stat(argv, *argc);
        }
        else if(strcmp(argv[0], "timeout") == 0) {
            printf("%s not created yet", argv[0]);
            timeout(argv, *argc);
        }
        else if(strcmp(argv[0], "wait") == 0) {
            printf("%s not created yet", argv[0]);
            wait(argv, *argc);
        }
        else
            printf("Command not recognised, type help for valid commands\n");
    } while(true);
}

#define LINE_BUFSIZE 1024
char *read_line(void) {
    char *line = (char*)malloc(LINE_BUFSIZE);
    fgets(line, LINE_BUFSIZE, stdin);
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