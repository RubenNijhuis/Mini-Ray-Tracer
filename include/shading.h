/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shading.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 19:59:03 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/08/03 20:17:29 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADING_H
# define SHADING_H

# include "minirt.h"

typedef struct s_light_data
{
	t_light	*light;
	t_scene	*scene;
	t_shape	*shape;
	t_vec3f	point;
	t_vec3f	normal;
}	t_light_data;

void	shade(t_color *color, t_light_data *light_data, t_ray *light_ray);

#endif
