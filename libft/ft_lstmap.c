/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 12:37:05 by vyastrub          #+#    #+#             */
/*   Updated: 2016/12/09 13:49:38 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*begin;

	if (!(lst && f))
		return (0);
	tmp = f(lst);
	begin = tmp;
	lst = lst->next;
	while (lst)
	{
		tmp->next = f(lst);
		lst = lst->next;
		tmp = tmp->next;
	}
	return (begin);
}
