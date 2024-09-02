/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures_colors_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:25:28 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/02 15:49:57 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

// TODO: check for leaks (free line)
void	extract_color(char *line, t_game *game, int *textures_found, int *err)
{
	line = skip_spaces(line);
	if (ft_strncmp(line, "F", 1) == 0 && !game->colors.floor)
	{
		game->colors.floor = parse_color(skip_spaces(line + 1), err);
		(*textures_found)++;
	}
	else if (ft_strncmp(line, "C", 1) == 0 && !game->colors.ceiling)
	{
		game->colors.ceiling = parse_color(skip_spaces(line + 1), err);
		(*textures_found)++;
	}
	else if (*line != '\n')
		*err = 1;
}

void	extract_texture(char *line, t_game *game, int *textures_found, int *err)
{
	char	*line_cpy;

	line_cpy = skip_spaces(line);
	if (ft_strncmp(line_cpy, "NO", 2) == 0 && !game->walls.no_path)
	{
		game->walls.no_path = ft_strdup(skip_spaces(line_cpy + 2));
		(*textures_found)++;
	}
	else if (ft_strncmp(line_cpy, "SO", 2) == 0 && !game->walls.so_path)
	{
		game->walls.so_path = ft_strdup(skip_spaces(line_cpy + 2));
		(*textures_found)++;
	}
	else if (ft_strncmp(line_cpy, "EA", 2) == 0 && !game->walls.ea_path)
	{
		game->walls.ea_path = ft_strdup(skip_spaces(line_cpy + 2));
		(*textures_found)++;
	}
	else if (ft_strncmp(line_cpy, "WE", 2) == 0 && !game->walls.we_path)
	{
		game->walls.we_path = ft_strdup(skip_spaces(line_cpy + 2));
		(*textures_found)++;
	}
	else
		extract_color(line_cpy, game, textures_found, err);
}
