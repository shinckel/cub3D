/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures_colors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:43:05 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/02 22:43:05 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

/*
 * if nor for norminette issues, we could initialize line to NULL
 * and set new line in the loop
 * while ((line = get_next_line(fd)) && texture_found < 6)
 */
void	extract_textures_and_colors(int fd, t_game *game)
{
	int		err;
	char	*line;
	int		texture_found;

	err = 0;
	line = get_next_line(fd);
	texture_found = 0;
	while (line && texture_found < 6)
	{
		trim_end_whitespace(line);
		extract_texture(line, game, &texture_found, &err);
		free(line);
		if (err || texture_found == 6)
			break ;
		line = get_next_line(fd);
	}
	if (err)
		finish_game("Textures/colors validation failed!", game);
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

int	parse_rgb_values(char *color_str, int *rgb, int *err)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (*color_str && !(*err) && count < 3)
	{
		while (*color_str == ' ')
			color_str++;
		rgb[count] = ft_atoi(color_str);
		if (rgb[count] < 0 || rgb[count] > 255)
			*err = 1;
		count++;
		while (*color_str && *color_str != ',')
			color_str++;
		if (*color_str == ',')
		{
			flag++;
			color_str++;
		}
	}
	if (*err || flag != 2 || count != 3)
		*err = 1;
	return (*err);
}

int	parse_color(char *color_str, int *err)
{
	int	rgb[3];

	if (*color_str == '\0')
		return (-1);
	*err = validate_color_string(color_str);
	if (parse_rgb_values(color_str, rgb, err) || *err)
		return (-1);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
