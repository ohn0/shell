#include "shell.h"

int prepareIO_BG_PIPE(char** commands, int argField){
	int i = 0;
	int j = 0;
	pid_t childA;
	int pipeFD[2];
	char path[100];
	getcwd(path, 100);
	int pipeArgLoc =  0;
	if(argField & PIPE_ENABLED){
		int pipeLoc = 0;
		char * postPipe[20];
		while(commands[i] != (char*)END_OF_ARGS){
			if(pipeLoc){
				postPipe[j] = commands[i];
				j++;
			}
			if(commands[i][0] == '|'){
				pipeLoc = 1;
				pipeArgLoc = i+1;
			}
			i++;
		}
		postPipe[j] = NULL;
		if(pipe(pipeFD) != 0){return 0;}
		childA = fork();
		pipeStatus = childA;
		if(childA != 0){
			FDstdout = dup(STD_OU);
			close(pipeFD[0]);
			dup2(pipeFD[1], 1);
			close(pipeFD[1]);
		}
		else{
			close(pipeFD[1]);
			dup2(pipeFD[0], 0);
			close(pipeFD[0]);
			execvp(commands[pipeArgLoc], postPipe);
		}
	}

	return 1;
}
