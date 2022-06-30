/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_objects.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 19:46:15 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/30 20:32:01 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"
#include "libft.h"
#include "parsing.h"

void	set_camera(t_camera *cam, char *settings)
{
	char		**split_settings;

	split_settings = ft_split(settings, ' ');
	if (settings == NULL)
		malloc_error();
	cam->position = get_vec3f_from_string(split_settings[1]);
	cam->rotation = get_vec3f_from_string(split_settings[2]);
	cam->fov = deg_to_rad(ft_atof(split_settings[3]));
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}

void	set_ambient_light(t_ambient_light *amb, char *settings)
{
	char		**split_settings;

	split_settings = ft_split(settings, ' ');
	if (settings == NULL)
		malloc_error();
	amb->range = ft_atof(split_settings[1]);
	amb->color = get_color_from_string(split_settings[2]);
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}

void	make_light(t_light *light, char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ' ');
	if (split_settings == NULL)
		malloc_error();
	light->position = get_vec3f_from_string(split_settings[1]);
	light->brightness = ft_atof(split_settings[2]);
	light->color = get_color_from_string(split_settings[3]);
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}

void	set_lights(t_scene *scene, t_line *file_content)
{
	size_t	current_light;
	size_t	i;

	i = 0;
	scene->lights = ft_calloc(scene->amount_lights, sizeof(t_light));
	if (scene->lights == NULL)
		malloc_error();
	current_light = 0;
	while (file_content[i].line != NULL)
	{
		if (rt_objstrcmp(LIGHT, file_content[i].line))
		{
			make_light(&scene->lights[current_light], file_content[i].line);
			current_light++;
		}
		i++;
	}
}

t_line	*find_obj_in_file(char *definition, t_line *file_content)
{
	size_t	current_line;

	current_line = 0;
	while (file_content[current_line].line != NULL)
	{
		if (rt_objstrcmp(definition, file_content[current_line].line))
			return (&file_content[current_line]);
		current_line++;
	}
	return (NULL);
}
