#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

/* pexit: program exit: exit the program with a return code and message */
void pexit(int ecode, char *format, ...){
	char *msg = malloc(sizeof(char *));
	va_list args;
	va_start(args, format);
	vsprintf(msg, format, args);
	va_end(args);
	printf("%s\n", msg);
	exit(ecode);
}


int e_return(int ecode, char *format, ...){
	char *msg = malloc(sizeof(char *));
	va_list args;
	va_start(args, format);
	vsprintf(msg, format, args);
	va_end(args);
	printf("%s\n", msg);
	return ecode;
}

/* get initial response: get flags from argument (user) */
struct InitRes get_init_res(int argc, char *argv[]){
	struct InitRes ires;

	if(argc != 3)
		pexit(1,
			"Argument Error:\n%s <SCALE:8-bit> <PORT:16-bit>", argv[0]);

	for(int i = 0; i < argc; ++i)
		if(i == 0)
			continue;
		else
			if(!ires.scale){
				if((ires.scale = atoi(argv[i])) > 8)
					ires.scale = 8;
				else if (ires.scale < 1)
					ires.scale = 1;
			} else
				ires.port = atoi(argv[i]);

	return ires;
}

