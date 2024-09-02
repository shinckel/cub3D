/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:17:31 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/02 14:58:31 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
}

void	finish_game(char* msg, t_game *game)
{
	printf("Error\n%s\n", msg);
	cleanup(game);
	exit(EXIT_FAILURE);
}

void	cleanup(t_game *game)
{
	if (!game)
		return ;
	free_textures(game);
	if (game->config.map)
		free_matrix(game->config.map);
	if (game->config.map_norm)
	 	free_matrix(game->config.map_norm);
	if (game->img.img_ptr)
		mlx_destroy_image(game->win.mlx_ptr, game->img.img_ptr);
	if (game->win.win_ptr)
		mlx_destroy_window(game->win.mlx_ptr, game->win.win_ptr);
	if (game->win.mlx_ptr)
	{
		mlx_destroy_display(game->win.mlx_ptr);
		free(game->win.mlx_ptr);
	}
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
