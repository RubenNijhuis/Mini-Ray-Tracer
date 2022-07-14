/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 17:00:04 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/14 13:57:25 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "libvec.h"
#include "ray.h"

#include "minirt.h"

#include <math.h>	/* sqrt */
#include <stdio.h>	// temp

#define X (0)
#define Z (2) // change these vars to change the axis

static t_vec3f	cylinder_default_direction(void)
{
	return (vec3f(0, 1, 0));
}

static float	sq(float n)
{
	return (n * n);
}

t_vec3f get_closest_p_on_line(t_cylinder *cyl, t_vec3f p)
{
	t_ray	ray = ray_init(cyl->base.position, cyl->base.rotation);

	float	origin_to_intersect = vec3f_len_sq(p - ray.origin);

	float distance_to_closest_point = sqrt(origin_to_intersect - cyl->radius * cyl->radius);

	t_vec3f intersect_point = ray_at(&ray, distance_to_closest_point);

	return (intersect_point);
}

static t_vec3f	get_cylinder_normal(const t_ray *ray, const float dist,
	t_cylinder *cyl)
{
	t_vec3f		p;
	t_vec3f		closest_point;
	t_ray		cylray = ray_init(cyl->base.position, cyl->base.rotation);

	p = ray_at(ray, dist);
	closest_point = ray_closest_point(&cylray, p);
	p = p - closest_point;
	vec3f_normalize(&p);
	return (p);
}

// TODO: fix caps..?
static t_intersect	check_caps(t_ray *initial_ray, t_ray *ray, float t, t_cylinder *cyl)
{
	t_disc		disc;
	t_intersect	i;
	float		y;

	// if (t >= 0.0f)
	// {
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
	// }
	if (t <= 0)
		return (no_intersect());
	return (init_intersect(t, get_cylinder_normal(initial_ray, t, cyl)));
}

t_intersect	intersects_cylinder(t_ray *initial_ray, t_shape *shape)
{
	t_cylinder	*cyl;
	t_vec3f		center;
	t_ray		ray;
	float		t;

	t = -1.0f;
	cyl = &shape->cylinder;

	ray = *initial_ray;
	ray.origin -= cyl->base.position; // translate ray so that cylinder is at (0,0,0)

	ray_rotate(&ray, cylinder_default_direction(), cyl->base.rotation);

	center = ray.origin;

	float a = sq(ray.direction[X]) + sq(ray.direction[Z]);
	float b = 2.0f * ((center[X] * ray.direction[X]) + (center[Z] * ray.direction[Z])); 
	float c = sq(center[X]) + sq(center[Z]) - sq(cyl->radius);
	float discriminant = sq(b) - 4.0f * a * c;

	if (discriminant > 0)
	{
		t = (-b - sqrt(discriminant)) / (2.0f * a);
	}

	return (check_caps(initial_ray, &ray, t, cyl));
}
