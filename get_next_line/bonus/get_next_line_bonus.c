/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:28:14 by shinckel          #+#    #+#             */
/*   Updated: 2024/09/02 20:55:33 by shinckel         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static char	buf[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*tmp;
	int			i;

	i = 0;
	if (fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		while (buf[fd][i])
			buf[fd][i++] = 0;
		return (NULL);
	}
	tmp = NULL;
	while (buf[fd][0] || read(fd, buf[fd], BUFFER_SIZE) > 0)
	{
		tmp = ft_join(tmp, buf[fd]);
		if (ft_check(buf[fd]))
			break ;
	}
	return (tmp);
}

// int main(void)
// {
// 	int fd;
// 	int fd2;

// 	fd = open("Sofia.txt", O_RDONLY);
// 	fd2 = open("Morango.txt", O_RDONLY);
// 	printf("line 01: %s\n", get_next_line(fd));
// 	printf("line 02: %s\n", get_next_line(fd));
// 	printf("line 01: %s\n", get_next_line(fd2));
// 	printf("line 02: %s\n", get_next_line(fd2));
// 	printf("line 01: %s\n", get_next_line(fd));
// 	printf("line 02: %s\n", get_next_line(fd));
// 	// printf("%s\n", get_next_line(fd));
// 	// printf("%s\n", get_next_line(fd));
// 	// printf("%s\n", get_next_line(fd));
// 	close(fd);
// 	close (fd2);
// 	return (0);
// }
