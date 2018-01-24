/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:11:44 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/06 15:20:02 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	str = (char*)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	i = -1;
	while (s[++i])
		str[i] = f(s[i]);
	str[i] = '\0';
	return (str);
}
