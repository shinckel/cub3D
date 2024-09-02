/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures_colors_utils2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:17:34 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/02 16:03:39 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void load_texture(t_game *game, t_image *texture, char *path)
{
    if (!path)
			finish_game("Texture path is NULL!", game);
    if (!game->win.mlx_ptr)
			finish_game("MLX pointer is NULL!", game);
    texture->img_ptr = mlx_xpm_file_to_image(game->win.mlx_ptr, path, &texture->w, &texture->h);
		if (!texture->img_ptr)
		{
			printf("Error\nTexture not found! %s\n", path);
			cleanup(game);
			exit (EXIT_FAILURE);
		}
		texture->addr = mlx_get_data_addr(texture->img_ptr,
				&texture->bpp, &texture->line_len, &texture->endian);
}

void load_all_textures(t_game *game)
{
    load_texture(game, &game->walls.no_textu, game->walls.no_path);
    load_texture(game, &game->walls.so_textu, game->walls.so_path);
    load_texture(game, &game->walls.ea_textu, game->walls.ea_path);
    load_texture(game, &game->walls.we_textu, game->walls.we_path);
}
