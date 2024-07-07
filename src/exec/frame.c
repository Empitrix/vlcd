#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include "../structs.h"
#include "../canvas.h"


void frame_exec(struct LoopEvent le, struct FRAME_COMM frame){
	// get color
	// SDL_Color klr;
	// SDL_Rect rect;

	// if(canvas.mono)
	// 	klr = frame.mono_color;
	// else
	// 	klr = frame.full_color;

	// rect = (SDL_Rect){frame.x, frame.y, frame.width, frame.height};
	// struct FRAME f = {rect, frame.data};
	// struct FRAME f;
	// f.rect = rect;
	// f.colors = frame.data;

	canvas.frames[canvas.fidx] = frame;
	canvas.fidx++;
}

