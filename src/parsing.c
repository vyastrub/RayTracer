/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 12:25:14 by ggrybova          #+#    #+#             */
/*   Updated: 2017/12/13 12:25:17 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define INI_IMPLEMENTATION
#include "../includes/rtv1.h"

char		*get_data(ini_t *ini, int i, char *name_prop, int prop)
{
	char	*a;
	int		len;

	if (i < 0)
		ft_error(1);
	if (prop == -1)
	{
		len = (int)ft_strlen(name_prop);
		prop = ini_find_property(ini, i, name_prop, len + 1);
		if (prop == -1)
			ft_error(1);
		a = (char*)ini_property_value(ini, i, prop);
		return (a);
	}
	a = (char*)ini_property_value(ini, i, prop);
	return (a);
}

void		create_objects(t_arr *gl, ini_t *ini, int j)
{
	while (--j > 2)
	{
		if (ft_strcmp(ini_property_value(ini, j, 0), "plane\0") == 0)
			gl->planes++;
		else if (ft_strcmp(ini_property_value(ini, j, 0), "sphere\0") == 0)
			gl->spheres++;
		else if (ft_strcmp(ini_property_value(ini, j, 0), "cylinder\0") == 0)
			gl->cylindres++;
		else if (ft_strcmp(ini_property_value(ini, j, 0), "cone\0") == 0)
			gl->cones++;
		else if (ft_strcmp(ini_property_value(ini, j, 0), "torus\0") == 0)
			gl->tores++;
		else if (ft_strcmp(ini_property_value(ini, j, 0), "disk\0") == 0)
			gl->disks++;
		else if (ft_strcmp(ini_property_value(ini, j, 0), "paraboloid\0") == 0)
			gl->parab++;
		else
			ft_error(1);
	}
	gl->pln = new_obj(gl->planes, gl, 1);
	gl->spr = new_obj(gl->spheres, gl, 2);
	gl->box = new_obj(gl->cylindres, gl, 3);
	gl->con = new_obj(gl->cones, gl, 4);
	gl->tor = new_obj(gl->tores, gl, 5);
	gl->dsk = new_obj(gl->disks, gl, 6);
	gl->prb = new_obj(gl->parab, gl, 7);
}

t_obj		*set_obj(t_obj *obj, ini_t *ini, int i)
{
	char *a;
	char *b;
    char *c;
	a = get_data(ini, i, "color", -1);
	set_col(obj->color, ft_atoi(a), ft_atoi(cut_str(a, ',')),
				ft_atoi(cut_str(cut_str(a, ','), ',')));
	b = get_data(ini, i, "centre", -1);
	create_v(obj->c, ration_n(b), ration_n(cut_str(b, ',')),
				ration_n(cut_str(cut_str(b, ','), ',')));
	if (obj->flag != 2 && (c = get_data(ini, i, "direct", -1)) != NULL)
		create_v(obj->v, ration_n(c), ration_n(cut_str(c, ',')),
					ration_n(cut_str(cut_str(c, ','), ',')));
	obj->r = (obj->flag != 1 && obj->flag != 4 && obj->flag != 7) ? ration_n(get_data(ini, i, "radius1", -1)) : 0;
	obj->r2 = (obj->flag == 5 || obj->flag == 7) ? ration_n(get_data(ini, i, "radius2", -1)) : 0;
	if (obj->flag == 3 || obj->flag == 4 || obj->flag == 7)
	{
		obj->h = ration_n(get_data(ini, i, "height", -1));
		obj->cap = ft_atoi(get_data(ini, i, "caps", -1));
		obj->k = (obj->flag == 4) ? ration_n(get_data(ini, i, "angle", -1)) * M_PI / 180 : 0;
        obj->r = (obj->flag == 4) ? obj->r = obj->h * obj->k : obj->r;
	}
	obj->diffuse = ration_n(get_data(ini, i, "diffuse", -1));
	obj->specular = ration_n(get_data(ini, i, "specular", -1));
	obj->reflection = ration_n(get_data(ini, i, "reflection", -1));
	obj->refraction = ration_n(get_data(ini, i, "refraction", -1));
    if (obj->refraction > 1 || obj->reflection >= 1)
        set_col(obj->color, 0, 0, 0);
	return (obj);
}

void		parse_objects(t_arr *gl, ini_t *ini, int n)
{
	int	s;
	int	j[8];

	s = 2;
	ft_memset(j, 0, sizeof(int) * 8);
	create_objects(gl, ini, n);
	while (++s < n)
	{
		if (ft_strcmp(ini_section_name(ini, s), "object") != 0)
			ft_error(1);
		if (ft_strcmp(ini_property_value(ini, s, 0), "plane") == 0)
			gl->all_obj[j[7]++] = set_obj(gl->pln[j[0]++], ini, s);
		else if (ft_strcmp(ini_property_value(ini, s, 0), "sphere") == 0)
			gl->all_obj[j[7]++] = set_obj(gl->spr[j[1]++], ini, s);
		else if (ft_strcmp(ini_property_value(ini, s, 0), "cylinder") == 0)
			gl->all_obj[j[7]++] = set_obj(gl->box[j[2]++], ini, s);
		else if (ft_strcmp(ini_property_value(ini, s, 0), "cone") == 0)
			gl->all_obj[j[7]++] = set_obj(gl->con[j[3]++], ini, s);
		else if (ft_strcmp(ini_property_value(ini, s, 0), "torus") == 0)
			gl->all_obj[j[7]++] = set_obj(gl->tor[j[4]++], ini, s);
		else if (ft_strcmp(ini_property_value(ini, s, 0), "disk") == 0)
			gl->all_obj[j[7]++] = set_obj(gl->dsk[j[5]++], ini, s);
		else if (ft_strcmp(ini_property_value(ini, s, 0), "paraboloid") == 0)
			gl->all_obj[j[7]++] = set_obj(gl->prb[j[6]++], ini, s);
		else
			ft_error(1);
	}
}



void		parsing(t_arr *gl, ini_t *ini)
{
	char	*a;
	char	*b;
	char	*c;
	int		s[3];
	int 	i;


	s[1] = ini_find_section(ini, "scene\0", 6);
	s[2] = ini_find_section(ini, "lights\0", 7);
	gl->scene_name = get_data(ini, s[1], "name", -1);
	init(gl);
	a = get_data(ini, s[1], "cam_orig", -1);
    create_v(&gl->eye, ration_n(a), ration_n(cut_str(a, ',')),
             ration_n(cut_str(cut_str(a, ','), ',')));
    b = get_data(ini, s[1], "cam_dir", -1);
    create_v(&gl->screen, ration_n(b), ration_n(cut_str(b, ',')),
             ration_n(cut_str(cut_str(b, ','), ',')));
	gl->amb = ration_n(get_data(ini, s[1], "ambient", -1));
	gl->lights = ini_property_count(ini, s[2]);
	gl->src = (t_lsrc***)malloc(sizeof(t_lsrc**) * THREADS);
	i = -1;
	while(++i < THREADS)
	{
		gl->src[i] = (t_lsrc**)malloc(sizeof(t_lsrc*) * gl->lights);
        s[0] = -1;
		while (++s[0] < gl->lights && (c = get_data(ini, s[2], 0, s[0])) != NULL)
		{
			gl->src[i][s[0]] = (t_lsrc*)malloc(sizeof(t_lsrc));
			gl->src[i][s[0]]->lgt = (t_vec*)malloc(sizeof(t_vec));
			create_v(gl->src[i][s[0]]->lgt, ration_n(c), ration_n(cut_str(c,
				',')), ration_n(cut_str(cut_str(c, ','), ',')));
		}
	}
	parse_objects(gl, ini, ini_section_count(ini));
}
