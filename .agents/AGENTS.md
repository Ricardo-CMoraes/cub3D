# AGENTS.md — cub3D Project Rules for Antigravity

This file defines the rules and constraints that Antigravity must follow when
assisting with the cub3D project. These rules must be applied to every file,
suggestion, commit message, and plan generated during this project.

---

## 1. Norma da 42 (Norminette)

All generated C code MUST comply with the 42 school Norminette:

- **Max 25 lines per function** (excluding blank lines and braces).
- **Max 5 functions per `.c` file** (static functions count).
- **Max 4 parameters per function**.
- **No `for` loops** — use `while` exclusively.
- **No `++i`** — use `i++` (post-increment only).
- **No assignment inside conditions** — `if ((x = foo()))` is forbidden.
- **No nested ternary operators**.
- **No `switch` or `do/while`** unless explicitly approved.
- **No global variables** — all state must be passed via structs.
- **No function declarations inside other functions**.
- **One blank line** between variable declarations and the first instruction.

### Header Guards
Every `.h` file must use the following pattern (UPPERCASE filename):

```c
#ifndef FILENAME_H
# define FILENAME_H

// content

#endif
```

### Includes
- System includes use `<angle_brackets>`.
- Project includes use `"double_quotes"`.
- No unused includes allowed.

---

## 2. Architecture Rules

### Project Structure
```
cub3D/
├── .agents/AGENTS.md
├── libs/
│   ├── minilibx-linux/             ← minilibx for Linux/WSL2
│   └── minilibx_macos_metal/       ← minilibx for macOS (Metal)
│       └── minilibx_mms_20200219/
├── includes/
│   ├── cub3d.h       ← main struct (t_game) + prototypes
│   ├── parser.h      ← Parser <-> Engine contract
│   └── keycodes.h    ← Cross-platform keycodes
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

### Struct Convention
- The central game state lives in `t_game` (defined in `cub3d.h`).
- The parser's output lives in `t_map_data` (defined in `parser.h`).
- Sub-structs should be embedded by value or pointer inside `t_game`.
- Naming: `t_` prefix for types, `s_` prefix for struct tags.

### Memory Management
- Every `malloc` must have a corresponding `free` path.
- Functions in `src/utils/memory.c` must handle cleanup.
- On any fatal error: call the cleanup function before `exit(1)`.

### Cross-Platform (macOS + Linux)
- All OS-specific code must use `#ifdef __linux__` / `#else` guards.
- Keycodes must use the constants defined in `includes/keycodes.h`.
- Makefile must detect OS with `$(shell uname -s)`.

---

## 3. Git & Versioning

### Branching Strategy
- `main` — Production. No direct commits. Merges via PR only.
- `develop` — Integration. All feature branches merge here first.
- `feature/<name>` — Individual features (e.g. `feature/dda-raycasting`).
- `bugfix/<name>` — Bug fixes (e.g. `bugfix/fix-texture-leak`).

### Conventional Commits
All commit messages must follow this format:

```
<type>(<scope>): <short description>

[optional body]
```

| Type | When to use |
|------|-------------|
| `feat` | New feature or behavior |
| `fix` | Bug fix |
| `refactor` | Code restructuring without behavior change |
| `chore` | Build, Makefile, dependency updates |
| `docs` | Documentation only changes |
| `test` | Adding or modifying test files |
| `style` | Formatting, whitespace (no logic change) |

**Examples:**
```
feat(engine): implement basic DDA algorithm setup
fix(parser): handle missing newline at end of map
chore(makefile): add mlx_linux detection for WSL2
```

### Pull Request Workflow
1. Branch from `develop`, never from `main`.
2. Open PR to `develop`, not to `main`.
3. PR must be reviewed by the partner before merging.
4. Delete branch after merge.

---

## 4. Antigravity Behavior Rules

### Planning Mode
- For tasks touching **multiple files** or involving **architectural decisions**,
  Antigravity MUST create an `implementation_plan.md` and await approval before
  writing any source code.
- For **simple, isolated tasks** (single function, single file, typo fix),
  Antigravity may write code directly.

### Code Generation
- Never generate code that violates the Norminette rules above.
- When generating a function, always include the prototype in the relevant `.h` file.
- When generating a new `.c` file, always create or update the corresponding header.
- Comment style: use `/* */` for multi-line, `//` is forbidden by Norminette — 
  use `/* inline comment */` only.

### Commit Messages
- When suggesting a commit, always format it as a Conventional Commit.
- Never suggest `git push --force` without explicit user approval.

### Scope of Work
- rida-cos handles: **Motor Gráfico, DDA Raycasting, MLX, Player Movement**.
- jnovais handles: **Parsing, Validation, `.cub` file reading**.
- Antigravity must respect this division and avoid generating parser code for
  rida-cos's scope unless explicitly asked.

---

## 5. Files to Never Modify (without explicit approval)

- `includes/parser.h` — This is a shared contract. Any change must be
  reviewed by both partners.
- `libs/minilibx-linux/` and `libs/minilibx_macos_metal/` — These are vendored dependencies.
- `.agents/AGENTS.md` — This file itself.

---

## 6. Additional Context

- The norma file from 42 school will be provided by the user and appended to
  this document. Once provided, treat it as the canonical reference.
- The project will be compiled with: `cc -Wall -Wextra -Werror`
- Target platforms: **macOS** (primary dev) and **Linux/WSL2** (partner dev).

---

## 7. Mandatory Part Specifications (Parte Obrigatória)

- **Program Name:** `cub3D`
- **Files to Turn In:** All project files
- **Makefile Targets:** `all`, `clean`, `fclean`, `re`, `bonus`
- **Arguments:** A map in format `*.cub`
- **Authorized External Functions:**
  - `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`, `gettimeofday`
  - All functions of the `math` library (`-lm`, `man 3 math`)
  - All functions of the `MinilibX` library
- **Libft Authorized:** Yes
- **Description:** 3D graphical representation of the inside of a maze from a first-person perspective using ray-casting.

### Constraints & Requirements
- **MiniLibX Usage:** Must use MiniLibX (system-installed or compiled from sources).
- **Window Management:** Window management must remain smooth (changing focus, minimizing, etc.).
- **Wall Textures:** 4 different wall textures depending on orientation (North, South, East, West).
- **Floor & Ceiling Colors:** Configurable as two distinct colors.
- **Window & Controls:**
  - Left / Right arrow keys: Look left / right.
  - `W`, `A`, `S`, `D` keys: Move perspective through the maze.
  - `ESC` key: Close window and terminate program cleanly.
  - Red `X` button (window close): Close window and terminate program cleanly.
  - Use of MiniLibX images is strongly recommended.
- **Scene Description File (`*.cub`):**
  - First argument must be a `.cub` scene description file.
  - **Map Composition:** Only 6 valid characters: `0` (empty space), `1` (wall), `N`, `S`, `E`, `W` (player start position and orientation).
  - **Map Closure:** The map must be completely closed/surrounded by walls (`1`), returning an error otherwise.
  - **Element Ordering & Formatting:**
    - Except for the map content, each element type must be separated by one or more empty lines.
    - Except for the map content (which must always be last), element types can appear in any order in the file.
    - Except for the map, information in element lines can be separated by one or more spaces.
    - The map must be parsed as it appears in the file. Spaces are a valid part of the map. Must parse any map respecting the rules.

