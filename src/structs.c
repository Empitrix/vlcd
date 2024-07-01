#include <SDL2/SDL_net.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>


/* Initial Respone: scale & port from argument list */
struct InitRes{
	unsigned int scale;    // 0..255
	unsigned int port: 16; // 16-bit => 0..65535
};


struct SSOC{
	int fd;
	int server;
};


struct LoopEvent {
	SDL_Window *win;
	SDL_Renderer *rend;
	TTF_Font *font;
	SDL_Event *event;
	TCPsocket *soc;
};



enum COLOR_MODE{MONO, FULL};

struct COMMAND_ONE {
	SDL_Color bg_color;
	int width, height;
	enum COLOR_MODE mode;
	int ecode;  // exit code
};

struct COMMAND_TWO {
	int x, y;
	int width, height;
	int color[3];
	int ecode;  // exit code
};

struct COMMAND_THREE {
	SDL_Color color;
	int ecode;  // exit code
};

struct COMMAND {
	struct COMMAND_ONE c_one;
	struct COMMAND_TWO c_two;
	struct COMMAND_THREE c_three;
	int id;
};

