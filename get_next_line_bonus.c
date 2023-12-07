/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:14:00 by ybouyzem          #+#    #+#             */
/*   Updated: 2023/12/07 20:32:12 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_check(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == (char) c)
			return (1);
		i++;
	}
	return (0);
}

char	*get_content(int fd, char *content)
{
	char	*str;
	int		len;

	len = 1;
	str = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	while (len != 0 && ft_check(content, '\n') == 0)
	{
		len = read(fd, str, BUFFER_SIZE);
		if (len == -1)
		{
			free(str);
			free(content);
			return (NULL);
		}
		str[len] = '\0';
		content = ft_strjoin(content, str);
	}
	free(str);
	return (content);
}

char	*get_reminder(char *buf)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\0')
		return (free(buf), NULL);
	if (buf[i] == '\n')
		i++;
	new = (char *)malloc(sizeof(char) * (ft_strlen(buf) - i + 1));
	if (!new)
		return (free(buf), NULL);
	j = 0;
	while (buf[i])
	{
		new[j] = buf[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (free(buf), new);
}

char	*get_new_line(char *buf)
{
	int		i;
	char	*line;

	i = 0;
	if (buf[i] == '\0' || !buf)
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	line = (char *)malloc((i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buf[10240];
	char		*line;

	line = 0;
	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buf[fd])
	{
		buf[fd] = (char *)malloc(1);
		if (!buf[fd])
			return (NULL);
		buf[fd][0] = '\0';
	}
	buf[fd] = get_content(fd, buf[fd]);
	if (!buf[fd])
		return (NULL);
	line = get_new_line(buf[fd]);
	buf[fd] = get_reminder(buf[fd]);
	return (line);
}
