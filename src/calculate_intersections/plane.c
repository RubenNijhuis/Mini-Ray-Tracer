/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:44:59 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/07/11 18:22:01 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "libvec.h"
#include "ray.h"

#include <math.h> /* fabs */

// cutoff threshold for when the ray is roughly parallel to the plane
#define PARALLEL_THRES (0.0001f)

// Maximum render distance of the plane.
#define MAX_DISTANCE (10000.0f)

t_intersect	intersects_plane(t_ray *ray, t_shape *shape)
{
	t_plane		*plane;
	float		divisor;
	float		t;

	plane = &shape->plane;
	divisor = vec3f_dot(plane->base.rotation, ray->direction);
	if (fabs(divisor) < PARALLEL_THRES)
	{
		return (no_intersect());
	}
	t = vec3f_dot(vec3f_subtract(plane->base.position, ray->origin),
			plane->base.rotation);
	t /= divisor;
	if (t < 0.0f || t > MAX_DISTANCE)
	{
		return (no_intersect());
	}
	return (init_intersect(t, plane->base.rotation));
}
