#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "rules.h"

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
		printf("Failed: %s\n", SDL_GetError());
	}

	SDL_Window* win = SDL_CreateWindow("Visual Canvas",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, 0);

	SDL_Renderer* rend = SDL_CreateRenderer(
		win, -1, SDL_RENDERER_ACCELERATED);

	// FONT
	TTF_Init();
	// TTF_Font *font = TTF_OpenFont("./assets/VCR_OSD_MONO_1.001.ttf", FONTSIZ);
	TTF_Font *font = TTF_OpenFont("./assets/RobotoMono-Regular.ttf", FONTSIZ);


	if(font == NULL)
		printf("TTF Failed: %s\n", TTF_GetError());


	while(running){
		SDL_Event event;

		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running = 0;
					break;

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

