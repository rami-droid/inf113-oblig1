#include <stdio.h>  // getline
#include <stdlib.h> // exit
#include <string.h> // strtok
#include <sys/types.h>
#include <unistd.h> // execvp
#include <sys/wait.h>

#define MAX_ARGS 256

size_t n = 0;
char *line = NULL;
char *args[MAX_ARGS];

/*
    Reads one line from the standard input and
    splits it into tokens. The resulting tokens
    are stored args, terminated by a NULL pointer.
*/
void parse_command_from_user()
{
    int rc = getline(&line, &n, stdin);


	if (strcmp(line, "terminate\n") == 0) {
		exit(0);
	}
    int i = 0;
    args[i++] = strtok(line, " \n");
    while (i < MAX_ARGS && args[i - 1] != NULL)
        args[++i] = strtok(NULL, " \n");
}

int main()
{
    //printf("I am a command runner skeleton ... ");

	for (;;) {
		printf("command runner > ");
		parse_command_from_user();

		pid_t pid = fork();
		if (pid == 0) {
			execvp(args[0], args);
		
		} else {
			wait(NULL);
		}
	
	}

    return 0;
}
