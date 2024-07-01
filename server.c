#include "src/utils.h"
#include "src/structs.h"
#include "src/sockets.h"
#include "src/renderer.h"
#include "src/rules.h"
#include "src/execute.h"
#include <SDL2/SDL_net.h>
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


char msg[MAX_TRANSITION];

void sdloop(struct LoopEvent le){

	if(le.soc != NULL){
		char message[MAX_TRANSITION];
		int len = SDLNet_TCP_Recv(*le.soc, message, MAX_TRANSITION);
		if(len){
			struct COMMAND c = get_command(message);
			if(c.id == 1){
				if(c.c_one.ecode == 0){
					printf("bg.red: %d\n", c.c_one.bg_color.r);
					printf("bg.green: %d\n", c.c_one.bg_color.g);
					printf("bg.blue: %d\n", c.c_one.bg_color.b);
					printf("bg.alpha: %d\n\n", c.c_one.bg_color.a);
					printf("width: %d\n", c.c_one.width);
					printf("height: %d\n\n", c.c_one.height);
					printf("color mode: %s\n\n", c.c_one.mode == 0 ? "MONO" : "FULL");
				} else
					printf("COMMAND 1 EXIT CODE FAILED\n");
			}
		}
	}

	// if(le.soc != NULL){
	// 	char message[MAX_TRANSITION];
	// 	int len = SDLNet_TCP_Recv(*le.soc, message, MAX_TRANSITION);
	// 	if(len){
	// 		strcpy(msg, message);
	// 	}
	// }

	// rtextf_rect(le.rend, le.font, msg, FONTSIZ + 1, (SDL_Rect){0, 0, (int)strlen(msg) * 30, 30}, (SDL_Color){0, 0, 0, 255});
}

