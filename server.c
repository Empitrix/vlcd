#include "src/utils.h"
#include "src/structs.h"
#include "src/sockets.h"
#include "src/renderer.h"
#include <stdio.h>
#include <unistd.h>

void sdloop(SDL_Window*, SDL_Renderer*, TTF_Font*, SDL_Event *);


int main(int argc, char *argv[]){
	struct InitRes ires = get_init_res(argc, argv);
	pport = ires.port;
	sdl_init_win(200, 200, sdloop);

	// struct COMMAND c;
	// c.c_one = (struct COMMAND_ONE){(SDL_Color){255, 255, 255, 255}, 0, 0, MONO};

	return 0;
}

void sdloop(SDL_Window* win, SDL_Renderer* rend, TTF_Font* font, SDL_Event * event){

	// initialize socket (waitnig for first command)
	if(sfd == 0){
		int tmp;
		sdl_cls(rend);
		rtextf_rect(rend, font, "Waiting...", FONTSIZ + 1, (SDL_Rect){0, 0, 150, 30}, (SDL_Color){0, 0, 0, 255});
		sdl_set(rend);
		if((tmp = server_soc(pport)) != -1)
			sfd = tmp;
		else
			close(tmp);
		return;
	}

	rtextf_rect(rend, font, "Connected", FONTSIZ + 1, (SDL_Rect){0, 0, 150, 30}, (SDL_Color){0, 0, 0, 255});
	printf("FLOP\n");
}

