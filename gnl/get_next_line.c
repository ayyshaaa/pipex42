/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:59:20 by aistierl          #+#    #+#             */
/*   Updated: 2024/10/01 15:58:26 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_concat_free(char *line, char *adding)
{
	char	*temporary;

	temporary = ft_strlink(line, adding);
	if (!temporary)
		return (free(line), free(adding), NULL);
	free(line);
	line = temporary;
	return (line);
}

char	*ft_read_concat(int fd, char *buffer, char *line)
{
	int	read_value;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_value = 1;
	while (read_value > 0)
	{
		read_value = read(fd, buffer, BUFFER_SIZE);
		if (read_value < 0)
			return (free(buffer), free(line), NULL);
		if (read_value == 0)
			break ;
		buffer[read_value] = '\0';
		line = ft_concat_free(line, buffer);
		if (!line)
			return (NULL);
		if (ft_strchr(line, 10))
			break ;
	}
	return (free(buffer), line);
}

char	*ft_left(char *line, char *stash)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (line && line[i] != '\0')
	{
		if (line[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	if (!line || line[i] == '\0')
		return (NULL);
	str = malloc(ft_strlen(line) - i + 1);
	if (!str)
		return (free(line), free(stash), NULL);
	j = 0;
	while (line[i] != '\0')
		str[j++] = line[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_extract(char *line, char *stash)
{
	char	*cropped;
	int		i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	cropped = malloc(i + 2);
	if (cropped == NULL)
		return (free(line), free(stash), NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		cropped[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		cropped[i++] = '\n';
	cropped[i] = '\0';
	return (free(line), cropped);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	buffer = NULL;
	if (stash != NULL)
	{
		line = ft_concat_free(line, stash);
		if (!line)
			return (NULL);
		free(stash);
		stash = NULL;
	}
	line = ft_read_concat(fd, buffer, line);
	if (!line)
		return (NULL);
	stash = ft_left(line, stash);
	line = ft_extract(line, stash);
	return (line);
}
