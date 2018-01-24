/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 15:53:40 by vyastrub          #+#    #+#             */
/*   Updated: 2016/11/28 19:06:52 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	char *d;

	d = dest;
	while (len > 0 && *src)
	{
		*d++ = *src++;
		--len;
	}
	while (len-- > 0)
		*d++ = '\0';
	return (dest);
}
