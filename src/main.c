/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <vyastrub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 20:07:59 by vyastrub          #+#    #+#             */
/*   Updated: 2017/10/29 07:19:52 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static int		ft_hook(int kc, t_arr *gl)
{
	(kc == 53 ? exit(1) : 0);

    (kc == 14 ? gl->cam.x_a += 5 : 0);
    (kc == 6 ? gl->cam.x_a -= 5 : 0);
    (kc == 2 ? gl->cam.y_a += 5 : 0);
    (kc == 0 ? gl->cam.y_a -= 5 : 0);
    (kc == 7 ? gl->cam.z_a += 5 : 0);
    (kc == 13 ? gl->cam.z_a -= 5 : 0);
    (kc == 124 ? gl->cam.x_t += 10 : 0);
    (kc == 123 ? gl->cam.x_t -= 10 : 0);
    (kc == 126 ? gl->cam.y_t += 10 : 0);
    (kc == 125 ? gl->cam.y_t -= 10 : 0);
    (kc == 78 ? gl->cam.z_t += 10 : 0);
    (kc == 69 ? gl->cam.z_t -= 10 : 0);
    (kc == 18 ? gl->uv = -gl->uv : 0);
    (kc == 19 ? gl->grey = -gl->grey : 0);
	mlx_clear_window(gl->mlx, gl->win);
	mmul(gl);
	make_pthreads(gl);
	mlx_put_image_to_window(gl->mlx, gl->win, gl->img, 0, 0);
	return (0);
}

void			ft_error(int flag)
{
	if (flag == 1)
		ft_putstr("Not correct input file.\nPlease, correct data and try again!\n");
	if (flag == 2)
		write(1, "Usage : ./RTv1 <scene_file>\n", 28);
	exit(0);
}


void			create_img(t_arr *gl, int x, int y, int col)
{
	int				bpp;
	int				szl;
	int				end;
	char			*image;
	unsigned int	c;

	image = mlx_get_data_addr(gl->img, &bpp, &szl, &end);
	c = mlx_get_color_value(gl->mlx, col);
	if (x >= 0 && x < W && y >= 0 && y < H)
		ft_memcpy((void *)(image + szl * y + x * sizeof(int)), (void *)&c, 4);
}

static char				*read_file(char *file)
{
    char			*s;
    char			*l;
    char			buf[10 + 1];
    int				fd;

    s = ft_strnew(0);
    if ((fd = open(file, O_RDONLY)) < 0 || read(fd, buf, 0) < 0 || !s)
    {
        ft_putstr("Cannot open file\n");
        exit(0);
    }
    ft_bzero(buf, 10 + 1);
    while (read(fd, buf, 10) > 0)
    {
        l = ft_strjoin(s, buf);
        free(s);
        s = ft_strdup(l);
        free(l);
        ft_bzero(buf, 10 + 1);
    }
    close(fd);
    return (s);
}


int					main(int ac, char **av)
{
	t_arr			*gl;
	ini_t			*ini;
    char    *s;

	(ac != 2 ? ft_error(2) : 0);
	gl = (t_arr*)malloc(sizeof(t_arr));
    s =read_file(av[1]);
	ini = ini_load(s, 0);
	gl->total = ini_section_count(ini) - 3;
	gl->all_obj = (t_obj **)malloc(sizeof(t_obj) * gl->total);
	parsing(gl, ini);
    to_arr(gl);
    mmul(gl);
	//raytrace(gl, -1, -1, 0);
	make_pthreads(gl);
	mlx_put_image_to_window(gl->mlx, gl->win, gl->img, 0, 0);
	mlx_key_hook(gl->win, ft_hook, gl);
	mlx_loop(gl->mlx);
    pthread_exit(NULL);
	return (0);
}
