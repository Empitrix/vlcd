#include "../structs.h"
#include "../rules.h"
#include <SDL2/SDL_stdinc.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*   c r   b   b
min: C 000 000 000
max: C 255 255 255
exmaple: C255255255
total len: 10*/ 

struct FILL_COMM get_fill_comm(char ord[]){
	struct FILL_COMM com;
	int l = (int)strlen(ord);
	int i, c;

	char holder[10];
	int h;

	// broken order
	if(l != 10){com.ecode = 1; return com; }

	h = c = i = 0;
	int red, green, blue;
	red = green = blue = -1;

	while(ord[i] != '\0'){
		if(i == 0 ){ ++i; continue; }
		c = ord[i];
		holder[h++] = c;

		// non valid cahrs
		if(!isdigit(c)){ com.ecode = 1; return com; }

		if(red == -1 && h == 3){           // red
			holder[h] = '\0';
			red = atoi(holder);
			h = 0;
		} else if(green == -1 && h == 3){  // green
			holder[h] = '\0';
			green = atoi(holder);
			h = 0;
		} else if(blue == -1 && h == 3){   // blue
			holder[h] = '\0';
			blue = atoi(holder);
			h = 0;
		}
		++i;
	}

	com.color = (SDL_Color){red, green, blue, ALPHA};
	com.ecode = 0;
	return com;
}

