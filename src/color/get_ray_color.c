/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_ray_color.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:49:58 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/07/12 15:45:16 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"
#include "ray.h"
#include "minirt.h"

#include <stdbool.h>
#include <stddef.h>
#include <math.h>

/**
 * Checks if the distance from origin to the current object is smaller
 * than the current record. If so -> update the record and update the color
*/
static bool	update_closest_hit(t_intersect *closest, t_intersect *cur)
{
	if (cur->t > 0 && cur->t <= closest->t)
	{
		*closest = *cur;
		return (true);
	}
	return (false);
}

static t_color	calc_color(t_scene *scene, t_shape *shape, t_ray *ray,
	t_intersect *i)
{
	t_color	color;
	t_color	temp;

	color = shape->base.color;
	ambient_mixin(&color, scene);
	temp = lights_mixin(scene, ray_at(ray, i->t), shape, i->normal);
	color_add(&color, &temp);
	return (color);
}

/*
 * Loops through the shapes array and checks if the ray intersects
 * If it intersects it returns the current hit distance and applies
 * color if needed
*/
t_color	get_ray_color(t_ray *ray, t_scene *scene)
{
	size_t		current_shape;
	t_shape		*cur_shape;
	t_intersect	cur_i;
	t_intersect	closest_i;
	t_color		color;

	current_shape = 0;
	color = get_default_color(scene);
	closest_i.normal = vec3f(0, 0, 0);
	closest_i.t = INFINITY;
	while (current_shape < scene->amount_shapes)
	{
		cur_shape = &scene->shapes[current_shape];
		cur_i = (lookup_intersect_function(cur_shape))(ray, cur_shape);
		if (!update_closest_hit(&closest_i, &cur_i))
		{
			current_shape++;
			continue ;
		}
		color = calc_color(scene, cur_shape, ray, &cur_i);
		current_shape++;
	}
	return (color);
}
