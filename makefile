shill: shell.c parseArgument.c analyzeArgument.c prepareIO_BG_PIPE.c executeCd.c executeDir.c executeQuit.c executeProgram.c clr.c redirect.c enablePiping.c findArgLocation.c shell.h
	gcc -g -Wall shell.c parseArgument.c analyzeArgument.c prepareIO_BG_PIPE.c  executeCd.c executeDir.c executeQuit.c executeProgram.c clr.c redirect.c enablePiping.c findArgLocation.c -o shill
