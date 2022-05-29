/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_ray_color.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:49:58 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/29 16:25:32 by rubennijhui   ########   odam.nl         */
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
		cur_hit_dist = (*lookup_intersect_function(cur_shape)) \
			(ray, cur_shape);
		// == fix
		t_color	newcol = cur_shape->base.color;
		if (cur_hit_dist != -1)
		{
			// surface normal
			// TODO: verify and move etc. this is temporary
			t_vec3f	pos = ray_at(ray, cur_hit_dist) - cur_shape->base.position;
			vec3f_normalize(&pos);
			newcol.r = (0.5f * (pos[0] + 1.0f));
			newcol.g = (0.5f * (pos[1] + 1.0f));
			newcol.b = (0.5f * (pos[2] + 1.0f));
		}
		// == fix
		update_color_from_dist(&hit_dist_record, cur_hit_dist, \
			&color, newcol);
		current_shape++;
	}
	return (color);
}
