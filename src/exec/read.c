#include "../structs.h"
#include "../canvas.h"
#include "../utils.h"
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#define CAPTURE_BLANK 0
#define CAPTURE_PIXEL 0

//Xa      Xb      Ya      Yb      Wa      Wb      Ha      Hb     ...MONO[0, 1]/RGB (WIDTH.HEIGHT)
// '\x00', '\xFA', '\x00', '\xFA', '\x00', '\x02', '\x00', '\x02' ...MONO[0, 1]/RGB (WIDTH.HEIGHT)
// total len: (MUST HAVE: 8)
//
void read_exec(struct LoopEvent le){
	int x, y, i, idx;
	x = y = idx = 0;

	unsigned char arr[MAX_TRANSITION];
	int j;
	j = 0;

	for(i = 0; i < canvas.win_width * canvas.win_height; ++i){

		if(x % canvas.win_width == 0){
			x = 0;
			y++;
		}
		++x;

		if(x == canvas.pixel.x && y == canvas.pixel.y){
			if(CAPTURE_PIXEL){
				SDL_Color k = canvas.pixel.color;
				printf("[P] [%3d, %3d]: {\x1B[31m%-3d\x1B[0m, \x1B[32m%-3d\x1B[0m, \x1B[34m%-3d\x1B[0m}\n", x, y, k.r, k.g, k.b);

				arr[j++] = first_h(x);
				arr[j++] = second_h(x);

				arr[j++] = first_h(y);
				arr[j++] = second_h(y);

				arr[j++] = ghex(k.r);
				arr[j++] = ghex(k.g);
				arr[j++] = ghex(k.b);
			}
		} else if(x >= canvas.frame.x && x <= canvas.frame.x - 1 + canvas.frame.width &&
				y >= canvas.frame.y && y <= canvas.frame.y - 1 + canvas.frame.height){
			SDL_Color k = canvas.frame.data[idx];
			printf("[F] [%3d, %3d]: {\x1B[31m%-3d\x1B[0m, \x1B[32m%-3d\x1B[0m, \x1B[34m%-3d\x1B[0m}\n", x, y, k.r, k.g, k.b);


			arr[j++] = first_h(x);
			arr[j++] = second_h(x);

			arr[j++] = first_h(y);
			arr[j++] = second_h(y);

			arr[j++] = ghex(k.r);
			arr[j++] = ghex(k.g);
			arr[j++] = ghex(k.b);

			++idx;

		} else {
			if(CAPTURE_BLANK){
				SDL_Color k = canvas.color;
				printf("[N] [%3d, %3d]: {\x1B[31m%3d\x1B[0m, \x1B[32m%3d\x1B[0m, \x1B[34m%3d\x1B[0m}\n", x, y, k.r, k.g, k.b);

				arr[j++] = first_h(x);
				arr[j++] = second_h(x);

				arr[j++] = first_h(y);
				arr[j++] = second_h(y);

				arr[j++] = ghex(k.r);
				arr[j++] = ghex(k.g);
				arr[j++] = ghex(k.b);
			}
		}
	}


	if(le.soc != NULL){
		int l = SDLNet_TCP_Send(*le.soc, arr, MAX_TRANSITION); 
		printf("SEND STATUS: %d\n", l);
	} else {
		printf("FAILED TO SEND BACK THE DATA\n");
	}

	idx = 0;
}

