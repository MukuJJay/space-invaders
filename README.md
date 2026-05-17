# Space Invaders

A simple Space Invaders-style arcade game written in C++ using [Raylib](https://www.raylib.com/).

## Features

- Player-controlled spaceship
- Alien formation movement
- Player lasers and alien lasers
- Defensive obstacles
- Mystery ship spawning
- Texture-based sprites

## Controls

- `A` - Move left
- `D` - Move right
- `Space` - Fire laser

## Requirements

- C++20 compiler, such as `g++`
- Raylib development libraries installed on your system
- `make`

On Debian/Ubuntu-based systems, Raylib may be available through your package manager, or you can install it from the official Raylib instructions.

## Build

```bash
make
```

This creates the executable:

```bash
build/space_invaders
```

## Run

```bash
make run
```

## Clean

```bash
make clean
```

## Project Structure

```text
assets/      Sprite images
src/         Game source files
Makefile     Build script
```

## Notes

The game uses Raylib for window creation, drawing, input handling, textures, and timing.
