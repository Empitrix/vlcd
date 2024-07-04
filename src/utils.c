#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
	return ecode;
}

/* get initial response: get flags from argument (user) */
struct InitRes get_init_res(int argc, char *argv[]){
	struct InitRes ires;
	ires.scale = ires.port = -1;

	if(argc != 3)
		pexit(1,
			"Argument Error:\n%s <SCALE:8-bit> <PORT:16-bit>", argv[0]);

	for(int i = 0; i < argc; ++i)
		if(i == 0)
			continue;

		// scale
		else if(i == 1){
			if((ires.scale = atoi(argv[i])) > 8)
				ires.scale = 8;
			else if (ires.scale < 1)
				ires.scale = 1;
		}
		else
			ires.port = atoi(argv[i]);

	return ires;
}



struct SCREEN_SIZE get_screen_size(){
	/* get screen width x height using 'xdpyinfo' */
	FILE *fp;
	struct SCREEN_SIZE size;
	fp = popen("xdpyinfo | grep dimensions", "r");
	int c, i, h;
	i = h = 0;
	char holder[1024];

	size.width = size.height = 0;
	while((c = getc(fp)) != EOF){
		if(i > 16 && i < 26){
			if(c == 'x'){
				holder[h] = '\0';
				size.width = atoi(holder);
				h = 0;
			} else
				holder[h++] = c;
		}
		++i;
	}

	holder[h] = '\0';
	size.height = atoi(holder);
	pclose(fp);
	return size;
}



int change_access(int w, int h){
	struct SCREEN_SIZE win_size;
	win_size = get_screen_size();  // get screen size
	// printf("%d %d\n", win_size.width, w);
	if(win_size.width >= w && win_size.height >= h){
		return 1;
	}
	return 0;
}