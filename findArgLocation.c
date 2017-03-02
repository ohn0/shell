#include "shell.h"

int executeCommand(char** commands, int argFLag){
	char * command = commands[0];

	if(strcmp(command, "cd") == 0){
		executeCD(commands[1]);
	}
	else if (strcmp(command, "clr") == 0){
		executeClr();
	}
	else if (strcmp(command, "dir") == 0){
		if(FDstdout == -1){
			printf("PROBLEM");}
		executeLS(commands);
	}
	else if (strcmp(command, "quit") == 0){
		executeQuit();}
	else{
		executeProgram(commands, argFLag);}
	if(FDstdin != STD_IN){
		dup2(FDstdin, STD_IN);
	}
	if(FDstdout != STD_OU){
		dup2(FDstdout, STD_OU);
	}
//	resetRedirect();
	return 1;
}	



