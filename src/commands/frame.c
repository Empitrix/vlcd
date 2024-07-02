#include "../structs.h"
#include "../rules.h"
#include <SDL2/SDL_stdinc.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// set a frame
struct FRAME_COM {
	int x, y;
	int width, height;
	int color[3];
	enum COLOR_MODE mode;
	int ecode;  // exit code
};

// /*   c x    y    w    h    r g b m
// min: B 0000 0000 0000 0000 0 0 0 0
// exmaple: B00000000000000000000
// total len: 21*/ 

struct FRAME_COMM get_frame_comm(char ord[]){
	struct FRAME_COMM com;
	int l = (int)strlen(ord);
	int i, c;

	/*
	char holder[10];
	int h;


	if(l != 21){com.ecode = 1; return com; }  // broken order

	while(ord[i] != '\0'){
		if(i == 0 ){ ++i; continue; }
		c = ord[i];
		holder[h++] = c;

		// non valid cahrs
		if(!isdigit(c)){ com.ecode = 1; return com; }

		++i;
	}

	com.ecode = 0;
	*/
	com.ecode = 1;
	return com;
}

