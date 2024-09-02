/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_map_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:37:32 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/02 21:05:09 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	find_max_width(char **map)
{
	int	i;
	int	width;
	int	max_width;

	i = 0;
	width = 0;
	max_width = 0;
	while (map[i])
	{
		trim_end_whitespace(map[i]);
		width = strlen(map[i]);
		if (width > max_width)
			max_width = width;
		i++;
	}
	return (max_width);
}

int	find_map_start_and_height(char **map, int *map_start, int *h, int *n_empty)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		*n_empty = 0;
		while (map[i][j])
		{
			if (ft_isalnum(map[i][j]))
			{
				if (*map_start == -1)
					*map_start = i;
				*n_empty = 1;
				(*h)++;
				break ;
			}
			j++;
		}
		if (*n_empty == 0 && *map_start != -1)
			break ;
		i++;
	}
	return (*h);
}

void	check_empty_line_validation(char **map, t_game *game)
{
	int	i;
	int	j;
	int	map_start;
	int	height;
	int	n_empty;

	map_start = -1;
	height = 0;
	find_map_start_and_height(map, &map_start, &height, &n_empty);
	if (map_start == -1)
		finish_game("Map in the wrong format!", game);
	i = map_start + height;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_isalnum(map[i][j]))
				finish_game("Map in the wrong format!", game);
			j++;
		}
		i++;
	}
}

int	find_height(char **map, t_game *game)
{
	int	height;

	height = 0;
	check_empty_line_validation(map, game);
	while (map[height])
	{
		trim_end_whitespace(map[height]);
		height++;
	}
	return (height);
}
