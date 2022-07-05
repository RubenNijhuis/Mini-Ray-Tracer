/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:44:59 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/30 00:03:23 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "libvec.h"
#include "ray.h"

#include <math.h> /* fabs */

// cutoff threshold for when the ray is roughly parallel to the plane
#define PARALLEL_THRES (0.0001f)

// Maximum render distance of the plane.
#define MAX_DISTANCE (10000.0f)

/* returns the surface normal of a plane, which is actually the rotation. */
t_vec3f	get_plane_normal(const t_ray *ray, const float dist, t_shape *shape)
{
	(void)ray;
	(void)dist;
	return (shape->base.rotation);
}

float	intersects_plane(t_ray *ray, t_shape *shape)
{
	t_plane	*plane;
	float	divisor;
	float	t;

	plane = &shape->plane;
	divisor = vec3f_dot(plane->base.rotation, ray->direction);
	if (fabs(divisor) < PARALLEL_THRES)
	{
		return (-1);
	}
	t = vec3f_dot(vec3f_subtract(plane->base.position, ray->origin),
			plane->base.rotation);
	t /= divisor;
	if (t < 0.0f || t > MAX_DISTANCE)
	{
		t = -1;
	}
	return (t);
}
