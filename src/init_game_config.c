/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:19:53 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/03 14:48:08 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	is_collision(t_game *game, double new_x, double new_y)
{
	double	margin;

	margin = 0.1;
	if (game->config.map[(int)(new_y)][(int)(new_x)] == ' ' || game->config.map[(int)(new_y + margin)][(int)(new_x + margin)] == '\0')
		return (1);
	if (game->config.map[(int)(new_y + margin)][(int)(new_x + margin)] == '1' || game->config.map[(int)(new_y + margin)][(int)(new_x + margin)] == '\0' || game->config.map[(int)(new_y + margin)][(int)(new_x + margin)] == ' ')
		return (1);
	if (game->config.map[(int)(new_y - margin)][(int)(new_x - margin)] == '1' || game->config.map[(int)(new_y + margin)][(int)(new_x + margin)] == '\0' || game->config.map[(int)(new_y + margin)][(int)(new_x + margin)] == ' ')
		return (1);
	return (0);
}

char	**create_mockup(int width, int height, t_game *game)
{
	int		i;
	int		j;
	char	**mockup;

	mockup = malloc((height + 2) * sizeof(char *));
	if (!mockup)
		finish_game("Failed in creating mockup!", game);
	i = 0;
	while (i < height)
	{
		j = 0;
		mockup[i] = malloc((width + 1) * sizeof(char));
		if (!mockup[i])
			finish_game("Failed in creating mockup!", game);
		while (j < width + 1)
		{
			mockup[i][j] = '+';
			j++;
		}
		mockup[i][width] = '\0';
		i++;
	}
	mockup[height] = NULL;
	return (mockup);
}

void	copy_map_to_mockup(char **map, char **mockup)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				mockup[i][j] = '+';
			else
				mockup[i][j] = map[i][j];
			j++;
		}
		i++;
	}
}

char	**normalize_map(char **map, t_game *game)
{
	int		max_width;
	int		height;
	char	**mockup;

	max_width = find_max_width(map);
	height = find_height(map, game);
	mockup = create_mockup(max_width, height, game);
	copy_map_to_mockup(map, mockup);
	return (mockup);
}
