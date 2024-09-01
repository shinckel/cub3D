/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:24:22 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/01 21:49:52 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->p.dir_x;
	old_plane_x = game->p.plane_x;
	game->p.dir_x = game->p.dir_x * cos(game->p.rot_speed)
		- game->p.dir_y * sin(game->p.rot_speed);
	game->p.dir_y = old_dir_x * sin(game->p.rot_speed)
		+ game->p.dir_y * cos(game->p.rot_speed);
	game->p.plane_x = game->p.plane_x * cos(game->p.rot_speed)
		- game->p.plane_y * sin(game->p.rot_speed);
	game->p.plane_y = old_plane_x * sin(game->p.rot_speed)
		+ game->p.plane_y * cos(game->p.rot_speed);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->p.dir_x;
	old_plane_x = game->p.plane_x;
	game->p.dir_x = game->p.dir_x * cos(-game->p.rot_speed)
		- game->p.dir_y * sin(-game->p.rot_speed);
	game->p.dir_y = old_dir_x * sin(-game->p.rot_speed)
		+ game->p.dir_y * cos(-game->p.rot_speed);
	game->p.plane_x = game->p.plane_x * cos(-game->p.rot_speed)
		- game->p.plane_y * sin(-game->p.rot_speed);
	game->p.plane_y = old_plane_x * sin(-game->p.rot_speed)
		+ game->p.plane_y * cos(-game->p.rot_speed);
}
