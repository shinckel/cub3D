/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures_colors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:43:05 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/01 22:15:43 by shinckel         ###   ########.fr       */
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
	{
		//free(color_str);
		finish_game("RGB in the wrong format!", game);
	}
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
