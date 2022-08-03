/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shading.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 19:59:39 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/08/03 20:18:36 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shading.h"

void	ambient_mixin(t_color *col, t_scene *scene)
{
	t_color	amb;

	amb = scene->amb_light.color;
	color_multiply_scalar(&amb, scene->amb_light.range);
	color_multiply(col, &amb);
}

float	calculate_diffuse(t_light_data *light_data, t_ray *light_ray)
{
	float	intensity;

	intensity = vec3f_dot(light_ray->direction, light_data->normal);
	if (intensity <= 0.0f)
	{
		intensity = 0.0f;
	}
	else
	{
		intensity *= light_data->light->brightness;
	}
	return (intensity);
}

void	shade(t_color *color, t_light_data *light_data, t_ray *light_ray)
{
	*color = light_data->shape->base.color;
	color_multiply_scalar(color, calculate_diffuse(light_data, light_ray));
	color_multiply(color, &light_data->light->color);
}
