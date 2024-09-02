/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:19:53 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/02 16:02:07 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

char **create_mockup(int width, int height, t_game *game)
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
    return mockup;
}

void copy_map_to_mockup(char **map, char **mockup)
{
    int i = 0;
    while (map[i])
    {
        int j = 0;
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

char **normalize_map(char **map, t_game *game)
{
    int max_width = find_max_width(map);
    int height = find_height(map, game);
    char **mockup = create_mockup(max_width, height, game);
    copy_map_to_mockup(map, mockup);

    return mockup;
}
