#include "structs.h"
#include <stdio.h>
#include <string.h>

#include "commands/init.c"
#include "commands/frame.c"
#include "commands/fill.c"

struct COMMAND get_command(char *data){
	struct COMMAND com;
	com.type = NONE;

	int c;
	c = data[0];
	com.type = (c >= 'A' && c <= 'D' ) ? (c - 'A') : -1;

	switch (com.type) {
		case INIT:
			com.init = get_init_comm(data);
			break;
		case FRAME:
			com.frame = get_frame_comm(data);
			break;
		case FILL:
			com.fill = get_fill_comm(data);
			break;
		case READ:
			if((int)strlen(data) != 1)
				com.type = NONE;
			break;
		default: break;
	}

	return com;
}

