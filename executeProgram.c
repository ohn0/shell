#include "shell.h"

int executeProgram(char** command, int arg){
	DIR* bin = opendir("/bin");
	struct dirent* binEntry;
	char* argList[20];
	int i = 0;
	while(command[i] != -1){
		if(command[i][0] == '<' || command[i][0] == '>' ||
		   command[i][0] == '|' || command[i][0] == '&'){
			argList[i] = NULL;
			break;
		}
		else{
			argList[i] = command[i];
		}
		i++;}
	while((binEntry = readdir(bin)) != NULL){
		if(strcmp(command[0], binEntry->d_name) == 0){
			pid_t myID = fork();
			if(myID == 0){
				execvp(command[0], argList);	
			}
			else{
				waitpid(myID, NULL, NULL);
			}
		}
	}
	return 0;
}
