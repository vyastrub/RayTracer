/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 14:42:19 by ggrybova          #+#    #+#             */
/*   Updated: 2017/12/20 14:42:23 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

char		*cut_str(char *str, char c)
{
	while (*str != c && *str != '\0')
		str++;
	if (*str != '\0')
		str++;
	return (str);
}

double		ration_n(char *a)
{
	double	n;
	int		i;
	int		k;
	char	sign;

	i = 0;
	k = 0;
	sign = 0;
	if (a[i] == '-')
		sign = 1;
	while (a[i] != ',' && a[i] != '.' && a[i] != '\n' &&
			a[i] != '\0' && a[i] != ' ')
		i++;
	if (a[i] != '.')
		n = abs(ft_atoi(a));
	else
	{
		while (a[++i] != ',' && a[i] != '\n' && a[i] != '\0' && a[i] != ' ')
			k++;
		n = abs(ft_atoi(a)) + abs(ft_atoi(cut_str(a, '.'))) / pow(10, k);
	}
	if (sign == 1)
		return (-n);
	return (n);
}
