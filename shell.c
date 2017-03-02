#include "shell.h"
int quit = 0;
char** environment;
int main(){
	char hostname[100];
	char username[100];
	char userInput[100];
	char cwd[200];
	char* commands[MAX_ARGS];
	int c;
	int i;
	int argField;
	initializeEnvironment();
//	getlogin_r(username, 100);
//	gethostname(hostname, 200);
//	updateCurrentDir(cwd); 
	while(!quit){
		i = 0; c = 0;
		//printf("%s@%s:%s: ", username, hostname, cwd);
		printf("%s@%s:%s: ", environment[2], environment[1], environment[0]);
		while((c = getchar()) != '\n'){
			userInput[i++] = c;
		}
		userInput[i] = '\0';
		//Tokenize
		parseArgument(userInput, commands);
		//Enable redirection
		argField = analyzeArgument(commands);
		if(argField != -1){
			executeCommand(commands, argField);
		}
		else{
			printf("Not a valid command\n");}
		freeArgument(commands, MAX_ARGS);
	}		
	return 0;

}
