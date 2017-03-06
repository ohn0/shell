#include "shell.h"

int executeFromCWD(char** command, int argFlag){
	//This was to execute a program for the current directory before I merged it with the general executeProgram method.
	//The current dir would be search for any executables and if found, would be executed.
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
	//Executes a program, requires the execution dir,  arg, which is an argument field, and a flag specifying if a pipe was activated.
	//Create an array to hold command parameters.
	char* argList[20];
	int i = 0;
	//Iterate through command and copy each char* to argList until the end of the command is reached or a redirection symbol is encountered.
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
	//Fork if no pipe was activated.
	if(piped){ myID = 0; piped = 0; }
	else { myID = fork(); }
	int exeVal = 0;
	//If child, check if user wants a background execution, if so, redirect output to an output_file.
	//Execute the command, if it is an invalid program, tell the user and exit.
	if(myID == 0){
		if(FDstdout == STD_OU && (arg & BG_ENABLED)){
			redirect("output_file", currentStdout);
		}
		if(argList[1] == NULL){exeVal = execl(command[0], command[0], NULL);}
		exeVal = execvp(command[0], argList);
		if(exeVal == -1){printf("Error executing %s\n", command[0]);exit(0); }
	}
	//If parent, wait for the child to complete if this is not a background process, or else just return.
	else{
		if(!(arg & BG_ENABLED)){
			waitpid(myID, NULL, 0);
		}else{return 2; }
	}
	return 0;
}
