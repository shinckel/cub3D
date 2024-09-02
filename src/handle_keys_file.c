/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:40:20 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/02 18:02:12 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int process_input(t_game *game)
{
    if (game->keys[0])
        move_forward(game);
    if (game->keys[1])
        move_backward(game);
    if (game->keys[2])
        move_left(game);
    if (game->keys[3])
        move_right(game);
    if (game->keys[4])
        rotate_left(game);
    if (game->keys[5])
        rotate_right(game);
		if (game->keys[0] || game->keys[1] || game->keys[2] || game->keys[3]
			|| game->keys[4] || game->keys[5])
        update_game(game);
    return 0;
}

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nThere is an error opening file");
		printf("%s\n", filename);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	my_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*trim_end_whitespace(char *str)
{
	char	*end;

	if (*str == 0)
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && my_isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
	return (str);
}
