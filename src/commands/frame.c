#include "../structs.h"
#include "../rules.h"
#include "../utils.h"
#include "../canvas.h"
#include <SDL2/SDL_stdinc.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
commM    Xa      Xb      Ya      Yb      Wa      Wb      Ha      Hb     ...MONO[0, 1]/RGB (WIDTH.HEIGHT)
'\x02', '\x00', '\xFA', '\x00', '\xFA', '\x00', '\x02', '\x00', '\x02' ...MONO[0, 1]/RGB (WIDTH.HEIGHT)
total len: (MUST HAVE: 9)
*/ 

#define MAX 9

struct FRAME_COMM get_frame_comm(char ord[]){
	struct FRAME_COMM comm;

	int red, green, blue, i, j, hold;
	red = green = blue = comm.x = comm.y
		= comm.height = comm.width = -1;

	// captrue primary data
	for(i = 1; i < MAX; ++i){
		if(i == 1 || i == 3 || i == 5 || i == 7){
			hold = ord[i];
			continue;
		}

		if(comm.x == -1)
			comm.x = hexm(hold, ord[i]);
		else if(comm.y == -1)
			comm.y = hexm(hold, ord[i]);
		else if(comm.width == -1)
			comm.width = hexm(hold, ord[i]);
		else 
			comm.height = hexm(hold, ord[i]);
	}

	// captrue secondary(color) data
	for(j = 0; i < ((comm.width * comm.height) * (canvas.mono ? 1 : 3)) + MAX; ++i){

		if(canvas.mono)
			comm.data[j++] = MONOKLR;
		else {
			if(red == -1)
				red = ghex(ord[i]);
			else if(green == -1)
				green = ghex(ord[i]);
			else {
				blue = ghex(ord[i]);
				comm.data[j++] = (SDL_Color){red, green, blue, ALPHA};
				red = green = blue = -1;
			}
		}
		
	}

	comm.ecode = 0;
	return comm;
}

