#include "shell.h"

int analyzeArgument(char** command){
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
	if(argumentError){return -1;}
	return argField;	
}


int generateArgFlag(char* commandParameter, int* argField, char* command){
	if(strcmp(commandParameter, "<") == 0){
		if(activateParameter(argField, IN_ENABLED, command)){
		}else{return 1;}
	}
	else if(strcmp(commandParameter, ">") == 0){
		if(activateParameter(argField, OUT_ENABLED, command)){
		}else{return 1;}
	}
	else if(strcmp(commandParameter, ">>") == 0){
		if(activateParameter(argField, OUT_APP_ENABLED, command)){
		}else{return 1;}
	}
	else if(strcmp(commandParameter, "|") == 0){
		if(activateParameter(argField, PIPE_ENABLED, command)){
		}else{return 1;}
	}
	else if(strcmp(commandParameter, "&") == 0 && command == END_OF_ARGS){
		*argField |= BG_ENABLED;
		}
	return 0;
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
