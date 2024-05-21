/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:41:40 by ousabbar          #+#    #+#             */
/*   Updated: 2023/11/18 16:41:45 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_new_line(char *s)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	i++;
	new_str = malloc(sizeof(char) * ft_strlen(s) - i + 2);
	if (!new_str)
		return (NULL);
	j = 0;
	while (s[i])
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	free(s);
	return (new_str);
}

char	*f_free(char *s)
{
	if (s[0] == '\0')
	{
		free(s);
		return (NULL);
	}
	return (s);
}

char	*ft_trim(char *s)
{
	int		i;
	char	*string;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	string = malloc(sizeof(char) * (i + 2));
	if (!string)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		string[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		string[i] = '\n';
		i++;
	}
	string[i] = '\0';
	return (f_free(string));
}

char	*ft_line(char *str, int fd)
{
	char	*buffer;
	int		byts;

	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	byts = 1;
	while (!ft_strchr(str, '\n') && byts != 0)
	{
		byts = read(fd, buffer, BUFFER_SIZE);
		if (byts == -1)
		{
			free(str);
			free(buffer);
			return (NULL);
		}
		buffer[byts] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*saved[OPEN_MAX];
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	saved[fd] = ft_line(saved[fd], fd);
	result = ft_trim(saved[fd]);
	saved[fd] = ft_new_line(saved[fd]);
	return (result);
}
