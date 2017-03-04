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
	argList[i] = NULL;
	while((binEntry = readdir(bin)) != NULL){
		if(strcmp(command[0], binEntry->d_name) == 0){
			pid_t myID = fork();
			if(myID == 0){
				printf("Executing %s in %d", command[0], getpid());
				if(currentStdout == 1 && (arg & BG_ENABLED)){
					redirect("output_file", currentStdout);
				}
				if(argList[1] == NULL){execl(command[0], command[0], NULL);}
				execvp(command[0], argList);	
			}
			else{
				if(!(arg & BG_ENABLED)){
					waitpid(myID, NULL, NULL);
				}else{return 2;}
			}
		}
	}
	return 0;
}
