#include <unistd.h>
#include <stdio.h>
int get_login(){
	char info[100];
	if(gethostname(info, 100)==0){
		printf("%s:my login\n",info);
	}
	return 0;

}

int main(){
	get_login();
	return 0;
}
