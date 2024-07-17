cc ./server.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_net -lSDL2_ttf -o "./server.out"
cc ./client.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_net -lSDL2_ttf -o "./client.out"

cc ./key_client.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_net -lSDL2_ttf -o "./key_client.out"

