/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 17:00:04 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/08 17:41:10 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "libvec.h"
#include "ray.h"

#include <math.h>	/* sqrt */
#include <stdio.h>	// temp

#define X (0)
#define Z (2) // change these vars to change the axis

static float	sq(float n)
{
	return (n * n);
}

t_vec3f	get_cylinder_normal(const t_ray *ray, const float dist, t_shape *shape)
{
	t_cylinder	*cyl;

	cyl = &shape->cylinder;
	(void)ray;
	(void)dist;
	(void)cyl;
	// TODO
	return (vec3f(0, 0, -1));
}

float	intersects_cylinder(t_ray *ray, t_shape *shape)
{
	t_cylinder		*cyl;
	t_vec3f			center;
	float			t;

	t = -1.0f;
	cyl = &shape->cylinder;

	center = ray->origin - cyl->base.position;

	float a = sq(ray->direction[X]) + sq(ray->direction[Z]);
	float b = 2.0f * ((center[X] * ray->direction[X]) + (center[Z] * ray->direction[Z])); 
	float c = sq(center[X]) + sq(center[Z]) - sq(cyl->radius);
	float discriminant = sq(b) - 4 * a * c;

	if (discriminant > 0)
	{
		t = (-b - sqrt(discriminant)) / (2 * a);
	}

	return (t);
}
