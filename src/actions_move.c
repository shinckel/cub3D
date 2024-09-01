/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:15:46 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/01 21:49:37 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x + game->p.dir_x
		* game->p.move_speed;
	new_y = game->p.pos_y + game->p.dir_y
		* game->p.move_speed;
	if (game->config.map[(int)new_y][(int)new_x] == '0'
		|| ft_strchr("NSWE", game->config.map[(int)new_y][(int)new_x]))
	{
		game->p.pos_x = new_x;
		game->p.pos_y = new_y;
	}
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x - game->p.dir_x
		* game->p.move_speed;
	new_y = game->p.pos_y - game->p.dir_y
		* game->p.move_speed;
	if (game->config.map[(int)new_y][(int)new_x] == '0'
		|| ft_strchr("NSWE", game->config.map[(int)new_y][(int)new_x]))
	{
		game->p.pos_x = new_x;
		game->p.pos_y = new_y;
	}
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x - game->p.plane_x
		* game->p.move_speed;
	new_y = game->p.pos_y - game->p.plane_y
		* game->p.move_speed;
	if (game->config.map[(int)new_y][(int)new_x] == '0'
		|| ft_strchr("NSWE", game->config.map[(int)new_y][(int)new_x]))
	{
		game->p.pos_x = new_x;
		game->p.pos_y = new_y;
	}
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x + game->p.plane_x
		* game->p.move_speed;
	new_y = game->p.pos_y + game->p.plane_y
		* game->p.move_speed;
	if (game->config.map[(int)new_y][(int)new_x] == '0'
		|| ft_strchr("NSWE", game->config.map[(int)new_y][(int)new_x]))
	{
		game->p.pos_x = new_x;
		game->p.pos_y = new_y;
	}
}
