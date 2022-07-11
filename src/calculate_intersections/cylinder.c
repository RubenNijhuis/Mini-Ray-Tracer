/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 17:00:04 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/11 18:30:40 by jobvan-d      ########   odam.nl         */
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

static t_vec3f	get_cylinder_normal(const t_ray *ray, const float dist,
	t_cylinder *cyl)
{
	t_vec3f		p;
	t_vec3f		center;

	center = cyl->base.position;
	p = ray_at(ray, dist);
	p[1] = 0.0f;
	center[1] = 0.0f;
	return (p - center);
}

// rotates a ray so that it matches the direciton.
// All vectors should be unit vectors.
// IMPORTANT: Assumes the ray has been translated by the object's position in
// question. i.e. obj at (2,0,2) and ray origin at (3,0,5) results in
// ray origin (1,0,3)
// his is easier and it makes that the ray can be properly rotated.
// ray is modified, so better make a copy of it.
static void	rotate_ray(t_ray *ray, t_vec3f default_dir, t_vec3f desired_dir)
{
	float	angle;
	t_vec3f	rotation_axis;

	angle = vec3f_unit_get_angle(default_dir, desired_dir);
	rotation_axis = vec3f_cross(default_dir, desired_dir);
	ray->direction = vec3f_rotate_axis(ray->direction, rotation_axis, angle);
	ray->origin = vec3f_rotate_axis(ray->origin, rotation_axis, angle);
}

// TODO: fix caps..?
static t_intersect	check_caps(t_ray *ray, float t, t_cylinder *cyl)
{
	t_disc	disc;
	float	y;

	// if (t >= 0.0f)
	// {
	y = ray_at(ray, t)[1];
	disc.base.position = vec3f(0, cyl->height / 2, 0);
	disc.base.rotation = cylinder_default_direction();
	disc.radius = cyl->radius;
	if (y >= cyl->height / 2)
	{
		return (intersects_disc(ray, (t_shape *)&disc));
	}
	else if (y <= -cyl->height / 2)
	{
		disc.base.position = -disc.base.position;
		disc.base.rotation = -disc.base.rotation;
		return (intersects_disc(ray, (t_shape *)&disc));
	}
	// }
	return (init_intersect(t, get_cylinder_normal(ray, t, cyl)));
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

	rotate_ray(&ray, cylinder_default_direction(), cyl->base.rotation);

	center = ray.origin;

	float a = sq(ray.direction[X]) + sq(ray.direction[Z]);
	float b = 2.0f * ((center[X] * ray.direction[X]) + (center[Z] * ray.direction[Z])); 
	float c = sq(center[X]) + sq(center[Z]) - sq(cyl->radius);
	float discriminant = sq(b) - 4.0f * a * c;

	if (discriminant > 0)
	{
		t = (-b - sqrt(discriminant)) / (2.0f * a);
	}

	return (check_caps(&ray, t, cyl));
}
