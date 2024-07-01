#include "structs.h"
#include <stdio.h>
#include <string.h>
#include "get/one.c"

struct COMMAND get_command(char *data){
	struct COMMAND com; com.id = 0;
	int c;

	c = data[0];
	com.id = (c >= 'A' && c <= 'D' ) ? (c - 'A') + 1 : -1;

	struct COMMAND_ONE command;

	// printf(">%s<", ord);


	switch (com.id) {
		case 1:
			// command
			com.c_one = get_command_one(data);
			// com.c_one = get_command_one(ord);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default: break;
	}

	return com;
}

