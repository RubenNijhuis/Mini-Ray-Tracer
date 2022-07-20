/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_color.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:13:07 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/20 13:32:54 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"

#include <stddef.h>

void	ambient_mixin(t_color *col, t_scene *scene)
{
	t_color	amb;

	amb = scene->amb_light.color;
	color_multiply_scalar(&amb, scene->amb_light.range);
	color_multiply(col, &amb);
}

/**
 * @brief 
 * Goes through the scene to check if a ray intersects with any 
 * shapes in the scene
 * @param scene 
 * @param ray 
 * @param max_dist_sq 
 * @return bool
 */
bool	scene_intersects(t_scene *scene, t_ray *ray, float max_dist_sq)
{
	size_t		i;
	t_shape		*cur_shape;
	t_intersect	intersect;

	i = 0;
	while (i < scene->amount_shapes)
	{
		cur_shape = &scene->shapes[i];
		intersect = (lookup_intersect_function(cur_shape))(ray, cur_shape);
		if (intersect.t > 0.0 && intersect.t * intersect.t <= max_dist_sq)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

/**
 * @brief 
 * Add the color of a light to a point. Checks if the ray from point to light
 * intersects any objects
 * 
 * @param light 
 * @param scene 
 * @param shape 
 * @param point 
 * @param normal 
 * @return t_color 
 */
t_color	get_light(t_light *light, t_scene *scene, t_shape *shape, \
	t_vec3f point, t_vec3f normal)
{
	t_ray	ray;
	t_color	color;
	float	max_dist_sq;
	float	intensity;

	ray.direction = light->position - point;
	max_dist_sq = vec3f_len_sq(ray.direction);
	vec3f_normalize(&ray.direction);
	ray.origin = point + (normal * (1.0f / 5000.0f));
	if (scene_intersects(scene, &ray, max_dist_sq))
		color = make_color(0, 0, 0);
	else
	{
		color = shape->base.color;
		color_multiply_scalar(&color, light->brightness);
		intensity = vec3f_dot(ray.direction, normal);
		if (intensity < 0.00001f)
			intensity = 0;
		color_multiply_scalar(&color, intensity);
		color_multiply(&color, &light->color);
	}
	return (color);
}

/**
 * @brief 
 * Goes through the lights array to calculate 
 * the color value of a pixel
 * @param scene 
 * @param p 
 * @param shape 
 * @param normal 
 * @return t_color 
 */
t_color	lights_mixin(t_scene *scene, t_vec3f p, t_shape *shape, t_vec3f normal)
{
	t_color	light_cols;
	t_color	cur_col;
	size_t	i;

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
