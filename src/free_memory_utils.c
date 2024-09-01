/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:15:56 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/01 21:28:45 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	free_textures(t_game *game)
{
	if (game == NULL)
		return ;
	free_texture_paths(game);
	destroy_texture_images(game);
}

int	exit_game(t_game *game)
{
	cleanup(game);
	exit(EXIT_SUCCESS);
}

void	free_texture_paths(t_game *game)
{
	if (game->walls.no_path)
	{
		free(game->walls.no_path);
		game->walls.no_path = NULL;
	}
	if (game->walls.so_path)
	{
		free(game->walls.so_path);
		game->walls.so_path = NULL;
	}
	if (game->walls.ea_path)
	{
		free(game->walls.ea_path);
		game->walls.ea_path = NULL;
	}
	if (game->walls.we_path)
	{
		free(game->walls.we_path);
		game->walls.we_path = NULL;
	}
}

void	destroy_texture_images(t_game *game)
{
	if (game->win.mlx_ptr == NULL)
		return ;
	if (game->walls.no_textu.img_ptr)
	{
		mlx_destroy_image(game->win.mlx_ptr, game->walls.no_textu.img_ptr);
		game->walls.no_textu.img_ptr = NULL;
	}
	if (game->walls.so_textu.img_ptr)
	{
		mlx_destroy_image(game->win.mlx_ptr, game->walls.so_textu.img_ptr);
		game->walls.so_textu.img_ptr = NULL;
	}
	if (game->walls.ea_textu.img_ptr)
	{
		mlx_destroy_image(game->win.mlx_ptr, game->walls.ea_textu.img_ptr);
		game->walls.ea_textu.img_ptr = NULL;
	}
	if (game->walls.we_textu.img_ptr)
	{
		mlx_destroy_image(game->win.mlx_ptr, game->walls.we_textu.img_ptr);
		game->walls.we_textu.img_ptr = NULL;
	}
}
