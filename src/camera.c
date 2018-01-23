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

void    to_arr(t_arr *gl)
{
    int x;
    int y;

    gl->cam.x_a = 0;
    gl->cam.y_a = 0;
    gl->cam.z_a = 0;
    gl->cam.x_a = 0;
    gl->cam.y_a = 0;
    gl->cam.z_a = 0;
    y = -1;
    while (++y < H)
    {
        x = -1;
        while (++x < W)
        {
            gl->arr[y][x].x = (2 * (x + gl->screen.x + 0.5) / W - 1) *
                    tan(M_PI / 6);
            gl->arr[y][x].y = (1 - 2 * (y + gl->screen.y + 0.5) / H ) *
                    tan(M_PI / 6);
            gl->arr[y][x].z = gl->screen.z;
        }
    }
}

void    cr_res(t_arr *gl, double m1[4][4], double m2[4][4])
{
    double  tmp;
    int     i;
    int     j;
    int     c;

    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
        {
            tmp = 0;
            c = -1;
            while (++c < 4)
                tmp += m1[i][c] * m2[c][j];
            gl->cam.res[i][j] = tmp;
        }
    }
}

void    multiple(t_arr *gl, t_cam cam, int i, int j)
{
    while (++i < H)
    {
        j = -1;
        while (++j < W)
        {
            gl->res[i][j].x = ((cam.res[0][0] * gl->arr[i][j].x) +
                (cam.res[0][1] * gl->arr[i][j].y) + (cam.res[0][2] *
                    gl->arr[i][j].z) + cam.res[0][3]);
            gl->res[i][j].y = ((cam.res[1][0] * gl->arr[i][j].x) +
                (cam.res[1][1] * gl->arr[i][j].y) + (cam.res[1][2] *
                    gl->arr[i][j].z) + cam.res[1][3]);
            gl->res[i][j].z = ((cam.res[2][0] * gl->arr[i][j].x) +
                (cam.res[2][1] * gl->arr[i][j].y) + (cam.res[2][2] *
                    gl->arr[i][j].z) + cam.res[2][3]);
        }
    }
    i = -1;
    while (++i < THREADS)
    {
        gl->cur[i][0]->ray->org->x = ((cam.res[0][0] * gl->eye.x) + (cam.res[0][1]
            * gl->eye.y) + (cam.res[0][2] * gl->eye.z) + cam.res[0][3]);
        gl->cur[i][0]->ray->org->y = ((cam.res[1][0] * gl->eye.x) + (cam.res[1][1]
            * gl->eye.y) + (cam.res[1][2] * gl->eye.z) + cam.res[1][3]);
        gl->cur[i][0]->ray->org->z = ((cam.res[2][0] * gl->eye.x) + (cam.res[2][1]
            * gl->eye.y) + (cam.res[2][2] * gl->eye.z) + cam.res[2][3]);
    }
}
