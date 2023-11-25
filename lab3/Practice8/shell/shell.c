#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>

void pipe_launch(int narg, char **argv) {
	pid_t pid;
	int command_pos = 0;
	int count_pipe = 0;
	int i = 0 ;
	int pd_idx = 0;
	int k = 0;
	int status;

	while(argv[command_pos] != NULL) {
		if(argv[command_pos][0] =='|')
			count_pipe ++;
		command_pos++;
	}

	int fd[count_pipe*2];
	for(i = 0; i < (count_pipe); i++){
		if(pipe(fd + i*2) < 0) {
			perror("couldn't pipe");
			exit(EXIT_FAILURE);
		}
	}

	command_pos = 0;
	for( i = 0 ; i<=count_pipe; i++) {
		int j =0;
		char **command = (char **)malloc(narg * sizeof(char *));
		if(!strcmp(argv[command_pos], "|"))
			command_pos++;
		if(i <count_pipe) {
			while(strcmp(argv[command_pos], "|") ) {
				command[j] = (char *)malloc(100 * sizeof(char));
				strcpy(command[j],argv[command_pos]);
				command_pos++;
				j++;
			}
		}
		else {
			while(argv[command_pos] != NULL) {
				command[j] = (char *)malloc(100 * sizeof(char));
				strcpy(command[j],argv[command_pos]);
				command_pos++;
				j++;
			}
		}

		command[j] = NULL;

		pid = fork();
		if(pid == 0) {
			if(i<count_pipe) {
				if(dup2(fd[pd_idx + 1], 1) < 0){
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			if(pd_idx != 0 ){
				if(dup2(fd[pd_idx-2], 0) < 0){
					perror(" dup2");
					exit(EXIT_FAILURE);
				}
			}

			for(k = 0; k < 2*count_pipe; k++){
				close(fd[k]);
			}

			if( execvp(command[0], command) < 0 ){
				perror(command);
				exit(EXIT_FAILURE);
			}
		}
		pd_idx+=2;

		k=0;
		while(command[k] != NULL) {
			free(command[k]);
			k++;
		}
		free(command);
	}

	for(k = 0; k < 2 * count_pipe; k++){
		close(fd[k]);
	}

	for(k = 0; k < count_pipe + 1; k++)
		wait(&status);
}

