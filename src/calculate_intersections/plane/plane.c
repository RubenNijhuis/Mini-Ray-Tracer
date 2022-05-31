/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:44:59 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/31 16:47:52 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"
#include "libvec.h"
#include "ray.h"

#include <stdio.h>

float	intersects_plane(t_ray *ray, t_object *shape)
{
	t_plane	*plane;
	float	divisor;
	float	t;

	plane = &shape->plane;
	divisor = vec3f_dot(plane->base.orientation, ray->direction);
	if (divisor < 0.00001f)
	{
		return (-1);
	}
	t = vec3f_dot(vec3f_subtract(plane->base.position, ray->origin), plane->base.orientation);
	//printf("%f\n", t);
	if (t >= 0)
	{
		printf("POSITIVE\n");
		//plane += 345;
		//plane->base.color.b = 5;
	}
	// if (t < 0.0f)
	// {
	// 	t = -1;
	// }
	return (t);
}
