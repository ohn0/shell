#include "shell.h"

int executeFromFile(char* argFile){
	//User started the shell with argFile, from which commands will be read. The program will quit once all commands have been read.
	FILE* args;
	char* line = NULL;
	char input[200];
	size_t len;
	args = fopen(argFile, "r");
	//Check that file is valid, if not, quit.
	if(args == (FILE*)NULL){printf("Invalid file argument.\n"); return 0;}
	//Get an array that will hold commands.
	char* commands[MAX_ARGS];
	int argField;
	initializeEnvironment();
	int i;
	while((getline(&line, &len, args) != -1)){
		//While there are still lines in the file, copy them into a char array.
		strcpy(input, line);
		i = 0;
		while(input[i++] != '\n'){}
		input[i-1] = '\0';
		//Tokenize the char* command and store each token into commands.
		parseArgument(input, commands);
		//Analyze command and set proper I/O redirections, if specified.
		argField = analyzeArgument(commands);
		if(argField != -1 && argField != -2){
			//Execute command.
			executeCommand(commands, argField);
		}
		else if(argField & BG_ENABLED){printf("\n");}
		else{
			//Command not recognized.
			printf("Not a valid command\n");}
		
		resetRedirect();
		freeArgument(commands, MAX_ARGS);
		//If a pipe was created, wait until the child is done.
		if(argField & PIPE_ENABLED){wait(NULL);}
	}
	return 1;
}

int executeFromUser(){
	//Execute any command the user types in, program will quit when user wants to quit.
	char userInput[200];
	char* commands[MAX_ARGS];
	int c;
	int i;
	int argField;
	initializeEnvironment();
	while(!quit){
		i = 0; c = 0;
		//Print the command path and wait for user input.
		printf("%s@%s:%s: ", environment[2], environment[1], environment[0]);
		while((c = getchar()) != '\n'){
			userInput[i++] = c;
		}
		userInput[i] = '\0';
		//Tokenize
		parseArgument(userInput, commands);
		//Analyze command and enable any redirecation.
		argField = analyzeArgument(commands);
		if(argField != -1 && argField != -2){
			executeCommand(commands, argField);
		}
		else if(argField & BG_ENABLED){printf("\n");}
		else{
			//Unrecognized command.
			printf("Not a valid command\n");}
		//Reset I/O, deallocate argument, if user piped, wait for child to finish.
		resetRedirect();
		freeArgument(commands, MAX_ARGS);
		if(argField & PIPE_ENABLED){wait(NULL);}
	}		
	return 1;
}
