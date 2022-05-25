/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:36:15 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/25 19:19:13 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "libvec.h"
#include "ray.h"

#include <math.h>
#include <stdbool.h>

static float	get_intersection_point(float radius, float y, float t)
{
	float	intersection_point;
	float	distance_from_origin_to_ray;

	distance_from_origin_to_ray = sqrt((radius * radius) - (y * y));
	intersection_point = t - distance_from_origin_to_ray;
	return (intersection_point);
}

// float ip2 = t + x;
// TODO: return closest value but only if not negative
float	intersects_sphere(t_ray *ray, t_object *shape)
{
	t_sphere	*sphere;
	t_vec3f		relpos;
	t_vec3f		closest_point;
	float		distance_to_so;
	float		distance_to_closest_point;

	sphere = &shape->sphere;
	relpos = sphere->base.position - ray->origin;
	distance_to_closest_point = vec3f_dot(relpos, ray->direction);
	closest_point = ray_at(ray, distance_to_closest_point);
	distance_to_so = vec3f_length(sphere->base.position - closest_point);
	if (distance_to_so <= sphere->diameter / 2)
	{
		return (get_intersection_point(sphere->diameter / 2,
				distance_to_so, distance_to_closest_point));
	}
	return (-1);
}
