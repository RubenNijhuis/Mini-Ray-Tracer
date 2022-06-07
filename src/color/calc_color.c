/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_color.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:13:07 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/07 16:34:50 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"

void	ambient_mixin(t_color *col, t_scene *scene)
{
	t_color	amb;

	amb = scene->amb_light.color;
	color_multiply_scalar(&amb, scene->amb_light.range);
	color_multiply(col, &amb);
}

#include <stdio.h>

bool	scene_intersects(t_scene *scene, t_ray *ray)
{
	uint32_t	i;
	t_object	*cur_shape;
	float		dist;

	i = 0;
	while (i < scene->amount_shapes)
	{
		cur_shape = &scene->shapes[i];
		dist = (lookup_intersect_function(cur_shape))(ray, cur_shape);
		if (dist >= 0.0f)
		{
			// if (cur_shape->base.obj_type == sphere && cur_shape->base.position[1] == 10.01f)
			// 	printf("%f \n", dist);
			return (true);
		}
		i++;
	}
	return (false);
}

t_color	get_light(t_light *light, t_scene *scene, t_object *shape, t_vec3f p, t_vec3f normal)
{
	t_ray	ray;
	t_color	color;

	ray.direction = light->position - p;
	vec3f_normalize(&ray.direction);
	ray.origin = p + (normal / 100.0f);
	if (scene_intersects(scene, &ray))
	{
		color = make_color(0, 0, 0);
	}
	else
	{
		color = shape->base.color;
		color_multiply_scalar(&color, light->brightness);
		color_multiply(&color, &light->color);
	}
	return (color);
}

t_color	lights_mixin(t_scene *scene, t_vec3f p, t_object *shape, t_vec3f normal)
{
	t_color		light_cols;
	t_color		cur_col;
	uint32_t	i;

	light_cols = make_color(0, 0, 0);
	i = 0;
	while (i < scene->amount_lights)
	{
		cur_col = get_light(&scene->lights[i], scene, shape, p, normal);
		color_add(&light_cols, &cur_col);
		i++;
	}
	return (light_cols);
}
