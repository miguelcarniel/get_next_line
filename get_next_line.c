/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarniel <mcarniel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 03:04:53 by mcarniel          #+#    #+#             */
/*   Updated: 2022/05/10 15:36:29 by mcarniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_find(char *accumulator, int fd)
{
	char	*buffer;
	int		chars_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	chars_read = 1;
	while (!ft_strchr(accumulator, '\n') && chars_read != 0)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[chars_read] = '\0';
		accumulator = ft_strjoin(accumulator, buffer);
	}
	free(buffer);
	return (accumulator);
}

char	*ft_get_line(char *accumulator)
{
	size_t	i;
	char	*line;

	i = 0;
	if (accumulator == NULL)
		return (NULL);
	while (accumulator[i] != '\0' && accumulator[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (accumulator[i] != '\0' && accumulator[i] != '\n')
	{
		line[i] = accumulator[i];
		i++;
	}
	if (accumulator[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_accumulate(char *accumulator)
{
	size_t	i;
	size_t	j;
	char	*new_accum;

	i = 0;
	while (accumulator[i] != '\0' && accumulator[i] != '\n')
		i++;
	if (accumulator[i] == '\0')
	{
		free(accumulator);
		return (0);
	}
	new_accum = (char *)malloc(sizeof(char) * (ft_strlen(accumulator) - i + 1));
	if (new_accum == NULL)
		return (NULL);
	i += 1;
	j = 0;
	while (accumulator[i] != '\0')
		new_accum[j++] = accumulator[i++];
	new_accum[j] = '\0';
	free(accumulator);
	return (new_accum);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*accumulator;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	accumulator = ft_find(accumulator, fd);
	if (accumulator == NULL)
		return (NULL);
	line = ft_get_line(accumulator);
	accumulator = ft_accumulate(accumulator);
	if (line[0] == '\0')
	{
		free(accumulator);
		free(line);
		return (NULL);
	}
	return (line);
}
