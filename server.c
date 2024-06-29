#include "src/utils.h"
#include "src/structs.h"
#include "src/sockets.h"
#include "src/renderer.h"


void sdloop(SDL_Window*, SDL_Renderer*, TTF_Font*, SDL_Event *);

int main(int argc, char *argv[]){
	struct InitRes ires = get_init_res(argc, argv);
	
	int soc = server_soc(ires.port);

	sdl_init_win(200, 200, sdloop);

	close(soc);
	return 0;
}

void sdloop(SDL_Window* win, SDL_Renderer* rend, TTF_Font* font, SDL_Event * event){
	// rtextf_rect(rend, font, "A", 5, (SDL_Rect){0, 0, 50, 50}, (SDL_Color){255, 255, 255, 255});
}
