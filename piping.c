//Piping works
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv){
	int pipefd[2];
	pipefd[1] = open(argv[2], O_WRONLY, S_IRWXU);
	pipefd[0] = open(argv[1], O_RDONLY); 
	dup2(pipefd[0], 0);
	dup2(pipefd[1], 1);
	pipe(pipefd);
	char buf[100];
	scanf("%s", buf);
	printf("%s", buf);
	close(pipefd[0]); close(pipefd[1]);


	return 0;
}
