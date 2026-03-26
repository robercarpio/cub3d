# Cub3D

*This project has been created as part of the 42 curriculum by mamaratr, rcarpio-.*


## Description

**cub3D** is a 42 school project designed to create a "realistic" 3D graphical representation of a maze from a first-person perspective. Inspired by the 90's classic *Wolfenstein 3D*, the engine is built from scratch in **C** using the **Ray-casting** principle.

The goal is to parse a scene description file (`.cub`), manage window events using the **miniLibX** library, and render a dynamic environment with specific wall textures and customizable floor/ceiling colors.

## Features

- **Raycasting Engine**: Real-time rendering of a 3D environment based on a 2D map.
- **Smooth Navigation**: Movement using `W`, `A`, `S`, `D` and camera rotation with `Left`/`Right` arrows.
- **Texture Mapping**: Support for distinct textures for North, South, East, and West walls.
- **Map Parsing**: Validates closed maps, player start positions (N, S, E, W), and configuration identifiers.
- **Memory Management**: Clean exit via `ESC` or window cross, ensuring no memory leaks.

## Instructions

### Compilation

To compile the project, run:
```bash
make
```

This will generate the executable using the provided Makefile.

### Cleaning

To remove object files:
```bash
make clean
```

To remove object files and the executable:
```bash
make fclean
```

To recompile everything from scratch:
```bash
make re
```

### Execution

After compilation, run the program with:
```bash
./cub3d maps/map.cub
```

## Resources

### Documentation & References

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - Fundamental logic for the raycasting and DDA algorithms.
- 42 Norm - The official coding standard for 42 projects.
- [MinilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Guide for handling pixels and window events.

### AI Usage

AI tools were used in the following capacity for this project:

- **Code review and debugging**: Used to identify potential memory leaks in the parser and logic errors in the raycasting loop.
- **Learning resources**: Generating explanations for Digital Differential Analysis (DDA) and vector rotation.
- **Code optimization**: Suggestions for improving the efficiency of the pixel buffer rendering.

**Note**: All core logic and implementation were developed independently by the project authors. AI was used as a supplementary tool for learning and refinement, not for generating the primary codebase.

---

*For questions or issues, please contact the project authors: **mamaratr** or **rcarpio-**.*

---