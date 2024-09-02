/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:38:38 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/02 22:42:43 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

char	**convert_map_to_array(t_list *map_lines)
{
	t_list	*tmp;
	int		map_height;
	char	**map;
	int		i;

	map_height = 0;
	i = 0;
	tmp = map_lines;
	while (tmp)
	{
		map_height++;
		tmp = tmp->next;
	}
	map = (char **)malloc(sizeof(char *) * (map_height + 1));
	map[map_height] = NULL;
	tmp = map_lines;
	while (tmp)
	{
		map[i] = ft_strdup((char *)tmp->content);
		i++;
		tmp = tmp->next;
	}
	free_list(map_lines);
	return (map);
}

char	**read_map(char *filename, t_game *game)
{
	int		fd;
	t_list	*map_lines;
	t_list	*new_node;
	char	*line;
	char	**map;

	fd = open_file(filename);
	extract_textures_and_colors(fd, game);
	map_lines = NULL;
	new_node = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		new_node = ft_lstnew(ft_strdup(line));
		ft_lstadd_back(&map_lines, new_node);
		free(line);
		line = get_next_line(fd);
	}
	if (!map_lines)
		finish_game("Map is empty!", game);
	close(fd);
	map = convert_map_to_array(map_lines);
	return (map);
}

void	flood_fill(char **map_copy, int x, int y, t_game *game)
{
	if (x < 0 || x >= game->config.width || y < 0 || y >= game->config.height)
	{
		free_matrix(map_copy);
		finish_game("There is a problem with the map!", game);
	}
	if (map_copy[y][x] == '1' || map_copy[y][x] == '*')
		return ;
	if (map_copy[y][x] == '\0' || map_copy[y][x] == ' '
		|| map_copy[y][x] == '\t' || map_copy[y][x] == '\n'
		|| map_copy[y][x] == '+')
	{
		free_matrix(map_copy);
		finish_game("There is a problem with the map!", game);
	}
	map_copy[y][x] = '*';
	flood_fill(map_copy, x + 1, y, game);
	flood_fill(map_copy, x - 1, y, game);
	flood_fill(map_copy, x, y + 1, game);
	flood_fill(map_copy, x, y - 1, game);
}

char	**map_copy(char **map, t_game *game)
{
	char	**mcopy;
	int		i;

	mcopy = (char **)malloc(sizeof(char *) * (game->config.height + 1));
	if (!mcopy)
	{
		printf("Error\nMemory allocation error\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (map[i])
	{
		mcopy[i] = ft_strdup(map[i]);
		if (!mcopy[i])
		{
			printf("Error\nMemory allocation error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	mcopy[i] = NULL;
	return (mcopy);
}
