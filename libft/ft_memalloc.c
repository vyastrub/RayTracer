/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 12:10:27 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/06 15:24:39 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*s;
	size_t	i;

	i = 0;
	if (!size)
		return (0);
	s = malloc(size);
	if (!s)
		return (0);
	while (i < size)
		*((unsigned char*)(s + i++)) = 0;
	return (s);
}
