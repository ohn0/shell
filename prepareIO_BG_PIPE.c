#include "shell.h"

int prepareIO_BG_PIPE(char** commands, int argField){
	//Input is a char* array containing the parsed commands, as well as an integer field containing any specified flags.
	//Returns 0 if there's a problem.
	int i = 0;
	int j = 0;
	pid_t childA;
	int pipeFD[2];
	char path[100];
	getcwd(path, 100);
	int pipeArgLoc =  0;
	if(argField & PIPE_ENABLED){
		int pipeLoc = 0;
		//We need an array to store all the arguments after the pipe, as they will be sent to an exec system call.
		char * postPipe[20];
		//Isolate the char* after the pipe into another array, and record the location of the pipe.
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
		//Create the pipe and fork.
		if(pipe(pipeFD) != 0){return 0;}
		childA = fork();
		pipeStatus = childA;
		//Redirect the parent's stdout into the pipe's write end. Close unneeded file descriptors.
		if(childA != 0){
			FDstdout = dup(STD_OU);
			close(pipeFD[0]);
			dup2(pipeFD[1], 1);
			close(pipeFD[1]);
		}
		else{
		//Redirect the child's stdin into the pipe's read end. Close unneeded file descriptors.
			close(pipeFD[1]);
			dup2(pipeFD[0], 0);
			close(pipeFD[0]);
			execvp(commands[pipeArgLoc], postPipe);
		}
	}

	return 1;
}
