//Add options -a, -l, -R
#include "shell.h"
#define ARG_BEGIN 2
#define MIN_ARG_VAL 2
int executeLS(int argc, char** fileName)
{
	char buf[100];
	int arguments = 0;
	int argLocation = ARG_BEGIN;
	int i = 0;
	char dir_exists = 0;
	char spacing[] = "\t";
	struct dirent* dir;
	char* name = fileName[1];
	DIR* my_dir;
	getcwd(buf, sizeof(buf));
	if (argc < MIN_ARG_VAL || name[0] == '-'){
		my_dir = opendir(buf);	
		argLocation = 1;
	}
	else{my_dir = opendir(name);}
	arguments = findArgsLS(arguments, argc, fileName);
	if(arguments & L_ENABLED){
		spacing[0] = '\n';
	}
	while(my_dir != NULL && (dir = readdir(my_dir))){
		if(dir && (R_ENABLED & arguments) && dir->d_type == DT_DIR && dir->d_name[0] != '.'){
			strcpy(buf, dir->d_name);
			fileName[1] = buf;
			executeLS(argc, fileName);
		}
		if((arguments & A_ENABLED)){
			printf("%s%s", dir->d_name, spacing);}
		else if (dir->d_name[0] != '.'){
			printf("%s%s", dir->d_name, spacing);
		}
	}
	if(!(arguments & L_ENABLED)){printf("\n");}
	return 0;
}

int findArgsLS(int argument, int argc, char** command){
	int i = 0;
	while(i < argc){
	switch(command[i][1]){
		case 'a':
			argument |= A_ENABLED;
			break;
		case 'l':
			argument |= L_ENABLED;
			break;		
		case 'R':
			argument |= R_ENABLED;
			break;
		}
		i++;
	}
	return argument;
}
