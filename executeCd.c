#include "shell.h"

int executeCD(char* path){
	if(chdir(path) == -1){
		printf("%s\n", getcwd(NULL, 0));
		return 0;
	}	
	//update PWD
	return 1;
}

