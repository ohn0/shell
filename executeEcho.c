#include "shell.h"

int executeEcho(char** commands){
	int i = 0;
	//Prints everything in commands except the first value to stdout. Stops if it encounters a redirection or pipe symbol.
	while(commands[i+1] != (char*)END_OF_ARGS){
		if(commands[i+1][0] == '<' || commands[i+1][0] == '>' || commands[i+1][0] == '|'){break;}
		printf("%s ", commands[i+1]);
		i++;
	}
	printf("\n");


	return 0;
}
