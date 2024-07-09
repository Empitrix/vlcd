# all:
# 	gcc -Isrc/Include -Lsrc/lib -o main main.c -lmingw32 -lSDL2main -lSDL2

windows:
	gcc -Isdl/Include -Lsdl/lib -o server server.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_net -lSDL2_image -lSDL2_ttf

linux:
	cc ./server.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_net -lSDL2_ttf -o ./server.out
	cc ./client.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -o ./client.out

