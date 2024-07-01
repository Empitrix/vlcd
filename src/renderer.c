#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "rules.h"
#include "utils.h"

void sdl_cls(SDL_Renderer *rend);
void sdl_set(SDL_Renderer *rend);
void sdl_end(SDL_Renderer *rend);


/* Render Text */
void rtextf_rect(SDL_Renderer *rend, TTF_Font* font, char* text, int size, SDL_Rect rect, SDL_Color color){
	int w = (int)strlen(text) * (size);
	SDL_Surface *txtrend = TTF_RenderText_Blended_Wrapped(font, text, color, w);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, txtrend);
	SDL_RenderCopy(rend, texture, NULL, &rect);
	SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
}


void sdl_init_win(int width, int height, void (*sdloop)(struct LoopEvent)) {

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		pexit(1, "Failed: %s\n", SDL_GetError());
	}

	SDL_Window* win = SDL_CreateWindow("Visual Canvas",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, 0);


	if(SDLNet_Init() == -1) {
		fprintf(stderr, "ER: SDLNet_Init: %sn", SDLNet_GetError());
		exit(-1);
	}

	SDL_Renderer* rend = SDL_CreateRenderer(
		win, -1, SDL_RENDERER_ACCELERATED);

	// FONT
	TTF_Init();
	TTF_Font *font = TTF_OpenFont("./assets/roboto.ttf", FONTSIZ);


	if(font == NULL)
		pexit(1, "TTF Failed: %s\n", TTF_GetError());


	IPaddress ip;
	TCPsocket server, client;
	// TCPsocket server;

	// TCPsocket *client;
	// SDLNet_ResolveHost(&ip,"127.0.0.1", pport);

	// if (SDLNet_ResolveHost(&ip,"127.0.0.1", pport) == -1) {
	if (SDLNet_ResolveHost(&ip, NULL, pport) == -1) {
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(1);
	}

	server = SDLNet_TCP_Open(&ip);
	if (!server) {
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}


	int granted = 0;

	while(running){
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_RenderClear(rend);

		SDL_Event event;

		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running = 0;
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode){
						case SDL_SCANCODE_Q:  // clsoe the program when 'q' pressed
							running = 0;
							break;

						default: break;
					}

				default: break;
			}
		}

		// win, rend, font, event, soc
		struct LoopEvent le;
		le.win = win;
		le.rend = rend;
		le.font = font;
		le.event = &event;

		if((client = SDLNet_TCP_Accept(server)))
			le.soc = &client;
		else
			le.soc = NULL;

		sdloop(le);

		free(client);

		SDL_RenderPresent(rend);
		SDL_Delay(FPS);
	}


	SDL_DestroyWindow(win);
	SDL_Quit();
}



void sdl_cls(SDL_Renderer *rend){
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	SDL_RenderClear(rend);
}

void sdl_set(SDL_Renderer *rend){
	SDL_RenderPresent(rend);
}

void sdl_end(SDL_Renderer *rend){
	SDL_RenderPresent(rend);
	SDL_Delay(FPS);
}

