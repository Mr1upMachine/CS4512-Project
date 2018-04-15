//Colors
#define COLOR_BLACK   "\u001b[30m"
#define COLOR_RED     "\u001b[31m"
#define COLOR_RED_BR  "\u001b[31m;1m"
#define COLOR_GREEN   "\u001b[32m"
#define COLOR_YELLOW  "\u001b[33m"
#define COLOR_BLUE    "\u001b[34m"
#define COLOR_MAGENTA "\u001b[35m"
#define COLOR_CYAN    "\u001b[36m"
#define COLOR_WHITE   "\u001b[37m"
#define COLOR_RESET   "\x1b[0m"

//General constants
#define STR_BUFSIZE 1024
#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"

//Postcondition: preforms cat command and returns 0 if successful or other if task not preformed
int cat(char *argv[], int argc);

int cd(char *argv[], int argc, char *cDir);

//Postcondition: clears out the terminal's current text
int clear();

//Postcondition: preforms cp command and returns 0 if successful or other if task not preformed
int cp(char *argv[]);

int diff(char *argv[], int argc);

//repeats the text on the line below it
int echo(char *command);

//TODO do this
int env(char *argv[], int argc);

//Postcondition: preforms grep command and returns 0 if successful or other if task not preformed
int grep(char *argv[], int argc);

//TODO do this
int kill(char *argv[], int argc);

//Postcondition: preforms ls command and returns 0 if successful or other if task not preformed
int ls(char *cDir);

//TODO do this
int mkdir(char *argv[], int argc, char *cDir);

//TODO do this
int rmdir(char *argv[], int argc, char *cDir);

//TODO do this
int sleep(char *argv[], int argc);

//TODO do this
int stat(char *argv[], int argc);

//TODO do this
int timeout(char *argv[], int argc);

//TODO do this
int wait(char *argv[], int argc);



//Utility methods
//Postcondition: returns 0 if successful
int dirBuilder(char* nDir, char *cDir, char *dest);