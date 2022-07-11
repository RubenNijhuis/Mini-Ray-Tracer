/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 17:00:04 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/11 13:52:45 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "libvec.h"
#include "ray.h"

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

t_vec3f	get_cylinder_normal(const t_ray *ray, const float dist, t_shape *shape)
{
	t_cylinder	*cyl;
	t_vec3f		p;
	t_vec3f		center;

	cyl = &shape->cylinder;
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
	float 	angle;
	t_vec3f	rotation_axis;
	
	angle = vec3f_unit_get_angle(default_dir, desired_dir);
	rotation_axis = vec3f_cross(default_dir, desired_dir);
	ray->direction = vec3f_rotate_axis(ray->direction, rotation_axis, angle);
	ray->origin = vec3f_rotate_axis(ray->origin, rotation_axis, angle);
}

float	intersects_cylinder(t_ray *initial_ray, t_shape *shape)
{
	t_cylinder		*cyl;
	t_vec3f			center;
	t_ray			ray;
	float			t;

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

	return (t);
}
