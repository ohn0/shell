#include "shell.h"

int executeCommand(char** commands, int argFlag){
	//Check the first command in commands to see if it is a built-in command or program.
	char * command = commands[0];
	int state = 0;
	//Check that something exists in the first slot.
	if(commands[0] == NULL){return -1;}
	//Figure out which command the user wants and call proper method.
	if(strcmp(command, "cd") == 0){
		state = executeCD(commands[1]);
	}
	else if (strcmp(command, "clr") == 0){
		state = executeClr();
	}
	else if (strcmp(command, "dir") == 0){
		if(FDstdout == -1){
			printf("Error: Unable to open output file.");}
		state =executeLS(commands);
	}
	else if (strcmp(command, "quit") == 0){
		executeQuit();
	}
	else if (strcmp(command, "help") == 0){
		state = executeHelp();
	}
	else if (strcmp(command, "environ") == 0){
		state = executeEnviron();
	}
	else if (strcmp(command, "echo") == 0){
		state = executeEcho(commands);
	}
	else if (strcmp(command, "pause") == 0){
		state = executePause();
	}
	else{
	//Command was not a built-in command and maybe is a program, try executing it.
		state = executeProgram(commands, NULL, argFlag, 0);
	}
	return state;
}	


int checkValidCommand(char** command, int argField){
	//Ensure command is a valid command and the user isn't trying anything that they shouldn't be allowed to do, like running a built-in command in
	//the background.
	int builtIn = 0;
	if(command[0] == NULL){return 0;}
	if(strcmp(command[0], "cd") == 0 || 
	   strcmp(command[0], "clr") == 0||
	   strcmp(command[0], "dir") == 0||
	   strcmp(command[0], "quit")==0 ||
	   strcmp(command[0], "help") == 0||
	   strcmp(command[0], "environ") == 0||
	   strcmp(command[0], "echo") == 0 ||
	   strcmp(command[0], "pause") == 0){
		builtIn = 1;}

	if(builtIn && (argField & BG_ENABLED)){return 0;}
	//Check the the second half of the pipe also makes sense.
	if(argField & PIPE_ENABLED){
		int i = 0;
		while(command[i] != (char*)END_OF_ARGS){
			if(command[i][0] == '|'){
				if(checkValidCommand(command+1, argField)){
					return 1;}
				else{return 0;}
			}
		i++;
		}
	}
	return 1;
}


