/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 11:20:43 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/02 13:34:17 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"
#include "libft.h"

void	set_camera(t_scene *scene, char **file_content)
{
	uint32_t	i;
	char		**settings;
	uint32_t	amount_cameras;

	i = 0;
	amount_cameras = 0;
	while (file_content[i] != NULL)
	{
		if (ft_strncmp(&file_content[i][0], CAMERA, 1) == 0)
		{
			amount_cameras++;
			settings = ft_split(file_content[i], ' ');
			scene->camera.position = get_vec3f_from_string(settings[1]);
			scene->camera.orientation = get_vec3f_from_string(settings[2]);
			scene->camera.fov = ft_atoi(settings[3]);
			ft_free_2d_array(&settings, ft_2d_arrlen(settings));
		}
		i++;
	}
}

void	set_ambient_light(t_scene *scene, char **file_content)
{
	uint32_t	i;
	char		**settings;

	i = 0;
	while (file_content[i] != NULL)
	{
		if (ft_strncmp(&file_content[i][0], AMBIENT_LIGHT, 1) == 0)
		{
			settings = ft_split(file_content[i], ' ');
			scene->amb_light.range = ft_atof(settings[1]);
			scene->amb_light.color = get_vec3i_from_string(settings[2]);
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
	light->position = get_vec3f_from_string(split_settings[1]);
	light->brightness = ft_atof(split_settings[2]);
	light->color = get_vec3i_from_string(split_settings[3]);
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}

void	set_lights(t_scene *scene, char **file_content)
{
	uint32_t	amount_lights;
	uint32_t	current_light;
	uint32_t	i;

	i = 0;
	amount_lights = get_amount_objects(file_content, "L");
	scene->lights = ft_calloc(amount_lights, sizeof(t_light));
	current_light = 0;
	while (file_content[i] != NULL)
	{
		if (ft_strncmp(&file_content[i][0], LIGHT, 1) == 0)
		{
			make_light(&scene->lights[current_light], file_content[i]);
			current_light++;
		}
		i++;
	}
	scene->amount_lights = amount_lights;
}

static void	convert_strings_to_shapes(t_object *shapes, char **objects)
{
	uint32_t	i;
	uint32_t	amount_objects;

	i = 0;
	amount_objects = 0;
	while (objects[i] != NULL)
	{
		if (ft_char_of_str_n_str(SCENE_SHAPES, objects[i]))
		{
			if (ft_strncmp(objects[i], SPHERE, 2) == 0)
				make_sphere(&shapes[amount_objects], objects[i]);
			else if (ft_strncmp(objects[i], PLANE, 2) == 0)
				make_plane(&shapes[amount_objects], objects[i]);
			else if (ft_strncmp(objects[i], CYLINDER, 2) == 0)
				make_cylinder(&shapes[amount_objects], objects[i]);
			amount_objects++;
		}
		i++;
	}
}

void	set_shapes(t_scene *scene, char **file_content)
{
	scene->amount_shapes = get_amount_objects(file_content, SCENE_SHAPES);
	scene->shapes = ft_calloc(scene->amount_shapes, sizeof(t_object));
	convert_strings_to_shapes(scene->shapes, file_content);
}
