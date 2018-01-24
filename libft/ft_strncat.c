/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 21:20:50 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/01 19:29:58 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *restrict dest, const char *restrict src, size_t n)
{
	size_t i;
	size_t k;

	i = 0;
	while (dest[i])
		i++;
	k = -1;
	while (++k < n && src[k])
		dest[i + k] = src[k];
	dest[i + k] = '\0';
	return (dest);
}
