//Postcondition: preforms cat command and returns 0 if successful or other if task not preformed
int cat(char *argv[], int argc);

//Postcondition: clears out the terminal's current text
int clear();

//Postcondition: preforms cp command and returns 0 if successful or other if task not preformed
int cp(char *argv[]);

int diff(char *argv[], int argc);

//repeats the text on the line below it
int echo(char *command);

//Postcondition: preforms grep command and returns 0 if successful or other if task not preformed
int grep(char *argv[], int argc);

//Postcondition: preforms ls command and returns 0 if successful or other if task not preformed
int ls();

