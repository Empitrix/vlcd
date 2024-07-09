#include "../structs.h"
#include "../canvas.h"

void fill_exec(struct LoopEvent le, struct FILL_COMM fill){
	canvas.color = fill.color;
}

