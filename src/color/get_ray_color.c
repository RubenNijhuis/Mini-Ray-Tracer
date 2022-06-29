/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_ray_color.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:49:58 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/30 00:03:23 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"
#include "ray.h"
#include "minirt.h"

#include <stdbool.h>
#include <stddef.h>
#include <math.h>

/**
 * @brief 
 * Retrieves the intersection function based on the shape object type
 * @param shape 
 * @return t_intersect_func 
 */
t_intersect_func	lookup_intersect_function(t_shape *shape)
{
	static const t_intersect_func	funcs[] = {
	[sphere] = &intersects_sphere,
	[plane] = &intersects_plane,
	[cylinder] = &intersects_cylinder,
	};

	return (funcs[shape->base.obj_type]);
}

/**
 * @brief 
 * Retrieves the normal function based on the shape object type
 * @param shape 
 * @return t_normal_func_ptr 
 */
t_normal_func_ptr	lookup_normal_function(t_shape *shape)
{
	static const t_normal_func_ptr	funcs[] = {
	[sphere] = &get_sphere_normal,
	[plane] = &get_plane_normal,
	[cylinder] = &get_cylinder_normal,
	};

	return (funcs[shape->base.obj_type]);
}

/**
 * Checks if the distance from origin to the current object is smaller
 * than the current record. If so -> update the record and update the color
*/
static bool	update_closest_hit(float *hit_dist_record, float hit_dist)
{
	if (hit_dist > 0 && hit_dist <= *hit_dist_record)
	{
		*hit_dist_record = hit_dist;
		return (true);
	}
	return (false);
}

/*
 * Loops through the shapes array and checks if the ray intersects
 * If it intersects it returns the current hit distance and applies
 * color if needed
 * NOTE: Uses a function roulette to acces the correct intersection func
*/
t_color	get_ray_color(t_ray *ray, t_scene *scene)
{
	uint32_t	current_shape;
	t_shape	*cur_shape;
	float		hit_dist_record;
	float		hit_dist;
	t_color		color;
	t_vec3f		normal;
	t_color		new_color;
	t_color		yeet;

	current_shape = 0;
	color = get_default_color(scene);
	hit_dist_record = INFINITY;
	while (current_shape < scene->amount_shapes)
	{
		cur_shape = &scene->shapes[current_shape];
		hit_dist = (lookup_intersect_function(cur_shape)) \
			(ray, cur_shape);
		if (!update_closest_hit(&hit_dist_record, hit_dist))
		{
			current_shape++;
			continue ;
		}
		normal = (lookup_normal_function(cur_shape)) \
			(ray, hit_dist, cur_shape);
		new_color = cur_shape->base.color;
		ambient_mixin(&new_color, scene);
		yeet = lights_mixin(scene,
				ray_at(ray, hit_dist),
				cur_shape, normal);
		color_add(&new_color, &yeet);
		color = new_color;
		current_shape++;
	}
	return (color);
}
