/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures_colors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:43:05 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/02 16:19:50 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void extract_textures_and_colors(int fd, t_game *game)
{
	int err;
	char *line;
	int textures_found;

	err = 0;
	line = NULL;
	textures_found = 0;
	while ((line = get_next_line(fd)) && textures_found < 6)
	{
			trim_end_whitespace(line);
			extract_texture(line, game, &textures_found, &err);
			free(line);
			if (err)
					break;
	}
	if (err)
			finish_game("Textures/colors validation failed!", game);
	else
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

int parse_rgb_values(char *color_str, int *rgb, int *err)
{
    int count = 0;
    int flag = 0;

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
        if (*color_str++ == ',')
            flag++;
    }
    if (*err || flag != 2 || count != 3)
        *err = 1;
    return *err;
}

int parse_color(char *color_str, int *err)
{
    int rgb[3];

    *err = validate_color_string(color_str);
    if (parse_rgb_values(color_str, rgb, err) || *err)
        return (-1);
    return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
