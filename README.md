# Virtual Canvas
an remote display emulator via socket

## Commands

Currently there is 4 commands:
- [Initialize](#initialize)
- [Frame](#frame)
- [Fill](#fill)
- [Read](#read)

> [!WARNING]
> There is no space is commands

Also by pressing `q` you close the program.

---

### Initialize
The startling letter for initialization is `A` followed by `RED value`, `GREEN value`, `BLUE value` and `WIDTH`, `HEIGHT` for size and lastly `0` or `1` for color mode; `0` means its **MONO** color and `1` means it's **FULL** color:

for example, following command creates a `400x400` window *FULL* color with white background
```text
# C R   G   B   W    H
# A 255 255 255 0400 0400 1

A255255255040004001
```

Usage:
```bash
./client "A255255255040004001"
```


### Frame
Frame command is to draw a frame and color it by given mode at initialization

Command starts with letter `B` followed by `X` and `Y` coordinates and `WIDTH`, `HEIGHT` for size, then `RED`, `GREEN`, `BLUE` for color of the frame

**FULL**: for example the following commands creates a frame at `[10, 10]` coordinates, with `15` pixel for it's size, and it's color is RED.

```text
# C X    Y    W    H    R   G   B
# B 0010 0010 0015 0015 000 000 255

B0010001000150015000000255
```
Usage:
```bash
./client "B0010001000150015000000255"
```
**MONO**: for example the following commands creates a frame at `[10, 10]` coordinates, with `15` pixel for it's size, and value of `255` for it's *mono* color:

```text
# C X    Y    W    H    M
# B 0010 0010 0015 0015 255

B0010001000150015255
```

Usage:
```bash
./client "B0010001000150015255"
```

### Fill
*FILL* color is for clearing the whole canvas, and pain it with given color.
The command stats with letter `C`, followed by `RED`, `GREEN`, `BLUE`.

For example the following command is for painting the canvas with color white.
```text
# C R   G   B
# C 255 255 255

C255255255
```
Usage:
```bash
./client "C255255255"
```

### Read
The command **READ** is for reading the frames by their coordinates, size, and their color, and it's only contains the letter `D`
for example:
```bash
./client "D"
```


## Build
For building the program for your self, you need to install [`SDL2`](https://gist.github.com/aaangeletakis/3187339a99f7786c25075d4d9c80fad5) library and `SDL-Net` by:

```bash
sudo apt install libsdl2-net-2.0-0
sudo apt install libsdl2-net-dev
```

For compiling the program you can use, `./compile.sh` or `CMake`.
```bash
chmod +x ./compile.sh
./compile.sh
```
after compiling you have `./server.out` and `./client.out` to work with,
NOTE: current port of the `./client.out` is `8080`.
