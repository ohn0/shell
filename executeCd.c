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
	getcwd(environment[0], 100);
}

void initializeEnvironment(){
	environment = (char**) malloc(10 * sizeof(char*));
	int i = 0;
	while(i < 10){
		environment[i] = (char*) malloc(100 * sizeof(char));
		i++;
	}
	getcwd(environment[0], 100);
	getlogin_r(environment[1], 100);
	gethostname(environment[2], 100);
}
