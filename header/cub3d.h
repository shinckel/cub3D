/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:19:57 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/02 20:52:00 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "config.h"
# include "../minilibx-linux/mlx.h"
# include "../get_next_line/header/get_next_line.h"
# include "../libft/header/libft.h"

# define WIN_W		800
# define WIN_H		600
# define TILE_SIZE	64
# define MAP_SCALE	4
# define KEY_A      97
# define KEY_S	    115
# define KEY_D      100
# define KEY_W	    119
# define KEY_LEFT	65361
# define KEY_RIGHT  65363
# define KEY_ESC	65307

// checking map validation
int		check_single_player(char **mcopy, t_game *game);
int		check_map_char(char **mcopy, t_game *game);
int		check_enclosed_map(char **map, t_game *game);
void	counting_map(t_game *game, char **map);
char	*trim_end_whitespace(char *str);
// free
void	free_matrix(char **matrix);
void	finish_game(char *msg, t_game *game);
void	cleanup(t_game *game);
void	free_list(t_list *lst);
void	free_textures(t_game *game);
int		exit_game(t_game *game);
void	free_texture_paths(t_game *game);
void	destroy_texture_images(t_game *game);
// map copy and flood fill
char	**map_copy(char **map, t_game *game);
void	flood_fill(char **map_copy, int x, int y, t_game *game);
char	**convert_map_to_array(t_list *map_lines);
void	copy_map_to_mockup(char **map, char **mockup);
char	**normalize_map(char **map, t_game *game);
// map size
int		find_max_width(char **map);
int		find_height(char **map, t_game *game);
void	check_empty_line_validation(char **map, t_game *game);
// validate textures and colors/determine texture && player
char	**read_map(char *filename, t_game *game);
void	extract_textures_and_colors(int fd, t_game *game);
void	extract_texture(char *line, t_game *game, int *texture_found, int *err);
int		parse_color(char *color_str, int *err);
void	load_all_textures(t_game *game);
void	load_texture(t_game *game, t_image *texture, char *path);
void	calculate_texture_coordinates(t_ray *ray, t_game *game);
void	determine_texture(t_game *game, t_ray *ray);
void	init_player_position(t_game *game);
void	get_texture(t_game *game, int i, int j);
// file management
int		open_file(char *filename);
// raycasting
void	perform_dda(t_game *game, t_ray *ray);
void	draw_vertical_stripe(t_game *game, t_ray *ray, int x);
void	calculate_distance(t_ray *ray, t_game *game);
void	initialize_step_and_side_dist(t_game *game, t_ray *ray);
void	initialize_ray(t_game *game, t_ray *ray, int x);
void	cast_single_ray(t_game *game, int x);
void	cast_rays(t_game *game);
// move
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
// rotate
void	rotate_right(t_game *game);
void	rotate_left(t_game *game);
// draw
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
int		get_texture_pixel(t_image *texture, int x, int y);
void	draw_ceiling(t_game *game, t_ray *ray, int x);
void	draw_floor(t_game *game, t_ray *ray, int x);
void	draw_tile(t_game *game, int x, int y, unsigned int color);
void	draw_texture(t_game *game, t_image *texture, int x, int y);
void	draw_player(t_image *img, t_game *game, int x, int y);
void	draw_player_on_map(t_game *game);
// handle keys and file utils
int		open_file(char *filename);
int		my_isspace(char c);
char	*trim_end_whitespace(char *str);
void	update_game(t_game *game);
int		handle_key_press(int keycode, t_game *game);
int		handle_key_release(int keycode, t_game *game);
int		process_input(t_game *game);

#endif
