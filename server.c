#include <SDL2/SDL_net.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <string.h>

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

	char msg[MAX_TRANSITION];
	if(canvas.initialized == 0)  // Loading Animation
		loading_anim(le.rend);

	if(le.buffer[0] != '\x00'){

		if(le.buffer[0] == '\x02'){
			printf("\nSTART-----------------\n\n");

			printf("\tRED: %d\n", ghex(le.buffer[9]));
			printf("\tGREEN: %d\n", ghex(le.buffer[10]));
			printf("\tBLUE: %d\n\n", ghex(le.buffer[11]));


			printf("\tRED: %d\n", ghex(le.buffer[12]));
			printf("\tGREEN: %d\n", ghex(le.buffer[13]));
			printf("\tBLUE: %d\n\n", ghex(le.buffer[14]));

			printf("\tRED: %d\n", ghex(le.buffer[15]));
			printf("\tGREEN: %d\n", ghex(le.buffer[16]));
			printf("\tBLUE: %d\n\n", ghex(le.buffer[17]));

			printf("\tRED: %d\n", ghex(le.buffer[18]));
			printf("\tGREEN: %d\n", ghex(le.buffer[19]));
			printf("\tBLUE: %d", ghex(le.buffer[20]));

			printf("\n\n-----------------END\n");
		}

		struct COMMAND c = get_command(le.buffer);  // get the order (command)



		if(c.type == INIT && c.init.ecode == 0 && canvas.initialized == 0)
			init_exec(le, c.init);    // Initialize the window

		else if(c.type == FRAME && c.frame.ecode == 0 && canvas.initialized)
			frame_exec(le, c.frame);  // Setup a frame

		else if(c.type == SPIXEL && c.spixel.ecode == 0 && canvas.initialized)
			spixel_exec(le, c.spixel);  // Set a pixel by current scale

		// Fill the canvas
		else if(c.type == FILL && c.fill.ecode == 0){
			fill_exec(le, c.fill);    // Fill the canvas
		}

		else if(c.type == READ && canvas.initialized){
			printf("NEED TO READ\n");
			read_exec(le);    // Read data and send them back
		}
	}

	memset(le.buffer, 0, sizeof(le.buffer));  // clear

	if(le.changed){
		SDL_SetWindowSize(le.win,
			canvas.win_width * pscale,
			canvas.win_width * pscale);
	}



	if(canvas.initialized)
		render_canvas(le);
}

