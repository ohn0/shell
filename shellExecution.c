#include "shell.h"

int executeFromFile(char* argFile){
	FILE* args;
	char* line = NULL;
	char input[200];
	size_t len;
	args = fopen(argFile, "r");
	if(args == (FILE*)NULL){printf("Invalid file argument.\n"); return 0;}
	char* commands[MAX_ARGS];
	int argField;
	initializeEnvironment();
	int i;
	while((getline(&line, &len, args) != -1)){
		strcpy(input, line);
		i = 0;
		while(input[i++] != '\n'){}
		input[i-1] = '\0';
		parseArgument(input, commands);
		argField = analyzeArgument(commands);
		if(argField != -1 && argField != -2){
			executeCommand(commands, argField);
		}
		else if(argField & BG_ENABLED){printf("\n");}
		else{
			printf("Not a valid command\n");}

		resetRedirect();
		freeArgument(commands, MAX_ARGS);
		if(argField & PIPE_ENABLED){wait(NULL);}
	}
	return 1;
}

int executeFromUser(){
	char userInput[200];
	char* commands[MAX_ARGS];
	int c;
	int i;
	int argField;
	initializeEnvironment();
	while(!quit){
		i = 0; c = 0;
		printf("%s@%s:%s: ", environment[2], environment[1], environment[0]);
		while((c = getchar()) != '\n'){
			userInput[i++] = c;
		}
		userInput[i] = '\0';
		//Tokenize
		parseArgument(userInput, commands);
		//Enable redirection
		argField = analyzeArgument(commands);
		if(argField != -1 && argField != -2){
			executeCommand(commands, argField);
		}
		else if(argField & BG_ENABLED){printf("\n");}
		else{
			printf("Not a valid command\n");}

		resetRedirect();
		freeArgument(commands, MAX_ARGS);
		if(argField & PIPE_ENABLED){wait(NULL);}
	}		
	return 1;
}
