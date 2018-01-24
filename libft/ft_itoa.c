/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 09:58:09 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/06 15:30:33 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	count(int n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*copy(char *str, int n, int size)
{
	int i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	str[size] = '\0';
	while (n > 0)
	{
		str[--size] = n % 10 + 48;
		n = n / 10;
	}
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;

	if (n == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		if (!str)
			return (0);
		ft_strcpy(str, "0");
		return (str);
	}
	else if (n == -2147483648)
	{
		str = (char *)malloc(sizeof(char) * 12);
		if (!str)
			return (0);
		ft_strcpy(str, "-2147483648");
		return (str);
	}
	i = count(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	return (copy(str, n, i));
}
