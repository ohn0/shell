#include "shell.h"
int currentStdin = 0;
int currentStdout = 1;
int quit = 0;
int pipeStatus;
char** environment;
int main(int argc, char** argv){
	//If user specified a file, execute as a file reader, otherwise execute by reading from the keyboard.
	if(argc == 2){
		executeFromFile(argv[1]);
	}
	else if(argc == 1){
		executeFromUser();
	}
	return 0;

}
