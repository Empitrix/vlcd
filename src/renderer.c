#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "rules.h"
#include "canvas.h"
#include "utils.h"

#include <string.h>

#include "udp/rcv.h"
#include "udp/snd.h"

void sdl_cls(SDL_Renderer *rend);
void sdl_set(SDL_Renderer *rend);
void sdl_end(SDL_Renderer *rend);

void key_state(SDL_Event, int *, int *, int*, int);


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

	SDL_SetWindowAlwaysOnTop(win, 1);

	if(SDLNet_Init() == -1) {
		fprintf(stderr, "ER: SDLNet_Init: %sn", SDLNet_GetError());
		exit(-1);
	}

	SDL_Renderer* rend = SDL_CreateRenderer(
		win, -1, SDL_RENDERER_ACCELERATED);

	// FONT
	TTF_Init();
	TTF_Font *font = TTF_OpenFont("./assets/HNFMR.ttf", FONTSIZ);


	if(font == NULL)
		pexit(1, "TTF Failed: %s\n", TTF_GetError());


	IPaddress ip;
	TCPsocket server, client;

	struct UDPSND snd;
	snd = udp_send_init("127.0.0.1", pport, MAX_TRANSITION);

	if (SDLNet_ResolveHost(&ip, NULL, pport) == -1) {
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(1);
	}

	server = SDLNet_TCP_Open(&ip);
	if (!server) {
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}


	int shift = 0;
	int ctrl = 0;
	int changed = 0;
	int is_updated = 0;


	while(running){
		SDL_Color bg = canvas.color;
		SDL_SetRenderDrawColor(rend, bg.r, bg.g, bg.b, bg.a);
		SDL_RenderClear(rend);

		changed = 0;


		struct LoopEvent le;
		if((client = SDLNet_TCP_Accept(server)))
			le.soc = &client;
		else
			le.soc = NULL;

		if(is_updated){
			char *keybf = get_movement_buffer();

			// send data
			udp_send(snd, keybf, 9);

			is_updated = 0;
		}


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

						case SDL_SCANCODE_MINUS:
							if(pscale - 1 >= 1){
								pscale--;
								changed = 1;
							}
							break;

						case SDL_SCANCODE_EQUALS:
							if(shift)
								if(pscale + 1 <= 8 && change_access(canvas.win_width * (pscale + 1), canvas.win_height * (pscale + 1)) ){
									pscale++;
									changed = 1;
								}
							break;

						default: break;
					}

					key_state(event, &ctrl, &shift, &is_updated, 1);
					break;

				/* {{ end of key-down }} */


				case SDL_MOUSEBUTTONUP: case SDL_MOUSEBUTTONDOWN:
					key_state(event, &ctrl, &shift, &is_updated, 0);
					break;

				case SDL_KEYUP:
					key_state(event, &ctrl, &shift, &is_updated, 0);
					break;

				default: break;
			}
		}


		// win, rend, font, event, soc

		le.win = win;
		le.rend = rend;
		le.font = font;
		le.changed = changed;

		sdloop(le);

		free(client);

		SDL_RenderPresent(rend);
		SDL_Delay(FPS);
	}


	SDL_DestroyWindow(win);
	SDL_Quit();
}



void key_state(SDL_Event event, int *shift, int *ctrl, int *is_updated, int is_down){
	if(is_down == 1){
		*shift = 0;
		*ctrl = 0;
	}
	switch (event.key.keysym.sym){
		case SDLK_RSHIFT: case SDLK_LSHIFT: *shift = 1; break;
		case SDLK_RCTRL: case SDLK_LCTRL: *ctrl = 1; break;
		default: break;
	}

	int mouse_idx = 0;
	int mouse_down = 0;

	switch (event.type) {
		case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
			*shift = 0;
			*ctrl = 0;

			update_movement_buffer(event.button.button, MOSUE_KEY);
			update_movement_buffer(abs(event.button.x), MOUSE_X);
			update_movement_buffer(abs(event.button.y), MOUSE_Y);
			break;

	}

	update_movement_buffer(event.key.keysym.scancode, CODE_S);

	// addiotional keys
	update_movement_buffer(*ctrl, IS_CTRL);
	update_movement_buffer(*shift, IS_SHIFT);

	update_movement_buffer(is_down, IS_DOWN_S);

	*is_updated = 1;
}


/* Loading Animation */
static int current = 1;
static int wait = 0;
// Render Image
void loading_anim(SDL_Renderer* rend){
	char path[100];
	sprintf(path, "./assets/wifi/svg/%d.svg", current);
	SDL_Texture *img;
	SDL_Rect rect;
	rect = (SDL_Rect){0, 0, 200, 200};
	img = IMG_LoadTexture(rend, path);
	SDL_RenderCopy(rend, img, NULL, &rect);
	if(wait > 50){
		current++;
		wait = 0;
	}
	if(current > 4)
		current = 1;
	wait++;
}

