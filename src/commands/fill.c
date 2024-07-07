#include "../structs.h"
#include "../rules.h"
#include "../utils.h"
#include <SDL2/SDL_stdinc.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
COMM    RED     GREEN   BLUE
'\x03', '\xFF', '\xFF', '\xFF'
TOTOAL: 4
*/ 

struct FILL_COMM get_fill_comm(char ord[]){
	struct FILL_COMM com;

	int red, green, blue, i;
	red = green = blue = -1;

	for(i = 1; i < 4; ++i){
		if(red == -1)
			red = ghex(ord[i]);
		else if (green == -1)
			green = ghex(ord[i]);
		else
			blue = ghex(ord[i]);
	}

	com.color = (SDL_Color){red, green, blue, ALPHA};
	com.ecode = 0;
	return com;
}

