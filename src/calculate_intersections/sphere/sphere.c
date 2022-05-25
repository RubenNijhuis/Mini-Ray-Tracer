/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:36:15 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/25 18:44:19 by rnijhuis      ########   odam.nl         */
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
	t_vec3f		v;
	t_vec3f		temp;
	t_vec3f		p;
	float		y;
	float		t;

	sphere = &shape->sphere;
	v = ray->direction;
	temp = vec3f_subtract(sphere->base.position, ray->origin);
	t = vec3f_dot(temp, ray->direction);
	vec3f_multiply_scalar(&v, t);
	p = vec3f_sum(ray->origin, v);
	y = vec3f_length(vec3f_subtract(sphere->base.position, p));
	if (y <= sphere->diameter / 2)
		return (get_intersection_point(sphere->diameter / 2, y, t));
	return (-1);
}
