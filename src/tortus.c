/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tortus.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 17:41:45 by ggrybova          #+#    #+#             */
/*   Updated: 2017/11/25 17:49:11 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static	double	select_root(t_pol *res)
{
	int			i;
	int			k;
	double		*temp;
	double		t;

	i = 0;
	k = -1;
	while (++k < res->deg)
		if (res->x_im[k] == 0 && res->x_re[k] > 0)
			i++;
	if (i == 0)
		return (-1);
	temp = (double *)malloc(sizeof(double) * i);
	i = -1;
	while (k-- >= 0)
		if (res->x_im[k] == 0 && res->x_re[k] > 0)
			temp[++i] = res->x_re[k];
	t = temp[i];
	while (--i >= 0)
		t = fmin(t, temp[i]);
	return (t);
}

int				torus_inter(t_arr *gl, t_ray *ray, t_obj *tor, int thread)
{
	t_pol		*res;
	t_vec		x;
	t_vec		d;
	double		a[3];
	double		w;

	x = add(ray->org, tor->c, 2);
	create_v(&d, ray->dir->x, ray->dir->y, ray->dir->z);
	norm(&d);
	norm(tor->v);
	a[0] = 1 - pow(dot(tor->v, &d), 2);
	a[1] = 2 * (dot(&x, &d) - dot(tor->v, &x) * dot(tor->v, &d));
	a[2] = dot(&x, &x) - pow(dot(tor->v, &x), 2);
	w = dot(&x, &x) + pow(tor->r, 2) - pow(tor->r2, 2);
	res = polinom_4_degr(4 * dot(&x, &d), 2 * w + 1 / 4.0 * pow(4 *
		dot(&x, &d), 2) - 4 * pow(tor->r, 2) * a[0], 4 * dot(&x, &d) * w - 4 *
		pow(tor->r, 2) * a[1], pow(w, 2) - 4 * pow(tor->r, 2) * a[2]);
	w = select_root(res);
	if (w < 0)
		return (0);
	gl->t[thread] = w;
	return (1);
}
