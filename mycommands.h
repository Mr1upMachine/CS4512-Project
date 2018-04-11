//Postcondition: preforms cat command and returns 0 if successful or other if task not preformed
int cat(char *argv[], int argc);

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
int ls();

//TODO do this
int mkdir(char *argv[], int argc);

//TODO do this
int rmdir(char *argv[], int argc);

//TODO do this
int sleep(char *argv[], int argc);

//TODO do this
int stat(char *argv[], int argc);

//TODO do this
int timeout(char *argv[], int argc);

//TODO do this
int wait(char *argv[], int argc);