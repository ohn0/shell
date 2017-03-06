#include "shell.h"

int executeCD(char* path){
	//Change the current directory.
	if(path == (char*)-1){
		//If no path was specified, print the current directory and return.
		printf("%s\n", getcwd(NULL,0));
		return 0;
	}
	//Check that a valid directory was specified.
	if(chdir(path) == -1){
		printf("Error: Directory %s does not exist.\n", path);
		return 0;
	}
	//Update the environment variable pertaining to the current path.	
	updateCurrentDir();
	return 1;
}

void updateCurrentDir(){
	getcwd(environment[0], 100);
}

void initializeEnvironment(){
	//Initialize environment strings, I have 10 in case I would need to add any more.
	//Currently only the current dir, login name, and host name are environment variables.
	//The environment array needs a NULL after the last valid environment variable.
	environment = (char**) malloc(10 * sizeof(char*));
	int i = 0;
	while(i < 10){
		environment[i] = (char*) malloc(100 * sizeof(char));
		i++;
	}
	


	getcwd(environment[0], 100);
	getlogin_r(environment[1], 100);
	gethostname(environment[2], 100);

	environment[3] = NULL;
}
