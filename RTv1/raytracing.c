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

#include "rtv1.h"

static void	setDistance(t_arr *gl, t_current *current, t_obj *obj)
{
	if (current->dt > 1e-4 && gl->t[current->id] >= current->dt)
		return;
    current->obj = obj;
	current->dt = gl->t[current->id];
	current->flag = obj->flag;
	//current->col = obj->color;
	set_col(current->col, obj->color->r, obj->color->g, obj->color->b);
	current->gloss = obj->specular;
	current->i = obj->index;
	current->mirror = obj->reflection;
	current->ref_c = obj->refraction;
    current->normal = obj->normal;
    if (current->cap)
        current->normal = normal_spr_pln;
    current->cap = 0;
}

void detection(t_arr *gl, t_ray *ray, t_current **cur, int ind)
{
	int i;

	i = -1;
    while (++i < gl->total)
        if(gl->all_obj[i]->intersect(gl, ray, gl->all_obj[i], cur[ind]->id))
            if (gl->t[cur[ind]->id] > 1e-4)
                setDistance(gl, cur[ind], gl->all_obj[i]);
}

static int	inshadow(t_arr *gl, t_obj **all, t_current *cur, double dist)
{
	int i;

    i = -1;
    while (++i < gl->total)
        if (all[i]->intersect(gl, cur->bck, all[i], cur->id))
            if (gl->t[cur->id] > 0 && gl->t[cur->id] < dist)
                if (all[i]->refraction <= 1)
                    return (1);
    return (0);
}

void	render(t_arr *gl, t_current *cur, t_lsrc *src)
{
	t_vec	tmp;
	double	dist;

    tmp = mul(&cur->n, BIAS, 1);
    tmp = add(&cur->p, &tmp, 1);
    //tmp = add(&cur->p, &cur->n, 1);
	create_v(cur->bck->org, tmp.x, tmp.y, tmp.z);
	tmp = add(src->lgt, &cur->p, 2);
	dist = sqrt(dot(&tmp, &tmp));
	create_v(cur->bck->dir, tmp.x, tmp.y, tmp.z);
	norm(cur->bck->dir);
	src->lamb = 0;
	src->fong = 0;
	if (!(inshadow(gl, gl->all_obj, cur, dist)))
	{
		light(cur, src);
		src->lamb /= gl->lights;
		if (src->lamb < 0)
			src->lamb = 0;
		if (src->lamb > 1.0)
			src->lamb = 1.0;
	}
}

static void tracing(t_arr *gl, t_current **cur, int x, pthrData *data)
{
	int i;

	gl->iter[data->id] = 0;
	cur[0]->flag = 0;
	cur[0]->dt = 0;
	create_v(cur[0]->ray->dir, gl->res[data->y][x].x, gl->res[data->y][x].y, gl->res[data->y][x].z);
	write_sub(cur[0]->ray->dir, cur[0]->ray->dir, cur[0]->ray->org);
	norm(cur[0]->ray->dir);
	detection(gl, cur[0]->ray, cur, gl->iter[data->id]);
	if (cur[0]->flag)
	{
		universal(gl, cur, gl->iter[data->id]);
		i = -1;
		while (++i < gl->lights)
			render(gl, cur[gl->iter[data->id]], gl->src[data->id][i]);
		create_img(gl, x, data->y, (getcol(gl, cur[gl->iter[data->id]]->col, cur[0])));
	}
	else
		create_img(gl, x, data->y, BCKG);
}

void		*raytrace(void* thread_data)
{
	int x;
	pthrData *data;

    data = (pthrData*) thread_data;
	while (++data->y < data->max_y)
	{
		x = -1;
		while (++x < W)
			tracing(data->gl, data->cur, x, data);
	}
    //pthread_exit(NULL);
    return (0);
}

void		make_pthreads(t_arr *gl)
{
	int k;
	pthread_t   *threads; //выделяем память под массив идентификаторов потоков
	pthrData    *threadData; //сколько потоков - столько и структур с потоковых данных
	
	threads = (pthread_t*)malloc(THREADS * sizeof(pthread_t));
	threadData = (pthrData*)malloc(THREADS * sizeof(pthrData));
	k = -1;
	while (++k < THREADS)//инициализируем структуры потоков
	{
	    threadData[k].y = H * k / THREADS - 1;
	    threadData[k].max_y = H * (k + 1) / THREADS;
	    threadData[k].gl = gl;
        threadData[k].id = k;
        threadData[k].cur = gl->cur[k];
	    pthread_create(&(threads[k]), NULL, raytrace, &threadData[k]);
	}
	k = -1;
    while (++k < THREADS)//ожидаем выполнение всех потоков
		pthread_join(threads[k], NULL);
	free(threads);//освобождаем память
	free(threadData);
}
