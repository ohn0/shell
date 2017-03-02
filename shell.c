#include "shell.h"
int quit = 0;
int main(){
	char hostname[100];
	char username[100];
	char userInput[100];
	char cwd[200];
	char* commands[MAX_ARGS];
	int c;
	int i;
	initizializeEnvironment();
	getlogin_r(username, 100);
	gethostname(hostname, 200);
	updateCurrentDir(cwd); 
	while(!quit){
		i = 0; c = 0;
		printf("%s@%s:%s: ", username, hostname, cwd);
		while((c = getchar()) != '\n'){
			userInput[i++] = c;
		}
		userInput[i] = '\0';
		//Tokenize
		parseArgument(userInput, commands);
		//Enable redirection
		if(!analyzeArgument(commands) == -1){
			freeArgument(commands, MAX_ARGS);}
	}		
	return 0;

}
