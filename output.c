#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int fd = open("input", O_RDONLY);
	dup2(fd,0);
	char buf[100];
	int i = scanf("%s", buf);
	printf("%s\n", buf);


	return 0;
}
