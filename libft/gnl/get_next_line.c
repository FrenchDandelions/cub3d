/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:51:55 by thole             #+#    #+#             */
/*   Updated: 2024/01/09 16:52:13 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_gnl_strlcpy(char *dest, char *src, size_t destsize)
{
	size_t	srcsize;
	size_t	i;

	i = 0;
	srcsize = ft_strlen(src);
	if (destsize > 0)
	{
		while (i < srcsize && i < destsize - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (srcsize);
}

// static char	*ft_gnl_strdup(char *s)
// {
// 	char	*copy;
// 	size_t	len;

// 	len = ft_strlen(s) + 1;
// 	copy = malloc(sizeof(char) * (len));
// 	if (!copy)
// 		return (NULL);
// 	ft_gnl_strlcpy(copy, s, len);
// 	return (copy);
// }

// static char	*ft_gnl_strjoin(char *s1, char *s2, size_t len)
// {
// 	size_t	len1;
// 	size_t	len2;
// 	char	*s3;

// 	len1 = ft_strlen(s1);
// 	len2 = len;
// 	s3 = malloc(sizeof(char) * (len1 + len2 + 1));
// 	if (!s3)
// 		return (NULL);
// 	ft_gnl_strlcpy(s3, s1, len1 + 1);
// 	ft_gnl_strlcpy((s3 + len1), s2, len2 + 1);
// 	free(s1);
// 	return (s3);
// }

// static void	do_new_line(char **line, char *stock)
// {
// 	int		to_copy;
// 	char	*new_line;

// 	new_line = ft_gnl_strchr((*line), '\n');
// 	if (new_line != NULL)
// 	{
// 		to_copy = new_line - (*line) + 1;
// 		ft_gnl_strlcpy(stock, new_line + 1, BUFFER_SIZE + 1);
// 	}
// 	else
// 	{
// 		to_copy = ft_strlen((*line));
// 		ft_gnl_strlcpy(stock, "", BUFFER_SIZE + 1);
// 	}
// 	(*line)[to_copy] = '\0';
// }

// char	*get_next_line(int fd)
// {
// 	static char	stock[BUFFER_SIZE + 1];
// 	char		*line;
// 	int			bytes_read;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	line = ft_gnl_strdup(stock);
// 	bytes_read = 1;
// 	while (!(ft_gnl_strchr(line, '\n')) && bytes_read > 0)
// 	{
// 		bytes_read = read(fd, stock, BUFFER_SIZE);
// 		stock[bytes_read] = '\0';
// 		line = ft_gnl_strjoin(line, stock, BUFFER_SIZE);
// 	}
// 	if (ft_strlen(line) == 0)
// 		return (free(line), NULL);
// 	do_new_line(&line, stock);
// 	return (line);
// }
char	*ft_free(char *s)
{
	free(s);
	return (NULL);
}

char	*ft_read(int fd, char *stock)
{
	char	*strj;
	int		i;

	if (!stock)
	{
		stock = malloc(1);
		*stock = '\0';
	}
	strj = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!strj)
		return (free(stock), ft_free(strj));
	i = 1;
	while (i > 0)
	{
		i = read(fd, strj, BUFFER_SIZE);
		if (i == -1)
			return (free(stock), ft_free(strj));
		strj[i] = '\0';
		stock = ft_freestrjoin(stock, strj);
		if (ft_strchr(stock, '\n') && ft_strchr(stock, '\0'))
			break ;
	}
	free(strj);
	return (stock);
}

char	*ft_new_line(char *stock)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!stock[i])
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	new_line = ft_calloc(sizeof(char), (i + 1));
	if (!new_line)
		return (ft_free(new_line));
	i = 0;
	while (stock[i] && stock[i] != '\n')
	{
		new_line[i] = stock[i];
		i++;
	}
	if (stock[i] && stock[i] == '\n')
		new_line[i++] = '\0';
	return (new_line);
}

char	*ft_delete_past_line(char *stock)
{
	char	*trimmed_line;
	int		i;
	int		j;

	i = 0;
	while (stock[i] != '\n' && stock[i])
		i++;
	if (!stock[i])
		return (ft_free(stock));
	trimmed_line = (char *)malloc(sizeof(char) * (ft_strlen(stock) - i + 1));
	if (!trimmed_line)
		return (ft_free(trimmed_line));
	i++;
	j = 0;
	while (stock[i])
	{
		trimmed_line[j++] = stock[i];
		i++;
	}
	free(stock);
	trimmed_line[j] = '\0';
	return (trimmed_line);
}

char	*get_next_line(int fd)
{
	static char	*stock[1025];
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0 || fd > 1024)
		return (NULL);
	stock[fd] = ft_read(fd, stock[fd]);
	new_line = ft_new_line(stock[fd]);
	stock[fd] = ft_delete_past_line(stock[fd]);
	return (new_line);
}
