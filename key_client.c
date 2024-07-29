#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#include "src/udp/rcv.h"

#define UDPPORT 8080
#define MAX_TRANSITION 1024

int main(int argc, char **argv) {

	struct UDPRCV rcv;
	rcv = udp_recv_init(UDPPORT, MAX_TRANSITION);
	
	

	/* Main loop */
	int running = 1;
	while (running) {
		if (udp_rcv(&rcv)) {
			printf("\nDATA:\n");
			printf("key-code: %d\n", rcv.pack->data[0]);
			printf("is down: %d\n", rcv.pack->data[1]);
			printf("is shift: %d\n", rcv.pack->data[2]);
			printf("is ctrl: %d\n", rcv.pack->data[3]);

			printf("mouse key: %d\n", rcv.pack->data[4]);

			printf("mouse x0: %d\n", rcv.pack->data[5]);
			printf("mouse x1: %d\n", rcv.pack->data[6]);
			printf("mouse y0: %d\n", rcv.pack->data[7]);
			printf("mouse y1: %d\n", rcv.pack->data[8]);
			printf("--------------------------\n");
		}
	}

	/* Clean and exit */
	SDLNet_FreePacket(rcv.pack);
	SDLNet_Quit();
	return 0;
}
