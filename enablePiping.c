#include "shell.h"

int enablePiping(char** command){
	int pipeFD[2];
	pipe(pipeFD);
	pid_t child = fork();
	if(child == 0){
		close(pipeFD[1]);
		redirect(STD_IN, pipeFD[0]);
	}
	else{
		close(pipeFD[0]);
		redirect(STD_OU, pipeFD[1]);
	}
	

}
