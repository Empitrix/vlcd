#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "rules.h"
#include "utils.h"

/* Render Text */
void rtextf_rect(SDL_Renderer *rend, TTF_Font* font, char* text, int size, SDL_Rect rect, SDL_Color color){
	int w = (int)strlen(text) * (size);
	SDL_Surface *txtrend = TTF_RenderText_Blended_Wrapped(font, text, color, w);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, txtrend);
	SDL_RenderCopy(rend, texture, NULL, &rect);
	SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
}


void sdl_init_win(int width, int height, void (*sdloop)(SDL_Window*, SDL_Renderer*, TTF_Font*, SDL_Event *)) {

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		pexit(1, "Failed: %s\n", SDL_GetError());
	}

	SDL_Window* win = SDL_CreateWindow("Visual Canvas",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, 0);

	SDL_Renderer* rend = SDL_CreateRenderer(
		win, -1, SDL_RENDERER_ACCELERATED);

	// FONT
	TTF_Init();
	// TTF_Font *font = TTF_OpenFont("./assets/poppins.ttf", FONTSIZ);
	TTF_Font *font = TTF_OpenFont("./assets/roboto.ttf", FONTSIZ);
	// TTF_Font *font = TTF_OpenFont("./assets/vcr.ttf", FONTSIZ);


	if(font == NULL)
		pexit(1, "TTF Failed: %s\n", TTF_GetError());


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

		SDL_PollEvent(&event);

		sdloop(win, rend, font, &event);

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

