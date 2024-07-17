#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

struct UDPRCV {
	UDPsocket soc;  // Socket descriptor
	UDPpacket *pack;  // Pointer to packet memory
	int running;
	int ecode;
};


struct UDPRCV udp_rcv_init(int port, int transition){
	struct UDPRCV rcv;
	rcv.ecode = 1;

	/* Initialize SDL_net */
	if (SDLNet_Init() < 0){
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		return rcv;
	}

	/* Open a socket */
	if (!(rcv.soc = SDLNet_UDP_Open(port))){
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		return rcv;
	}

	/* Make space for the packet */
	if ((rcv.pack = SDLNet_AllocPacket(transition)) < 0){
		printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		return rcv;
	}

	rcv.ecode = 0;
	return rcv;
}

char *udp_rcv(struct UDPRCV rcv){

	if(SDLNet_UDP_Recv(rcv.soc, rcv.pack)){
		return (char *)rcv.pack->data;
	}

	return NULL;
}


