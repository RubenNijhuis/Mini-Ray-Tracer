/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:43 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/01 11:32:00 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

//	t_camera t_ambient_light
//	t_light t_object
# include "objects.h"

// uint32_t
# include <stdlib.h>
// bool
# include <stdbool.h>

// If rendering in bonus mode
# ifndef BONUS
#  define BONUS 1
# endif

// The program can only handle so much ;)
# define MAX_SHAPES 100
# define MAX_LIGHTS 100

typedef struct program_data
{
	t_scene	scene;
}t_program_data;

// Setup components
void		set_camera(t_scene *scene, char **file_content);
void		set_ambient_light(t_scene *scene, char **file_content);
void		set_lights(t_scene *scene, char **file_content);
void		set_shapes(t_scene *scene, char **file_content);

// Vec from string
t_vec3i		get_vec3i_from_string(char *str);
t_vec3f		get_vec3f_from_string(char *str);

// Utils
void		is_correctly_formatted(char **file_content);
char		*get_file_content(char *file_name);
double		ft_atof(const char *str);
void		exit_error(char *str);
uint32_t	get_amount_objects(char **file_contents, char *type);
bool		ft_char_of_str_n_str(char *h, char *n);
char		*get_shape_type_string(t_object_type obj_type);

#endif