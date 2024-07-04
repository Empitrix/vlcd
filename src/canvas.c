#include <SDL2/SDL_pixels.h>
#include "structs.h"

struct FRAME {
	SDL_Rect rect;
	SDL_Color color;
};


struct CANVAS {
	int initialized;                // is initialized
	int fidx;                       // total frames length
	int mono;                       // is mono color
	int win_width;                  // is mono color
	int win_height;                 // is mono color
	SDL_Color color;
	struct FRAME frames[MAXFRAME];  // frames
};


struct CANVAS canvas = {0, 0, 0, 200, 200, (SDL_Color){255, 255, 255, 255}, {}};

void render_canvas(struct LoopEvent le){
	int i;
	for(i = 0; i < canvas.fidx; ++i){
		SDL_Color k;
		SDL_Rect r;
		k = canvas.frames[i].color;
		r = canvas.frames[i].rect;

		r.w *= pscale;
		r.h *= pscale;

		r.x *= pscale;
		r.y *= pscale;

		SDL_SetRenderDrawColor(le.rend, k.r, k.g, k.b, k.a);
		SDL_RenderFillRect(le.rend, &r);
	}
}

