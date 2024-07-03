#include "../structs.h"
#include "../canvas.h"

/* Execution */
void init_exec(struct LoopEvent le, struct INIT_COMM init){
	SDL_SetWindowSize(le.win, init.width, init.height);
	canvas.initialized = 1;
	canvas.mono = init.mode == 0 ? 1 : 0;
	canvas.color = init.color;
}
