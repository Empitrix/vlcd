#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include "../structs.h"
#include "../canvas.h"


void frame_exec(struct LoopEvent le, struct FRAME_COMM frame){
	canvas.frame = frame;
}

