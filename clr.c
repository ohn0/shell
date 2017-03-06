#include "shell.h"
//Clears the shell screen.
int executeClr()
{
	char newlines[100];
	int i;
	for(i = 0; i < 100; i++){
		newlines[i] = '\n';
	}
	newlines[i-1] = '\0';
	//Reset the cursor to the top left corner of the shell.
	printf("%s\033[H", newlines);



	return 0;
}
