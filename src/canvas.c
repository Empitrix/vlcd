#include <SDL2/SDL_pixels.h>
#include "structs.h"

struct CANVAS {
	int initialized;            // is initialized
	int mono;                   // is mono color
	int pixel_init;             // is any pixel initialized
	int win_width;              // window width
	int win_height;             // window height
	SDL_Color color;
	struct FRAME_COMM frame;    // frame
	struct SPIXEL_COMM pixel;   // pixel
};


struct CANVAS canvas = {0, 0, 0, 200, 200, (SDL_Color){255, 255, 255, 255}, {}, {}};

void render_canvas(struct LoopEvent le){
	int i;

	SDL_Rect r;
	SDL_Color empty = {0, 0, 0, 255};

	r.x = canvas.frame.x * pscale;
	r.y = canvas.frame.y * pscale;

	int loop_count;
	loop_count = canvas.frame.width * canvas.frame.height;

	r.w = canvas.frame.width * pscale;
	r.h = canvas.frame.height * pscale;


	for(int j = 0, height = 0, width = 0; j < loop_count; ++j){
		SDL_Color klr;

		if(canvas.mono){

			if(canvas.frame.mono_data[j] == (unsigned char)'\xFF')
				klr = (SDL_Color){255, 255, 255, 255};
			else
				klr = (SDL_Color){0, 0, 0, 255};

		} else{
			klr = canvas.frame.data[j];
		}

		SDL_Rect rect;

		rect.x = r.x + (width * pscale);
		rect.y = r.y + (height * pscale);
		rect.w = rect.h = 1 * pscale;

		if((j + 1) % canvas.frame.width == 0){
			height++;
			width = 0;
		} else
			width++;

		SDL_SetRenderDrawColor(le.rend, klr.r, klr.g, klr.b, klr.a);
		SDL_RenderFillRect(le.rend, &rect);
	}


	// draw pixels
	if(canvas.pixel_init){
		SDL_Color pk;
		SDL_Rect pr;
		pk = canvas.pixel.color;

		pr.w = pr.h = 1 * pscale;
		pr.x = canvas.pixel.x * pscale;
		pr.y = canvas.pixel.y * pscale;

		SDL_SetRenderDrawColor(le.rend, pk.r, pk.g, pk.b, pk.a);
		SDL_RenderFillRect(le.rend, &pr);
	}

}

