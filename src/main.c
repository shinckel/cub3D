/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:14:12 by dde-sott          #+#    #+#             */
/*   Updated: 2024/09/01 21:48:04 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

// void print_map(char **map)
// {
//     int i = 0;
//     while (map[i])
//     {
//         printf("%s\n", map[i]);
//         i++;
//     }
// }

void	update_game(t_game *game)
{
	ft_memset(game->img.addr, 0, WIN_H * game->img.line_len);
	cast_rays(game);
	mlx_put_image_to_window(game->win.mlx_ptr, game->win.win_ptr,
		game->img.img_ptr, 0, 0);
}

void	init_game(t_game *game)
{
	game->p.move_speed = 0.4;
	game->p.rot_speed = 0.4;
	game->config.width = 0;
	game->config.height = 0;
	game->win.mlx_ptr = mlx_init();
	load_all_textures(game);
	game->config.mt_size = ((TILE_SIZE + MAP_SCALE - 1) / MAP_SCALE);
	game->win.win_ptr = mlx_new_window(game->win.mlx_ptr,
			WIN_W, WIN_H, "Cub3D");
	game->img.img_ptr = mlx_new_image(game->win.mlx_ptr,
			WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.img_ptr,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
}

int	check_name(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len < 5 || name[len - 4] != '.' || name[len - 3] != 'c'
		|| name[len - 2] != 'u' || name[len - 1] != 'b')
	{
		printf("Error\nMap name needs to end with \".cub\"\n");
		return (1);
	}
	return (0);
}

/*
 * read_map: validate textures, colors, check if empty, create list
 * counting_map: map size and direction
 * normalize map
 * check_map_char: validate map
 * check_enclosed_map: flood-fill
*/
int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
	{
		printf("Error\nThe filename is missing!\n");
		return (EXIT_FAILURE);
	}
	if (check_name(argv[1]))
		return (1);
	game.config.map = read_map(argv[1], &game);
	counting_map(&game, game.config.map);
	game.config.map_norm = normalize_map(game.config.map, &game);
	check_map_char(game.config.map_norm, &game);
	check_enclosed_map(game.config.map_norm, &game);
	check_single_player(game.config.map_norm, &game);
	init_game(&game);
	init_player_position(&game);
	cast_rays(&game);
	mlx_put_image_to_window(game.win.mlx_ptr, game.win.win_ptr,
		game.img.img_ptr, 0, 0);
	mlx_hook(game.win.win_ptr, 2, 1L << 0, handle_key_press, &game);
	mlx_hook(game.win.win_ptr, 17, 1L << 17, exit_game, &game);
	mlx_loop(game.win.mlx_ptr);
	cleanup(&game);
	return (EXIT_SUCCESS);
}
