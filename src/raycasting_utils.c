/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:20:49 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/01 21:21:33 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	initialize_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_W - 1;
	ray->dir_x = game->p.dir_x + game->p.plane_x * ray->camera_x;
	ray->dir_y = game->p.dir_y + game->p.plane_y * ray->camera_x;
	ray->map_x = (int)game->p.pos_x;
	ray->map_y = (int)game->p.pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	initialize_step_and_side_dist(game, ray);
}

void	cast_single_ray(t_game *game, int x)
{
	t_ray	ray;

	initialize_ray(game, &ray, x);
	perform_dda(game, &ray);
	calculate_distance(&ray, game);
	draw_vertical_stripe(game, &ray, x);
}

void	cast_rays(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		cast_single_ray(game, x);
		x++;
	}
}
