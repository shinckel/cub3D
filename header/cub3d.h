/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:19:57 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/01 19:27:59 by shinckel         ###   ########.fr       */
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
# include "cub_math.h"
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
void	finish_game(char* msg, t_game *game);
void	cleanup(t_game *game);
void	free_list(t_list *lst);
// map copy and flood fill
char	**map_copy(char **map, t_game *game);
void	flood_fill(char **map_copy, int x, int y, t_game *game);
char	**convert_map_to_array(t_list *map_lines);
// map size

// validate textures and colors
char	**read_map(char *filename, t_game *game);
void	extract_textures_and_colors(int fd, t_game *game);
void	extract_texture(char *line, t_game *game, int *textures_found);
int		parse_color(char *color_str, t_game *game);
// file management
int		open_file(char *filename);

#endif
