#include "shell.h"

int prepareIO_BG_PIPE(char** commands, int argField){
	if(argField & PIPE_ENABLED){
	
	}

	if(argField & BG_ENABLED){
		pid_t myID = fork();
		if(myID == 0){
			printf("running\n");
			quit = 1;
			close(1);
		}
		else{
			freeCommand(commands[0]);
		}
	}

}
