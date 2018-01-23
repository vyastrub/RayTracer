/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <vyastrub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 19:27:48 by vyastrub          #+#    #+#             */
/*   Updated: 2017/10/29 07:10:17 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void	recurtion(t_arr *gl, t_current *src, t_current *cur, int i)
{
    double     n;

    cur->p = mul(cur->ray->dir, cur->dt, 1);
    cur->p = add(cur->ray->org, &cur->p, 1);
    cur->normal(cur);
    if (cur->mirror && gl->iter[cur->id] < DEPTH)
    {
        reflecting(gl, gl->cur[cur->id], ++(gl->iter[cur->id]));
        i = -1;
        while (++i < gl->lights)
            render(gl, gl->cur[cur->id][0], gl->src[cur->id][i]);
        if (gl->iter[cur->id] != 0)
            getcol(gl, gl->cur[cur->id][gl->iter[cur->id]]->col, gl->cur[cur->id][gl->iter[cur->id]]);
    }
    else if (cur->ref_c > 1.0 && gl->iter[cur->id] < DEPTH)
    {
        n = src->n1;
        cur->n1 = src->n2;
        cur->n2 = n;
        if (i > 0 && cur->flag == src->flag && cur->i == src->i)
            cur->n = mul(&cur->n, -1, 1);
        else
            cur->n2 = cur->ref_c;
        refracting(gl, cur, cur, gl->iter[cur->id]);
    }
}

void refracting(t_arr *gl, t_current *src, t_current *cur, int i)
{
	double     n;
	double     c1;
	double     c2;
	t_vec      tmp;

	n = src->n1 / src->n2;
	c1 = dot(src->ray->dir, &src->n);
    c2 = sqrt(1 - pow(n, 2) * (1 - pow(c1, 2)));
    tmp = mul(&src->n, (src->n1 < src->n2 ? -BIAS : BIAS), 1);
    tmp = add(&src->p, &tmp, 1);
    create_v(cur->ray->org, tmp.x, tmp.y, tmp.z);
    tmp = mul(src->ray->dir, n, 1);
    write_mul(cur->ray->dir, &src->n, (n * c1 - c2));
    write_sum(cur->ray->dir, cur->ray->dir, &tmp);
    norm(cur->ray->dir);
    cur->dt = 0;
    cur->flag = 0;
    detection(gl, cur->ray, gl->cur[cur->id], gl->iter[cur->id]);
    if (cur->flag)
        recurtion(gl, src, cur, i);
    else
        gl->iter[cur->id]--;
}

void		reflecting(t_arr *gl, t_current **cur, int i)
{
    t_vec tmp;

    tmp = mul(&cur[i - 1]->n, BIAS, 1);
    tmp = add(&cur[i - 1]->p, &tmp, 1);
	create_v(cur[i]->ray->org, tmp.x, tmp.y, tmp.z);
    //create_v(cur[i]->ray->org, cur[i - 1]->p.x, cur[i - 1]->p.y, cur[i - 1]->p.z);
    write_mul(cur[i]->ray->dir, &(cur[i - 1]->n), 2 * dot(cur[i - 1]->ray->dir, &(cur[i - 1]->n)));
    write_sub(cur[i]->ray->dir, cur[i - 1]->ray->dir, cur[i]->ray->dir);
	norm(cur[i]->ray->dir);
	cur[i]->dt = 0;
	cur[i]->flag = 0;
	detection(gl, cur[i]->ray, cur, gl->iter[cur[i]->id]);
	if (cur[i]->flag)
        universal(gl, cur, i);
	else
		gl->iter[cur[i]->id]--;
}

void        universal(t_arr *gl, t_current **cur, int i)
{
	int 	j;

	cur[i]->p = mul(cur[i]->ray->dir, cur[i]->dt, 1);
	cur[i]->p = add(cur[i]->ray->org, &cur[i]->p, 1);
	cur[i]->normal(cur[i]);
	if (cur[i]->mirror && gl->iter[cur[i]->id] < DEPTH)
	{
		reflecting(gl, cur, ++(gl->iter[cur[i]->id]));
		j = -1;
		while (++j < gl->lights)
			render(gl, cur[0], gl->src[cur[i]->id][j]);
		if (i != 0)
			getcol(gl, cur[gl->iter[cur[i]->id]]->col, cur[i]);
	}
	else if (cur[i]->ref_c > 1.0 && gl->iter[cur[i]->id] + 1 < DEPTH)
	{
        cur[i]->n1 = AIR;//(cur[i]->dt > 1e-4 ? AIR : cur[i - 1]->ref_c);
        cur[i]->n2 = cur[i]->ref_c;
		refracting(gl, cur[i], cur[i + 1], ++gl->iter[cur[i]->id]);
	}
}