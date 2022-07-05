/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:36:15 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/30 00:03:23 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "libvec.h"
#include "ray.h"

#include <math.h> // sqrt
#include <stdbool.h>

/* gets the surface normal of a sphere.
 * TODO: verify if correct. */
t_vec3f	get_sphere_normal(const t_ray *ray, const float dist, t_shape *shape)
{
	t_vec3f	intersect_point;
	t_vec3f	normal;

	intersect_point = ray_at(ray, dist);
	normal = intersect_point - shape->base.position;
	vec3f_normalize(&normal);
	return (normal);
}

static float	get_sphere_intersection(float radius, float distance_to_so_sq, \
	float distance_to_closest_point)
{
	float	intersect_dist;
	float	distance_from_origin_to_ray;

	distance_from_origin_to_ray = sqrt(radius * radius - distance_to_so_sq);
	intersect_dist = distance_to_closest_point - distance_from_origin_to_ray;
	return (intersect_dist);
}

// TODO: return closest value but only if not negatives
// see also: https://www.khanacademy.org/computer-programming/c/5311392656179200
float	intersects_sphere(t_ray *ray, t_shape *shape)
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
		return (get_sphere_intersection(sphere->radius,
				distance_to_so_sq, distance_to_closest_point));
	}
	return (-1);
}
