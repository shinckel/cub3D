/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures_colors_util3.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:31:55 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/01 21:36:50 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	calculate_texture_coordinates(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->wall_x = game->p.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = game->p.pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)(ray->texture->w));
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = ray->texture->w - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = ray->texture->w - ray->tex_x - 1;
	ray->step = 1.0 * ray->texture->h / ray->line_height;
	ray->tex_pos = (ray->draw_start - WIN_H
			/ 2 + ray->line_height / 2) * ray->step;
}

void	determine_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 1)
	{
		if (ray->dir_y > 0)
			ray->texture = &game->walls.so_textu;
		else
			ray->texture = &game->walls.no_textu;
	}
	else
	{
		if (ray->dir_x > 0)
			ray->texture = &game->walls.ea_textu;
		else
			ray->texture = &game->walls.we_textu;
	}
}

void	init_player_position(t_game *game)
{
	int		y;
	int		x;
	char	**map;

	y = 0;
	map = game->config.map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NSWE", map[y][x]))
			{
				game->p.pos_x = x + 0.5;
				game->p.pos_y = y + 0.5;
				game->p.dir_x = (map[y][x] == 'E') - (map[y][x] == 'W');
				game->p.dir_y = (map[y][x] == 'S') - (map[y][x] == 'N');
				game->p.plane_x = -game->p.dir_y * tan(30 * M_PI / 180);
				game->p.plane_y = game->p.dir_x * tan(30 * M_PI / 180);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	get_texture(t_game *game, int i, int j)
{
	t_image	*player_texture;

	player_texture = NULL;
	if (game->config.map[i][j] == '0')
		player_texture = &game->walls.so_textu;
	if (game->config.map[i][j] == 'N')
		player_texture = &game->walls.no_textu;
	else if (game->config.map[i][j] == 'S')
		player_texture = &game->walls.so_textu;
	else if (game->config.map[i][j] == 'E')
		player_texture = &game->walls.ea_textu;
	else if (game->config.map[i][j] == 'W')
		player_texture = &game->walls.we_textu;
	if (player_texture)
		draw_texture(game, player_texture, j
			* game->config.mt_size, i * game->config.mt_size);
	draw_player_on_map(game);
}
