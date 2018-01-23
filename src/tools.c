/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <vyastrub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 20:09:25 by vyastrub          #+#    #+#             */
/*   Updated: 2017/10/28 20:15:02 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double	dot(t_vec *a, t_vec *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

void	norm(t_vec *a)
{
	double	mg;

	mg = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
	a->x = a->x / mg;
	a->y = a->y / mg;
	a->z = a->z / mg;
}

void	create_v(t_vec *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void		set_col(t_col *c, int r, int g, int b)
{
    c->r = r;
    c->g = g;
    c->b = b;
    c->arr[0] = b;
    c->arr[1] = g;
    c->arr[2] = r;
}
