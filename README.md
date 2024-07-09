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

### Initialize
The command index for initialize is `\x01`, followed by its color, size, and color mode.
for example the following commands initialize a `400x400` window, with a white background and `FULL-Color` as it's mode

```text
COMM    RED     Green   Blue    Wa       Wb     Ha      Hb      mode
'\x01', '\xFF', '\xFF', '\xFF', '\x01', '\x90', '\x01', '\x90', '\x01'
```

**WIDTH** and **HEIGHT** are broken down into two bites

### Frame
 The command index for frame is `\x02` followed by frame's X and Y coordinate and width and height after that it's place for frame's data if the `COLOR-MODE` is *MONO* the data is only 0's and 1's otherwise the data contains 3-bit for `RED`, `GREEN`, `BLUE`.
 For example the following command is for to setup a 2x2 frame at `[250, 250]`, with `RED`, `GREEN`, `BLUE`, `WHITE` as it's data
 ```text
COMM    Xa      Xb      Ya      Yb      Wa      Wb     Ha        Hb
'\x02', '\x00', '\xFA', '\x00', '\xFA', '\x00', '\x02', '\x00', '\x02',
	'\xff', '\x00', '\x00',  // RED   Color
	'\x00', '\xff', '\x00',  // GREEN Color
	'\x00', '\x00', '\xff',  // BLUE  Color
	'\xff', '\xff', '\xff',  // WHITE Color
}; 
```

The `X`, `Y` and `Height`, `Width` are broken down into 2 bites.

### Set Pixel
The command index for set-pixel is `\x03`, followed by it's `X`, `Y` and `RED`, `GREEN`, `BLUE`.

for example the following command is to color a pixel at `[200, 200]` with *BLUE* color
```text
COMM    Xa      Xb      Ya      Yb      Red     Green   Blue
'\x03', '\x00', '\xC8', '\x00', '\xC8', '\x00', '\x00', '\xFF'
```


### Fill
The command index for fill is `\x04` followed by value of `RED`, `GREEN`, `BLUE` for colorizing the whole canvas.
For example the following command, will fill the whole canvas with color *GREEN*
```text
COMM    RED     GREEN   BLUE
'\x04', '\x00', '\xFF', '\x00'
```

### Read
The index for read command is `\x05`.
The read command returns a data of whole canvas and need to be read from socket
for example the following command is to getting pixel's data
```
COMM
'\x05'
```

The return data is an `char` array with size of `(width * height) * 7`, you can change the width and height (capture) in `./src/exec/read.c` to specify limits and the `7` is for (`Xa`, `Xb`, `Ya`, `Yb`, `R`, `G`, `B`) which is 7 memeber in total.


## Build
You build the program yourself:

First you need to clone the repository and going to project's folder:
```bash
git clone "https://github.com/empitrix/virtual_canvas"
cd ./virtual_canvas
```

after that you can compile the program by:
```bash
chmod +x ./compile.sh
./compile.sh
```

Two file `client.out` and `server.out` will be created.

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
