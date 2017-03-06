#include "shell.h"


int executeLS( char** fileName)
{
	//Prints the contents of fileName to the shell. If fileName is not specified, prints contents of current directory.
	char buf[100];
	int arguments = 0;
	int lines = 0;
	int i = 0;
	char spacing[] = "\t";
	struct dirent* dir;
	char* name = fileName[1];
	DIR* my_dir;
	getcwd(buf, sizeof(buf));

	//Check if a fileName is a valid pointer, if it is, ensure it is not a redirection character.
	if (fileName[1] == (char*)-1 || name[0] == '-' || name[0] == '<' || name[0] == '>' || name[0] == '|'){
		my_dir = opendir(buf);
		//Check that fileName is a valid file.	
		if(my_dir == NULL){
			printf("Error opening %s\n", buf);
			return 0;}
	}
	else{my_dir = opendir(name);}
	//Figure out which arguments the user has specified.
	arguments = findArgsLS(arguments, fileName);
	if(arguments & L_ENABLED){
		spacing[0] = '\n';
	}
	//Read the through my_dir and print out the names of each entry.
	while(my_dir != NULL && (dir = readdir(my_dir))){
		//If another dir is encountered and the user has specified they want it's contents, also print those.
		if(dir && (R_ENABLED & arguments) && dir->d_type == DT_DIR && dir->d_name[0] != '.'){
			strcpy(buf, dir->d_name);
			fileName[1] = buf;
			executeLS(fileName);
		}

		//Format the output so it doesn't look awful.
		if(spacing[0] == '\t'){lines++;}

		//If file is hidden, print if the user wanted to see it.
		if((arguments & A_ENABLED)){
			printf("%-30s%s", dir->d_name, spacing);
		}
		else if (dir->d_name[0] != '.'){
			printf("%-30s%s",dir->d_name, spacing);
		}
		if(i == 3 && !(arguments & L_ENABLED)){
			printf("\n");
			i=0;}
		i++;
	}
	if(!(arguments & L_ENABLED)){printf("\n");}
	return 0;
}

int findArgsLS(int argument,  char** command){
	int i = 0;
	//Figure out if the user specified any of the arguments (-l, -a, -r).
	//Return an integer that flags which command was set.
	while(command[i] != (char*)-1){
		if(!(strcmp(command[i], "<") == 0 || 
		   strcmp(command[i], ">") == 0 ||
		   strcmp(command[i], "&") == 0)){
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
		}
		i++;
	}
	return argument;
}
