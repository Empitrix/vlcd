#include "../structs.h"
#include "../rules.h"
#include "../utils.h"
#include <SDL2/SDL_stdinc.h>

/*
COMM    Xa      Xb      Ya      Yb      R       G      B
'\x03', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF'
TOTAL: 8
*/ 

struct SPIXEL_COMM get_spixel_comm(unsigned char ord[]){
	struct SPIXEL_COMM com;

	int red, green, blue, i, hold;
	red = green = blue = com.x = com.y = -1;
  

	for(i = 1; i < 8; ++i){

		if(i == 1 || i == 3)
			hold = ord[i];
		else if (i == 2)
			com.x = hexm(hold, ord[i]);
		else if (i == 4)
			com.y = hexm(hold, ord[i]);
		else {
			if(red == -1)
				red = ghex(ord[i]);
			else if (green == -1)
				green = ghex(ord[i]);
			else
				blue = ghex(ord[i]);
		}
	}

	com.color = (SDL_Color){red, green, blue, ALPHA};
	com.ecode = 0;

	return com;
}

