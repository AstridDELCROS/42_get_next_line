/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 15:54:44 by adelcros          #+#    #+#             */
/*   Updated: 2020/02/01 15:56:13 by adelcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 32
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

void	*ft_calloc(int count, int size_type);
char	*ft_strchr(char *str, int c);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	*ft_strndup(char *s1, int n);
int		find_n(char *str);
char	*ft_newline(char **str);
char	*ft_read(int fd, char *buffer, char **str);
int		get_next_line(int fd, char **line);

#endif
