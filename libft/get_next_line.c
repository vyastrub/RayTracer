/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:23:00 by vyastrub          #+#    #+#             */
/*   Updated: 2017/03/01 14:16:26 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

static int		my_str(char *s, int flag)
{
	int i;

	if (!s)
		return (0);
	if (flag == 1)
	{
		i = 0;
		while (s[i] != '\0')
			i++;
		return (i);
	}
	i = -1;
	while (s[++i])
		if (s[i] == '\n')
		{
			s[i++] = '\0';
			return (i);
		}
	return (0);
}

static char		*unistr(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (my_str(s1, 1) + my_str(s2, 1) + 1));
	if (!str)
		return (0);
	i = -1;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	else
		i = 0;
	j = -1;
	if (s2)
		while (s2[++j] != '\0')
			str[i + j] = s2[j];
	else
		j = 0;
	if (s1)
		free(s1);
	str[i + j] = '\0';
	return (str);
}

static int		proc(int fd, char **line, char **cache)
{
	char	buff[BUFF_SIZE + 1];
	int		i;

	while ((i = read(fd, buff, BUFF_SIZE)))
	{
		if (i < 0)
			return (-1);
		buff[i] = '\0';
		if ((i = my_str(buff, 0)))
		{
			*cache = unistr(*cache, buff);
			*line = unistr(*cache, NULL);
			*cache = (buff[i] ? unistr(NULL, buff + i) : NULL);
			return (1);
		}
		*cache = unistr(*cache, buff);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	int			i;
	static char *cache[7000];
	char		*t;
	char		b[0];

	if (fd < 0 || fd > 7000 || !line || BUFF_SIZE < 1 || BUFF_SIZE > 8000000)
		return (-1);
	if ((i = read(fd, b, 0)) < 0)
		return (-1);
	*line = NULL;
	if ((i = my_str(cache[fd], 0)))
	{
		*line = unistr(*line, cache[fd]);
		t = (cache[fd][i] ? unistr(NULL, cache[fd] + i) : NULL);
		free(cache[fd]);
		cache[fd] = t;
		t = NULL;
		return (1);
	}
	while ((i = proc(fd, line, &cache[fd])))
		if (i != 0)
			return (i > 0 ? 1 : -1);
	*line = unistr(cache[fd], NULL);
	cache[fd] = NULL;
	return (*line ? 1 : 0);
}
