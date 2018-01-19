/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <vyastrub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 06:59:00 by vyastrub          #+#    #+#             */
/*   Updated: 2017/10/29 07:10:47 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray		*new_ray(void)
{
	t_ray	*ray;

	ray = (t_ray*)malloc(sizeof(t_ray));
	ray->org = (t_vec*)malloc(sizeof(t_vec));
	ray->dir = (t_vec*)malloc(sizeof(t_vec));
	return (ray);
}

void		init(t_arr *gl)
{
	int i;
	int j;
	
	gl->mlx = mlx_init();
	gl->win = mlx_new_window(gl->mlx, W, H, gl->scene_name);
	gl->img = mlx_new_image(gl->mlx, W, H);
    gl->cur = (t_current***)malloc(sizeof(t_current**) * THREADS);
    j = -1;
	while (++j < THREADS)
	{
		gl->cur[j] = (t_current**)malloc(sizeof(t_current*) * DEPTH + 1);
		i = -1;
		while (++i <= DEPTH)
		{
			gl->cur[j][i] = (t_current *) malloc(sizeof(t_current));
			gl->cur[j][i]->ray = new_ray();
			gl->cur[j][i]->bck = new_ray();
			gl->cur[j][i]->i = 0;
			gl->cur[j][i]->id = j;
			gl->cur[j][i]->flag = 0;
            gl->cur[j][i]->cap = 0;
			gl->cur[j][i]->col = (t_col*)malloc(sizeof(t_col));
    	    set_col(gl->cur[j][i]->col, 0, 0, 0);
		}
		gl->t[j] = 0;
        gl->t2[j] = 0;
	}
	gl->lights = 0;
	gl->planes = 0;
	gl->spheres = 0;
	gl->cylindres = 0;
	gl->cones = 0;
	gl->tores = 0;
	gl->disks = 0;
	gl->parab = 0;
}

t_obj		*fill_obj(int fl, int i, int (*in)(), void (*n)())
{
	t_obj	*obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	obj->c = (t_vec*)malloc(sizeof(t_vec));
	obj->c2 = (t_vec*)malloc(sizeof(t_vec));
	obj->v = (t_vec*)malloc(sizeof(t_vec));
	obj->r = 0;
	obj->r2 = 0;
	obj->k = 0;
	obj->h = 0;
	obj->cap = 0;
	obj->index = i;
	obj->color = (t_col*)malloc(sizeof(t_col));
	obj->flag = fl;
	obj->diffuse = 0;
	obj->specular = 0;
	obj->reflection = 0;
	obj->refraction = 0;
	obj->intersect = in;
	obj->normal = n;
	return (obj);
}

t_obj		**new_obj(int c, t_arr *gl, int fl)
{
	t_obj	**obj;
	int		i;

	i = -1;
	obj = (t_obj **)malloc(sizeof(t_obj *) * c);
	while (++i < c)
	{
		if (fl == 1)
			obj[i] = fill_obj(fl, i, plane_inter, normal_spr_pln);
		else if (fl == 2)
			obj[i] = fill_obj(fl, i, spher_inter, normal_spr_pln);
		else if (fl == 3)
			obj[i] = fill_obj(fl, i, cylin_inter, normal_con_cyl);
		else if (fl == 4)
			obj[i] = fill_obj(fl, i, conus_inter, normal_con_cyl);
		else if (fl == 5)
			obj[i] = fill_obj(fl, i, torus_inter, normal_tor);
		else if (fl == 6)
			obj[i] = fill_obj(fl, i, disk_inter, normal_spr_pln);
		else if (fl == 7)
            obj[i] = fill_obj(fl, i, parab_inter, normal_prb);
	}
    gl->amb = 0;
	return (obj);
}

void		print_obj(t_obj *obj)
{
	if (obj->flag == 1)
		printf("--plane[%d]-------\n", obj->index);
	if (obj->flag == 2)
		printf("--sphere[%d]-------\n", obj->index);
	if (obj->flag == 3)
		printf("--cylinder[%d]-------\n", obj->index);
	if (obj->flag == 4)
		printf("--cone[%d]-------\n", obj->index);
	if (obj->flag == 5)
		printf("--torus[%d]-------\n", obj->index);
	if (obj->flag == 6)
		printf("--disk[%d]-------\n", obj->index);
	printf("c  \t%f, %f, %f\n", obj->c->x, obj->c->y, obj->c->z);
	printf("dir\t%f, %f, %f\n", obj->v->x, obj->v->y, obj->v->z);
	printf("r_1\t%f\n", obj->r);
	printf("r_2\t%f\n", obj->r2);
	printf("h\t%f\n", obj->h);
	printf("k\t%f\n", obj->k);
	printf("cap\t%d\n", obj->cap);
	printf("col\t%d, %d, %d\n", obj->color->r, obj->color->g, obj->color->b);
	printf("diff\t%f\n", obj->diffuse);
	printf("spec\t%f\n", obj->specular);
	printf("refl\t%f\n", obj->reflection);
	printf("refr\t%f\n", obj->refraction);
}

