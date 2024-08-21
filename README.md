# flappybirdCPP
# flappybirdCPP
# Window Game

This is a simple window game created using C++ and SFML.

## Installation

### Installing SFML on Linux

To install SFML on Linux, you can use your distribution's package manager. Here are instructions for some common distributions:

#### Ubuntu or Debian:

```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

#### Fedora:

```bash
sudo dnf install SFML SFML-devel
```

#### Arch Linux:

```bash
sudo pacman -S sfml
```

If your distribution is not listed here, please check your package manager for SFML or visit the [official SFML website](https://www.sfml-dev.org/download.php) for more information.

## Compiling and Running the Game

After installing SFML, you can compile and run the game with these commands:

```bash
g++ -c window_game.cpp
g++ window_game.o -o window_game -lsfml-graphics -lsfml-window -lsfml-system
./window_game
```

Enjoy playing!
