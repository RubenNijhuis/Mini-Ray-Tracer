/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 17:00:04 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/27 17:07:02 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "libvec.h"
#include "ray.h"

#include <math.h> /* sqrt */
#include <stdio.h> // temp

#define X (0)
#define Y (1)

static float sq(float n)
{
	return (n * n);
}

t_vec3f	get_cylinder_normal(const t_ray *ray, const float dist, t_object *shape)
{
	t_cylinder	*cyl;

	cyl = &shape->cylinder;
	(void)ray;
	(void)dist;
	// TODO
	return (vec3f(0, 0, -1));
}

float	intersects_cylinder(t_ray *ray, t_object *shape)
{
	t_cylinder		*cyl;
	float			t;
	// t_vec3f		trans_pos;

	t = -1.0f;
	cyl = &shape->cylinder;
	//trans_pos = cyl->base.position - ray->origin;

	float a = sq(ray->direction[X]) + sq(ray->direction[Y]);
	float b = 2.0f * ray->origin[X] * ray->direction[X] +
		2.0f * ray->origin[Y] * ray->direction[Y];
	float c = sq(ray->origin[X]) + sq(ray->origin[Y]) - sq(cyl->radius);

	float discriminant = b * b + 4.0f * a * c;
	if (discriminant < 0)
	{
		return (-1.0f);
	}
	float closest_t = (-b + sqrt(discriminant)) / (2.0f * a);

	t = closest_t;
	//printf("%f\n", t);
	return (t);
}
