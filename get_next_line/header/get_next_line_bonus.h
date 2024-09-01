/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:49:43 by shinckel          #+#    #+#             */
/*   Updated: 2022/12/16 13:04:00 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
/* 1 is commonly used for creating infinite loops (e.g. while(1));
 * here, the macro is only for making the code more explicitly and readable;
 */
# define TRUE 1
/* sys/types, sys/stat, fcntl=> libraries for using open(); 
 * unistd => library for using close();
 */
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
int		ft_count(char *str);
char	*ft_join(char *tmp, char *buf);
int		ft_check(char *buf);

#endif