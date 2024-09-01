/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:19:57 by shinckel          #+#    #+#             */
/*   Updated: 2024/08/29 15:53:22 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
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

#endif
// # define MINIMAP_W	100
// # define MINIMAP_H	100
// # define MT_SZE ((TILE_SIZE + MAP_SCALE - 1) / MAP_SCALE)
// MAP_TILE_SIZE = (int)round((double)TILE_SIZE / (double)MAP_SCALE)
// This must be true ALWAYS!
// Because of the norm ;( we can't have this
//# define MAP_TILE_SIZE        8
// # define MAGNITUDE_ANGLE	3
// # define MAGNITUDE		10
// # define SPRITE_AMMOUNT 	3
// # ifndef LINUX
// #  define LINUX
// #  define KEY_Q	12
// #  define KEY_E	14
// #  define KEY_UP	126
// #  define KEY_DOWN	125
// #  define BUFFER_SIZE 1024
// # else
// #  define KEY_A 97
// #  define KEY_S 115
// #  define KEY_D 100
// #  define KEY_Q 113
// #  define KEY_W 119
// #  define KEY_E 101
// #  define KEY_UP	65362
// #  define KEY_DOWN	65364
// #  define KEY_LEFT	65361
// #  define KEY_RIGHT	65363
// #  define KEY_ESC	65307
// # endif
// # include "limits.h"
// # include "ft_printf.h"