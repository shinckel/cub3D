/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:24:22 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/02 18:00:17 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int handle_key_press(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->keys[0] = 1;
    else if (keycode == KEY_S)
        game->keys[1] = 1;
    else if (keycode == KEY_A)
        game->keys[2] = 1;
    else if (keycode == KEY_D)
        game->keys[3] = 1;
    else if (keycode == KEY_LEFT)
        game->keys[4] = 1;
    else if (keycode == KEY_RIGHT)
        game->keys[5] = 1;
    else if (keycode == KEY_ESC)
        exit_game(game);
    return (0);
}

int handle_key_release(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->keys[0] = 0;
    else if (keycode == KEY_S)
        game->keys[1] = 0;
    else if (keycode == KEY_A)
        game->keys[2] = 0;
    else if (keycode == KEY_D)
        game->keys[3] = 0;
    else if (keycode == KEY_LEFT)
        game->keys[4] = 0;
    else if (keycode == KEY_RIGHT)
        game->keys[5] = 0;
    return (0);
}

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
