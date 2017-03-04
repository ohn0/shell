#include "shell.h"

int prepareIO_BG_PIPE(char** commands, int argField){
	if(argField & PIPE_ENABLED){
	
	}

	if(argField & BG_ENABLED){
		pid_t myID = fork();
		if(myID == 0){
			quit = 1;
			printf("Background: %d\n", getpid());
		}
		else{
			return 0;
		}
	}
	return 1;
}
