#include "shell.h"
int FDstdout = 1;
int FDstdin = 0;
int analyzeArgument(char** command){
	if(command[0] == -1){
		return -1;
	}
	char* commandParameter;
	int i = 0;
	int argField = 0;
	int argumentError = 0;
	while(command[i] != (char*)END_OF_ARGS){
		commandParameter = command[i];
		if(commandParameter != NULL){
			argumentError = generateArgFlag(commandParameter, &argField, command[i+1]);
		}
		i++;	
	}
	
	if(checkValidCommand(command, argField) == 0){printf("Error: cannot make built-in function a background process.\n"); return -1 ;}


	if(argField & PIPE_ENABLED){
	//	enablePiping(command);
	}

	if(argField & BG_ENABLED){
	//	if(!prepareIO_BG_PIPE(command, argField)){return -2;}
	}

	if(!argumentError){return -1;}
	return argField;	
}


int generateArgFlag(char* commandParameter, int* argField, char* command){
	int validRedirect = 1;
	if(strcmp(commandParameter, "<") == 0){
		validRedirect = redirect(command, STD_IN);
	}
	else if(strcmp(commandParameter, ">") == 0){
		validRedirect = redirect(command, STD_OU);
	}
	else if(strcmp(commandParameter, ">>") == 0){
		validRedirect = redirect(command, STD_OU_APPEND);
	}
	else if(strcmp(commandParameter, "|") == 0){
		*argField |= PIPE_ENABLED;
	}
	else if(strcmp(commandParameter, "&") == 0 && command == END_OF_ARGS){
		*argField |= BG_ENABLED;
		}
	

	return validRedirect;
}

int freeCommand(char* command){
	free((char*) command);
	command = NULL;
	return 1;
}
int activateParameter(int* argField, int flag, char* nextCommand){
	if(nextCommand != NULL){
		*argField |= flag;
		return 1;
	}
	else{
		return 0;
	}

}
