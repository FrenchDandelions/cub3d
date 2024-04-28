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

static char	*ft_gnl_strdup(char *s)
{
	char	*copy;
	size_t	len;

	len = ft_strlen(s) + 1;
	copy = malloc(sizeof(char) * (len));
	if (!copy)
		return (NULL);
	ft_gnl_strlcpy(copy, s, len);
	return (copy);
}

static char	*ft_gnl_strjoin(char *s1, char *s2, size_t len)
{
	size_t	len1;
	size_t	len2;
	char	*s3;

	len1 = ft_strlen(s1);
	len2 = len;
	s3 = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!s3)
		return (NULL);
	ft_gnl_strlcpy(s3, s1, len1 + 1);
	ft_gnl_strlcpy((s3 + len1), s2, len2 + 1);
	free(s1);
	return (s3);
}

static void	do_new_line(char **line, char *stock)
{
	int		to_copy;
	char	*new_line;

	new_line = ft_gnl_strchr((*line), '\n');
	if (new_line != NULL)
	{
		to_copy = new_line - (*line) + 1;
		ft_gnl_strlcpy(stock, new_line + 1, BUFFER_SIZE + 1);
		(*line)[to_copy - 1] = '\0';
	}
	else
	{
		to_copy = ft_strlen((*line));
		ft_gnl_strlcpy(stock, "", BUFFER_SIZE + 1);
		(*line)[to_copy] = '\0';
	}
}

char	*get_next_line(int fd)
{
	static char	stock[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_gnl_strdup(stock);
	bytes_read = 1;
	while (!(ft_gnl_strchr(line, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, stock, BUFFER_SIZE);
		stock[bytes_read] = '\0';
		line = ft_gnl_strjoin(line, stock, BUFFER_SIZE);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	do_new_line(&line, stock);
	return (line);
}
