#ifndef _SHELL_H
#define _SHELL_H
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#define STD_IN 0
#define STD_OU 1
#define STD_OU_APPEND 2
#define A_ENABLED 	 0x1
#define L_ENABLED 	 0x10
#define R_ENABLED 	 0x100
#define IN_ENABLED 	 0x1
#define PIPE_ENABLED	 0x10
#define BG_ENABLED	 0x100
#define END_OF_ARGS	 -0x1
#define MAX_ARGS 200
extern int FDstdout;
extern int FDstdin;
extern int currentStdout;
extern int quit;
extern int currentStdin;
extern char** environment;
extern int pipeStatus;
int executeFromFile(char *);
int executeFromUser();
int redirect(char *, int);
int resetRedirect();
int executeCommand(char**, int);
int executeFromBin(char**, int);
int executeFromCWD(char**, int);
int executeProgram(char**, char *, int, int);
int executeLS(char**);
int executeCD(char*);
int findArgsLS(int, char**);
int checkValidCommand(char**, int);
void updateCurrentDir();
void initializeEnvironment();
char** parseArgument(char*, char**);
int freeArgument(char**, int);
int freeCommand(char*);
int prepareIO_BG_PIPE(char** ,int);
int activateParameter(int*, int, char*);
int analyzeArgument(char**);
int executeQuit();
int executeHelp();
int executeEnviron();
int executeEcho(char**);
int executePause();
int executeClr();
int generateArgFlag(char*, int*, char*);
#endif
