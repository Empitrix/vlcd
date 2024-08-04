#include "../structs.h"
#include "../rules.h"
#include "../utils.h"
#include <SDL2/SDL_stdinc.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
COMM    RED     GREEN   BLUE    Wa      Wb      Ha      Hb      MODE
'\x01', '\xFF', '\xFF', '\xFF', '\x01', '\x90', '\x01', '\x90', '\x01'
TOTAL: 9
*/ 

struct INIT_COMM get_init_comm(unsigned char ord[]){
	struct INIT_COMM com;

	int red, green, blue, i;
	red = green = blue = com.width = com.height = -1;

	unsigned char hold;

	for(i = 0; i < 9; ++i){
		if(i == 0 ){ continue; }

		if(red == -1)
			red = ghex(ord[i]);
		else if (green == -1)
			green = ghex(ord[i]);
		else if (blue == -1)
			blue = ghex(ord[i]);
		else {

			// hold the first part of the hex
			if(i == 4 || i == 6){
				hold = ord[i];
				continue;
			}

			if(com.width == -1)
				com.width = hexm(hold, ord[i]);
			else if(com.height == -1)
				com.height = hexm(hold, ord[i]);
			else
				com.mode = ghex(ord[i]);
		}
	}

	com.color = (SDL_Color){red, green, blue, ALPHA};
	com.ecode = 0;
	return com;
}

