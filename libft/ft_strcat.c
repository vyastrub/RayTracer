/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 13:20:50 by vyastrub          #+#    #+#             */
/*   Updated: 2016/11/29 11:08:15 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *restrict dest, char *restrict src)
{
	int i;
	int k;

	i = 0;
	while (dest[i])
		i++;
	k = -1;
	while (src[++k])
		dest[i + k] = src[k];
	dest[i + k] = '\0';
	return (dest);
}
