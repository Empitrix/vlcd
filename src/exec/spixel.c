#include "../structs.h"
#include "../canvas.h"
#include <stdio.h>

void spixel_exec(struct LoopEvent le, struct SPIXEL_COMM spixel){
	SDL_Color klr;

	if(canvas.mono)
		klr = MONOKLR;
	else
		klr = spixel.color;

	spixel.color = klr;
	canvas.pixel = spixel;
}

