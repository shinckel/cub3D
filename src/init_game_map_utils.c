/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_map_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:37:32 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/01 22:01:14 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int find_max_width(char **map)
{
    int max_width = 0;
    int i = 0;
    while (map[i])
    {
		trim_end_whitespace(map[i]);
        int width = strlen(map[i]);
        if (width > max_width)
            max_width = width;
        i++;
    }
    return max_width;
}

int find_map_start_and_height(char **map, int *map_start)
{
	int i = 0;
	int j;
	int height = 0;
	int not_empty;

	*map_start = -1;
	while (map[i])
	{
		j = 0;
		not_empty = 0;
		while (map[i][j])
		{
			if (ft_isalnum(map[i][j]))
			{
				if (*map_start == -1)
					*map_start = i;
				not_empty = 1;
				height++;
				break ;
			}
			j++;
		}
		if (not_empty == 0 && *map_start != -1)
			break ;
		i++;
	}
	return height;
}

void check_empty_line_validation(char **map, t_game *game)
{
	int map_start;
	int height = find_map_start_and_height(map, &map_start);
	int i;
	int	j;

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

int find_height(char **map, t_game *game)
{
    int height = 0;
	check_empty_line_validation(map, game);
    while (map[height])
	{
		trim_end_whitespace(map[height]);
		height++;
	}
    return height;
}

// TODO: check validation
// void	check_empty_line_validation(char **map, t_game *game)
// {
//     int height = 0;
// 	int i = 0;
// 	int j;
// 	int map_start;
// 	int not_empty = 0;

// 	map_start = -1;
//     while (map[i])
// 	{
// 		j = 0;
// 		not_empty = 0;
// 		while (map[i][j])
// 		{
// 			if (ft_isalnum(map[i][j])) // Encontrou uma linha não vazia
// 			{
// 				if (map_start == -1) // Primeira linha válida
// 					map_start = i;
// 				not_empty = 1;
// 				height++;
// 				break ;
// 			}
// 			j++;
// 		}
// 		if (not_empty == 0 && map_start != -1) // Linha vazia depois do mapa começar
// 			break ;
// 		i++;
// 	}

// 	// Se map_start nunca foi definido, o mapa não tem linhas válidas
// 	if (map_start == -1)
// 	{
// 		printf("Error\nMap in the wrong format!\n");
// 		cleanup(game);
// 		exit(EXIT_FAILURE);
// 	}

// 	i = map_start + height;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			if (ft_isalnum(map[i][j])) // Linha não vazia após o final do mapa
// 			{
// 				printf("Error\nMap in the wrong format!\n");
// 				cleanup(game);
// 				exit(EXIT_FAILURE);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	check_empty_line_validation(char **map, t_game *game)
// {
//     int height = 0;
// 	int i = 0;
// 	int j;
// 	int map_start;
// 	int not_empty = -1;

// 	map_start = 0;
//     while (map[i])
// 	{
// 		j = 0;
// 		if (!not_empty)
// 			break ;
// 		not_empty = 0;
// 		while (map[i][j])
// 		{
// 			if (ft_isalnum(map[i][j]) && !map_start)
// 			{
// 				map_start = i;
// 				not_empty = 1;
// 				height++;
// 				break ;
// 			}
// 			else if(ft_isalnum(map[i][j]))
// 			{
// 				not_empty = 1;
// 				height++;
// 				break ;
// 			}
// 			else if (!map_start)
// 				not_empty = 1;
// 			j++;
// 		}
// 		i++;
// 	}
// 	i = map_start + height - 1;
// 	if (map[i])
// 	{
// 		while (map[i])
// 		{
// 			j = 0;
// 			while (map[i][j])
// 			{
// 				if (ft_isalnum(map[i][j]))
// 				{
// 					printf("Error\nMap in the wrong format!");
// 					cleanup(game);
// 					exit(EXIT_FAILURE);
// 				}
// 				j++;
// 			}
// 			i++;
// 		}
// 	} 
// }
