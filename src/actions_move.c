/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:15:46 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/03 17:04:28 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

/*
The reason for checking collisions separately for the x and y axes is to handle
cases where the player might be moving diagonally and could get stuck on corners.
By checking each axis independently, you can ensure smoother movement and avoid 
getting stuck.
*/
// TRIAL
void move_forward(t_game *game)
{
    double new_x = game->p.pos_x + game->p.dir_x * game->p.move_speed;
    double new_y = game->p.pos_y + game->p.dir_y * game->p.move_speed;

    if (!is_collision(game, new_x, game->p.pos_y))
        game->p.pos_x = new_x;
    if (!is_collision(game, game->p.pos_x, new_y))
        game->p.pos_y = new_y;
}

void move_backward(t_game *game)
{
    double new_x = game->p.pos_x - game->p.dir_x * game->p.move_speed;
    double new_y = game->p.pos_y - game->p.dir_y * game->p.move_speed;

    if (!is_collision(game, new_x, game->p.pos_y))
        game->p.pos_x = new_x;
    if (!is_collision(game, game->p.pos_x, new_y))
        game->p.pos_y = new_y;
}

void move_left(t_game *game)
{
    double new_x = game->p.pos_x - game->p.plane_x * game->p.move_speed;
    double new_y = game->p.pos_y - game->p.plane_y * game->p.move_speed;

    if (!is_collision(game, new_x, game->p.pos_y))
        game->p.pos_x = new_x;
    if (!is_collision(game, game->p.pos_x, new_y))
        game->p.pos_y = new_y;
}

void move_right(t_game *game)
{
    double new_x = game->p.pos_x + game->p.plane_x * game->p.move_speed;
    double new_y = game->p.pos_y + game->p.plane_y * game->p.move_speed;

    if (!is_collision(game, new_x, game->p.pos_y))
        game->p.pos_x = new_x;
    if (!is_collision(game, game->p.pos_x, new_y))
        game->p.pos_y = new_y;
}

// SECOND
// void	move_forward(t_game *game)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = game->p.pos_x + game->p.dir_x * game->p.move_speed;
// 	new_y = game->p.pos_y + game->p.dir_y * game->p.move_speed;
// 	if (!is_collision(game, new_x, new_y))
// 	{
// 		game->p.pos_x = new_x;
// 		game->p.pos_y = new_y;
// 	}
	
// }

// void	move_backward(t_game *game)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = game->p.pos_x - game->p.dir_x * game->p.move_speed;
// 	new_y = game->p.pos_y - game->p.dir_y * game->p.move_speed;
// 	if (!is_collision(game, new_x, new_y))
// 	{
// 		game->p.pos_x = new_x;
// 		game->p.pos_y = new_y;
// 	}
// }

// void	move_left(t_game *game)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = game->p.pos_x - game->p.plane_x * game->p.move_speed;
// 	new_y = game->p.pos_y - game->p.plane_y * game->p.move_speed;
// 	if (!is_collision(game, new_x, new_y))
// 	{
// 		game->p.pos_x = new_x;
// 		game->p.pos_y = new_y;
// 	}
// }

// void	move_right(t_game *game)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = game->p.pos_x + game->p.plane_x * game->p.move_speed;
// 	new_y = game->p.pos_y + game->p.plane_y * game->p.move_speed;
// 	if (!is_collision(game, new_x, new_y))
// 	{
// 		game->p.pos_x = new_x;
// 		game->p.pos_y = new_y;
// 	}
// }

// void	move_forward(t_game *game)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = game->p.pos_x + game->p.dir_x
// 		* game->p.move_speed;
// 	new_y = game->p.pos_y + game->p.dir_y
// 		* game->p.move_speed;
// 	if (game->config.map[(int)new_y][(int)new_x] == '0'
// 		|| ft_strchr("NSWE", game->config.map[(int)new_y][(int)new_x]))
// 	{
// 		game->p.pos_x = new_x;
// 		game->p.pos_y = new_y;
// 	}
// }

// void	move_backward(t_game *game)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = game->p.pos_x - game->p.dir_x
// 		* game->p.move_speed;
// 	new_y = game->p.pos_y - game->p.dir_y
// 		* game->p.move_speed;
// 	if (game->config.map[(int)new_y][(int)new_x] == '0'
// 		|| ft_strchr("NSWE", game->config.map[(int)new_y][(int)new_x]))
// 	{
// 		game->p.pos_x = new_x;
// 		game->p.pos_y = new_y;
// 	}
// }

// void	move_left(t_game *game)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = game->p.pos_x - game->p.plane_x
// 		* game->p.move_speed;
// 	new_y = game->p.pos_y - game->p.plane_y
// 		* game->p.move_speed;
// 	if (game->config.map[(int)new_y][(int)new_x] == '0'
// 		|| ft_strchr("NSWE", game->config.map[(int)new_y][(int)new_x]))
// 	{
// 		game->p.pos_x = new_x;
// 		game->p.pos_y = new_y;
// 	}
// }

// void	move_right(t_game *game)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = game->p.pos_x + game->p.plane_x
// 		* game->p.move_speed;
// 	new_y = game->p.pos_y + game->p.plane_y
// 		* game->p.move_speed;
// 	if (game->config.map[(int)new_y][(int)new_x] == '0'
// 		|| ft_strchr("NSWE", game->config.map[(int)new_y][(int)new_x]))
// 	{
// 		game->p.pos_x = new_x;
// 		game->p.pos_y = new_y;
// 	}
// }