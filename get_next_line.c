/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:46:21 by adelcros          #+#    #+#             */
/*   Updated: 2020/02/01 15:56:02 by adelcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(int count, int size_type)
{
	char *str;
	int i;

	i = 0;
	if (!(str = malloc(size_type * count)))
		return (NULL);
	while (i < size_type * count)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	*ft_strchr(char *str, int c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	return (0);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int i;
	int j;
	char *s3;

	if (!(s3 = malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	return (s3);
}

char	*ft_strdup(char *s1)
{
	char *s2;
	int i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	if (!(s2 = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strndup(char *s1, int n)
{
	int i;
	int len;
	char *s2;

	i = 0;
	while (s1[i] != '\0')
		i++;
	len = (i < n) ? i : n;
	if (!(s2 = malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	i = 0;
	while (*s1 && i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int		find_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char	*ft_newline(char **str)
{
	char *buffer;
	char *newline;
	// c est la ligne qu on veut envoyer
	// et str c est le residu
	char *tmp;

	buffer = ft_strchr(*str, '\n');
	// ici buffer est ce qui est lu apres le /n
	// 3/ buffer = \nsa
	tmp = NULL;
	if (buffer)
	{
		if (!(newline = ft_strndup(*str, buffer - (*str))))
		// 3/ str = "hello world\nsa", buffer = \nsa
		// 3/ newline = "hello world" car ("\nsa" - ("hello world + \nsa") == hello world)
			return (NULL);
		tmp = *str;
		// 3/ on envoie "hello world\nsa" dans tmp
		if (!(*str = ft_strdup(buffer + 1)))
		// 3/ on envoie "sa" dans str (apres le \n de \nsa)
			return (NULL);
		free(tmp);
		// 3/ on free "hello world\nsa"
	}
	else if (!(newline = ft_strdup(*str)))
	// si on ne trouve pas de '\n', on envoie str dans newline
	// 3/ ce n est pas le cas ici puisqu on a \nsa
		return (NULL);
	if (!(*str) || !(tmp))
	{
	// si on a pas de str, on clean
		free(*str);
		*str = NULL;
	}
	return (newline);
	// 3/ on renvoie "hello world"
}

char	*ft_read(int fd, char *buffer, char **str)
{
	int res;
	char *temp;

	res = 1;
	temp = NULL;
	// ex = "hello world \n salut" avec un buffer_size de 7 :
	while (!(find_n(*str)) && (res = read(fd, buffer, BUFFER_SIZE)) > 0)
	// find_n ne sert qu a indiquer s il y a un \n, si pas de \n, on entre dans
	// la condition, sinon on free directement buffer et on renvoie str (la 
	// ligne jusqu au \n)
	// read lit buffer_size par buffer_size
	// find_n cherche dans str qui est vide donc pas de \n et on lit jusqu a
	// 1/ "hello w"
	// 2/ str contient maintenant "hello w" -> find_n ne trouve pas de \n
	// 2/ read lit de la fin de str ("hello w", car la tete de lecture avance
	// avec read, voir man) jusqu a fin de buffer_size, donc "orld\nsa"
	// 3/ on cherche \n dans "orld\nsa", on le trouve
	// 3/ donc on n'entre pas dans la boucle
	{
		temp = *str;
		// 1/ str est vide, rien a envoyer
		// 2/ on envoie le contenu de str : "hello w" dans temp
		buffer[res] = '\0';
		// 1/ buffer = "hello w\0"
		// 2/ buffer = "orld/nsa\0"
		if (!(*str = ft_strjoin(*str, buffer)))
		// 1/ str = rien + hello w\0
		// 2/ str = hello w + orld\nsa\0
			return (NULL);
		free(temp);
		// 1/ rien a free
		// 1/ on continue la boucle puisqu on a pas de \n
		// 2/ on free hello w
	}
	free(buffer);
	// 3/ on free "orld\nsa"
	return (*str);
	// on return "hello world/nsa"
}

int		get_next_line(int fd, char **line)
{
	static char *str;
	char *buffer;
	char *end;

	if (fd < 0 || !(*line = ft_calloc(1, 1)) || BUFFER_SIZE < 1
		|| !(buffer = ft_calloc(1, BUFFER_SIZE + 1))
		|| read(fd, buffer, 0) == -1 || (!str && !(str = ft_calloc(1, 1))))
		return (-1);
//	*line = NULL;
	if (!(ft_read(fd, buffer, &str)))
	// si rien a lire
		return (-1);
	if (*str)
	// 3/ on a "hello world\nsa"
	{
		end = ft_strchr(str, '\n');
		// 3/ on envoie dans end, "sa"
		free(*line);
		// on reinitialise line, pour cleaner
		if (!(*line = ft_newline(&str)))
			// et on lui envoie newline pour que ce soit newline qui soit lue a
			// l'appel de fonction gnl
			// 3/ line = "hello world"
			return (-1);
		if (!end)
		{
		// si on ne trouve pas de \n a la fin, c est qu il n y a pas de residu
			free(str);
			str = NULL;
			// on reinitialise tout
			return (0);
			// on sort de la fonction et on recommence a lire
		}
		return (1);
		// une ligne a ete lue
		// 3/ "hello world" et on continue
	}
	return (0);
	// la fin de fichier a ete atteinte
}
