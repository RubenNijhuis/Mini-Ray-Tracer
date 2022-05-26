/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:36:15 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/26 13:07:42 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "libvec.h"
#include "ray.h"

#include <math.h>
#include <stdbool.h>

static float	get_intersection_point(float radius, float distance_to_so_sq, \
	float distance_to_closest_point)
{
	float	intersect_point;
	float	distance_from_origin_to_ray;
	float	radius_sq;

	radius_sq = radius * radius;
	distance_from_origin_to_ray = sqrt(radius_sq - distance_to_so_sq);
	intersect_point = distance_to_closest_point - distance_from_origin_to_ray;
	return (intersect_point);
}

// float ip2 = t + x;
// TODO: return closest value but only if not negatives
float	intersects_sphere(t_ray *ray, t_object *shape)
{
	t_sphere	*sphere;
	t_vec3f		relpos;
	t_vec3f		closest_point;
	float		distance_to_so_sq;
	float		distance_to_closest_point;

	sphere = &shape->sphere;
	relpos = sphere->base.position - ray->origin;
	distance_to_closest_point = vec3f_dot(relpos, ray->direction);
	closest_point = ray_at(ray, distance_to_closest_point);
	distance_to_so_sq = vec3f_len_sq(sphere->base.position - closest_point);
	if (distance_to_so_sq <= sphere->radius * sphere->radius)
	{
		return (get_intersection_point(sphere->radius,
				distance_to_so_sq, distance_to_closest_point));
	}
	return (-1);
}
