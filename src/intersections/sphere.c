/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:36:15 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/07/22 19:04:19 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "libvec.h"
#include "ray.h"

#include <math.h> // sqrt
#include <stdbool.h>

/* gets the surface normal of a sphere.
 * it's just the intersection point minus the sphere's origin. */
static t_vec3f	get_sphere_normal(const t_ray *ray,
	const float dist, t_sphere *shape)
{
	t_vec3f	intersect_point;
	t_vec3f	normal;

	intersect_point = ray_at(ray, dist);
	normal = intersect_point - shape->base.position;
	vec3f_normalize(&normal);
	return (normal);
}

static t_intersect	get_sphere_intersection(t_ray *ray, t_sphere *sphere,
	float distance_to_so_sq, float distance_to_closest_point)
{
	t_intersect	i;
	float		distance_from_origin_to_ray;

	distance_from_origin_to_ray = sqrt(sq(sphere->radius) - distance_to_so_sq);
	i.t = distance_to_closest_point - distance_from_origin_to_ray;
	if (i.t < 0)
	{
		i.t = distance_to_closest_point + distance_from_origin_to_ray;
		i.normal = -get_sphere_normal(ray, i.t, sphere);
	}
	else
	{
		i.normal = get_sphere_normal(ray, i.t, sphere);
	}
	return (i);
}

// see also: https://www.khanacademy.org/computer-programming/c/5311392656179200
t_intersect	intersects_sphere(t_ray *ray, t_shape *shape)
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
	if (distance_to_so_sq <= sq(sphere->radius))
	{
		return (get_sphere_intersection(ray, sphere,
				distance_to_so_sq, distance_to_closest_point));
	}
	return (no_intersect());
}
