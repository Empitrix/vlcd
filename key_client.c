#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>


#define SOCPORT 8080


int main(int argc, char *argv[]){

	IPaddress serverIP;
	UDPsocket udpsock;
	UDPpacket* recv_packet;
	SDLNet_SocketSet socketset = NULL;
	int numused;

	static const int MAX_PACKET_SIZE = 512;

	if (SDLNet_Init() < 0) {
		printf("Couldn't initialize net: %s\n", SDLNet_GetError());
		exit(1);
	}


	udpsock = SDLNet_UDP_Open(SOCPORT);
	if(!udpsock) {
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(2);
	} else {
		printf("listening on 0.0.0.0:3333\n");
	}

	socketset = SDLNet_AllocSocketSet(2);
	if ( socketset == NULL ) {
		fprintf(stderr, "Couldn't create socket set: %s\n", SDLNet_GetError());
		exit(2);
	}

	numused = SDLNet_UDP_AddSocket(socketset,udpsock);
	if(numused==-1) {
		printf("SDLNet_AddSocket: %s\n", SDLNet_GetError());
		exit(2);
	}

	recv_packet = SDLNet_AllocPacket(MAX_PACKET_SIZE);
	if(!recv_packet) {
		printf("Could not allocate packet\n");
		exit(2);
	}

	while(1) {
		// if (SDLNet_UDP_Recv(udpsock, recv_packet)) {
		// 	printf("AWESOME\n");
		// }
		SDLNet_CheckSockets(socketset, ~0);
		if (SDLNet_SocketReady(udpsock)) {
			if (SDLNet_UDP_Recv(udpsock, recv_packet)) {
				printf("AWESOME\n");
			}
		}

		SDL_Delay(1000 / 60);
	}

	return 0;
}
