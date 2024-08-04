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
comm    Xa      Xb      Ya      Yb      Wa      Wb      Ha      Hb     ...MONO[0, 1]/RGB (WIDTH.HEIGHT)
'\x02', '\x00', '\xFA', '\x00', '\xFA', '\x00', '\x02', '\x00', '\x02' ...MONO[0, 1]/RGB (WIDTH.HEIGHT)
total len: (MUST HAVE: 9)
*/ 


/* Update the screen buffer by given hex for mono-color */
void update_mono_buffer(unsigned char hex, unsigned char buff[], int idx, int width){
	int stepper = idx;

	if(idx >= width)
		stepper += (idx - (idx % width)) * 7;

	for (int i = 0; i <= 7; i += 1) {
		buff[stepper] = (hex & 1) ? '\x00' : '\xFF';  // Reverse
		hex >>= 1;
		stepper += width;
	}

}

#define MAX 9

struct FRAME_COMM get_frame_comm(unsigned char ord[]){
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
	
	if(canvas.mono){
		for(int i = 0; i < comm.height * comm.width; i++)
			comm.mono_data[i] = '\x00';
	}


	int basesiz = comm.width * comm.height;

	if(canvas.mono)  // one byte for mono color
		basesiz /= 8;
	else
		basesiz *= 3;  // three byte for each value of full color (r, g, b)

	basesiz += MAX;


	// captrue secondary(color) data
	for(j = 0; i < basesiz ; ++i, j++){
		if(canvas.mono)
			update_mono_buffer(ord[i], comm.mono_data, j, comm.width);
		else {
			if(red == -1)
				red = ghex(ord[i]);
			else if(green == -1)
				green = ghex(ord[i]);
			else {
				blue = ghex(ord[i]);
				comm.data[j] = (SDL_Color){red, green, blue, ALPHA};
				red = green = blue = -1;
			}
		}
	}

	comm.ecode = 0;
	return comm;
}

