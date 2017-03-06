#include "shell.h"
int FDstdout = 1;
int FDstdin = 0;
int analyzeArgument(char** command){
	//Analyze the command and flag any redirection or pipes the user specified. These flags are in an int and will be used later in the case of pipes and background execution.
	//Make sure user actually typed something.
	if(command[0] == (char*)-1){
		return -1;
	}
	char* commandParameter;
	int i = 0;
	int argField = 0;
	int argumentError = 0;
	//Parse each command to see if it is an argument or redirection character.
	while(command[i] != (char*)END_OF_ARGS){
		commandParameter = command[i];
		if(commandParameter != NULL){
			//Check argument and set proper flag depending on which argument specified, if user wants redirection, it will be activated.
			argumentError = generateArgFlag(commandParameter, &argField, command[i+1]);
		}
		i++;	
	}
	//Check to make sure the command makes sense.
	if(checkValidCommand(command, argField) == 0){printf("Error: cannot make built-in function a background process.\n"); return -1 ;}

	//Create a pipe if the user specified.
	if(argField & PIPE_ENABLED){
		prepareIO_BG_PIPE(command, argField);
	}
	//Something went wrong.
	if(!argumentError){return -1;}

	return argField;	
}


int generateArgFlag(char* commandParameter, int* argField, char* command){
	int validRedirect = 1;
	//Compare each parameter to see if it is a redirection, background, or pipe symbol.
	//If it's a redirection symbol, perfrom the redirection operation.
	if(strcmp(commandParameter, "<") == 0 && currentStdin == 0){
		validRedirect = redirect(command, STD_IN);
	}
	else if(strcmp(commandParameter, ">") == 0 && currentStdout == 1){
		validRedirect = redirect(command, STD_OU);
	}
	else if(strcmp(commandParameter, ">>") == 0 && currentStdout == 1){
		validRedirect = redirect(command, STD_OU_APPEND);
	}
	else if(strcmp(commandParameter, "|") == 0){
		*argField |= PIPE_ENABLED;
	}
	else if(strcmp(commandParameter, "&") == 0 && command == (char*)END_OF_ARGS){
		*argField |= BG_ENABLED;
		}
	

	return validRedirect;
}

int freeCommand(char* command){
	//Deallocate any commands and set the char* to NULL.
	free((char*) command);
	command = (char*)NULL;
	return 1;
}
int activateParameter(int* argField, int flag, char* nextCommand){
	//This was to activate I/O flags before I realized I could just redirect and not use flags for I/O.
	if(nextCommand != NULL){
		*argField |= flag;
		return 1;
	}
	else{
		return 0;
	}

}
