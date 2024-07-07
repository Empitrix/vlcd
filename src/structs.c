#include <SDL2/SDL_net.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include "rules.h"


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
	// SDL_Event event;
	int changed;
	TCPsocket *soc;
};

struct SCREEN_SIZE {
	int height;
	int width;
};

enum COMMANDS { INIT, FRAME, SPIXEL, FILL, READ, NONE };

enum COLOR_MODE { MONO, FULL };

// initialize window
struct INIT_COMM {
	SDL_Color color;
	int width, height;
	enum COLOR_MODE mode;
	int ecode;  // exit code
};

// set a frame
struct SPIXEL_COMM {
	int x, y;
	SDL_Color color;
	int ecode;  // exit code
};

// set a frame
struct FRAME_COMM {
	int x, y;
	int width, height;
	SDL_Color full_color;
	SDL_Color mono_color;
	int ecode;  // exit code
};

// fill canvas
struct FILL_COMM {
	SDL_Color color;
	int ecode;  // exit code
};

struct COMMAND {
	struct INIT_COMM init;
	struct FRAME_COMM frame;
	struct SPIXEL_COMM spixel;
	struct FILL_COMM fill;
	enum COMMANDS type;
};

