/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <vyastrub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 19:34:05 by vyastrub          #+#    #+#             */
/*   Updated: 2017/10/29 05:03:19 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int	disc(t_arr *gl, double a[3], int thread)
{
	double d;

	d = a[1] * a[1] - 4 * a[0] * a[2];
	if (d < 1e-4)
		return (0);
	d = sqrt(d);
	if (a[2] > 0)
	{
		gl->t[thread] = ((-a[1] - d) / (2 * a[0]));
		gl->t2[thread] = ((-a[1] + d) / (2 * a[0]));
	}
	else
	{
		gl->t[thread] = ((-a[1] + d) / (2 * a[0]));
		gl->t2[thread] = ((-a[1] - d) / (2 * a[0]));
	}
	return (1);
}

int			plane_inter(t_arr *gl, t_ray *ray, t_obj *pln, int thread)
{
	t_vec	oc;
	double	a;
	double	b;

	if (pln->v->z < 0)
		pln->v->z = -pln->v->z;
	norm(pln->v);
	oc = add(pln->c, ray->org, 2);
	a = dot(&oc, pln->v);
	b = dot(ray->dir, pln->v);
	if (b == 0)
		return (0);
	gl->t[thread] = a / b;
	if (gl->t[thread] < 0)
		return (0);
	return (1);
}

int			spher_inter(t_arr *gl, t_ray *ray, t_obj *spr, int thread)
{
	t_vec	oc;
	double	a[3];

	oc = add(ray->org, spr->c, 2);
	a[0] = dot(ray->dir, ray->dir);
	a[1] = 2 * dot(ray->dir, &oc);
	a[2] = dot(&oc, &oc) - (spr->r * spr->r);
	return (disc(gl, a, thread));
}

int			disk_inter(t_arr *gl, t_ray *ray, t_obj *dsk, int thread)
{
	t_vec	oc;
	double	a;
	double	b;
	t_vec	p;
	t_vec	tmp;

	if (dsk->v->z < 0)
		dsk->v->z = -dsk->v->z;
	norm(dsk->v);
	oc = add(dsk->c, ray->org, 2);
	a = dot(&oc, dsk->v);
	b = dot(ray->dir, dsk->v);
	if (b == 0)
		return (0);
	gl->t[thread] = a / b;
	if (gl->t[thread] < 0)
		return (0);
	tmp = mul(ray->dir, gl->t[thread], 1);
	p = add(ray->org, &tmp, 1);
	oc = add(&p, dsk->c, 2);
	a = sqrt(dot(&oc, &oc));
	if (a > dsk->r)
		return (0);
	return (1);
}
