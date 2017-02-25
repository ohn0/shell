#include "shell.h"

char** parseArgument(char* command){
	char** arguments = (char**) malloc(20 * sizeof(char*));
	char* arg = strtok(command, " ");
	int i = 0;
	size_t argLen;
	while(arg){
		argLen = strlen(&arg);
		arguments[i] = (char*) malloc(argLen*sizeof(char));
		strcpy(arguments[i++], arg);
		arg = strtok(NULL, " ");
	}	
	arguments[i] = -1;
	return arguments;
}
