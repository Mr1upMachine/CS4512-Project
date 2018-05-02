#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mycommands.h"
#include <signal.h>

struct stat info;


int run_command(char *command, char *argv[], int argc, char *cDir) {
    if(!strcmp(argv[0], "cat"))
        cat(argv, argc, cDir);
    else if(!strcmp(argv[0], "cd"))
        cd(argv, cDir);
    else if(!strcmp(argv[0], "clear"))
        clear();
    else if(!strcmp(argv[0], "cp"))
        cp(argv, cDir);
    else if(!strcmp(argv[0], "diff"))
        diff(argv, argc, cDir);
    else if(!strcmp(argv[0], "echo"))
        echo(command);
    else if(!strcmp(argv[0], "env"))
        env();
    else if(!strcmp(argv[0], "exit"))
        return -1;
    else if(!strcmp(argv[0], "grep"))
        grep(argv, argc, cDir);
    else if(!strcmp(argv[0], "help"))
        help();
    else if(!strcmp(argv[0], "kill"))
        kill(argv);
    else if(!strcmp(argv[0], "ls"))
        ls(cDir);
    else if(!strcmp(argv[0], "mkdir"))
        mkdir(argv, argc, cDir);
    else if(!strcmp(argv[0], "rmdir"))
        rmdir(argv, argc, cDir);
    else if(!strcmp(argv[0], "sleep"))
        sleep(argv);
    else if(!strcmp(argv[0], "stat"))
        stat(argv, argc);
    else if(!strcmp(argv[0], "timeout"))
        timeout(argv, argc);
    else if(!strcmp(argv[0], "wait"))
        wait(argv);
    else
        printf("Command not recognised, type \"help\" for valid commands\n");
}

