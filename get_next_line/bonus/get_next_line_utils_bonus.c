/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:28:20 by shinckel          #+#    #+#             */
/*   Updated: 2024/06/16 17:34:43 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/get_next_line_bonus.h"

int	ft_count(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_join(char *tmp, char *buf)
{
	int		i;
	int		j;
	char	*aux;

	aux = malloc(ft_count(tmp) + ft_count(buf) + 1);
	if (!aux)
		return (NULL);
	i = 0;
	j = 0;
	while (tmp && tmp[i])
		aux[j++] = tmp[i++];
	free (tmp);
	i = 0;
	while (buf && buf[i])
	{
		aux[j++] = buf[i];
		if (buf[i++] == '\n')
			break ;
	}
	aux[j] = '\0';
	return (aux);
}

int	ft_check(char *buf)
{
	int	i;
	int	j;
	int	n_line;

	i = 0;
	j = 0;
	n_line = 0;
	while (buf[i])
	{
		if (n_line)
			buf[j++] = buf[i];
		if (buf[i] == '\n')
			n_line = 1;
		buf[i++] = 0;
	}
	return (n_line);
}
