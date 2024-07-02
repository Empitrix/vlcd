#include "../structs.h"
#include "../rules.h"
#include <SDL2/SDL_stdinc.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*   c  r   b   b   w    h   m
min: A 000 000 000 0000 0000 0
max: A 255 255 255 9999 9999 1
exmaple: A255255255111122220
total len: 19*/ 

struct INIT_COMM get_init_comm(char ord[]){
	struct INIT_COMM com;
	int l = (int)strlen(ord);
	int i, c;

	char holder[10];
	int h;

	int red, green, blue;
	red = green = blue = com.width = com.height = -1;

	if(l != 19){com.ecode = 1; return com; }  // broken order

	h = c = i = 0;

	while(ord[i] != '\0'){
		if(i == 0 ){ ++i; continue; }
		c = ord[i];
		holder[h++] = c;

		// non valid cahrs
		if(!isdigit(c)){ com.ecode = 1; return com; }

		if(red == -1 && h == 3){                 // red
			holder[h] = '\0';
			red = atoi(holder);
			h = 0;
		} else if(green == -1 && h == 3){        // green
			holder[h] = '\0';
			green = atoi(holder);
			h = 0;
		} else if(blue == -1 && h == 3){         // blue
			holder[h] = '\0';
			blue = atoi(holder);
			h = 0;
		} else if (com.width == -1 && h == 4){   // width
			holder[h] = '\0';
			com.width = atoi(holder);
			h = 0;
		} else if (com.height == -1 && h == 4){  // height
			holder[h] = '\0';
			com.height = atoi(holder);
			h = 0;
		} else {
			if(com.height != -1){
				holder[h] = '\0';
				com.mode = atoi(holder);
			}
		}
		++i;
	}

	com.bg_color = (SDL_Color){red, green, blue, ALPHA};
	com.ecode = 0;
	return com;
}

