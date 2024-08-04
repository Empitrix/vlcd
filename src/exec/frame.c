#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include "../structs.h"
#include "../canvas.h"


void frame_exec(struct LoopEvent le, struct FRAME_COMM frame){
	canvas.frame = frame;

	memset(canvas.frame.mono_data, 0, sizeof(canvas.frame.mono_data));

	for(int i = 0; i < frame.width * frame.height + 10; i++)
		canvas.frame.mono_data[i] = '\x00';

	for(int i = 0; i < frame.width * frame.height; i++)
		canvas.frame.mono_data[i] = frame.mono_data[i];

}

