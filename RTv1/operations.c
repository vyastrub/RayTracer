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

#include "rtv1.h"

t_vec	add(t_vec *a, t_vec *b, int flag)
{
	t_vec tmp;

	tmp.x = (flag == 1 ? a->x + b->x : a->x - b->x);
	tmp.y = (flag == 1 ? a->y + b->y : a->y - b->y);
	tmp.z = (flag == 1 ? a->z + b->z : a->z - b->z);
	return (tmp);
}

t_vec	mul(t_vec *a, double d, int flag)
{
	t_vec tmp;

	tmp.x = (flag == 1 ? a->x * d : a->x / d);
	tmp.y = (flag == 1 ? a->y * d : a->y / d);
	tmp.z = (flag == 1 ? a->z * d : a->z / d);
	return (tmp);
}

void write_sum(t_vec *dest, t_vec *src1, t_vec *src2)
{
    dest->x = src1->x + src2->x;
    dest->y = src1->y + src2->y;
    dest->z = src1->z + src2->z;
}

void write_sub(t_vec *dest, t_vec *src1, t_vec *src2)
{
    dest->x = src1->x - src2->x;
    dest->y = src1->y - src2->y;
    dest->z = src1->z - src2->z;
}

void write_mul(t_vec *dest, t_vec *src1, double a)
{
    dest->x = src1->x * a;
    dest->y = src1->y * a;
    dest->z = src1->z * a;
}
