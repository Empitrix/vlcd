#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
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

	printf("INIT (COLOR FULL)...\n");
	//                 COMM    RED     GREEN   BLUE    Wa      Wb      Ha      Hb      MODE
	char init[1024] = {'\x01', '\xFF', '\xFF', '\xFF', '\x00', '\x64', '\x00', '\x64', '\x01'};
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
	char spixel[1024] = {'\x03', '\x00', '\x32', '\x00', '\x32', '\x00', '\x00', '\xFF'};
	if((s = send_msg(spixel)) == -1){ pexit(1, "ERR"); }
	sleep(1);
	close(s);


	printf("FRAME at [250, 250] - 2 x 2 (FULL-COLOR)...\n");
	//                   COMM    Xa      Xb      Ya      Yb      Wa      Wb     Ha      Hb
	char frame[1024] = {'\x02', '\x00', '\x4B', '\x00', '\x4B', '\x00', '\x02', '\x00', '\x02',
		'\xff', '\x00', '\x00',  // RED   Color 
		'\x00', '\xff', '\x00',  // GREEN Color 
		'\x00', '\x00', '\xff',  // BLUE  Color 
		'\xff', '\xff', '\xff',  // WHITE Color 
	};
	if((s = send_msg(frame)) == -1){ pexit(1, "ERR"); }
	sleep(1);
	close(s);

	printf("READING: \n");
	char r[1024] = {'\x05'};
	if((s = send_msg(r)) == -1){ pexit(1, "ERR"); }
	sleep(1);

	char msg[MAX_TRANSITION];
	read(s, msg, MAX_TRANSITION);
	close(s);

	// /*
	int i, j;
	printf("\n\n");

	//            w:2  h:2  (data)
	for(i = 0; i < (2 * 2) * 7; i += 7){
		printf("Xa: \\x%x\n", msg[i]);
		printf("Xb: \\x%x\n", msg[i + 1]);
		printf("Ya: \\x%x\n", msg[i + 2]);
		printf("Yb: \\x%x\n", msg[i + 3]);
		printf("R: \x1B[31m\\x%x\n\x1B[0m",  msg[i + 4]);
		printf("G: \x1B[32m\\x%x\n\x1B[0m",  msg[i + 5]);
		printf("B: \x1B[34m\\x%x\n\x1B[0m",  msg[i + 6]);
		printf("\n-----------\n");
	}





	printf("READING (MIX): \n");
	if((s = send_msg(r)) == -1){ pexit(1, "ERR"); }
	sleep(1);
	memset(msg, 0, MAX_TRANSITION);
	read(s, msg, MAX_TRANSITION);
	close(s);
	j = 0;
	printf("\n\n");
	for(i = 0; i < (2 * 2) * 7; i += 7){
		printf("X: \\x%d\n", hexm(msg[i], msg[i + 1]));
		printf("Y: \\x%d\n", hexm(msg[i + 2], msg[i + 3]));
		printf("{\x1B[31m\\x%2x\x1B[0m, \x1B[32m\\x%2x\x1B[0m, \x1B[34m\\x%2x\x1B[0m}\n",
			ghex(msg[i + 4]),
			ghex(msg[i + 5]),
			ghex(msg[i + 6]));
		printf("\n-----------\n");
	}

	return 0;
}

