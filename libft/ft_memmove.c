/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 13:31:07 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/01 19:18:47 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	i;
	char	*d;
	char	*s;

	d = (char*)dest;
	s = (char*)src;
	i = -1;
	if (s > d)
		while (++i < len)
			d[i] = s[i];
	else
		while (++i != len)
			d[len - i - 1] = s[len - i - 1];
	return (dest);
}
