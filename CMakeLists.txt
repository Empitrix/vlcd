cmake_minimum_required(VERSION 3.10)

project(virtual_canvas)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_net REQUIRED)


INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

file(COPY
	"${CMAKE_CURRENT_SOURCE_DIR}/assets/HNFMR.ttf" DESTINATION
	"${CMAKE_CURRENT_BINARY_DIR}/assets")


# Copy Assets
list(APPEND SVGS_IDX 1 2 3 4)
foreach(SVG IN LISTS SVGS_IDX)
	file(COPY
		"${CMAKE_CURRENT_SOURCE_DIR}/assets/wifi/svg/${SVG}.svg" DESTINATION
		"${CMAKE_CURRENT_BINARY_DIR}/assets/wifi/svg/")
endforeach()


if(LINUX) 
	set(SOURCES "server.c;client.c")
elseif(WIN32)
	# NOT WRITTEN YET
	# set(SOURCES "server.c;win_client.c")
endif()

# Loop through each source file and make an executable
foreach(source_file IN LISTS SOURCES)
	# get element's name
	get_filename_component(target_name ${source_file} NAME_WE)

	add_executable("${target_name}" "${source_file}")

	target_link_libraries("${target_name}" 
		SDL2
		SDL2main
		SDL2_image
		SDL2_ttf
		SDL2_net
	)
endforeach()

