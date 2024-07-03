#include "../structs.h"
#include "../rules.h"
#include <SDL2/SDL_stdinc.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*       c x    y    w    h    r   g   b
FULL: B 0000 0000 0000 0000 000 000 000
MONO: B 0000 0000 0000 0000 000
                            m

exmaple1: B0000000000000000000000000
exmaple2: B0000000000000000000

total len: 26, 20
*/ 


struct FRAME_COMM get_frame_comm(char ord[]){
	struct FRAME_COMM com;

	int l = (int)strlen(ord);
	int i, c, h, is_mono;
	char holder[10];

	int red, green, blue, mono;
	red = green = blue = com.width = com.height = com.x = com.y = -1;
	h = c = i = 0;

	// broken order
	if(!(l == 20 || l == 26)){ com.ecode = 1; return com; }
	is_mono = l == 20 ? 1 : 0;

	
	
	while(ord[i] != '\0'){
		if(i == 0 ){ ++i; continue; }
		c = ord[i];
		holder[h++] = c;

		// non valid cahrs
		if(!isdigit(c)){ com.ecode = 1; return com; }


		if(com.x == -1 && h == 4){               // x
			holder[h] = '\0';
			com.x = atoi(holder);
			h = 0;
		} else if(com.y == -1 && h == 4){        // y
			holder[h] = '\0';
			com.y = atoi(holder);
			h = 0;
		} else if(com.width == -1 && h == 4){    // width
			holder[h] = '\0';
			com.width = atoi(holder);
			h = 0;
		} else if (com.height == -1 && h == 4){   // height
			holder[h] = '\0';
			com.height = atoi(holder);
			h = 0;
		}

		if(com.height != -1){
			if(is_mono){
				if(red == -1 && h == 3){
					holder[h] = '\0';
					red = green = blue = atoi(holder);
					h = 0;
				}
			} else {
				if(red == -1 && h == 3){
					holder[h] = '\0';
					red = atoi(holder);
					h = 0;
				} else if(green == -1 && h == 3){
					holder[h] = '\0';
					green = atoi(holder);
					h = 0;
				} else if (blue == -1 && h == 3){
					holder[h] = '\0';
					blue = atoi(holder);
					h = 0;
				}
			}
		}

		++i;
	}

	

	if(is_mono)
		com.mono_color = (SDL_Color){red, green, blue, ALPHA};
	else
		com.full_color = (SDL_Color){red, green, blue, ALPHA};

	com.ecode = 0;
	return com;
}

