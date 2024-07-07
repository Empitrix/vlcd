#include <SDL2/SDL_pixels.h>
#include <stdio.h>
#include "structs.h"

// struct FRAME {
// 	SDL_Rect rect;
// 	SDL_Color colors[MAXFRAME];
// };


struct CANVAS {
	int initialized;                // is initialized
	int fidx;                       // total frames length
	int pidx;                       // total pixels length
	int mono;                       // is mono color
	int win_width;                  // is mono color
	int win_height;                 // is mono color
	SDL_Color color;
	struct FRAME_COMM frames[MAXFRAME];  // frames
	struct SPIXEL_COMM pixels[MAXFRAME];  // frames
};


struct CANVAS canvas = {0, 0, 0, 0, 200, 200, (SDL_Color){255, 255, 255, 255}, {}, {}};

/*
void draw_pixel(SDL_Renderer *rend){
	SDL_Color k;
	SDL_Rect r;
	k = canvas.pixels[i].color;

	r.w = r.h = 1 * pscale;
	r.x = canvas.pixels[i].x;
	r.y = canvas.pixels[i].x;

	SDL_SetRenderDrawColor(le.rend, k.r, k.g, k.b, k.a);
	SDL_RenderFillRect(le.rend, &r);
}
*/



void render_canvas(struct LoopEvent le){
	int i;
	// frames
	for(i = 0; i < canvas.fidx; ++i){

		SDL_Rect r;
		SDL_Color empty = {0, 100, 100, 255};

		r.x = canvas.frames[i].x * pscale;
		r.y = canvas.frames[i].y * pscale;

		int loop_count;
		loop_count = canvas.frames[i].width * canvas.frames[i].height;

		r.w = canvas.frames[i].width * pscale;
		r.h = canvas.frames[i].height * pscale;

		SDL_SetRenderDrawColor(le.rend, empty.r, empty.g, empty.b, empty.a);
		SDL_RenderFillRect(le.rend, &r);

		for(int j = 0, height = 0, width = 0; j < loop_count; ++j){
			SDL_Color klr = canvas.frames[i].data[j];
			SDL_Rect rect;

			rect.x = r.x + (width * pscale);
			rect.y = r.y + (height * pscale);

			// rect.x *= pscale;
			// rect.y *= pscale;

			rect.w = rect.h = 1 * pscale;

			if((j + 1) % canvas.frames[i].width == 0){
				height++;
				width = 0;
			} else
				width++;

			SDL_SetRenderDrawColor(le.rend, klr.r, klr.g, klr.b, klr.a);
			SDL_RenderFillRect(le.rend, &rect);
		}
	}


	// draw pixels
	for(i = 0; i < canvas.pidx; ++i){
		SDL_Color k;
		SDL_Rect r;
		k = canvas.pixels[i].color;

		r.w = r.h = 1 * pscale;
		r.x = canvas.pixels[i].x;
		r.y = canvas.pixels[i].x;

		SDL_SetRenderDrawColor(le.rend, k.r, k.g, k.b, k.a);
		SDL_RenderFillRect(le.rend, &r);
	}

}

