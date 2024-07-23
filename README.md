# Virtual Canvas
an remote display emulator via socket

## Commands

Currently there is 5 commands:
- [Initialize](#initialize)
- [Frame](#frame)
- [set pixel](#set-pixel)
- [Fill](#fill)
- [Read](#read)

> [!NOTE]
> All of the data transition between sockets are hexadecimal, and the long numbers are broken into two hex, such as coordinates, size...


Also by pressing `q` you close the program.

---
## Protocol Overview
This protocol defines communication between a client and a graphical display server.
Commands are sent as byte sequences, allowing the client to control the display's appearance and retrieve pixel data.

### Initialize

The command index for initialize is `\x01`, followed by its color, size, and color mode.
for example the following commands initialize a `400x400` window, with a white background and `FULL-Color` as its mode
<!--
```text

COMM       Green       Width                   Mode
│          │           │                       │    
└───       └───        └──────────             └─── 
\x01, \xFF, \xFF, \xFF, \x01, \x90, \x01, \x90, \x01
      ───┐        ───┐              ──────────┐
         │           │                        │
         Red         Blue                     Height
```
-->

```text

┌ COMM     ┌ Green     ┌ Width                 ┌ Mode
└───       └───        └──────────             └──── 
\x01, \xFF, \xFF, \xFF, \x01, \x90, \x01, \x90, \x01
      ───┐        ───┐              ──────────┐
     Red ┘      Blue ┘                 Height ┘
```

**WIDTH** and **HEIGHT** are broken down into two bites

### Frame
 The command index for frame is `\x02` followed by frames X and Y coordinate and width and height after that its place for frames data if the `COLOR-MODE` is *MONO* the data is only 0s and 1s otherwise the data contains 3-bit for `RED`, `GREEN`, `BLUE`.
 For example the following command is for to setup a 2x2 frame at `[250, 250]`, with `RED`, `GREEN`, `BLUE`, `WHITE` as its data
<!--
 ```text
COMM   X            Y            Width        Height        
│      │            │            │            │          
└───   └──────────  └──────────  └──────────  └──────────
\x02,  \x00, \xFA,  \x00, \xFA,  \x00, \x02,  \x00, \x02,
	\xff, \x00, \x00,  // RED   Color
	\x00, \xff, \x00,  // GREEN Color
	\x00, \x00, \xff,  // BLUE  Color
	\xff, \xff, \xff,  // WHITE Color
}
```
-->
 ```text
┌ COMM ┌ X          ┌ Y          ┌ Width      ┌ Height
└───   └──────────  └──────────  └──────────  └──────────
\x02,  \x00, \xFA,  \x00, \xFA,  \x00, \x02,  \x00, \x02,
	\xff, \x00, \x00,  // RED   Color
	\x00, \xff, \x00,  // GREEN Color
	\x00, \x00, \xff,  // BLUE  Color
	\xff, \xff, \xff,  // WHITE Color
}
```

The `X`, `Y` and `Height`, `Width` are broken down into 2 bites.

### Set Pixel
The command index for set-pixel is `\x03`, followed by its `X`, `Y` and `RED`, `GREEN`, `BLUE`.

for example the following command is to color a pixel at `[200, 200]` with *BLUE* color
<!--
```text
COMM              Y                 Green
│                 │                 │
└───              └─────────        └─
\x03, \x00, \xC8, \x00, \xC8, \x00, \x00, \xFF
      ──────────┐             ────┐       ───┐ 
                │                 │          │
                X                 Red        Blue

```
-->

```text
┌ COMM            ┌ Y               ┌ Green
└───              └─────────        └───
\x03, \x00, \xC8, \x00, \xC8, \x00, \x00, \xFF
      ──────────┐             ────┐       ───┐ 
              X ┘             Red ┘     Blue ┘

```

### Fill
The command index for fill is `\x04` followed by value of `RED`, `GREEN`, `BLUE` for colorizing the whole canvas.
For example the following command, will fill the whole canvas with color *GREEN*
```text
┌ COMM      ┌ Green
└───        └───
\x04, \x00, \xFF, \x00
      ────┐       ────┐
      Red ┘      Blue ┘
```

### Read
The index for read command is `\x05`.
The read command returns a data of whole canvas and need to be read from socket
for example the following command is to getting pixels data
<!--
```text
COMM
│
└───
\x05
```
-->
```text
┌ COMM
└───
\x05
```

The return data is an `char` array with size of `(width * height) * 7`, you can change the width and height (capture) in `./src/exec/read.c` to specify limits and the `7` is for (`Xa`, `Xb`, `Ya`, `Yb`, `R`, `G`, `B`) which is 7 memeber in total.


### Preview

| Command    | Index | Size | Parameters                                                       | Description                                                                              |
|------------|-------|------|------------------------------------------------------------------|------------------------------------------------------------------------------------------|
| Initialize | 1     |      | Color (3 bytes), Size (4 bytes), Color Mode (1 byte)             | Sets up the display window with specified dimensions, background color, and color depth. |
| Frame      | 2     |      | X, Y coordinates (4 bytes), Width, Height (4 bytes), Pixel Data* | Defines a rectangular area and its pixel values.                                         |
| Set Pixel  | 3     |      | X, Y coordinates (4 bytes), Color (3 bytes)                      | Sets the color of a single pixel.                                                        |
| Fill       | 4     |      | Color (3 bytes)                                                  | Fills the entire canvas with the specified color.                                        |
| Read       | 5     |      | None                                                             | Requests pixel data for the entire canvas from the server.                               |



## Build
You build the program yourself:

First you need to clone the repository and going to projects folder:
```bash
git clone "https://github.com/empitrix/virtual_canvas"
cd ./virtual_canvas
```

after that you can compile the program by:
```bash
chmod +x ./compile.sh
./compile.sh
```

or you can use `Makefile` to compile for Windows or Linux.
for compiling the program for **WINDOWS** you can use following steps:
```bash
./install.ps1
make windows
```

for compiling the program for **LINUX** you can use following steps:
```bash
make linux
```

Two file `client.out` and `server.out` will be created.


## Compile Using CMake

Requirements:
- CMake

### Linux

Install SDL2 libraries:
```bash
#install sdl2
sudo apt install libsdl2-dev libsdl2-2.0-0 -y;

#install sdl image  - if you want to display images
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y;

#install sdl mixer  - if you want sound
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y;

# install sdl true type fonts - if you want to use text
sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y;

# net
sudo apt install libsdl2-net-2.0-0
sudo apt install libsdl2-net-dev    

```

Compile:
```bash
git clone "https://github.com/empitrix/virtual_canvas"
cd ./virtual_canvas

mkdir build && cd ./build

# run cmake:
cmake ..
cmake --build .
```
now in you have `./build/server` and `./build/client` in Linux


## Run
To run the program you need to compile the program; after that, two files `server.out` and `client.out` will be created.

you can run the server by following command, the first argument is scale which is from `0` to `8` and can be changed with `+` for increase and `-` for decrease, and the second argument is the port for program to listen to, the default port is `8080`

run the server:
```bash
./server.out 1 8080
```

run the client:
```bash
./client.out
```



