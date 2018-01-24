/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 12:54:05 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/06 15:21:17 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		j;
	int		x;

	if (!s)
		return (0);
	i = 0;
	j = 0;
	while (s[i] != '\0')
		i++;
	while (s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t')
		i--;
	while ((s[j] == ' ' || s[j] == '\n' || s[j] == '\t') && j < i)
		j++;
	str = (char *)malloc(sizeof(char) * (i - j + 1));
	if (!str)
		return (0);
	x = 0;
	while (j < i)
		str[x++] = s[j++];
	str[x] = '\0';
	return (str);
}
