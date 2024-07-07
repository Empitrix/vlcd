#include "../structs.h"
#include "../canvas.h"

void fill_exec(struct LoopEvent le, struct FILL_COMM fill){
	// clear the array of frames
	memset(canvas.frames, 0, sizeof(canvas.frames));
	memset(canvas.pixels, 0, sizeof(canvas.pixels));
	canvas.fidx = 0;
	canvas.pidx = 0;
	canvas.color = fill.color;
}

