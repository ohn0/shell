#include "shell.h"

char** parseArgument(char* command, char** commands){
	char* arg = strtok(command, " ");
	int i = 0;
	size_t argLen;
	while(arg){
		argLen = strlen(arg);
		commands[i] = (char*) malloc((argLen)*sizeof(char));
		strcpy(commands[i++], arg);
		arg = strtok(NULL, " ");
	}	
	commands[i] = (char*)-1;
	return commands;
}

int freeArgument(char** argList, int argSize){
	//deallocate the entire command.
	int cp = 0;
	while(argList[cp] != (char*)-1){
		if(argList[cp] != NULL){
			freeCommand(argList[cp]);
		}
		cp++;
	}
	argList[cp] = NULL;
	return 1;
}
