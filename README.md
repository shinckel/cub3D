# Cub3D
This project was developed for 42 school. For comprehensive information regarding the requirements, please consult the PDF file in the subject folder of the repository. Furthermore, I have provided my notes and a concise summary below.
``` diff
+ keywords: raycasting
+ top down 2D game into 3D
+ windows, colors, events, shapes 
```

## High-level Overview

This project is inspired by the world-famous Wolfenstein 3D game, developed by John Carmack and John Romero, which was the first FPS (first person shooter) ever. The goal is to make a dynamic view inside a maze, in which you’ll have to find your way.

Convert a top down 2D game (map 2D square grid) into 3D:
1. Each square can either be 0 (no wall) or positive value (a wall with a certain texture)
2. From user point of view, cast rays until they reach the wall;
3. If the ray hits a wall, then the loop can stop. Calculate the distance and draw the wall with the correct height; **_The raycasting loop is a for loop that goes through every x, so there isn't a calculation for every pixel of the screen, but only for every vertical stripe, which isn't much at all!_
4. If it doesn't hit a wall, you have to trace it further: add a certain value to its position, in the direction of the direction of this ray, and for this new position check again if it hits a wall or not; <br /><br />
![raycastingcamera](https://github.com/lets-cpp/cub_3D/assets/115558344/8d730871-559c-4ae3-a682-6ae81be7b05a) <br />

- green point -> position (vector pos)
- black line ending in a black spot -> direction (vector dir)
- the position of the black dot is $pos + dir$
- blue line -> full camera plane (blue dot to the right -> $pos + dir + plane$ and blue dot to the left -> $pos + dir - plane$
- red lines are rays -> direction is calculated as the sum of the direction vector and plane vector of the camera (third red ray on the image, goes through the right part of the camera plane at the point about 1/3th of its length -> $dir + plane*1/3$)
- the ray direction calculated before is the vector rayDir and the x and y component of this vector are used in DDA algorithm)
- the two outer rays are the left and right border of the screen and the angle between those is the field of vision FOV. It is the ratio of the direction vector length and the plane length. If both have the same length, it will be 90°
- if the direction vector is much longer than the camera plane, the FOV will be much smaller than 90° (narrow vision, zoom in)
- if the direction vector is shorter than the camera plane, the FOV will be larger than 90° (180° is the maximum, if the direction vector is close to 0) (wider vision, zoom out)
- when the player rotates, the camera has to rotate (so both the direction vector and the plane vector have to be rotated. Then, the rays will all automaticly rotate as well)
- To rotate a vector, multiply it with the rotation matrix $[cos(a) -sin(a)]$ $[sin(a)  cos(a)]$

### Creating a new window using XQuartz
```c
int main(void)
{
    void *mlx_ptr;
    void *win_ptr;

    mlx_ptr = mlx_init();
    if (!mlx_ptr)
    {
        fprintf(stderr, "Error: Failed to initialize MiniLibX.\n");
        return EXIT_FAILURE;
    }

    win_ptr = mlx_new_window(mlx_ptr, WIN_W, WIN_H, "Red Window");
    if (!win_ptr)
    {
        fprintf(stderr, "Error: Failed to create a new window.\n");
        return EXIT_FAILURE;
    }

    // Fill the window with red color
    mlx_clear_window(mlx_ptr, win_ptr);
    mlx_string_put(mlx_ptr, win_ptr, WIN_W/2 - 50, WIN_H/2 - 10, 0xFF0000, "Hello, World!");

    mlx_loop(mlx_ptr);

    return EXIT_SUCCESS;
}
```

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
[Wolfenstein 3D game](http://users.atw.hu/wolf3d/)<br />
[Vectors | Chapter 1, Essence of linear algebra](https://www.youtube.com/watch?v=fNk_zzaMoSs)<br />
[Lec 1: Dot product | MIT 18.02 Multivariable Calculus, Fall 2007](https://www.youtube.com/watch?v=PxCxlsl_YwY&list=PLYzxBBT5iehMCyHxKZOg9EMETK3nLBbfC)

## Concepts

| Task | Prototype | Description |
|:----|:-----:|:--------:|
| **Raycasting** | `Raycasting is not the same as raytracing` | Raycasting can go very fast, because only a calculation has to be done for every vertical line of the screen. Later games such as Doom and Duke Nukem 3D also used raycasting, but much more advanced engines that allowed sloped walls, different heights, textured floors and ceilings, transparent walls, etc... `Raytracing` is a realistic rendering technique that supports reflections and shadows in true 3D scenes, and only recently computers became fast enough to do it in realtime for reasonably high resolutions and complex scenes. |
| **Sprites** | x | The sprites (enemies, objects and goodies) are 2D images. |
| **Rotate the player** | $cos$ $sin$ | In C instead of using degrees for measuring rotation, it should use radians (unit of measurement of angles). Half a revolution is therefore equal to 2π/2 = π radians. One quarter of a revolution (a right angle) equals 2π/4 = π/2 radians. Three quarters of a revolution measures 3 × π/2 = 3π/2 radians. I can define values (macros) from the unit circle, so it is easier to use them later. <img width="1236" alt="Screenshot 2024-06-05 at 19 46 57" src="https://github.com/lets-cpp/cub_3D/assets/115558344/54d38902-8b0f-4c12-81b1-75a40f0f660e"> |
| **Draw the shortest line that hits the wall first** | `distH = dist(px, py, hx, hy, ra)` | From the players rotation and `drawRays3D` calculation, find the shortest line that hits the wall first. Calculate the rays distance from the player. |
| **Define one degree in radians** | `#define DR 0.0174533` | Cast/offset rays 30 degrees left and right from the player. Moreover, define `PI 3.1415926535`. |
| **dist** | | Create a variable to hold the final distance. |
| **Cast rays until they reach the wall** | `The larger the distance, shorter will be the wall height` | For every x of the screen (i.e. for every vertical stripe of the screen), send out a ray that starts at the player location and with a direction that depends on both the player's looking direction, and the x-coordinate of the screen. Then, let this ray move forward on the 2D map, until it hits a map square that is a wall. If it hit a wall, calculate the distance of this hit point to the player, and use this distance to calculate how high this wall has to be drawn on the screen: the further away the wall, the smaller it's on screen, and the closer, the higher it appears to be. These are all 2D calculations.![raycastgrid](https://github.com/lets-cpp/cub_3D/assets/115558344/8ad3a660-aa4e-4e79-9323-77b48540eec5) |
| **Step size** | | It is not constant, it depends on the distance to the next size of the wall. This is the best approach to have a finite number of calculations (better performance) and guarantee that every wall is hit by a ray. Otherwise, there is the risk of missing it or detecting a wall in the wrong position. ![raycastmiss](https://github.com/lets-cpp/cub_3D/assets/115558344/4ce50d90-ab15-4649-b5a1-ac60f58048f3) ![raycastmiss2](https://github.com/lets-cpp/cub_3D/assets/115558344/e18a8f6f-9578-468d-9595-a084557665eb) ![raycasthit](https://github.com/lets-cpp/cub_3D/assets/115558344/d476f3cb-8df1-4b75-b4f5-4575fac900d9) |
| **Fix fish eye** | $cos$ | |
||| They are geometrical and computational at the same time, meaning, they can be draw but also computed by numbers. |
| **Vector and matrix** | $\[ \vec{p} \]$ | Linear Algebra. Scalar: quantity with magnitude (to know more, search about tensors). Vector quantities also have a magnitude (distance + direction = displacement). Vectors remain invariant to the coordinate system (e.g. $-2x -3y$ is not the same as $2x + 3y$ in the coordinate system. However, the vector is the same). Therefore, different representation from two basis can describe the same vector. In computer science, I can assume vectors as an ordered list of numbers. |
| **Adding two vectors** | $\[ \vec{1, 2} \] + \[ \vec{3, -1} \] = \[ \vec{4, 1} \]$ | <img width="633" alt="Screenshot 2024-07-04 at 00 23 01" src="https://github.com/lets-cpp/cub_3D/assets/115558344/1abc9a5a-9209-4a9c-aaa2-0a5efa7f4200"> |
| **Decompose a vector** | $\vec{v} = \vec{i} + \vec{j} + \vec{k}$ | Decompose a vector according to the unit axis. \vec{i} points along the x axis, \vec{j} points along the y axis and \vec{k} to the z axis. **Answer 2 is the correct one.** So, the general formula to find the vector A is $\[ \vec{A} \] = \sqrt{i^2 + j^2 + k^2}$  <img width="896" alt="Screenshot 2024-07-04 at 00 49 07" src="https://github.com/lets-cpp/cub_3D/assets/115558344/13670945-2435-42d9-9482-2ab6f0381fb9"> |
| **Scaling a vector** | $2\[ \vec{p} \]$ | Multiply each one of the vector components by its scalar, a.k.a. multiply the ordered list of numbers by 2 in the case of $2\[ \vec{p} \]$ |
| **mapX and mapY** | `ray()->mapX = (int)data->posX;` | mapX and mapY represent the current square of the map the ray is in. The ray position itself is a floating point number and contains both info about in which square of the map we are, and where in that square we are, but mapX and mapY are only the coordinates of that square. |
| **sideDistX and sideDistY** | `ray()->sideDistX` | Distance the ray has to travel from its start position to the first x-side and the first y-side. Later in the code they will be incremented while steps are taken. |
| **deltaDistX and deltaDistY** | `ray()->deltaDistX;` | Distance the ray has to travel to go from 1 x-side to the next x-side, or from 1 y-side to the next y-side. When deriving deltaDistX geometrically you get, with Pythagoras, the formulas below. For the blue triangle (deltaDistX), one side has length 1 (as it is exactly one cell) and the other has length raydirY / raydirX because it is exaclty the amount of units the ray goes in the y-direction when taking 1 step in the X-direction. For the green triangle (deltaDistY), the formula is similar. `deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))` `deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))` ![raycastdelta](https://github.com/user-attachments/assets/8bdbb37b-beea-4998-82cb-00b38cd74fd0) |
| **DDA algorithm** | [DDA](https://www.geeksforgeeks.org/dda-line-generation-algorithm-computer-graphics/) | Digital differential analyzer. After the DDA is done, we have to calculate the distance of the ray to the wall, so that we can calculate how high the wall has to be drawn after this. We don't use the Euclidean distance to the point representing player, but instead the distance to the camera plane (or, the distance of the point projected on the camera direction to the player), to avoid the **fisheye effect**. With P the player, and the black line the camera plane: To the left of the player, a few red rays are shown from hitpoints on the wall to the player, representing Euclidean distance. On the right side of the player, a few green rays are shown going from hitpoints on the wall directly to the camera plane instead of to the player. So the lengths of those green lines are examples of the perpendicular distance we'll use instead of direct Euclidean distance. ![raycastdist](https://github.com/user-attachments/assets/3133559f-6683-4ac2-9e21-b7253b08e906) |
| **[Adding submodules](https://gist.github.com/gitaarik/8735255)** | `mlx` `libft` | Adding a new submodule -> `git submodule init` `git submodule add https://github.com/42Paris/minilibx-linux.git`. Updating submodules in a new machine -> `git submodule update` `git submodule update --init` `git submodule update --recursive`. Close main repository and update submodules -> `git clone --recurse-submodules`. Pull main repository and update submodules -> `git pull --recurse-submodules`. Clone a specific submodule -> `git submodule update --init --recursive get_next_line` |
| **Create cool Makefile messages** | [patorjk.com/](https://patorjk.com/software/taag/#p=display&c=echo&f=Star%20Wars&t=%20%2B%20utils) | |
| **Install packages in your VM** | `sudo apt-get install libx11-dev libxext-dev libxft-dev libxrandr-dev``sudo apt-get install libbsd-dev` | Update your virtual machine, so you can compile mlx submodule. |
| **Virtual machine** | `DISPLAY` `ssh -X ubuntu@ip` | In this project, it is used a virtual machine OS Ubuntu in a host MAC computer. Therefore, to open a window in your host machine via running the program in the VM, a ssh connection between both machines need to be set. First, be sure that `Xquartz` is installed in the host machine. Reboot the computer. Then, run `Xquartz` and check for `echo $DISPLAY` value. The output must be something like `echo $DISPLAY /private/tmp/com.apple.launchd.e4xk3lThXR/org.xquartz:0`. When you use `ssh -X` (or `ssh -Y` for trusted X11 forwarding) to connect to your virtual machine, the `DISPLAY` environment variable is automatically set in your virtual machine session. This setup allows X11 applications run on the virtual machine to be displayed on your host machine (macOS) using XQuartz without manually setting the `DISPLAY` variable on the virtual machine. **By following these steps, you can run X11 applications from a remote server on your local machine without needing to use the terminal provided by XQuartz directly.** |

