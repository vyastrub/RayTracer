/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 12:10:27 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/09 13:25:09 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*s;
	size_t	i;

	s = malloc(size + 1);
	if (!s)
		return (0);
	i = 0;
	while (i < size)
		s[i++] = 0;
	s[i] = '\0';
	return (s);
}
