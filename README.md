*This project was created as part of the 42 curriculum by rida-cos, jnovais.*

# cub3D

## Description

**cub3D** is a 42 School project inspired by the legendary Wolfenstein 3D, the world's first first-person shooter (FPS) game. The main goal of this project is to create a real-time 3D raycasting graphics engine, written purely in C and using the MiniLibX graphics library.

This project allows exploring fundamental concepts of computer graphics, applied mathematics (trigonometry, vectors, and matrices), window and event management (inputs), texture rendering, and performance optimization. It serves as a robust introduction to graphics engine development and low-level programming of interactive visual interfaces.

## Instructions

### Prerequisites

To compile and run the project, you will need the following dependencies:

**macOS:**
```bash
# XCode command line tools
xcode-select --install
```

**Linux / WSL2:**
```bash
sudo apt-get install -y gcc make xorg libxext-dev libbsd-dev
```

### Installation

Clone the repository to your machine:

```bash
git clone <repo_url> cub3D
cd cub3D
```

Ensure that the MiniLibX library is correctly placed in the `libs/` directory. The project is structured to support `mlx_mac` for macOS (Metal) and `mlx_linux` for Linux environments.

### Compilation

The project includes a `Makefile` with the following rules available:
- `make` or `make all`: Compiles the `cub3D` executable.
- `make clean`: Removes intermediate object files.
- `make fclean`: Removes object files and the final executable.
- `make re`: Recompiles the entire project from scratch.
- `make norm`: Runs the Norminette tool on the source directories (`src/` and `includes/`).

### Execution

To start the game, run the binary passing the path to a valid `.cub` map as an argument:

```bash
./cub3D maps/test.cub
```

**Basic Controls:**
- `W`, `A`, `S`, `D`: Move the perspective through the maze (forward, left, backward, right).
- `←` and `→` (Arrows): Rotate the camera (vision) to the left or right.
- `ESC` or close window button: Cleanly exits the program, without memory leaks.

## Resources

### Classic References
- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html) - The most complete and widely used tutorial to understand and implement the mathematical logic behind DDA and raycasting.
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Extensive unofficial documentation to understand MiniLibX hooks, events, and image management.

