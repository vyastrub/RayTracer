/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 12:21:53 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/09 15:54:48 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		*ft_range(int min, int max)
{
	int	i;
	int *a;

	if (min >= max)
		return (0);
	i = max - min;
	a = (int*)malloc(sizeof(*a) * i);
	if (!a)
		return (0);
	i = 0;
	while (min < max)
		a[i++] = min++;
	return (a);
}
