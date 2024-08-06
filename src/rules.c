int running = 1;
#define FONTSIZ 72
#define FPS 1000 / 60

#define SOCKET_TIMEOUT 500

#define MAX_TRANSITION 1500

#define ALPHA 255

// #define MAXFRAME 1000
#define MAXFRAME 1024

// you can change this to '1' if you want to see data when reading command is executed
// you can change this to '0' if you dont want to see data when reading command is executed
#define DEBUG_MODE 1


#define MONOKLR (SDL_Color){255, 255, 255, 255}

// public port
int pport = 0;
int pscale = 1;
char p_ipaddr[128];

