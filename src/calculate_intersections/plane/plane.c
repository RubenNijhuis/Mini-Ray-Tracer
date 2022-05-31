/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:44:59 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/31 18:24:40 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"
#include "libvec.h"
#include "ray.h"

#include <stdio.h>

#define THRES (0.00001f)

float	intersects_plane(t_ray *ray, t_object *shape)
{
	t_plane	*plane;
	float	divisor;
	float	t;

	plane = &shape->plane;
	divisor = vec3f_dot(plane->base.orientation, ray->direction);
	if (divisor * divisor < THRES)
	{
		return -1;
	}
	t = vec3f_dot(vec3f_subtract(plane->base.position, ray->origin), plane->base.orientation);
	t /= divisor;
	if (t < 0.0f || t > 10000.0f)
	{
		t = -1;
	}
	return (t);
}
