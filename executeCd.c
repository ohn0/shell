#include "shell.h"

int executeCD(char* path){
	if(chdir(path) == -1){
		printf("%s\n", getcwd(NULL, 0));
		return 0;
	}	
	updateCurrentDir();
	return 1;
}


void updateCurrentDir(){
	char* cwd = (char *) malloc(200 * sizeof(char));
	getcwd(cwd, 200);
	return cwd;
}

void initializeEnvironment(){
	char** environment = (char**) malloc(10 * sizeof(char*));
	int i = 0;
	while(i < 10){
	//	environment[i] = (char*) malloc
	}
}
