/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_ray_color.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:49:58 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/08 13:54:34 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"
#include "ray.h"
#include "minirt.h"


#include <stdbool.h>
#include <stddef.h>
#include <math.h>

// see e_objects_type in objects.h
t_intersect_func_ptr	lookup_intersect_function(t_object *shape)
{
	static const t_intersect_func_ptr	funcs[] = {
	[sphere] = &intersects_sphere,
	[plane] = &intersects_plane,
	};

	return (funcs[shape->base.obj_type]);
}

// see e_objects_type in objects.h
t_normal_func_ptr	lookup_normal_function(t_object *shape)
{
	static const t_normal_func_ptr	funcs[] = {
	[sphere] = &get_sphere_normal,
	[plane] = &get_plane_normal,
	};

	return (funcs[shape->base.obj_type]);
}

// t_vec3f	normal = (lookup_normal_function(cur_shape))(ray,
// 	cur_hit_dist, cur_shape);
// if (cur_hit_dist != -1)
// {
// 	// surface normal
// 	// TODO: verify and move etc. this is temporary
// 	newcol.r = (0.5f * (normal[0] + 1.0f));
// 	newcol.g = (0.5f * (normal[1] + 1.0f));
// 	newcol.b = (0.5f * (normal[2] + 1.0f));
// }
// else if (cur_hit_dist != -1 && cur_shape->base.obj_type == plane)
// {
// 	newcol.r = (cur_hit_dist / 100);
// 	newcol.g = sin(cur_hit_dist / 100);
// 	newcol.b = cos((cur_hit_dist) / 100 + M_PI) / 1.1f;
// }

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
	t_object	*cur_shape;
	float		hit_dist_record;
	float		hit_dist;
	t_color		color;

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
			continue;
		}

		t_vec3f	normal = (lookup_normal_function(cur_shape))(ray, hit_dist, cur_shape);

		t_color	newcol = cur_shape->base.color;
		ambient_mixin(&newcol, scene);
		t_color	yeet = lights_mixin(scene,
			ray_at(ray, hit_dist),
			cur_shape, normal);
		color_add(&newcol, &yeet);
		color = newcol;
		current_shape++;
	}
	return (color);
}
