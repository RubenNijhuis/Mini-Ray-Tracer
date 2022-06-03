/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_ray_color.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:49:58 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/03 14:15:38 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"
#include "ray.h"
#include "minirt.h"

#include <stddef.h>
#include <math.h>

/**
 * Checks if the distance from origin to the current object is smaller
 * than the current record. If so -> update the record and update the color
*/
static void	update_color_from_dist(float *hit_dist_record, float cur_hit_dist, \
	t_color *color, t_color new_color)
{
	if (cur_hit_dist != -1 && cur_hit_dist < *hit_dist_record)
	{
		*hit_dist_record = cur_hit_dist;
		*color = new_color;
	}
}

// see e_objects_type in objects.h
static t_intersect_func_ptr	lookup_intersect_function(t_object *shape)
{
	static const t_intersect_func_ptr	funcs[] = {
	[sphere] = &intersects_sphere,
	[plane] = &intersects_plane,
	};

	return (funcs[shape->base.obj_type]);
}

// see e_objects_type in objects.h
static t_normal_func_ptr	lookup_normal_function(t_object *shape)
{
	static const t_normal_func_ptr	funcs[] = {
	[sphere] = &get_sphere_normal,
	[plane] = &get_plane_normal,
	};

	return (funcs[shape->base.obj_type]);
}

/*
 * Loops through the shapes array and checks if the ray intersects
 * If it intersects it returns the current hit distance and applies
 * color if needed
 * NOTE: Uses a function roulette to acces the correct intersection func
*/
t_color	get_ray_color(t_ray *ray, uint32_t x, uint32_t y, t_program_data *pd)
{
	uint32_t	current_shape;
	t_object	*cur_shape;
	float		hit_dist_record;
	float		cur_hit_dist;
	t_color		color;

	(void)x;
	(void)y;
	current_shape = 0;
	color = get_default_color(pd);
	hit_dist_record = INFINITY;
	while (current_shape < pd->scene.amount_shapes)
	{
		cur_shape = &pd->scene.shapes[current_shape];
		cur_hit_dist = (lookup_intersect_function(cur_shape)) \
			(ray, cur_shape);
		t_color	newcol = cur_shape->base.color;
		t_vec3f	normal = (lookup_normal_function(cur_shape))(ray,
			cur_hit_dist, cur_shape);
		if (cur_hit_dist != -1 && cur_shape->base.obj_type == sphere)
		{
			// surface normal
			// TODO: verify and move etc. this is temporary
			newcol.r = (0.5f * (normal[0] + 1.0f));
			newcol.g = (0.5f * (normal[1] + 1.0f));
			newcol.b = (0.5f * (normal[2] + 1.0f));
		}
		else if (cur_hit_dist != -1 && cur_shape->base.obj_type == plane)
		{
			newcol.r = (cur_hit_dist / 100);
			newcol.g = sin(cur_hit_dist / 100);
			newcol.b = cos((cur_hit_dist) / 100 + M_PI) / 1.1f;
		}
		ambient_mixin(&newcol, &pd->scene);
		update_color_from_dist(&hit_dist_record, cur_hit_dist, \
			&color, newcol);
		current_shape++;
	}
	return (color);
}
