cmake_minimum_required(VERSION 3.24)
# find_package(SDL2 REQUIRED)

project(virtual_canvas)


# Project
set(SOURCE_FILES
	server.c)

# set(CMAKE_C_FLAGS
# 	"`sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_net -lSDL2_ttf")

# set(CMAKE_C_FLAGS
# 	"`pkg-config --cflags --libs sdl2` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_net -lSDL2_ttf")

set(CMAKE_C_FLAGS
	"`sdl2-config --cflags --libs sdl2` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_net -lSDL2_ttf")


add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
