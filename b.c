#include <stdio.h>
int main(){
	int c;
	while((c = getchar()) != '\n'){
		printf("Read %c\n", c);
	}
	return 0;
}
