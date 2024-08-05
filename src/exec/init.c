#include "../structs.h"
#include "../canvas.h"
#include "../utils.h"

/* Execution */
void init_exec(struct LoopEvent le, struct INIT_COMM init){
	if(change_access(init.width * pscale, init.height * pscale)){
		canvas.win_width = init.width * pscale;
		canvas.win_height = init.height * pscale;
	} else {
		canvas.win_width = init.width;
		canvas.win_height = init.height;
		pscale = 1;
	}
	SDL_SetWindowSize(le.win, canvas.win_width, canvas.win_height);
	canvas.initialized = 1;
	canvas.mono = init.mode == 0;
	canvas.mono_color = init.color;
}
