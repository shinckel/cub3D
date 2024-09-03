/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures_colors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:43:05 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/03 19:40:41 by shinckel         ###   ########.fr       */
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
	{
		close(fd);
		finish_game("Textures/colors validation failed!", game);
	}
}

// int	validate_color_string(char *color_str)
// {
// 	int	i;
// 	int	found_digit;

// 	i = 0;
// 	found_digit = 0;
// 	while (color_str[i])
// 	{
// 		if (ft_isdigit(color_str[i]))
// 		{
// 			found_digit = 1;
// 			while (ft_isdigit(color_str[i]))
// 				i++;
// 			if (color_str[i] == ' ' || color_str[i] == ',')
// 			{
// 				while (color_str[i] == ' ')
// 					i++;
// 				if (ft_isdigit(color_str[i]))
// 					return (1);
// 			}
// 		}
// 		else if (color_str[i] == ',')
// 		{
// 			if (!found_digit)
// 				return (1);
// 			found_digit = 0;
// 			i++;
// 		}
// 		else if (color_str[i] == ' ')
// 			i++;
// 		else
// 			return (1);
// 	}
// 	if (!found_digit)
// 		return (1);
// 	return (0);
// }

int	validate_digits(char **color_str)
{
	int	found_digit;

	found_digit = 0;
	while (**color_str)
	{
		while (**color_str == ' ')
			(*color_str)++;
		if (ft_isdigit(**color_str))
		{
			found_digit = 1;
			while (ft_isdigit(**color_str))
				(*color_str)++;
		}
		if (**color_str != ',' && **color_str != ' ' && **color_str != '\0')
			return (1);
		break ;
	}
	if (found_digit == 0)
		return (1);
	else
		return (0);
}

int	validate_color_string(char *color_str)
{
	while (*color_str)
	{
		if (validate_digits(&color_str))
			return (1);
		while (*color_str == ' ')
			color_str++;
		if (*color_str == ',')
			color_str++;
		else if (*color_str != '\0')
			return (1);
	}
	return (0);
}

// validation: we should have exactly 3 numbers and 2 commas
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

	*err = validate_color_string(color_str);
	if (*color_str == '\0' || *err || parse_rgb_values(color_str, rgb, err))
	{
		*err = 1;
		return (-1);
	}
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
