#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <stdio.h>
#include <strings.h>


struct UDPSND {
	UDPsocket soc;
	IPaddress srvadd;
	UDPpacket *pack;
	int ecode;
};


/* udp_send_init: Initialize UDP socket & pocket for sending data */
struct UDPSND udp_send_init(char *addr, int port, int transition){
	struct UDPSND snd;
	snd.ecode = 1;

	/* Open a socket on random port */
	if ((snd.soc = SDLNet_UDP_Open(0)) < 0) {
		printf("FAIELD TO OPEN UDP\n");
		return snd;
	}

	/* Resolve server name */
	if (SDLNet_ResolveHost(&snd.srvadd, addr, port)) {
		printf("FAILED TO RESOLVE HOST\n");
		return snd;
	}

	/* Allocate memory for the packet */
	if ((snd.pack = SDLNet_AllocPacket(transition)) < 0) {
		printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		return snd;
	}

	snd.ecode = 0;
	return snd;
}



/* udp_send: UDP send data */
int udp_send(struct UDPSND *snd, char *data, int len){

	if(snd->ecode)
		return -1;

	// strcpy((char *)snd.pack->data, data);

	snd->pack->data = (Uint8 *)data;

	// looping
	snd->pack->address.host = snd->srvadd.host;  // Set the destination host
	snd->pack->address.port = snd->srvadd.port;  // And destination port

	if(len < 0)
		snd->pack->len = strlen((char *)snd->pack->data) + 1;  // This sets the p->channel
	else 
		snd->pack->len = len + 1;


	return SDLNet_UDP_Send(snd->soc, -1, snd->pack);
}

