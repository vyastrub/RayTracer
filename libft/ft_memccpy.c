/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 13:31:07 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/07 12:52:57 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*src;
	unsigned char	smb;

	i = 0;
	dst = (unsigned char*)d;
	src = (unsigned char*)s;
	smb = (unsigned char)c;
	if (n == 0)
		return (0);
	while (n-- > 0)
	{
		dst[i] = src[i];
		if (src[i] == smb)
			return (&d[i + 1]);
		i++;
	}
	return (0);
}
