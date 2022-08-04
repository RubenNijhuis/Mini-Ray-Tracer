/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light_calc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:13:07 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/08/04 16:25:45 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shading.h"

#include <stddef.h>

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
t_color	get_light(t_light_data *lighting)
{
	t_ray	ray;
	t_color	color;
	float	max_dist_sq;

	ray.direction = lighting->light->position - lighting->point;
	max_dist_sq = vec3f_len_sq(ray.direction);
	vec3f_normalize(&ray.direction);
	ray.origin = lighting->point + (ray.direction * 0.0001f)
		+ (lighting->normal * 0.0002f);
	if (scene_intersects(lighting->scene, &ray, max_dist_sq))
	{
		color = make_color(0, 0, 0);
	}
	else
	{
		shade(&color, lighting, &ray);
	}
	return (color);
}

/**
 * @brief 
 * Goes through the lights array to calculate 
 * the color value of a pixel
 * @param color
 * @param light_data
 */
void	lights_mixin(t_color *color, t_light_data *light_data)
{
	t_color		cur_col;
	uint32_t	i;

	i = 0;
	while (i < light_data->scene->amount_lights)
	{
		light_data->light = &light_data->scene->lights[i];
		cur_col = get_light(light_data);
		color_add(color, &cur_col);
		i++;
	}
}
