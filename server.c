#include "src/utils.h"
#include "src/structs.h"
#include "src/sockets.h"
#include "src/renderer.h"
#include "src/rules.h"
#include <SDL2/SDL_net.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void sdloop(SDL_Window*, SDL_Renderer*, TTF_Font*, SDL_Event *, TCPsocket*);


int main(int argc, char *argv[]){
	struct InitRes ires = get_init_res(argc, argv);
	pport = ires.port;

	sdl_init_win(200, 200, sdloop);

	return 0;
}

int initiated = 0;


char msg[MAX_TRANSITION];

void sdloop(SDL_Window* win, SDL_Renderer* rend, TTF_Font* font, SDL_Event * event, TCPsocket *soc){

	// rtextf_rect(rend, font, "Waiting...", FONTSIZ + 1, (SDL_Rect){0, 0, 150, 30}, (SDL_Color){0, 0, 0, 255});

	if(soc != NULL){
		char message[MAX_TRANSITION];
		int len = SDLNet_TCP_Recv(*soc, message, MAX_TRANSITION);
		if(len){
			strcpy(msg, message);
		}
	}

	// 150 -> 5
	// rtextf_rect(rend, font, msg, FONTSIZ + 1, (SDL_Rect){0, 0, 150, 30}, (SDL_Color){0, 0, 0, 255});
	rtextf_rect(rend, font, msg, FONTSIZ + 1, (SDL_Rect){0, 0, (int)strlen(msg) * 30, 30}, (SDL_Color){0, 0, 0, 255});
}

