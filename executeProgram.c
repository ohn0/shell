#include "shell.h"

int executeFromCWD(char** command, int argFlag){
	char path[100];
	getcwd(path, 100);
	
	DIR* myDir = opendir(path);
	struct dirent* dirEntry;
	while((dirEntry = readdir(myDir)) != NULL){
		if(access(dirEntry->d_name, X_OK) == 0 && strcmp(command[0], dirEntry->d_name) == 0){
			executeProgram(command, path, argFlag, 0);
		}
	}
	return 0;

}

int executeProgram(char** command, char* execDir, int arg, int piped){
	char* argList[20];
	int i = 0;
	while(command[i] !=(char*) -1){
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
	pid_t myID;
	if(piped){ myID = 0; }
	else { myID = fork(); }
	int exeVal = 0;
	if(myID == 0){
		if(FDstdout == STD_OU && (arg & BG_ENABLED)){
			redirect("output_file", currentStdout);
		}
		if(argList[1] == NULL){exeVal = execl(command[0], command[0], NULL);}
		exeVal = execvp(command[0], argList);
		if(exeVal == -1){printf("Error executing %s\n", command[0]);exit(0); }
	}
	else{
		if(!(arg & BG_ENABLED)){
			waitpid(myID, NULL, 0);
		}else{return 2; }
	}
//	while((binEntry = readdir(bin)) != NULL){
//		if(strcmp(command[0], binEntry->d_name) == 0){
//			pid_t myID;
//			if(piped){ myID = 0; }
//			else { myID = fork(); }
//			if(myID == 0){
//				printf("Executing %s in %d", command[0], getpid());
//				if(FDstdin == STD_IN  && (arg & BG_ENABLED)){
//					redirect("output_file", currentStdout);
//				}
//				if(argList[1] == NULL){execl(command[0], command[0], NULL);}
//				execvp(command[0], argList);	
//			}
//			else{
//				if(!(arg & BG_ENABLED)){
//					waitpid(myID, NULL, NULL);
//				}else{return 2;}
//			}
//		}
//	}
	return 0;
}
