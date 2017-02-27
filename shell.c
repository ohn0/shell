#include <unistd.h>
#include <stdio.h>
int main(){
	char hostname[100];
	char username[100];
	char userInput[100];
	char cwd[100];
	char* commands[20];
	int c,i;
	getlogin_r(username, 100);
	gethostname(hostname, 200);
	getcwd(cwd, 100);
	while(1){
		i = 0; cp = 0;
		printf("%s@%s:%s: ", username, hostname, getcwd);
		while((c = getchar()) != '\n'){
			userInput[i++] = c;
		}
		userInput[i] = '\0';
		freeArgument(commands, 20);
		commands = parseArgument(userInput);
	}		
	return 0;

}
