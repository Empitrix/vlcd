#include <sys/socket.h>
#include "src/sockets.h"
#include "src/rules.h"

int main(int argc, char *argv[]){

	int soc = client_soc(8080);

	char buffer[MAX_TRANSITION] = "Awesome";
	send(soc, buffer, MAX_TRANSITION, 0);
	return 0;
}

