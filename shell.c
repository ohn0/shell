#include "shell.h"
int currentStdin = 0;
int currentStdout = 1;
int quit = 0;
int pipeStatus;
char** environment;
int main(int argc, char** argv){
	if(argc == 2){
		executeFromFile(argv[1]);
	}
	else if(argc == 1){
		executeFromUser();
	}
	return 0;

}
