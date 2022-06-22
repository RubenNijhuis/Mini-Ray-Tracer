/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_objects.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 19:46:15 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/22 10:56:49 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"
#include "libft.h"
#include "parsing.h"

void	set_camera(t_scene *scene, t_line *file_content)
{
	uint32_t	i;
	char		**settings;
	uint32_t	amount_cameras;

	i = 0;
	amount_cameras = 0;
	while (file_content[i].line != NULL)
	{
		if (ft_strncmp(&file_content[i].line[0], CAMERA, 1) == 0)
		{
			amount_cameras++;
			settings = ft_split(file_content[i].line, ' ');
			if (settings == NULL)
				malloc_error();
			scene->camera.position = get_vec3f_from_string(settings[1]);
			scene->camera.orientation = get_vec3f_from_string(settings[2]);
			scene->camera.fov = deg_to_rad(ft_atof(settings[3]));
			ft_free_2d_array(&settings, ft_2d_arrlen(settings));
		}
		i++;
	}
}

void	set_ambient_light(t_scene *scene, t_line *file_content)
{
	uint32_t	i;
	char		**settings;

	i = 0;
	while (file_content[i].line != NULL)
	{
		if (ft_strncmp(&file_content[i].line[0], AMBIENT_LIGHT, 1) == 0)
		{
			settings = ft_split(file_content[i].line, ' ');
			if (settings == NULL)
				malloc_error();
			scene->amb_light.range = ft_atof(settings[1]);
			scene->amb_light.color = get_color_from_string(settings[2]);
			ft_free_2d_array(&settings, ft_2d_arrlen(settings));
			return ;
		}
		i++;
	}
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

void	set_lights(t_scene *scene, t_line *lines)
{
	uint32_t	current_light;
	uint32_t	i;

	i = 0;
	scene->lights = ft_calloc(scene->amount_lights, sizeof(t_light));
	if (scene->lights == NULL)
		malloc_error();
	current_light = 0;
	while (lines[i].line != NULL)
	{
		if (lines[i].line[0] == 'L')
		{
			make_light(&scene->lights[current_light], lines[i].line);
			current_light++;
		}
		i++;
	}
}
