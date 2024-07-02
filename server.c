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
			if(c.type == INIT){
				if(c.init.ecode == 0){
					printf("COMMAND 1, INIT: \n");
					printf("bg.red: %d\n", c.init.bg_color.r);
					printf("bg.green: %d\n", c.init.bg_color.g);
					printf("bg.blue: %d\n", c.init.bg_color.b);
					printf("bg.alpha: %d\n\n", c.init.bg_color.a);
					printf("width: %d\n", c.init.width);
					printf("height: %d\n\n", c.init.height);
					printf("color mode: %s\n\n", c.init.mode == 0 ? "MONO" : "FULL");
				} else
					printf("Command 1 (INIT) is broken\n");
			} else if(c.type == FILL){
				if(c.fill.ecode == 0){
					printf("COMMAND 3, FILL: \n");
					printf("color.red: %d\n", c.fill.color.r);
					printf("color.green: %d\n", c.fill.color.g);
					printf("color.blue: %d\n\n", c.fill.color.b);
				} else
					printf("Command 3 (FILL) is broken\n");
			} else if(c.type == READ){
				printf("COMMAND 4, READ! \n");
			} else
				printf("Command not found\n");
		}
		printf("\n------------------\n");
	}

}

