/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 18:11:30 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/08 10:38:37 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	x;
	unsigned char	*str;

	x = (unsigned char)c;
	str = (unsigned char *)s;
	i = 0;
	if (!n)
		return (0);
	while (n-- > 0)
		if (str[i++] == x)
			return ((void *)(s + i - 1));
	return (0);
}
