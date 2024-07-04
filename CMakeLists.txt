cmake_minimum_required(VERSION 3.24)
project(virtual_canvas)

# Project
set(SOURCE_FILES
	server.c)

set(CMAKE_SDL_FLAGS
	`sdl2-config --cflags --libs`
	-lSDL2
	-lSDL2_mixer
	-lSDL2_image
	-lSDL2_net
	-lSDL2_ttf)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${CMAKE_SDL_FLAGS})

