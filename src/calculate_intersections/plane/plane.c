/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:44:59 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/03 14:19:42 by jobvan-d      ########   odam.nl         */
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

/* returns the surface normal of a plane, which is actually the orientation. */
t_vec3f	get_plane_normal(const t_ray *ray, const float dist, t_object *shape)
{
	(void)ray;
	(void)dist;
	return (shape->base.orientation);
}

float	intersects_plane(t_ray *ray, t_object *shape)
{
	t_plane	*plane;
	float	divisor;
	float	t;

	plane = &shape->plane;
	divisor = vec3f_dot(plane->base.orientation, ray->direction);
	if (fabs(divisor) < PARALLEL_THRES)
	{
		return (-1);
	}
	t = vec3f_dot(vec3f_subtract(plane->base.position, ray->origin),
			plane->base.orientation);
	t /= divisor;
	if (t < 0.0f || t > MAX_DISTANCE)
	{
		t = -1;
	}
	return (t);
}
