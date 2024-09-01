/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures_colors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:43:05 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/01 19:27:11 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	extract_textures_and_colors(int fd, t_game *game)
{
	char	*line;
	int		textures_found;

	textures_found = 0;
	line = get_next_line(fd);
	while (line && textures_found < 6)
	{
		trim_end_whitespace(line);
		extract_texture(line, game, &textures_found);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

// void	extract_texture(char *line, t_game *game, int *textures_found)
// {
// 	if (ft_strncmp(line, "NO ", 3) == 0 && !game->walls.no_path)
// 		game->walls.no_path = ft_strdup(line + 3), (*textures_found)++;
// 	else if (ft_strncmp(line, "SO ", 3) == 0 && !game->walls.so_path)
// 		game->walls.so_path = ft_strdup(line + 3), (*textures_found)++;
// 	else if (ft_strncmp(line, "EA ", 3) == 0 && !game->walls.ea_path)
// 		game->walls.ea_path = ft_strdup(line + 3), (*textures_found)++;
// 	else if (ft_strncmp(line, "WE ", 3) == 0 && !game->walls.we_path)
// 		game->walls.we_path = ft_strdup(line + 3), (*textures_found)++;
// 	else if (ft_strncmp(line, "F ", 2) == 0 && !game->colors.floor)
// 		game->colors.floor = parse_color(line + 2, game), (*textures_found)++;
// 	else if (ft_strncmp(line, "C ", 2) == 0 && !game->colors.ceiling)
// 		game->colors.ceiling = parse_color(line + 2, game), (*textures_found)++;
// 	else if (!ft_strncmp(line, "\n", 1) == 0)
// 		finish_game("Texture or color information is wrong in the map file!", game);
// }

char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

void	extract_texture(char *line, t_game *game, int *textures_found)
{
	line = skip_spaces(line);

	// Ignorar espaços entre o identificador e o caminho
	if (ft_strncmp(line, "NO", 2) == 0 && !game->walls.no_path)
	{
		line = skip_spaces(line + 2); // Pular "NO" e espaços após
		game->walls.no_path = ft_strdup(line);
		(*textures_found)++;
	}
	else if (ft_strncmp(line, "SO", 2) == 0 && !game->walls.so_path)
	{
		line = skip_spaces(line + 2); // Pular "SO" e espaços após
		game->walls.so_path = ft_strdup(line);
		(*textures_found)++;
	}
	else if (ft_strncmp(line, "EA", 2) == 0 && !game->walls.ea_path)
	{
		line = skip_spaces(line + 2); // Pular "EA" e espaços após
		game->walls.ea_path = ft_strdup(line);
		(*textures_found)++;
	}
	else if (ft_strncmp(line, "WE", 2) == 0 && !game->walls.we_path)
	{
		line = skip_spaces(line + 2); // Pular "WE" e espaços após
		game->walls.we_path = ft_strdup(line);
		(*textures_found)++;
	}
	else if (ft_strncmp(line, "F", 1) == 0 && !game->colors.floor)
	{
		line = skip_spaces(line + 1); // Pular "F" e espaços após
		game->colors.floor = parse_color(line, game);
		(*textures_found)++;
	}
	else if (ft_strncmp(line, "C", 1) == 0 && !game->colors.ceiling)
	{
		line = skip_spaces(line + 1); // Pular "C" e espaços após
		game->colors.ceiling = parse_color(line, game);
		(*textures_found)++;
	}
	else if (!ft_strncmp(line, "\n", 1) == 0)
	{
		printf("Error\nTexture or color information is wrong in the map file!\n");
		cleanup(game);
		exit(EXIT_FAILURE);
	}
}

int	validate_color_string(char *color_str)
{
	int	i;

	i = 0;
	while (color_str[i])
	{
		if (!ft_isdigit(color_str[i]) && color_str[i] != ','
			&& color_str[i] != ' ')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	parse_color(char *color_str, t_game *game)
{
	int	rgb[3];
	int	count;
	int	flag;
	int	err;

	err = validate_color_string(color_str);
	count = 0;
	flag = 0;
	while (*color_str && !err && count < 3)
	{
		while (*color_str == ' ')
			color_str++;
		rgb[count] = ft_atoi(color_str);
		if (rgb[count] < 0 || rgb[count] > 255)
			err = 1;
		count++;
		while (*color_str && *color_str != ',')
			color_str++;
		if (*color_str++ == ',')
			flag++;
	}
	if (err || flag != 2 || count != 3)
		finish_game("RGB in the wrong format!", game);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
