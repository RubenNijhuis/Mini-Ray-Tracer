/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 17:00:04 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/21 15:13:16 by jobvan-d      ########   odam.nl         */
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

static t_intersect	get_cap_intersect(t_ray *obj_ray, t_cylinder *cyl)
{
	t_disc		disc;
	t_intersect	i;
	float		prev_t;

	disc.base.rotation = cylinder_default_direction();
	disc.base.position = disc.base.rotation * (cyl->height * 0.5f);
	disc.radius = cyl->radius;
	i = intersects_disc(obj_ray, (t_shape *)&disc);
	prev_t = i.t;
	disc.base.position = -disc.base.position;
	i = intersects_disc(obj_ray, (t_shape *)&disc);
	if (i.t <= 0.0f || (prev_t >= 0.0f && prev_t < i.t))
	{
		i.t = prev_t;
	}
	return (i);
}

static t_intersect	get_cylinder_intersect(t_ray *obj_ray,
	t_cylinder *cyl, float t)
{
	t_intersect	i;
	float		y;

	y = ray_at(obj_ray, t)[1];
	if (y <= -cyl->height * 0.5f || y >= cyl->height * 0.5f)
	{
		i.t = -1.0f;
	}
	else
	{
		i.t = t;
	}
	return (i);
}

// returns true if cap intersect is closer than cyl intersect.
// overwrites cyl intersect if this is is the case.
static bool	check_cap_intersect(t_intersect cap, t_intersect *cyl)
{
	if (cyl->t < 0.0f || (cap.t >= 0.0f && cap.t < cyl->t))
	{
		*cyl = cap;
		return (true);
	}
	return (false);
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
	bool		inside_cyl;

	cyl = &shape->cylinder;
	ray = *initial_ray;
	ray.origin -= cyl->base.position;
	ray_rotate(&ray, cylinder_default_direction(), cyl->base.rotation);
	center = ray.origin;
	t = abc_solve(sq(ray.direction[X]) + sq(ray.direction[Z]),
			2.0f * ((center[X] * ray.direction[X])
				+ (center[Z] * ray.direction[Z])),
			sq(center[X]) + sq(center[Z]) - sq(cyl->radius),
			&inside_cyl);
	i = get_cylinder_intersect(&ray, cyl, t);
	if (check_cap_intersect(get_cap_intersect(&ray, cyl), &i))
	{
		t_plane	plane;
		plane.base.rotation = cyl->base.rotation;
		i.normal = get_plane_normal(initial_ray, &plane);
	}
	else
	{
		i.normal = get_cylinder_normal(initial_ray, t, cyl);
		if (inside_cyl)
		{
			i.normal *= -1.0f;
		}
	}
	return (i);
}
