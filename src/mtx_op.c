/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 19:45:05 by vyastrub          #+#    #+#             */
/*   Updated: 2017/06/14 19:45:11 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void rotatex(t_arr *gl, double a)
{
	float	arr[4];
	int		i;
	int		j;

	arr[0] = cos(a);
	arr[1] = cos(a);
	arr[2] = 1;
	arr[3] = 1;
	i = 0;
	while (i < 4)
	{
		j = -1;
		while (++j < 4)
			gl->cam.rot_x[i][j] = (i == j ? arr[i] : 0);
		i++;
	}
	gl->cam.rot_x[0][1] = -sin(a);
	gl->cam.rot_x[1][0] = sin(a);
}

static void rotatey(t_arr *gl, double a)
{
	float	arr[4];
	int		i;
	int		j;

	arr[0] = cos(a);
	arr[1] = 1;
	arr[2] = cos(a);
	arr[3] = 1;
	i = 0;
	while (i < 4)
	{
		j = -1;
		while (++j < 4)
			gl->cam.rot_y[i][j] = (i == j ? arr[i] : 0);
		i++;
	}
	gl->cam.rot_y[0][2] = sin(a);
	gl->cam.rot_y[2][0] = -sin(a);
}

static void rotatez(t_arr *gl, double a)
{
	float	arr[4];
	int		i;
	int		j;

	arr[0] = 1;
	arr[1] = cos(a);
	arr[2] = cos(a);
	arr[3] = 1;
	i = 0;
	while (i < 4)
	{
		j = -1;
		while (++j < 4)
			gl->cam.rot_z[i][j] = (i == j ? arr[i] : 0);
		i++;
	}
	gl->cam.rot_z[1][2] = -sin(a);
	gl->cam.rot_z[2][1] = sin(a);
}

static void translate(t_arr *gl, double x, double y, double z)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = -1;
		while (++j < 4)
			gl->cam.trans[i][j] = (i == j ? 1 : 0);
		i++;
	}
	gl->cam.trans[0][3] = x;
	gl->cam.trans[1][3] = y;
	gl->cam.trans[2][3] = z;
}



void			mmul(t_arr *gl)
{
	rotatex(gl, gl->cam.x_a * M_PI / 180);
	rotatey(gl, gl->cam.y_a * M_PI / 180);
	rotatez(gl, gl->cam.z_a * M_PI / 180);
	translate(gl, gl->cam.x_t, gl->cam.y_t, gl->cam.z_t);
	cr_res(gl, gl->cam.rot_x, gl->cam.rot_y);
	cr_res(gl, gl->cam.res, gl->cam.rot_z);
	cr_res(gl, gl->cam.res, gl->cam.trans);
	multiple(gl, gl->cam, -1, -1);
}