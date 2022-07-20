/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 17:00:04 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/20 13:56:53 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "libvec.h"
#include "ray.h"

#include <math.h>	/* sqrt */

#define X (0) // macro to simplify reading of axes
#define Z (2) // change them to change the cylinders direction(will break)

static t_vec3f	cylinder_default_direction(void)
{
	return (vec3f(0, 1, 0));
}

static float	sq(float n)
{
	return (n * n);
}

static t_vec3f	get_cylinder_normal(const t_ray *ray, const float dist,
	t_cylinder *cyl)
{
	t_vec3f		p;
	t_vec3f		closest_point;
	t_ray		cyl_ray;

	cyl_ray = ray_init(cyl->base.position, cyl->base.rotation);
	p = ray_at(ray, dist);
	closest_point = ray_closest_point(&cyl_ray, p);
	p = p - closest_point;
	vec3f_normalize(&p);
	return (p);
}

static t_intersect	check_caps(t_ray *initial_ray, t_ray *ray, float t,
	t_cylinder *cyl)
{
	t_disc		disc;
	t_intersect	i;
	float		y;

	y = ray_at(ray, t)[1];
	disc.base.position = vec3f(0, cyl->height / 2, 0);
	disc.base.rotation = cylinder_default_direction();
	disc.radius = cyl->radius;
	if (y >= cyl->height / 2)
	{
		i = intersects_disc(ray, (t_shape *)&disc);
		i.normal = cyl->base.rotation;
		return (i);
	}
	else if (y <= -cyl->height / 2)
	{
		disc.base.position = -disc.base.position;
		disc.base.rotation = -disc.base.rotation;
		i = intersects_disc(ray, (t_shape *)&disc);
		i.normal = -cyl->base.rotation;
		return (i);
	}
	if (t <= 0)
		return (no_intersect());
	return (init_intersect(t, get_cylinder_normal(initial_ray, t, cyl)));
}

// solves an ABC formula equation. The flip normals is when there's a
// later intersect, it implies that the ray origin is inside the object,
// so that means we have to flip the normals.
static float	abc_solve(float a, float b, float c, bool *flip_normals)
{
	float	discriminant;
	float	sqrt_discriminant;
	float	t;

	t = -1.0f;
	*flip_normals = false;
	discriminant = sq(b) - 4.0f * a * c;
	if (discriminant > 0)
	{
		sqrt_discriminant = sqrt(discriminant);
		t = (-b - sqrt_discriminant) / (2.0f * a);
		if (t < 0)
		{
			t = (-b + sqrt_discriminant) / (2.0f * a);
			*flip_normals = true;
		}
	}
	return (t);
}

// the ray.origin -= cyl->base.position is so that the cylinder is at (0,0,0)
// damn you norm!!
t_intersect	intersects_cylinder(t_ray *initial_ray, t_shape *shape)
{
	t_intersect	i;
	t_cylinder	*cyl;
	t_vec3f		center;
	t_ray		ray;
	float		t;
	bool		flip_normals;

	cyl = &shape->cylinder;
	ray = *initial_ray;
	ray.origin -= cyl->base.position;
	ray_rotate(&ray, cylinder_default_direction(), cyl->base.rotation);
	center = ray.origin;
	t = abc_solve(sq(ray.direction[X]) + sq(ray.direction[Z]),
			2.0f * ((center[X] * ray.direction[X])
				+ (center[Z] * ray.direction[Z])),
			sq(center[X]) + sq(center[Z]) - sq(cyl->radius),
			&flip_normals);
	i = check_caps(initial_ray, &ray, t, cyl);
	if (flip_normals)
		i.normal *= -1.0f;
	return (i);
}
