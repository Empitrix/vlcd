#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "src/sockets.h"
#include "src/rules.h"

char *gline(){
	char *ll = malloc(sizeof(char));
	int i, c;
	i = 0;
	while((c = getchar()) != '\n' || c != '\0')
		ll[i++] = c;
	ll[i] = '\0';
	return ll;
}

int main(int argc, char *argv[]){


	
	int soc = client_soc(8080);
	if(soc == -1)
		return 0;

	if(!(send(soc, argv[1], MAX_TRANSITION, 0) > 0))
		printf("ERROR on sending informations\n");

	if(strcmp(argv[1], "D") == 0){
		char msg[MAX_TRANSITION];
		read(soc, msg, MAX_TRANSITION);
		printf("Result:\n---------------\n%s", msg);
	}

	close(soc);

	putchar('\n');
	return 0;
}

