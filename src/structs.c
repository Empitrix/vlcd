
/* Initial Respone: scale & port from argument list */
#include <SDL2/SDL_pixels.h>
struct InitRes{
	unsigned int scale;    // 0..255
	unsigned int port: 16; // 16-bit => 0..65535
};


enum COLOR_MODE{MONO, FULL};


struct COMMAND_ONE {
	SDL_Color bg_color;
	int width, height;
	enum COLOR_MODE mode;
};

struct COMMAND_TWO {
	int x, y;
	int width, height;
	int color[3];
};

struct COMMAND_THREE {
	SDL_Color color;
};


struct COMMAND {
	struct COMMAND_ONE c_one;
	struct COMMAND_TWO c_two;
	struct COMMAND_THREE c_three;
	int id;
};
