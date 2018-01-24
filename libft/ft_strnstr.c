/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 19:02:45 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/09 14:14:45 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t l)
{
	size_t i;
	size_t j;
	size_t s;

	s = 0;
	while (to_find[s])
		s++;
	if (s == 0)
		return ((char*)&str[0]);
	i = 0;
	while (i < l && str[i])
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (i + j == l)
				return (0);
			if (j++ == s - 1)
				return ((char*)&str[i]);
		}
		i++;
	}
	return (0);
}
