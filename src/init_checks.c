/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:48:54 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/01 18:35:43 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	check_single_player(char **mcopy, t_game *game)
{
	int		i;
	int		j;
	int		player_count;

	player_count = 0;
	i = 0;
	while (mcopy[i])
	{
		j = 0;
		while (mcopy[i][j])
		{
			if (mcopy[i][j] == 'N' || mcopy[i][j] == 'E' || mcopy[i][j] == 'W'
				|| mcopy[i][j] == 'S')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		if (player_count == 0)
			finish_game("No player found on the map!", game);
		finish_game("Multiple players found on the map!", game);
	}
	return (0);
}

int	check_map_char(char **mcopy, t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (mcopy[i])
	{
		j = 0;
		while (mcopy[i][j])
		{
			if (mcopy[i][j] != '0' && mcopy[i][j] != 'N'
				&& mcopy[i][j] != 'E' && mcopy[i][j] != 'W'
				&& mcopy[i][j] != 'S' && mcopy[i][j] != '1'
				&& mcopy[i][j] != '\0' && mcopy[i][j] != ' '
				&& mcopy[i][j] != '\t' && mcopy[i][j] != '\n'
				&& mcopy[i][j] != '+')
			{
				finish_game("There are different characters in the map!", game);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_enclosed_map(char **map, t_game *game)
{
	int		i;
	int		j;
	char	**mcopy;

	mcopy = map_copy(map, game);
	i = 0;
	while (mcopy[i])
	{
		j = 0;
		while (mcopy[i][j])
		{
			if (mcopy[i][j] == '0' || mcopy[i][j] == 'N' || mcopy[i][j] == 'E'
				|| mcopy[i][j] == 'W' || mcopy[i][j] == 'S')
				flood_fill(mcopy, j, i, game);
			j++;
		}
		i++;
	}
	free_matrix(mcopy);
	return (0);
}

void	counting_map(t_game *game, char **map)
{
	int	i;
	int	len;

	i = 0;
	while (map[i])
	{
		len = 0;
		trim_end_whitespace(map[i]);
		len = ft_strlen(map[i]);
		if (len > game->config.width)
			game->config.width = len;
		game->config.height++;
		i++;
	}
}
