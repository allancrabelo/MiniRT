*This project has been created as part of the 42 curriculum by mqueiros, aaugusto.*

---

## Description

**miniRT** is a minimal ray tracer written in C, built as part of the 42 school curriculum. It's goal is to render 3D scenes described in `.rt` configuration files by simulating the physical behavior of light rays: Computing intersections with geometric objects, applying lighting models, and producing a pixel-accurate image displayed in a window.

The renderer supports the following scene elements:

| Element | Identifier |
|---|---|
| Ambient light | `A` |
| Camera | `C` |
| Point light | `L` |
| Sphere | `sp` |
| Plane | `pl` |
| Cylinder | `cy` |

Lighting is computed with a **Phong shading model** (ambient + diffuse + specular components) and includes hard shadow casting. The window is interactive: the camera can be moved and rotated in real time using the keyboard.

---

## Instructions

### Dependencies

- A C compiler (`clang`)
- X11 development libraries (required by MiniLibX)
- `make`

On Debian/Ubuntu:
```bash
sudo apt-get install gcc make libx11-dev libxext-dev
```

### Compilation

Clone the repository and run `make` at the project root:

```bash
git clone git@github.com:allancrabelo/MiniRT.git miniRT
cd miniRT
make
```

This compiles `libft`, `minilibx`, and the project itself, producing the `miniRT` binary.

| Target | Description |
|---|---|
| `make` / `make all` | Build the binary |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | Full rebuild |

### Execution

```bash
./miniRT <scene_file.rt>
```

Example using one of the provided evaluation scenes:

```bash
./miniRT evaluation_sheets/01_sphere_basic.rt
```

### Scene File Format

Each line in a `.rt` file describes one scene element. Lines starting with `#` are comments.

```
# Ambient light: identifier  brightness  R,G,B
A  0.2  255,255,255

# Camera: identifier  position  orientation_vector  FOV(degrees)
C  0,0,5  0,0,-1  70

# Point light: identifier  position  brightness  R,G,B
L  0,10,5  0.7  255,255,255

# Sphere: identifier  center  diameter  R,G,B
sp  0,0,0  2  255,0,0

# Plane: identifier  point  normal_vector  R,G,B
pl  0,-1,0  0,1,0  100,200,100

# Cylinder: identifier  center  axis_vector  diameter  height  R,G,B
cy  0,0,0  0,1,0  1.5  4  50,150,255
```

### Controls

| Key | Action |
|---|---|
| Arrow keys | Move camera (translate) |
| `W` / `S` | Move camera forward / backward |
| `A` / `D` | Strafe left / right |
| Numpad `1`–`9` | Jump to preset camera positions |
| `Q` | Re-render at full quality |
| `R` | Reset camera to initial position |
| `Tab` | Toggle on-screen controls help |
| `Escape` / close button | Quit |

---

## Resources

### Ray Tracing & Computer Graphics

- **"The Ray Tracer Challenge"** - Jamis Buck - https://pragprog.com/titles/jbtracer/the-ray-tracer-challenge/
  Foundational book covering ray–sphere intersection, shading, reflection, and camera models.
- **MiniLibX documentation** - https://harm-smits.github.io/42docs/libs/minilibx
  Documentation for the 42-school graphics library used to open windows and write pixels.

### AI Usage

AI tools (GitHub Copilot / ChatGPT) were used during development for the following tasks:

- **Debugging** - Identifying edge cases in ray–cylinder intersection logic (caps, degenerate axes) and shadow-acne artefacts caused by floating-point precision.
- **Mathematical derivations** - Verifying the quadratic formula expansions for ray–sphere and ray–cylinder intersections, and simplifying vector projection formulas.
- **Code review** - Suggesting improvements to memory management patterns and spotting potential out-of-bounds accesses in the parser.
- **Documentation** - Generating Doxygen-style function comments (`@brief`, `@param`, `@return`) as a starting point, subsequently reviewed and corrected by hand.

AI-generated suggestions were always reviewed, tested, and adjusted before being integrated into the codebase. No AI tool was used to produce complete algorithmic solutions without prior understanding.
