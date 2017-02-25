#include "shell.h"
int redirect(char* newStdin, int oldFD){
	int newFd;
	if(oldFD == 2){
		newFd = open(newStdin, O_WRONLY|O_APPEND);
		dup2(newFd, oldFD);
		return 1;
	}
	if(oldFD){
		newFd = open(newStdin, O_WRONLY);
	}
	else{
		newFd = open(newStdin, O_RDONLY);
	}
	dup2(newFd, oldFD);
	return 1;
}

int resetRedirect(){
	//Set FD to originals
}
