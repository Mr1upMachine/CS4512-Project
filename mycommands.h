//Colors
#define COLOR_BLACK     "\e[30m"
#define COLOR_RED       "\e[31m"
#define COLOR_RED_BR    "\e[31m;1m"
#define COLOR_GREEN     "\e[32m"
#define COLOR_GREEN_BR  "\e[92m"
#define COLOR_YELLOW    "\e[33m"
#define COLOR_BLUE      "\e[34m"
#define COLOR_MAGENTA   "\e[35m"
#define COLOR_CYAN      "\e[36m"
#define COLOR_WHITE     "\e[37m"
#define COLOR_RESET     "\e[39m"
#define BG_COLOR_GREY   "\e[100m"
#define BG_COLOR_RESET  "\e[49m"

//General constants & structs
#define STR_BUFSIZE 1024
#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"

//Postcondition: preforms cat command and returns 0 if successful or other if task not preformed
int cat(char *argv[], int argc, char *cDir);

int cd(char *argv[], char *cDir);

//Postcondition: clears out the terminal's current text
void clear();

//Postcondition: preforms cp command and returns 0 if successful or other if task not preformed
int cp(char *argv[], char *cDir);

int diff(char *argv[], int argc, char *cDir);

//repeats the text on the line below it
int echo(char *command);

//TODO do this
int env();

//Postcondition: preforms grep command and returns 0 if successful or other if task not preformed
int grep(char *argv[], int argc, char *cDir);

void help();

//TODO do this
int kill(char *argv[]);

//Postcondition: preforms ls command and returns 0 if successful or other if task not preformed
int ls(char *cDir);

int mkdir(char *argv[], int argc, char *cDir);

int rmdir(char *argv[], int argc, char *cDir);

//TODO do this
int sleep(char *argv[]);

//TODO do this
int stat(char *argv[], int argc);

//TODO do this
int timeout(char *argv[], int argc);

//TODO do this
int wait(char *argv[]);



//Utility methods
//Postcondition: returns new directory
char* dirBuilder(char *cDir, char *dest);

//doesn't seem to work?
int isDirectory(const char *path);