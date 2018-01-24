/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 21:20:50 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/01 19:30:42 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t		ft_strlcat(char *restrict dest, const char *restrict src, size_t n)
{
	size_t i;
	size_t j;
	size_t l;

	i = -1;
	while (dest[++i] && n > 0)
		n--;
	l = 0;
	while (src[l])
		l++;
	if (n-- < 2)
		return (i + l);
	j = -1;
	while (src[++j] && n-- > 0)
		dest[i + j] = src[j];
	dest[i + j] = '\0';
	return (i + l);
}
