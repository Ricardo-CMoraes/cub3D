# cub3D

> Inspired by the legendary Wolfenstein 3D, the world's first FPS game.  
> A real-time 3D raycasting engine written in C using the MiniLibX graphics library.

---

## Team

| Partner | Scope |
|---------|-------|
| rida-cos | Motor Gráfico, DDA Raycasting, MLX, Player |
| Joao | Parser, Validation, `.cub` file reading |

---

## Project Structure

```
cub3D/
├── .agents/
│   └── AGENTS.md          ← AI agent rules (Antigravity)
├── libs/
│   ├── mlx_linux/         ← MiniLibX for Linux/WSL2
│   └── mlx_mac/           ← MiniLibX for macOS (Metal)
├── includes/
│   ├── cub3d.h            ← Main structs and prototypes
│   ├── parser.h           ← Parser <-> Engine contract
│   └── keycodes.h         ← Cross-platform keycodes
├── src/
│   ├── main.c
│   ├── parser/
│   ├── engine/
│   ├── player/
│   └── utils/
├── maps/
│   └── test.cub
└── Makefile
```

---

## Prerequisites

### macOS

```bash
# XCode command line tools
xcode-select --install
```

### Linux / WSL2

```bash
sudo apt-get install -y gcc make xorg libxext-dev libbsd-dev
```

---

## Installation

Clone and add the MiniLibX libraries:

```bash
git clone <repo_url> cub3D
cd cub3D

# Download and extract MiniLibX (place inside libs/)
# macOS: minilibx_macos_metal.tgz  → libs/mlx_mac/
# Linux: minilibx-linux.tgz        → libs/mlx_linux/
```

---

## Compilation

```bash
make        # build the binary
make re     # clean + rebuild
make clean  # remove object files
make fclean # remove objects + binary
make norm   # run Norminette on src/ and includes/
```

---

## Usage

```bash
./cub3D maps/test.cub
```

The `.cub` file must include valid texture paths (`.xpm`), RGB floor/ceiling colors, and a properly enclosed map grid.

---

## Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` / `→` | Rotate camera |
| `ESC` | Quit |

---

## Git Branching Strategy

| Branch | Purpose |
|--------|---------|
| `main` | Production — merges only, no direct commits |
| `develop` | Integration — test all features here before main |
| `feature/<name>` | New features |
| `bugfix/<name>` | Bug fixes |

### Conventional Commits

```
feat(engine): implement DDA raycasting loop
fix(parser): handle missing newline at map EOF
chore(makefile): add norm target for norminette
```

---

## Subject Reference

- 42 School — cub3D project
- [MiniLibX Linux](https://github.com/42Paris/minilibx-linux)
