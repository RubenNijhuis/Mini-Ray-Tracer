/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:43 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/30 23:38:44 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

//	t_camera t_ambient_light
//	t_light t_object
#include "objects.h"

// uint32_t
#include <stdlib.h>

// If rendering in bonus mode
# ifndef BONUS
#  define BONUS 0
# endif

// The program can only handle so much ;)
#define MAX_SHAPES 100
#define MAX_LIGHTS 100

typedef struct program_data
{
	t_camera		camera;

	t_ambient_light	amb_light;
	t_light			*lights;
	uint32_t		amount_lights;

	t_object		*shapes;
	uint32_t		amount_shapes;
}	t_program_data;

// Setup components
void	set_camera(t_program_data *pd, char **file_content);
void	set_ambient_light(t_program_data *pd, char **file_content);
void	set_lights(t_program_data *pd, char **file_content);
void	set_shapes(t_program_data *pd, char **file_content);

// Vec from string
t_vec3i	get_vec3i_from_string(char *str);
t_vec3f	get_vec3f_from_string(char *str);

// Utils
char	*get_file_content(char *file_name);
double	ft_atof(const char *str);

// Cant put this in objects.h
// Utils
void	print_shapes(t_object *shapes, uint32_t amount_shapes);
void	print_lights(t_light *lights, uint32_t amount_lights);
void	print_camera(t_camera camera);
void	print_scene_elements(t_program_data *pd);

#endif