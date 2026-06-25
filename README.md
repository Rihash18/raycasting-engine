# Raycaster

A raycasting engine built in C using the [raylib](https://www.raylib.com/) library, inspired by [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html).

## Features

- DDA (Digital Differential Analysis) raycasting algorithm
- Distance-based wall darkening for depth perception
- Minimap for navigation reference
- Player movement and rotation

## Built With

- **C** — core language
- **raylib** — graphics and input handling

## Getting Started

### Prerequisites

- GCC or Clang
- raylib installed on your system

### Build & Run

```bash
gcc main.c -o raycaster -lraylib -lm
./raycaster
```

## Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Rotate left |
| `D` | Rotate right |

## Reference

- [Lode's Computer Graphics Tutorial — Raycasting](https://lodev.org/cgtutor/raycasting.html)

## Author

**Rihash** — [GitHub](https://github.com/Rihash18)
