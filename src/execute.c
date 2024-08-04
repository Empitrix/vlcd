#include "structs.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

#include "commands/init.c"
#include "commands/frame.c"
#include "commands/spixel.c"
#include "commands/fill.c"

struct COMMAND get_command(unsigned char data[]){
	struct COMMAND com;
	com.type = NONE;

	int c = ghex(data[0]);
	com.type = (c >= 1 && c <= 5 ) ? c - 1 : -1;

	switch (com.type) {
		case INIT:
			com.init = get_init_comm(data);
			break;

		case FRAME:
			com.frame = get_frame_comm(data);
			break;

		case SPIXEL:
			com.spixel = get_spixel_comm(data);
			break;

		case FILL:
			com.fill = get_fill_comm(data);
			break;

		case READ:
			// if((int)strlen((char *)data) != 1)
			// 	com.type = NONE;
			break;

		default: break;
	}

	return com;
}

