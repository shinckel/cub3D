/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:20:00 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/02 16:57:42 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "cub3d.h"

struct	s_pov;

/* Window struct, it has a pointer to the window ptr and to the loop */
typedef struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		height;
	int		width;
}		t_window;

/* Image struct, it has a pointer to it's window and a pointer to the image */
typedef struct s_image
{
	t_window	*win;
	void		*img_ptr;
	char		*addr;
	int			h;
	int			w;
	int			bpp;
	int			endian;
	int			line_len;
}		t_image;

typedef struct s_walls
{
	char			*no_path;
	t_image			no_textu;
	char			*so_path;
	t_image			so_textu;
	char			*ea_path;
	t_image			ea_textu;
	char			*we_path;
	t_image			we_textu;
}				t_walls;

/* ****************************************** */
/* floor	: floor color                     */
/* ceiling	: ceiling color                   */
/* width	: map width (# of chars per line) */
/* height	: map height (# of lines)         */
/* map		: list whith every map line       */
/* ??_path	: the sprite path (image) NWSE    */
/* ****************************************** */
typedef struct s_config
{
	struct s_pov	*pov;
	struct s_image	*img_map;
	struct s_image	*img_game;
	int				floor;
	int				ceiling;
	int				width;
	int				height;
	char			**map;
	int				mt_size;
	char			**map_norm;
	t_walls			walls;
}		t_config;

typedef struct s_colors
{
	int	floor;
	int	ceiling;
}	t_colors;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	wall_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	tex_pos;
	double	step;
	t_image	*texture;
}	t_ray;

typedef struct s_info
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}				t_info;

typedef struct s_game
{
	t_window	win;
	t_image		img;
	t_walls		walls;
	t_colors	colors;
	t_info		p;
	char		**map;
	t_config	config;
	int				keys[6];
}				t_game;

#endif
