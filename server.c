#include "src/utils.h"
#include "src/structs.h"
#include "src/sockets.h"
#include "src/renderer.h"
#include "src/rules.h"
#include "src/canvas.h"
#include "src/execute.h"
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


void sdloop(struct LoopEvent);


int main(int argc, char *argv[]){
	struct InitRes ires = get_init_res(argc, argv);
	pport = ires.port;
	sdl_init_win(200, 200, sdloop);
	return 0;
}


void sdloop(struct LoopEvent le){

	if(canvas.initialized == 0)
		loading_anim(le.rend);

	if(le.soc != NULL){
		char msg[MAX_TRANSITION];


		if(SDLNet_TCP_Recv(*le.soc, msg, MAX_TRANSITION)){
			struct COMMAND c = get_command(msg);

			// Initiate the window
			if(c.type == INIT && c.init.ecode == 0){
				SDL_SetWindowSize(le.win, c.init.width, c.init.height);
				canvas.initialized = 1;
				canvas.mono = c.init.mode == 0 ? 1 : 0;
				canvas.color = c.init.color;


			// Setup a frame
			} else if(c.type == FRAME && c.frame.ecode == 0){
				// get color
				SDL_Color klr;
				SDL_Rect rect;
				if(canvas.mono)
					klr = c.frame.mono_color;
				else
					klr = c.frame.full_color;
				rect = (SDL_Rect){c.frame.x, c.frame.y, c.frame.width, c.frame.height};
				struct FRAME f = {rect, klr};
				canvas.frames[canvas.fidx] = f;
				canvas.fidx++;


			// Fill the canvas
			} else if(c.type == FILL && c.fill.ecode == 0){
				// clear the array of frames
				memset(canvas.frames, 0, sizeof(canvas.frames));
				canvas.fidx = 0;
				canvas.color = c.fill.color;

			// Send frames data (READ)
			} else if(c.type == READ){
				char message[MAX_TRANSITION];
				int i;
				sprintf(message, "FRAMES:\n");
				for(i = 0; i < canvas.fidx; ++i){
					SDL_Color k;
					SDL_Rect r;
					k = canvas.frames[i].color;
					r = canvas.frames[i].rect;
					sprintf(message,"%sCoordinate[%d, %d], Size:[W:%d, H:%d], Color:[R:%d, G:%d, B:%d]\n", message, r.x, r.y, r.w, r.y, k.r, k.g, k.b);
				}
				SDLNet_TCP_Send(*le.soc, message, MAX_TRANSITION);
			}
		}
	}

	if(canvas.initialized)
		render_canvas(le);

}

