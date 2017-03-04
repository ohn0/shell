#include "shell.h"
int currentStdin = 0;
int currentStdout = 1;
int redirect(char* newRedirect, int oldFD){
	int newFd;
	FDstdout = dup(STD_OU);
	FDstdin = dup(STD_IN);
	if(oldFD == 2){
		newFd = open(newRedirect, O_CREAT|O_WRONLY|O_APPEND, S_IRWXU|S_IRWXG|S_IRWXO);
		currentStdout = dup2(newFd, STD_OU);
		if (currentStdout == -1){
			return 0;}
	}
	if(oldFD){
		newFd = open(newRedirect, O_CREAT|O_WRONLY, S_IRWXU|S_IRWXG|S_IRWXO);
		currentStdout = dup2(newFd, oldFD);
	}
	else{
		newFd = open(newRedirect, O_RDONLY);
		currentStdin = dup2(newFd, oldFD);
	}
	if(currentStdout == -1 || currentStdin == -1){
		return 0;}

	return 1;
}

int resetRedirect(){
	if(FDstdin != STD_IN){
		dup2(FDstdin, STD_IN);
	}
	if(FDstdout != STD_OU){
		dup2(FDstdout, STD_OU);
	}
	return 0;
}
