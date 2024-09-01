# Cub3D
This project was developed for 42 school. For comprehensive information regarding the requirements, please consult the PDF file in the subject folder of the repository. Furthermore, I have provided my notes and a concise summary below.
``` diff
+ keywords: raycasting
+ top down 2D game into 3D
```

## High-level Overview

This project is inspired by the world-famous Wolfenstein 3D game, which
was the first FPS ever. The goal is to make a dynamic view inside a maze, in which you’ll have to find your way.

Convert a top down 2D game (map 2D square grid) into 3D:
1. Each square can either be 0 (no wall) or positive value (a wall with a certain texture)
2. From user point of view, cast rays until they reach the wall;
3. Convert ray distance into a vertical line;


```c
void  drawRays3D() {
  // check horizontal and vertical lines in the 2D plan
  // is the ray looking up or down (we discover it by looking the rays angle)
  // is it less then pi?
  // looking straight left or right it is impossible to hit a horizontal line
  while() {
    // stop when ray hits a wall
    // if it didnt hit a wall
    // else -> add x and y offset to check the next
  }
}

int mapX=12; mapY=8; mapS=64;
int map[] = {
  1,1,1,1,1,1,1,1,1,1,1,1
  1,0,0,0,0,0,0,0,0,0,0,1
  1,0,0,0,0,0,0,0,0,0,0,1
  1,0,0,0,0,0,0,0,0,0,0,1
  1,0,0,0,0,0,0,0,0,0,0,1
  1,0,0,0,0,0,0,0,0,0,0,1
  1,0,0,0,0,0,0,0,0,0,0,1
  1,1,1,1,1,1,1,1,1,1,1,1
} // 0 for space and 1 for wall

void data() {
  // structure with data we want to persist
}

void  drawPlayer() {
}

void  drawMap2D() {
  int x, y, xo, yo;
  for(x=0; x < mapX; x++) {
    if (map[y*mapX + x] == 1) { color(1,1,1); } else{ color(0,0,0); }
    ...
  }
}

void  display() {
  drawPlayer();
}

void init() {
  px = 300;
  py = 300;
}

int main() {
  init();
}
```

### References:
[Make Your Own Raycaster Part 1](https://www.youtube.com/watch?v=gYRrGTC7GtA)<br />
[42 Docs - Cub3D](https://harm-smits.github.io/42docs/projects/cub3d)<br />

## Concepts

| Task | Prototype | Description |
|:----|:-----:|:--------:|
| **Raycasting** | `Raycasting is not the same as raytracing` | Raycasting can go very fast, because only a calculation has to be done for every vertical line of the screen. Later games such as Doom and Duke Nukem 3D also used raycasting, but much more advanced engines that allowed sloped walls, different heights, textured floors and ceilings, transparent walls, etc... `Raytracing` is a realistic rendering technique that supports reflections and shadows in true 3D scenes, and only recently computers became fast enough to do it in realtime for reasonably high resolutions and complex scenes. |
| **Sprites** | x | The sprites (enemies, objects and goodies) are 2D images. |
| **Rotate the player** | $cos$ $sin$ | In C instead of using degrees for measuring rotation, it should use radians (unit of measurement of angles). Half a revolution is therefore equal to 2π/2 = π radians. One quarter of a revolution (a right angle) equals 2π/4 = π/2 radians. Three quarters of a revolution measures 3 × π/2 = 3π/2 radians. I can define values (macros) from the unit circle, so it is easier to use them later. <img width="1236" alt="Screenshot 2024-06-05 at 19 46 57" src="https://github.com/lets-cpp/cub_3D/assets/115558344/54d38902-8b0f-4c12-81b1-75a40f0f660e"> |
| **Draw the shortest line that hits the wall first** | `distH = dist(px, py, hx, hy, ra)` | From the players rotation and `drawRays3D` calculation, find the shortest line that hits the wall first. Calculate the rays distance from the player. |
| **Define one degree in radians** | `#define DR 0.0174533` | Cast/offset rays 30 degrees left and right from the player. Moreover, define `PI 3.1415926535`. |
| **dist** | | Create a variable to hold the final distance. |
| **Draw 3D walls** | | The larger the distance, shorter will be the wall height. |
| **Fix fish eye** | $cos$ | |
| **[Adding submodules](https://gist.github.com/gitaarik/8735255)** | `mlx` `libft` | Adding a new submodule -> `git submodule init` `git submodule add https://github.com/42Paris/minilibx-linux.git`. Updating submodules in a new machine -> `git submodule update` `git submodule update --init` `git submodule update --recursive`. Close main repository and update submodules -> `git clone --recurse-submodules`. Pull main repository and update submodules -> `git pull --recurse-submodules`. |
| **Create cool Makefile messages** | [patorjk.com/](https://patorjk.com/software/taag/#p=display&c=echo&f=Star%20Wars&t=%20%2B%20utils) | |
# cub3D
# cub3D
