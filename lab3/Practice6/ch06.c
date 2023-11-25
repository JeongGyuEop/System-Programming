#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void system_call(int argc, char ** argv) {
	char **shell_argv =(char **)malloc(argc * sizeof(char *));
	for(int i =0; i<argc-1; i++) {
		shell_argv[i] = (char *)malloc(100 * sizeof(char));
		strcpy(shell_argv[i],argv[i+1]);
	}

	pid_t pid;
	pid = fork();
	if (pid == 0) {
		if(execvp(shell_argv[0], shell_argv) < 0)
			perror("execvp");
	}
	else if (pid > 0)
		wait((int *) 0);

	for(int i = 0; i<argc-1; i++)
		free(shell_argv[i]);
	free(shell_argv);
}

int main(int argc, char ** argv) {
	system_call(argc,argv);
}

