#include "../structs.h"
#include "../canvas.h"
#include "../utils.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>


//Xa      Xb      Ya      Yb      Wa      Wb      Ha      Hb     ...MONO[0, 1]/RGB (WIDTH.HEIGHT)
// '\x00', '\xFA', '\x00', '\xFA', '\x00', '\x02', '\x00', '\x02' ...MONO[0, 1]/RGB (WIDTH.HEIGHT)
// total len: (MUST HAVE: 8)

SDL_Color GetPixel ( SDL_Surface* pSurface , int x , int y ) 
{
  SDL_Color color ;
  Uint32 col = 0 ;

  //determine position
  char* pPosition = ( char* ) pSurface->pixels ;

  //offset by y
  pPosition += ( pSurface->pitch * y ) ;

  //offset by x
  pPosition += ( pSurface->format->BytesPerPixel * x ) ;

  //copy pixel data
  memcpy ( &col , pPosition , pSurface->format->BytesPerPixel ) ;

  //convert color
  SDL_GetRGB ( col , pSurface->format , &color.r , &color.g , &color.b ) ;
  

  return ( color ) ;
}

void read_exec(struct LoopEvent le){
	int x, y, i;
	x = y = 0;

	SDL_UpdateWindowSurface(le.win);


	SDL_Surface *window_surf = SDL_GetWindowSurface(le.win);
	// SDL_Surface *surface = SDL_CreateRGBSurface(0, canvas.win_width, canvas.win_height, 32, 0, 0, 0, 0);
	// SDL_Surface *surface = SDL_CreateRGBSurface(0, canvas.win_width, canvas.win_height, 32, 0, 0, 0, 0);


	printf("TOTAL: %d\n", canvas.frame.width * canvas.frame.height);
	for(i = 0; i < canvas.win_width * canvas.win_height; ++i){

		if(x % canvas.win_width == 0){
			x = 0;
			y++;
		}

		++x;



		// SDL_SetColorKey(window_surf ,SDL_TRUE,SDL_MapRGB(window_surf ->format, 100, 100, 100));
		// SDL_Texture *newTexture = SDL_CreateTextureFromSurface(le.rend, window_surf);
		// SDL_FreeSurface(window_surf);

		// SDL_Surface * surface = SDL_GetWindowSurface(le.win);
		// const Uint8 Bpp = surface->format->BytesPerPixel;
		// Uint8* pPixel = (Uint8*)surface->pixels + y * surface->pitch + x * Bpp;
		// Uint32 PixelData = *(Uint32*)pPixel;
		SDL_Color color = {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE};
		// SDL_GetRGB(PixelData, surface->format, &color.r, &color.g, &color.b);
		color = GetPixel(window_surf, x, y);


		// printf("[%d, %d]: {%d, %d, %d}\n", x, y, color.r, color.g, color.b);
		// printf("[%d, %d]: {%d, %d, %d}\n", x, y, color.r, color.g, color.b);

		if(color.r != 0 || color.g != 0 || color.b != 0)
			printf("[%d, %d]: {%d, %d, %d}\n", x, y, color.r, color.g, color.b);
			// exit(0);

		// if(color.r != 0 || color.g != 0 || color.b != 0)
		// 	exit(0);

	}

}

