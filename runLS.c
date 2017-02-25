#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
void get_line(char*)
int main()
{
	char[30] line;
//	pid_t lsFork = fork();
//
//	if(lsFork == 0)
//	{
//		execlp("/bin/ls","/bin/ls",  NULL);
//	}
//	else{
//		waitpid(lsFork,NULL, 0);
//	}
	char[30] name;
	getcwd(name, 30);
	while(1)
	{
		printf("%s:", name);
		get_line(line);
	}


	return 0;
}

void get_line(char * line){
	int c,i;
	i = 0;
	while((c = getchar())!=EOF)
	{
		line[i++] = c;	
	}

}
