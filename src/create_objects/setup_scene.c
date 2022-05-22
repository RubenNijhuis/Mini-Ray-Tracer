/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 11:20:43 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/18 17:49:33 by jobvan-d      ########   odam.nl         */
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
	amount_lights = get_amount_objects(file_content, "L ");
	scene->lights = ft_calloc(amount_lights, sizeof(t_light));
	current_light = 0;
	while (file_content[i] != NULL)
	{
		if (file_content[i][0] == 'L')
		{
			make_light(&scene->lights[current_light], file_content[i]);
			current_light++;
		}
		i++;
	}
	scene->amount_lights = amount_lights;
}

typedef struct s_make_func
{
	const char	*name;
	void		(*obj_func)(t_object *, char *);
}	t_make_func;

static uint32_t	lookup_shape_function(t_object *shape, char *name)
{
	size_t				i;
	const t_make_func	funcs[] = {
	{SPHERE, &make_sphere},
	{PLANE, &make_plane},
	{CYLINDER, &make_cylinder}
	};

	i = 0;
	while (i < sizeof(funcs) / sizeof(t_make_func))
	{
		if (ft_strncmp(name, funcs[i].name, 2) == 0)
		{
			(*funcs[i].obj_func)(shape, name);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief 
 * Goes through the strings of a file and checks weather 
 * a string is a type of shape. If so create an object 
 * based on the object function.
 * 
 * @param shapes 
 * @param objects 
 */
static void	convert_strings_to_shapes(t_object *shapes, char **object_strings)
{
	uint32_t			amount_objects;

	amount_objects = 0;
	while (*object_strings != NULL)
	{
		if (ft_is_object(SCENE_SHAPES, *object_strings))
		{
			amount_objects += lookup_shape_function(&shapes[amount_objects],
					*object_strings);
		}
		object_strings++;
	}
}

void	set_shapes(t_scene *scene, char **file_content)
{
	scene->amount_shapes = get_amount_objects(file_content, SCENE_SHAPES);
	scene->shapes = ft_calloc(scene->amount_shapes, sizeof(t_object));
	convert_strings_to_shapes(scene->shapes, file_content);
}
