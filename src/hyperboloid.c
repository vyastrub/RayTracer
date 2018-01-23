
#include "../includes/rtv1.h"

int			parab_inter(t_arr *gl, t_ray *ray, t_obj *hprb, int thread)
{
	t_vec	oc;
	double	a[3];

	oc = add(ray->org, hprb->c, 2);
	norm(hprb->v);
	a[0] = dot(ray->dir, ray->dir) - pow(dot(ray->dir, hprb->v), 2);
	a[1] = 2 * (dot(ray->dir, &oc) - dot(ray->dir, hprb->v) * (dot(hprb->v, &oc) + 2 * hprb->r2));
	a[2] = dot(&oc, &oc) - dot(hprb->v, &oc) * (dot(hprb->v, &oc) + 4 * hprb->r2);
	if (hprb->h > 0 && disc(gl, a, thread) > 0)
	{
		limit_obj(gl, ray, hprb, thread);
		return (1);
	}
	return (disc(gl, a, thread));
}