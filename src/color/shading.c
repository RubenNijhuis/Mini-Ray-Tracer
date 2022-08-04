/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shading.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 19:59:39 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/08/04 16:11:43 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shading.h"

#include <math.h> /* pow */

void	ambient_mixin(t_color *col, t_scene *scene)
{
	t_color	amb;

	amb = scene->amb_light.color;
	color_multiply_scalar(&amb, scene->amb_light.range);
	color_multiply(col, &amb);
}

static t_vec3f	mirror_reflect(t_vec3f incoming, t_vec3f normal)
{
	float	angle;

	angle = vec3f_dot(incoming, normal);
	return (2.0f * angle * normal - incoming);
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

// specular shading, kind of like a reflection of the light.
// the pow is to make it smaller.
float	calculate_specular(t_light_data *light_data, t_ray *light_ray)
{
	t_vec3f	reflected;
	float	angle;
	float	intensity;

	reflected = mirror_reflect(light_ray->direction, light_data->normal);
	// because the ray direction is in the wrong way, invert the dot product.
	// this is faster than inverting the ray direction.
	angle = -vec3f_dot(reflected, light_data->orig_ray.direction);
	intensity = 0;
	if (angle > 0)
	{
		intensity = powf(angle, 12.0f);
	}
	return (intensity);
}

// thanks Bui Tuong Phong
void	shade(t_color *color, t_light_data *light_data, t_ray *light_ray)
{
	static const double	difspec_ratio = 0.89;

	*color = light_data->shape->base.color;
	color_multiply_scalar(color,
		difspec_ratio * calculate_diffuse(light_data, light_ray)
		+ (1 - difspec_ratio) * calculate_specular(light_data, light_ray));
	color_multiply(color, &light_data->light->color);
}
