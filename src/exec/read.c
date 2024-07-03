#include "../structs.h"
#include "../canvas.h"


void read_exec(struct LoopEvent le, struct FILL_COMM fill){
	char message[MAX_TRANSITION];
	int i;
	sprintf(message, "FRAMES:\n");
	for(i = 0; i < canvas.fidx; ++i){
		SDL_Color k;
		SDL_Rect r;
		k = canvas.frames[i].color;
		r = canvas.frames[i].rect;
		sprintf(message,"%sCoordinate[%d, %d], Size:[W:%d, H:%d], Color:[R:%d, G:%d, B:%d]\n", message, r.x, r.y, r.w, r.y, k.r, k.g, k.b);
	}
	SDLNet_TCP_Send(*le.soc, message, MAX_TRANSITION);
}

