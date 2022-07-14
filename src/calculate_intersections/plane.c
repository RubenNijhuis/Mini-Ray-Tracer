/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:44:59 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/07/14 16:57:36 by jobvan-d      ########   odam.nl         */
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

// the normal is equal to the plane's direction, however,
// when hit from the back you need to flip it.
static t_vec3f	plane_normal(t_ray *ray, t_plane *plane)
{
	t_vec3f	normal;
	float	angle;

	normal = plane->base.rotation;
	angle = vec3f_dot(ray->direction, normal);
	if (angle > 0.0f)
	{
		normal = -normal;
	}
	return (normal);
}

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
	return (init_intersect(t, plane_normal(ray, plane)));
}
