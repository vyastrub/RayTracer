/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:02:11 by ggrybova          #+#    #+#             */
/*   Updated: 2017/12/09 16:02:13 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double		caps(t_ray *ray, t_obj *obj)
{
	t_vec	oc;
	double	t;
	double	t2;
	t_vec	p;
	t_vec	tmp;

	oc = add(obj->c2, ray->org, 2);
	t2 = dot(&oc, obj->v) / dot(ray->dir, obj->v);
	p = mul(ray->dir, t2, 1);
	p = add(ray->org, &p, 1);
	tmp = add(&p, obj->c2, 2);
	t2 = (t2 > 0 && dot(&tmp, &tmp) < pow(obj->r, 2)) ? t2 : -1;
	if (obj->k != 0)
		return (t2);
	oc = add(obj->c, ray->org, 2);
	t = dot(&oc, obj->v) / dot(ray->dir, obj->v);
	p = mul(ray->dir, t, 1);
	p = add(ray->org, &p, 1);
	tmp = add(&p, obj->c, 2);
	t = (t > 0 && dot(&tmp, &tmp) < pow(obj->r, 2)) ? t : -1;
	if (t > 0 && t2 < 0)
		return (t);
	if (t < 0 && t2 > 0)
		return (t2);
	return (fmin(t, t2));
}

double		find_t(double t, t_ray *ray, t_obj *obj)
{
	t_vec	p1;
	t_vec	tmp1;
	t_vec	tmp2;

	p1 = mul(ray->dir, t, 1);
	p1 = add(ray->org, &p1, 1);
	tmp1 = add(&p1, obj->c, 2);
	tmp2 = add(&p1, obj->c2, 2);
	norm(&tmp1);
	norm(&tmp2);
	if (!(t > 0 && dot(obj->v, &tmp1) > 0 && dot(obj->v, &tmp2) < 0))
		t = -1;
	return (t);
}

void		limit_obj(t_arr *gl, t_ray *ray, t_obj *obj, int i)
{
	t_vec	p;

	p = mul(obj->v, obj->h, 1);
	p = add(obj->c, &p, 1);
	create_v(obj->c2, p.x, p.y, p.z);
	if (gl->t[i] > 0)
		gl->t[i] = find_t(gl->t[i], ray, obj);
	if (gl->t2[i] > 0)
		gl->t2[i] = find_t(gl->t2[i], ray, obj);
	gl->t[i] = (gl->t[i] > 0 && gl->t2[i] > 0) ? fmin(gl->t[i], gl->t2[i])
		: gl->t[i];
	gl->t[i] = (gl->t[i] < 0 && gl->t2[i] > 0) ? gl->t2[i] : gl->t[i];
	if (obj->cap > 0)
	{
		gl->t2[i] = caps(ray, obj);
		if ((gl->t[i] > 0 && gl->t[i] > gl->t2[i] &&
                gl->t2[i] > 0) || (gl->t[i] < 0 && gl->t2[i] > 0))
		{
			gl->t[i] = gl->t2[i];
            gl->cur[i][gl->iter[i]]->cap = 1;
		}
	}
}

int			cylin_inter(t_arr *gl, t_ray *ray, t_obj *box, int thread)
{
	t_vec	oc;
	double	a[3];

	oc = add(ray->org, box->c, 2);
	norm(box->v);
	a[0] = dot(ray->dir, ray->dir) - pow(dot(ray->dir, box->v), 2);
    a[1] = 2 * (dot(ray->dir, &oc) - dot(ray->dir, box->v) *
		dot(&oc, box->v));
    a[2] = dot(&oc, &oc) - pow(dot(&oc, box->v), 2) - (box->r * box->r);
	if (box->h > 0 && disc(gl, a, thread) > 0)
	{
		limit_obj(gl, ray, box, thread);
		return (1);
	}
	return (disc(gl, a, thread));
}

int			conus_inter(t_arr *gl, t_ray *ray, t_obj *con, int thread)
{
	t_vec	oc;
	double	a[3];

	oc = add(ray->org, con->c, 2);
	norm(con->v);
	a[0] = dot(ray->dir, ray->dir) - (1 + (con->k * con->k)) *
		dot(ray->dir, con->v) * dot(ray->dir, con->v);
    a[1] = 2 * (dot(ray->dir, &oc) - (1 + (con->k * con->k)) *
		dot(ray->dir, con->v) * dot(&oc, con->v));
    a[2] = dot(&oc, &oc) - (1 + con->k * con->k) * pow(dot(&oc, con->v), 2);
	if (con->h > 0 && disc(gl, a, thread) > 0)
	{
		limit_obj(gl, ray, con, thread);
		return (1);
	}
	return (disc(gl, a, thread));
}
