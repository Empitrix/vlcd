#include <SDL2/SDL_net.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_video.h>
#include <string.h>

#include "src/renderer.h"
#include "src/execute.h"

#include "src/exec/init.h"
#include "src/exec/frame.h"
#include "src/exec/fill.h"
#include "src/exec/read.h"
#include "src/exec/spixel.h"
#include "src/utils.h"

void sdloop(struct LoopEvent);


int main(int argc, char *argv[]){
	struct InitRes ires = get_init_res(argc, argv);
	pport = ires.port;
	pscale = ires.scale;
	strcpy(p_ipaddr, ires.ipaddr);
	sdl_init_win(canvas.win_width, canvas.win_height, sdloop);
	return 0;
}


void sdloop(struct LoopEvent le){

	char msg[MAX_TRANSITION];
	if(canvas.initialized == 0)  // Loading Animation
		loading_anim(le.rend);

	if(le.buffer[0] != '\x00'){
		struct COMMAND c = get_command(le.buffer);  // get the order (command)

		if(c.type == INIT && c.init.ecode == 0 && canvas.initialized == 0)
			init_exec(le, c.init);    // Initialize the window

		else if(c.type == FRAME && c.frame.ecode == 0 && canvas.initialized)
			frame_exec(le, c.frame);  // Setup a frame

		else if(c.type == SPIXEL && c.spixel.ecode == 0 && canvas.initialized)
			spixel_exec(le, c.spixel);  // Set a pixel by current scale

		else if(c.type == FILL && c.fill.ecode == 0)
			fill_exec(le, c.fill);    // Fill the canvas

		else if(c.type == READ && canvas.initialized)
			read_exec(le);    // Read data and send them back
	}

	memset(le.buffer, 0, sizeof(le.buffer));  // clear
	clear_buff(le.buffer, (int)sizeof(le.buffer));

	le.buffer[0] = '\x00';

	if(le.changed){
		SDL_SetWindowSize(le.win,
			canvas.win_width * pscale,
			canvas.win_width * pscale);
	}

	if(canvas.initialized)
		render_canvas(le);
}

