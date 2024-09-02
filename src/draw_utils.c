/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:29:47 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/02 20:07:32 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	draw_tile(t_game *game, int x, int y, unsigned int color)
{
	int	k;
	int	l;

	k = 0;
	while (k < game->config.mt_size)
	{
		l = 0;
		while (l < game->config.mt_size)
		{
			my_mlx_pixel_put(&game->img, x + l, y + k, color);
			l++;
		}
		k++;
	}
}

void	draw_texture(t_game *game, t_image *texture, int x, int y)
{
	unsigned int	tex_color;
	int				k;
	int				l;

	if (texture->img_ptr)
	{
		k = 0;
		while (k < game->config.mt_size)
		{
			l = 0;
			while (l < game->config.mt_size)
			{
				tex_color = *(unsigned int *)(texture->addr
						+ (((k * texture->h) / game->config.mt_size)
							* texture->line_len + ((l * texture->w)
								/ game->config.mt_size) *(texture->bpp / 8)));
				my_mlx_pixel_put(&game->img, x + l, y + k, tex_color);
				l++;
			}
			k++;
		}
	}
}

void	draw_player(t_image *img, t_game *game, int x, int y)
{
	int	player_size;
	int	center_x;
	int	center_y;
	int	i;
	int	j;

	player_size = 4;
	center_x = x + game->config.mt_size / 2;
	center_y = y + game->config.mt_size / 2;
	i = -player_size;
	while (i <= player_size)
	{
		j = -player_size;
		while (j <= player_size)
		{
			if (center_x + i >= 0 && center_x + i
				< WIN_W && center_y + j >= 0 && center_y + j < WIN_H)
			{
				my_mlx_pixel_put(img, center_x + i, center_y + j, 0x00FF0000);
			}
			j++;
		}
		i++;
	}
}

void	draw_player_on_map(t_game *game)
{
	int	player_x;
	int	player_y;

	player_x = game->p.pos_x * game->config.mt_size;
	player_y = game->p.pos_y * game->config.mt_size;
	draw_player(&game->img, game, player_x, player_y);
}
