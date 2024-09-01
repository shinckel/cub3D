/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:19:53 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/01 19:20:38 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

char **create_mockup(int width, int height, t_game *game)
{
	int	i;
	int	j;
    char **mockup;
	mockup = malloc((height + 2) * sizeof(char *));
	if (!mockup)
	{
		printf("Error\n");
		cleanup(game);
		exit(EXIT_FAILURE);
	}

	i = 0;
	while (i < height)
	{
		j = 0;
		mockup[i] = malloc((width + 1) * sizeof(char));
		if (!mockup[i]) {
            printf("Error\n");
            cleanup(game);
            exit(EXIT_FAILURE);
        }
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