### Project Study Materials
- [Desmos Raycasting Simulation](https://www.desmos.com/calculator/ipqm4bs6qd) - Interactive simulation created to visually illustrate the behavior of the direction (`dir`) and camera plane (`plan`) vectors, as well as the mechanics of rotation and ray calculation.
- [Desmos Distancies](https://www.desmos.com/geometry/h8tzdh6jai) - Ilustration of ray directions

### Use of Artificial Intelligence

In line with 42's encouragement (*"Develop prompt skills — both for coding and other tasks — that will benefit your future career"*), artificial intelligence was employed in this project responsibly, methodologically, and critically.

We did not use AI as a mere final code generator (copy and paste), but rather as an advanced tool for learning and workflow orchestration. The main applications included:

1. **Agentic Development & Pair Programming:** AI was integrated into the repository through strict rules (`AGENTS.md` files) defining clear contracts regarding project architecture, Norminette conventions, and individual student responsibilities (`rida-cos` and `jnovais`).
2. **12factor Agentics Ops:** We applied modern methodologies to manage AI "operations", ensuring the agent acted with determinism within well-defined architectural boundaries and isolated code scopes, facilitating iterative human validation.
3. **Prompt Engineering for Learning:** We actively used AI to discuss mathematical optimization approaches in DDA and parsing designs for secure validation of closed maps. The generated discussions were subsequently validated with peers, refining the group's joint implementation and ensuring complete mastery over all inserted code.

#### AI and Agentic Ops Study References
- [Anthropic Learn - AI and Prompt Engineering Learning Guide](https://www.anthropic.com/learn)
- [12 Factor Agent Ops - Methodology for AI agents](https://www.12factoragentops.com)
- [Fábio Akita Article - How to use AI in real projects](https://akitaonrails.com/2026/02/20/do-zero-a-pos-producao-em-1-semana-como-usar-ia-em-projetos-de-verdade-bastidores-do-the-m-akita-chronicles/)
- [Reference Video - AI and Development (YouTube)](https://youtu.be/yDO21vewdes?si=wydUPbgAtf6ZVg7g)

---

## Raycasting Math Formulas

This section documents the core mathematical formulas used in the engine, mapped to the exact variable names found in our codebase (`ray`, `player`, `tex`). These formulas are adapted from Lode's Computer Graphics Tutorial - Raycasting. It is recommend to open this file in an IDE with math formula rendering support.

### 1. Ray Screen Mapping

$$\text{camera\_x} = 2 \times \frac{x}{\text{WIN\_WIDTH}} - 1$$

$$\text{ray->dir\_x} = \text{player.dir\_x} + \text{player.plane\_x} \times \text{camera\_x}$$

$$\text{ray->dir\_y} = \text{player.dir\_y} + \text{player.plane\_y} \times \text{camera\_x}$$

---

### 2. Grid Increment Distances ($\Delta$)

$$\text{ray->delta\_x} = \left\vert{} \frac{1}{\text{ray->dir\_x}} \right\vert{}$$

$$\text{ray->delta\_y} = \left\vert{} \frac{1}{\text{ray->dir\_y}} \right\vert{}$$

---

### 3. Initial Distance to the First Grid Line

$$\text{If } \text{ray->dir\_x} < 0:$$

$$\text{ray->step\_x} = -1$$

$$\text{ray->side\_x} = (\text{player.pos\_x} - \text{ray->map\_x}) \times \text{ray->delta\_x}$$

$$\text{If } \text{ray->dir\_x} \ge 0:$$

$$\text{ray->step\_x} = 1$$

$$\text{ray->side\_x} = (\text{ray->map\_x} + 1.0 - \text{player.pos\_x}) \times \text{ray->delta\_x}$$

$$\text{If } \text{ray->dir\_y} < 0:$$

$$\text{ray->step\_y} = -1$$

$$\text{ray->side\_y} = (\text{player.pos\_y} - \text{ray->map\_y}) \times \text{ray->delta\_y}$$

$$\text{If } \text{ray->dir\_y} \ge 0:$$

$$\text{ray->step\_y} = 1$$

$$\text{ray->side\_y} = (\text{ray->map\_y} + 1.0 - \text{player.pos\_y}) \times \text{ray->delta\_y}$$

---

### 4. DDA Algorithm (Loop Step)

$$\text{If } \text{ray->side\_x} < \text{ray->side\_y}:$$

$$\text{ray->side\_x} = \text{ray->side\_x} + \text{ray->delta\_x}$$

$$\text{ray->map\_x} = \text{ray->map\_x} + \text{ray->step\_x}$$

$$\text{ray->side} = 0$$

$$\text{If } \text{ray->side\_x} \ge \text{ray->side\_y}:$$

$$\text{ray->side\_y} = \text{ray->side\_y} + \text{ray->delta\_y}$$

$$\text{ray->map\_y} = \text{ray->map\_y} + \text{ray->step\_y}$$

$$\text{ray->side} = 1$$

---

### 5. Perpendicular Wall Distance

$$\text{If } \text{ray->side} == 0:$$

$$\text{ray->wall\_dist} = \text{ray->side\_x} - \text{ray->delta\_x}$$

$$\text{If } \text{ray->side} == 1:$$

$$\text{ray->wall\_dist} = \text{ray->side\_y} - \text{ray->delta\_y}$$

---

### 6. Screen Projection (Line Height and Limits)

$$\text{ray->line\_h} = \left\lfloor \frac{\text{WIN\_HEIGHT}}{\text{ray->wall\_dist}} \right\rfloor$$

$$\text{ray->draw\_start} = \frac{\text{WIN\_HEIGHT}}{2} - \frac{\text{ray->line\_h}}{2}$$

$$\text{ray->draw\_end} = \frac{\text{WIN\_HEIGHT}}{2} + \frac{\text{ray->line\_h}}{2}$$

---

### 7. Horizontal Texture Coordinate

$$\text{If } \text{ray->side} == 0:$$

$$\text{ray->wall\_x} = \text{player.pos\_y} + \text{ray->wall\_dist} \times \text{ray->dir\_y}$$

$$\text{If } \text{ray->side} == 1:$$

$$\text{ray->wall\_x} = \text{player.pos\_x} + \text{ray->wall\_dist} \times \text{ray->dir\_x}$$

$$\text{ray->wall\_x} = \text{ray->wall\_x} - \lfloor \text{ray->wall\_x} \rfloor$$

$$\text{tex\_x} = \lfloor \text{ray->wall\_x} \times \text{tex->width} \rfloor$$

---

### 8. Vertical Texture Mapping

$$\text{step} = \frac{\text{tex->height}}{\text{ray->line\_h}}$$

$$\text{tex\_pos} = \left( \text{ray->draw\_start} - \frac{\text{WIN\_HEIGHT}}{2} + \frac{\text{ray->line\_h}}{2} \right) \times \text{step}$$

$$\text{tex\_y} = \lfloor \text{tex\_pos} \rfloor \pmod{\text{tex->height}}$$
