#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "src/sockets.h"
#include "src/rules.h"

#define SOCPORT 8080


int send_msg(char arr[]){
	int soc = client_soc(SOCPORT);
	if(soc == -1)
		return -1;

	if(!(send(soc, arr, MAX_TRANSITION, 0) > 0))
		printf("ERROR on sending informations\n");

	return soc;
}

int main(int argc, char *argv[]){
	int s;

	printf("INIT...\n");
	//                           COMM    RED     GREEN   BLUE    Wa      Wb      Ha      Hb      MODE
	char init[1024] = {'\x01', '\xFF', '\xFF', '\xFF', '\x01', '\x90', '\x01', '\x90', '\x01'};
	if((s = send_msg(init)) == -1){ pexit(1, "ERR"); }
	sleep(1);
	close(s);


	printf("Fill...\n");
	//                  COMM    RED     GREEN   BLUE
	char fill[1024] = {'\x04', '\x00', '\xFF', '\x00'};
	if((s = send_msg(fill)) == -1){ pexit(1, "ERR"); }
	sleep(1);
	close(s);


	printf("SPIXEL...\n");
	//                   COMM    Xa      Xb      Ya      Yb      R       G       B
	char spixel[1024] = {'\x03', '\x00', '\xC8', '\x00', '\xC8', '\x00', '\x00', '\xFF'};
	if((s = send_msg(spixel)) == -1){ pexit(1, "ERR"); }
	sleep(1);
	close(s);

	// printf("FRAME...\n");
	// //                   COMM    Xa      Xb      Ya      Yb      R       G       B
	// char frame[1024] = {'\x03', '\x00', '\xC8', '\x00', '\xC8', '\x00', '\x00', '\xFF'};
	// if((s = send_msg(frame)) == -1){ pexit(1, "ERR"); }
	// sleep(1);
	// close(s);

	/*
	printf("READING: \n");
	char r[1024] = {'\x05'};
	if((s = send_msg(r)) == -1){ pexit(1, "ERR"); }
	sleep(1);
	char msg[MAX_TRANSITION];
	read(s, msg, MAX_TRANSITION);
	printf("Result:\n---------------\n>%s<", msg);
	close(s);
	*/


	return 0;
}

