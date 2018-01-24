/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 16:50:39 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/08 17:08:16 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *tmp;

	tmp = (t_list *)malloc(sizeof(t_list) * content_size);
	if (!tmp)
		return (0);
	if (content)
	{
		tmp->content = malloc(content_size);
		if (!tmp->content)
			return (0);
		ft_memmove(tmp->content, content, content_size);
		tmp->content_size = content_size;
	}
	else
	{
		tmp->content = 0;
		tmp->content_size = 0;
	}
	tmp->next = 0;
	return (tmp);
}