int cat(char *argv[], int argc, char *cDir) {
    if(strcmp(argv[argc - 2], ">") == 0) {
        FILE *output;
        output = fopen( dirBuilder(cDir, argv[argc - 1]), "w" );
        if (output == NULL) {
            printf("cat: Output file cannot be opened");
            return 1;
        }

        const int end = argc-2;
        for(int i=1; i<end; i++) {
            FILE *input;
            char c;
            // Open first file for reading
            input = fopen( dirBuilder(cDir, argv[i]), "r" );
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
            input = fopen( dirBuilder(cDir, argv[i]), "r" );
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
        }
    }
    printf("\n");
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

int cp(char *argv[], char *cDir) {
    FILE *fptr1, *fptr2;
    char c;

    // Open first file for reading
    fptr1 = fopen( dirBuilder(cDir, argv[1]), "r" );
    if (fptr1 == NULL) {
        printf("Cannot find file %s \n", argv[1]);
        return 1;
    }

    // Opens other file for writing
    fptr2 = fopen( dirBuilder(cDir, argv[2]), "w" );
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

int diff(char *argv[], int argc, char *cDir) {
    FILE *fp1, *fp2;
    char filebuff[STR_BUFSIZE];
    char filebuff2[STR_BUFSIZE];
    int linecount = 0;

    fp1 = fopen( dirBuilder(cDir, argv[1]), "r" );
    fp2 = fopen( dirBuilder(cDir, argv[2]), "r" );

    if(argc != 3)
    {
        printf("Wrong use of diff! Ex: diff File1 File2");
        return 0;
    }

    if (fp1 == NULL)
        printf("File %s not found", argv[1]);

    if (fp2 == NULL)
        printf("File %s not found", argv[2]);


    while (((fgets(filebuff, STR_BUFSIZE, fp1)) && (fgets(filebuff2, STR_BUFSIZE, fp2)))) {
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

int env() {
	extern char **environ;
	int i = 0;
	while(environ[i]) {
  	printf("%s\n", environ[i++]); // prints in form of "variable=value"
	}
	  
}

int grep(char *argv[], int argc, char *cDir) {
    for(int i=2; i<argc; i++) {
        FILE *fp;
        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        fp = fopen( dirBuilder(cDir, argv[i]), "r" );
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

int kill(char *argv[]) {
    
    int pid = atoi(argv[1]);
    int sig = atoi(argv[2]);

//SIGKILL
if (sig == 9)
    {
        kill(SIGKILL,pid);
    }

//SIGTERM
if (sig == 15)
    {
        kill(SIGTERM,pid);
    }

//SIGHUP
if (sig == 1)
    {
        kill(SIGHUP,pid);
    }
	
	
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

int mkdir(char *argv[], int argc, char *cDir) {
    if( mkdir(dirBuilder(cDir, argv[1]), 0777) == 0 )
        return 0;
    printf("Directory \"%s\" already exists\n", argv[1]);
    return -1;
}

int rmdir(char *argv[], int argc, char *cDir) {
    if( rmdir(dirBuilder(cDir, argv[1])) == 0 )
        return 0;
    printf("Directory \"%s\" does not exist\n", argv[1]);
    return -1;
}

int sleep(char *argv[]) {
     int x = atoi(argv[1]);
        sleep(x);
}

int stat(char *argv[], int argc) {
    struct stat s;

           if (argc != 2) {
               exit(EXIT_FAILURE);
           }

           if (lstat(argv[1], &s) == -1) {
               perror("lstat");
               exit(EXIT_FAILURE);
           }

           printf("File:%s\n ", argv[1]);
	   printf("Size:%lld bytes\n", (long long) s.st_size); 
           printf("Blocks:%lld\n",(long long) s.st_blocks);
	   printf("I/O block:%ld bytes\n", (long) s.st_blksize); 
	   printf("File type:");

		   switch (s.st_mode & S_IFMT) {
		   case S_IFBLK:  printf("block device\n");            break;
		   case S_IFCHR:  printf("character device\n");        break;
		   case S_IFDIR:  printf("directory\n");               break;
		   case S_IFIFO:  printf("FIFO/pipe\n");               break;
		   case S_IFLNK:  printf("symlink\n");                 break;
		   case S_IFREG:  printf("regular file\n");            break;
		   case S_IFSOCK: printf("socket\n");                  break;
		   default:       printf("unknown?\n");                break;
           }
           printf("Device:%ld\n", (long) s.st_dev);
	   printf("Links:%ld\n", (long) s.st_nlink); 
           printf("I-node:%ld\n", (long) s.st_ino);
	   printf("Access:%ld\n", (long) s.st_mode);
	   printf("UID:%ld\n",(long) s.st_uid);
	   printf("GID:%ld\n",(long) s.st_gid);
	   printf("Access:%s", ctime(&s.st_atime));
           printf("Modify:%s", ctime(&s.st_mtime));
           printf("Change:%s", ctime(&s.st_ctime));

           exit(EXIT_SUCCESS);
}

int timeout(char *argv[], int argc) {
       int pid;
    pid = fork();
    int time = atoi(argv[1]);
    
    if (pid == 0)
        //exec Command
    
    if (pid < 0)
        while(pid == 0)
            for (int i = 0; i < time; i++)
            {
                sleep(1);
            }
    kill(SIGTERM,0);
    
    exit(1);
    
}

int wait(char *argv[]) {
	//Char to Int
   	int pid = atoi(argv[1]);
	if(kill(pid,0) == 0)
	{
		sleep(1);
	}
}


//Utility methods
char* dirBuilder(char *cDir, char *target) {
    //TODO .. and ~ does not work with chaining, create better parsing algo that transforms path all at once
    if(target[0] == '~') //home path
        return getenv("HOME");
    else if(target[0] == '/') //absolute path
        return target;

    char *nDir = (char*)malloc(sizeof(char) * STR_BUFSIZE);

    if(target[0] == '.' && target[1] == '.') { //parent path
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
        if(target[0] == '.') //TODO Bug where just a . by itself adds a / to string
            strcat(nDir, target+2);
        else
            strcat(nDir, target);
        return nDir;
    }

}

//TODO doesnt work to my knowledge
int isValidDir(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}
