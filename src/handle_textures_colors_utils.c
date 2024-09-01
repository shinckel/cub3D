/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures_colors_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:25:28 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/01 19:27:02 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

// char	*skip_spaces(char *line)
// {
// 	while (*line == ' ' || *line == '\t')
// 		line++;
// 	return (line);
// }

// void	extract_texture(char *line, t_game *game, int *textures_found)
// {
// 	line = skip_spaces(line);

// 	// Ignorar espaços entre o identificador e o caminho
// 	if (ft_strncmp(line, "NO", 2) == 0 && !game->walls.no_path)
// 	{
// 		line = skip_spaces(line + 2); // Pular "NO" e espaços após
// 		game->walls.no_path = ft_strdup(line);
// 		(*textures_found)++;
// 	}
// 	else if (ft_strncmp(line, "SO", 2) == 0 && !game->walls.so_path)
// 	{
// 		line = skip_spaces(line + 2); // Pular "SO" e espaços após
// 		game->walls.so_path = ft_strdup(line);
// 		(*textures_found)++;
// 	}
// 	else if (ft_strncmp(line, "EA", 2) == 0 && !game->walls.ea_path)
// 	{
// 		line = skip_spaces(line + 2); // Pular "EA" e espaços após
// 		game->walls.ea_path = ft_strdup(line);
// 		(*textures_found)++;
// 	}
// 	else if (ft_strncmp(line, "WE", 2) == 0 && !game->walls.we_path)
// 	{
// 		line = skip_spaces(line + 2); // Pular "WE" e espaços após
// 		game->walls.we_path = ft_strdup(line);
// 		(*textures_found)++;
// 	}
// 	else if (ft_strncmp(line, "F", 1) == 0 && !game->colors.floor)
// 	{
// 		line = skip_spaces(line + 1); // Pular "F" e espaços após
// 		game->colors.floor = parse_color(line, game);
// 		(*textures_found)++;
// 	}
// 	else if (ft_strncmp(line, "C", 1) == 0 && !game->colors.ceiling)
// 	{
// 		line = skip_spaces(line + 1); // Pular "C" e espaços após
// 		game->colors.ceiling = parse_color(line, game);
// 		(*textures_found)++;
// 	}
// 	else if (!ft_strncmp(line, "\n", 1) == 0)
// 	{
// 		printf("Error\nTexture or color information is wrong in the map file!\n");
// 		cleanup(game);
// 		exit(EXIT_FAILURE);
// 	}
// }
