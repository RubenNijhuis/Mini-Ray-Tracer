/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_ray_color.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:49:58 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/25 18:51:14 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"
#include "ray.h"
#include "minirt.h"
#include <stdlib.h>

/**
 * Checks if the distance from origin to the current object is smaller
 * than the current record. If so -> update the record and update the color
*/
static void	update_color_from_dist(float *hit_dist_record, float cur_hit_dist, \
	t_vec3i *color, t_vec3i new_color)
{
	if (cur_hit_dist != -1 && cur_hit_dist < *hit_dist_record)
	{
		*hit_dist_record = cur_hit_dist;
		*color = new_color;
	}
}

typedef float	(*t_intersect_func_ptr)(t_ray *, t_object *);

typedef struct s_intersect_func
{
	t_object_type			type;
	t_intersect_func_ptr	func;
}	t_intersect_func;

static t_intersect_func_ptr	lookup_intersect_function(t_object *shape)
{
	size_t					i;
	const t_intersect_func	funcs[] = {
	{sphere, &intersects_sphere},
	{plane, &intersects_plane},
	};

	i = 0;
	while (i < sizeof(funcs) / sizeof(t_intersect_func))
	{
		if (funcs[i].type == shape->base.obj_type)
			return (funcs[i].func);
		i++;
	}
	return (NULL);
}

/*
 * Loops through the shapes array and checks if the ray intersects
 * If it intersects it returns the current hit distance and applies
 * color if needed
 * NOTE: Uses a function roulette to acces the correct intersection func
*/
t_vec3i	get_ray_color(t_ray *ray, uint32_t x, uint32_t y, t_program_data *pd)
{
	uint32_t	current_shape;
	t_object	*cur_shape_struct;
	float		hit_dist_record;
	float		cur_hit_dist;
	t_vec3i		color;

	(void)x;
	(void)y;
	current_shape = 0;
	color = get_default_color(pd);
	hit_dist_record = 100000; // Set to infinity
	while (current_shape < pd->scene.amount_shapes)
	{
		cur_shape_struct = &pd->scene.shapes[current_shape];
		cur_hit_dist = (*lookup_intersect_function(cur_shape_struct)) \
			(ray, cur_shape_struct);
		update_color_from_dist(&hit_dist_record, cur_hit_dist, \
			&color, cur_shape_struct->base.color);
		current_shape++;
	}
	return (color);
}
