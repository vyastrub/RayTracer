/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyastrub <vyastrub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 12:28:56 by vyastrub          #+#    #+#             */
/*   Updated: 2017/10/29 07:11:07 by vyastrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibX/mlx.h"
# include "ini.h"
# include "../libft/libft.h"
# include <pthread.h>

# define W 1000
# define H 1000
# define DEPTH 7
# define AIR 1
# define BIAS 0.00001
# define BCKG 0x000000
# define AMBI 0.0001
# define THREADS 16


typedef	struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

typedef	struct	s_col
{
	int			r;
	int			g;
	int			b;
	int			arr[3];
}				t_col;

typedef struct	s_ray // структура луча
{
	t_vec		*org;
	t_vec		*dir;
}				t_ray;


typedef struct	s_pol
{
   int         deg;
   double      S;
   double      p;
   double      q;
   double      r;
   double      f;
   double      x_im[4];
   double      x_re[4];
}                t_pol;

typedef struct	s_cam
{
	int			x_a;
	int			y_a;
	int			z_a;
	double		x_t;
	double		y_t;
	double		z_t;
	double		trans[4][4];
	double		rot_x[4][4];
	double		rot_y[4][4];
	double		rot_z[4][4];
	double		res[4][4];
}				t_cam;

typedef struct	s_lsrc  //структура источника света 
{
	t_vec		*lgt;
	double		lamb;
	double		fong;
	double		ambi;

}				t_lsrc;

typedef struct	s_obj // структура обьекта
{
	t_vec		*c;				//object_centre 
	t_vec		*c2;
	t_vec		*v;				//direction
	t_col		*color;			//color =)

	double		r;				//radius
	double		r2;				//radius of torus 	
	double		k;				//angle (conus)
	double		h;
	int 		cap;
	double		specular;		//glossy - 1.0; mate 0.0;
	double		diffuse;		//unused !!!!!!!!!!!!!!!!!!!!!!!!!!!!  
	int			flag;			//object_type_identyfier
	//int			total;			//total_quantity_of this type
	int			index;			//index of obect of this type
	double		reflection;
	double		refraction;
	int			(*intersect)();	//pointer to intersection function of its type
	void		(*normal)();	//find normal vector in current and write in struct.
}				t_obj;

typedef struct	s_current //структура текущих параметров пикселя для итерации
{
	t_obj		*obj;
	t_col		*col;
	
	double		dt;
	double		gloss;
    double      ref_c;
    double      n1;
    double      n2;
	int			flag;
	int			i;
    int			id;
	int 		mirror;
	int 		cap;
	t_vec		p;
	t_vec		n;
	t_ray		*ray;
	t_ray		*bck;
	void		(*normal)();

}				t_current;

typedef	struct	s_arr
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*scene_name;

	t_current	***cur;
	t_cam		cam;
	t_lsrc		***src;
	double		amb;

	t_obj		**all_obj;
	t_obj		**spr;
	t_obj		**pln;
	t_obj		**box;
	t_obj		**con;
	t_obj		**tor;
	t_obj		**dsk;
	t_obj 		**prb;
	t_vec 		arr[H][W];
	t_vec 		res[H][W];
	t_vec		eye;
    t_vec       screen;

    int 		uv;
    int 		grey;
	int			total;
	int			lights;
	int			planes;
	int			spheres;
	int			cylindres;
	int			cones;
	int			tores;
	int			disks;
	int			parab;
	int			iter[THREADS];

	double		t[THREADS];
	double		t2[THREADS];

}				t_arr;

typedef struct
{
    int     max_y;
    int     y;
    int     id;
    t_arr   *gl;
    t_current **cur;
}           pthrData;



t_vec			add(t_vec *a, t_vec *b, int flag);
t_vec			mul(t_vec *a, double d, int flag);
double			dot(t_vec *a, t_vec *b);
void			write_sum(t_vec *dest, t_vec *src1, t_vec *src2);
void			write_sub(t_vec *dest, t_vec *src1, t_vec *src2);
void			write_mul(t_vec *dest, t_vec *src1, double a);
void			ft_error(int flag);
void			init(t_arr *gl);
void			norm(t_vec *a);
void			create_v(t_vec *vec, double x, double y, double z);
void    		*raytrace(void* thread_data);
//void			*raytrace(t_arr *gl, int x, int y, int col);
void			make_pthreads(t_arr *gl);
//int			outlight(t_arr *gl, t_vec *lgt, double nd);
void			create_img(t_arr *gl, int x, int y, int col);
//void			colors(t_arr *gl);
void			lambert(t_arr *gl, t_lsrc *src);
int				getcol(t_arr *gl, t_col *col, t_current *cur);
int				plane_inter(t_arr *gl, t_ray *ray, t_obj *pln, int thread);
int				conus_inter(t_arr *gl, t_ray *ray, t_obj *con, int thread);
int				spher_inter(t_arr *gl, t_ray *ray, t_obj *spr, int thread);
int				cylin_inter(t_arr *gl, t_ray *ray, t_obj *box, int thread);
int				torus_inter(t_arr *gl, t_ray *ray, t_obj *tor, int thread);
int				parab_inter(t_arr *gl, t_ray *ray, t_obj *hpb, int thread);
int				disk_inter(t_arr *gl, t_ray *ray, t_obj *dsk, int thread);
void    		limit_obj(t_arr *gl, t_ray *ray, t_obj *obj,  int thread);
void			normal_spr_pln(t_current *cur);
void			normal_con_cyl(t_current *cur);
void			normal_tor(t_current *cur);
void			normal_prb(t_current *cur);
void			light(t_current *cur, t_lsrc *src);
t_ray			*new_ray(void);
t_obj			**new_tor(int c, t_arr *gl);
t_pol			polinom_2_degr(double a, double b, double c);
t_pol			polinom_3_degr(double a, double b, double c, double d);
t_pol			*polinom_4_degr(double b, double c, double d, double e);
int	            disc(t_arr *gl, double a[3], int thread);
//int				disc(t_arr *gl, double a, double b, double c);
void			set_col(t_col *c, int r, int g, int b);
char			*cut_str(char *str, char c);
double			ration_n(char *a);
void   			parsing(t_arr *gl, ini_t *ini);
t_obj			**new_obj(int c, t_arr *gl, int fl);
void            detection(t_arr *gl, t_ray *ray, t_current **cur, int ind);
void	        render(t_arr *gl, t_current *cur, t_lsrc *src);
void			reflecting(t_arr *gl, t_current **cur, int i);
void    		refracting(t_arr *gl, t_current *src, t_current *cur, int i);
void        	universal(t_arr *gl, t_current **cur, int i);
void			to_arr(t_arr *gl);
void			mmul(t_arr *gl);
void			cr_res(t_arr *gl, double m1[4][4], double m2[4][4]);
void			multiple(t_arr *gl, t_cam cam, int i, int j);


#endif
