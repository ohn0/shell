#include "shell.h"

int executeHelp(){
	//Print the manual using the more filter and wait for it to complete.
	pid_t childID = fork();
	if(childID == 0){
		execlp("more","more", "readme", NULL);
	}
	else{
		waitpid(childID, NULL, 0);}
	return 0;
}

int executePause(){
	//Check to see if enter was typed and do nothing else.
	printf("Hit enter to resume\n");
	int c;
	while((c = getchar()) != 10){
	}
	return 0;
}

int executeEnviron(){
	//Print all the environment strings.
	char* envParam[10];
	envParam[0] = "Shell path:";
	envParam[1] = "login name:";
	envParam[2] = "Hostname:";
	int i = 0;
	while(environment[i] != NULL){
		printf("%s%s\n", envParam[i], environment[i]);
		i++;
	}
	
	return 0;
}
