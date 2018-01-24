/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 19:02:45 by vyastrub          #+#    #+#             */
/*   Updated: 2016/11/29 10:21:13 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int j;
	int s;

	i = 0;
	s = 0;
	while (to_find[s])
		s++;
	if (s == 0)
		return ((char*)&str[i]);
	while (str[i])
	{
		j = 0;
		while (to_find[j] == str[i + j])
			if (j++ == s - 1)
				return ((char*)&str[i]);
		i++;
	}
	return (0);
}
