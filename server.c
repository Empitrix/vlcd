#include <SDL2/SDL_net.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#include "src/renderer.h"
#include "src/execute.h"

#include "src/exec/init.h"
#include "src/exec/frame.h"
#include "src/exec/fill.h"
#include "src/exec/read.h"
#include "src/exec/spixel.h"

void sdloop(struct LoopEvent);

int main(int argc, char *argv[]){
	struct InitRes ires = get_init_res(argc, argv);
	pport = ires.port;
	pscale = ires.scale;
	sdl_init_win(canvas.win_width, canvas.win_height, sdloop);
	return 0;
}


void sdloop(struct LoopEvent le){

	if(canvas.initialized == 0)  // Loading Animation
		loading_anim(le.rend);

	if(le.soc != NULL){
		char msg[MAX_TRANSITION];

		if(SDLNet_TCP_Recv(*le.soc, msg, MAX_TRANSITION)){
			struct COMMAND c = get_command(msg);  // get the order (command)

			if(c.type == INIT && c.init.ecode == 0)
				init_exec(le, c.init);    // Initialize the window

			else if(c.type == FRAME && c.frame.ecode == 0 && canvas.initialized)
				frame_exec(le, c.frame);  // Setup a frame

			else if(c.type == SPIXEL && c.spixel.ecode == 0 && canvas.initialized)
				spixel_exec(le, c.spixel);  // Set a pixel by current scale

			// Fill the canvas
			else if(c.type == FILL && c.fill.ecode == 0 && canvas.initialized)
				fill_exec(le, c.fill);    // Fill the canvas

			else if(c.type == READ)
				read_exec(le, c.fill);    // Read data and send them back
		}
		memset(msg, 0, MAX_TRANSITION);  // clear
	}


	if(le.changed){
		SDL_SetWindowSize(le.win,
			canvas.win_width * pscale,
			canvas.win_width * pscale);
	}



	if(canvas.initialized)
		render_canvas(le);
}

