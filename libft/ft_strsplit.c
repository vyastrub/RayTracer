/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <vyastrub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 13:17:13 by vyastrub          #+#    #+#             */
/*   Updated: 2017/09/26 11:29:34 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count(char const *str, char c, int i, int w)
{
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			w++;
		while (str[i] != '\0' && str[i] != c)
			i++;
	}
	return (w);
}

static char	*copy(char const *str, char c, int i, int j)
{
	char	*temp;
	int		l;

	l = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	temp = (char*)malloc(sizeof(char) * (i - j + 1));
	while (str[j] != '\0' && str[j] != c)
		temp[l++] = str[j++];
	temp[l] = '\0';
	return (temp);
}

char		**my_split(char const *str, char c)
{
	int		w;
	int		i;
	int		j;
	char	**arr;

	w = count(str, c, 0, 0);
	arr = (char**)malloc(sizeof(char*) * (w + 1));
	i = 0;
	j = 0;
	while (str[j] && i < w)
	{
		while (str[j] == c)
			++j;
		arr[i++] = copy(str, c, j, j);
		while (str[j] != '\0' && str[j] != c)
			j++;
	}
	arr[i] = 0;
	return (arr);
}
