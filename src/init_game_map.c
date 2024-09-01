// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   init_game_map.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/29 16:38:38 by shinckel          #+#    #+#             */
// /*   Updated: 2024/08/29 16:38:39 by shinckel         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// char	**map_copy(char **map, t_game *game)
// {
// 	char	**mcopy;
// 	int		i;

// 	mcopy = (char **)malloc(sizeof(char *) * (game->config.height + 1));
// 	if (!mcopy)
// 	{
// 		printf("Error:\n Memory allocation error\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	i = 0;
// 	while (map[i])
// 	{
// 		mcopy[i] = ft_strdup(map[i]);
// 		if (!mcopy[i])
// 		{
// 			printf("Error:\nMemory allocation error\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// 	mcopy[i] = NULL;
// 	return (mcopy);
// }

// int	check_map_char(char **mcopy, t_game *game)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (mcopy[i])
// 	{
// 		j = 0;
// 		while (mcopy[i][j])
// 		{
// 			if (mcopy[i][j] != '0' && mcopy[i][j] != 'N'
// 				&& mcopy[i][j] != 'E' && mcopy[i][j] != 'W'
// 				&& mcopy[i][j] != 'S' && mcopy[i][j] != '1'
// 				&& mcopy[i][j] != '\0' && mcopy[i][j] != ' '
// 				&& mcopy[i][j] != '\t' && mcopy[i][j] != '\n')
// 			{
// 				printf("Error:\nThere are different characters in the map!\n");
// 				cleanup(game);
// 				exit(EXIT_FAILURE);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	check_enclosed_map(char **map, t_game *game)
// {
// 	int		i;
// 	int		j;
// 	char	**mcopy;

// 	mcopy = map_copy(map, game);
// 	i = 0;
// 	while (mcopy[i])
// 	{
// 		j = 0;
// 		while (mcopy[i][j])
// 		{
// 			if (mcopy[i][j] == '0' || mcopy[i][j] == 'N' || mcopy[i][j] == 'E'
// 				|| mcopy[i][j] == 'W' || mcopy[i][j] == 'S')
// 				flood_fill(mcopy, j, i, game);
// 			j++;
// 		}
// 		i++;
// 	}
// 	free_matrix(mcopy);
// 	return (0);
// }

// void	counting_map(t_game *game)
// {	
// 	int	i;
// 	int	len;

// 	i = 0;
// 	while (game->config.map[i])
// 	{
// 		len = 0;
// 		trim_end_whitespace(game->config.map[i]);
// 		len = ft_strlen(game->config.map[i]);
// 		if (len > game->config.width)
// 			game->config.width = len;
// 		game->config.height++;
// 		i++;
// 	}
// }