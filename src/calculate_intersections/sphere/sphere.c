/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:36:15 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/31 15:30:03 by jobvan-d      ########   odam.nl         */
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

	distance_from_origin_to_ray = sqrt(radius * radius - distance_to_so_sq);
	intersect_point = distance_to_closest_point - distance_from_origin_to_ray;
	return (intersect_point);
}

// TODO: return closest value but only if not negatives
// see also: https://www.khanacademy.org/computer-programming/circle-intersect-test/5311392656179200
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
