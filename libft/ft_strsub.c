/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 12:05:27 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/05 12:19:16 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	b;

	if (!s)
		return (0);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i = -1;
	b = (size_t)start;
	while (++i < len)
		str[i] = s[i + b];
	str[i] = '\0';
	return (str);
}
