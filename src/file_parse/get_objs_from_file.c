/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_objs_from_file.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 19:37:07 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/29 20:36:12 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "objects.h"
#include "minirt.h"

#include <stdbool.h>// true false
#include <fcntl.h>  // open
#include <stdio.h> 	// printf
#include <stdlib.h> // uint32_t

char	*get_file_contents(int fd)
{
	char	*total_string;
	char	*new_str;
	char	*tmp;

	total_string = ft_calloc(1, sizeof(char));
	tmp = ft_calloc(1, sizeof(char));
	while (1)
	{
		new_str = get_next_line(fd);
		if (new_str == NULL)
			break ;
		free(total_string);
		total_string = ft_strjoin(tmp, new_str);
		free(tmp);
		free(new_str);
		tmp = ft_strdup(total_string);
	}
	free(tmp);
	free(new_str);
	return (total_string);
}

// objects_array[0].type = ambient_light;
// colors = ft_split(object_settings[2], ',');
// objects_array[0].colors = vec3_from_array(colors);

// t_object	create_object_from_type(char *settings)
// {
	
// }


/*
	Checks wether a char of a string is in another string
	Loops through string one and compares if a char in 
	string two is equal to the current char in string one
 */
bool	ft_charnstr(char *h, char *n)
{
	int	i;

	i = 0;
	while (h[i] != '\0')
	{
		if (ft_strncmp(&h[i], n, 1) == 0)
			return (true);
		i++;
	}
	return (false);
}

uint32_t	get_amount_objects(char **file_contents, char *type)
{
	uint32_t	amount_objects;
	uint32_t	i;

	i = 0;
	amount_objects = 0;
	while (file_contents[i] != NULL)
	{
		if (ft_charnstr(type, file_contents[i]) == true)
			amount_objects++;
		i++;
	}
	return (amount_objects);
}

t_vec	get_vec_from_string(char *str)
{
	uint32_t	i;
	t_vec		vec;
	char 		**split_vec;

	split_vec = ft_split(str, ',');
	i = 0;
	while (i < 3)
	{
		vec.values[i] = ft_atoi(split_vec[i]);
		i++;
	}
	ft_free_2d_array(&split_vec, 3);
	return (vec);
}

void	make_sphere(t_object *sphere_obj, char *settings)
{
	char		**split_settings;
	
	split_settings = ft_split(settings, ' ');
	sphere_obj->sphere.base.obj_type = sphere;
	sphere_obj->sphere.base.position = get_vec_from_string(split_settings[1]);
	sphere_obj->sphere.diameter = ft_atoi(split_settings[2]);
	sphere_obj->cylinder.height = 100;
	sphere_obj->sphere.base.color = get_vec_from_string(split_settings[3]);
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}

void	convert_strings_to_objects(t_object *shapes, char **objects)
{
	uint32_t	i;
	uint32_t	amount_objects;

	i = 0;
	amount_objects = 0;
	while (objects[i] != NULL)
	{
		if (ft_charnstr(SCENE_SHAPES, objects[i]))
		{
			if (ft_strncmp(objects[i], SPHERE, 2) == 0)
				make_sphere(&shapes[amount_objects], objects[i]);
			else if (ft_strncmp(objects[i], PLANE, 2) == 0)
				printf("what\n");
			else if (ft_strncmp(objects[i], CYLINDER, 2) == 0)
				printf("what\n");
			else if (ft_strncmp(objects[i], CUBE, 2) == 0)
				printf("what\n");
			amount_objects++;
				// make_plane(shapes[amount_objects], objects[i]);
		}
		i++;
	}
	if (shapes[0].base.obj_type == sphere)
	{
		printf("%i \n", shapes[0].base.obj_type);
		printf("%i \n", shapes[0].sphere.diameter);
	}
}

void	get_objects_from_file(t_program_data *pd, char *file_name)
{
	char			*file_contents;
	char			**items_from_file;

	int fd = open(file_name, O_RDONLY);

	file_contents = get_file_contents(fd);
	items_from_file = ft_split(file_contents, '\n');

	pd->amount_shapes = get_amount_objects(items_from_file, SCENE_SHAPES);
	pd->shapes = ft_calloc(pd->amount_shapes, sizeof(t_object));
	convert_strings_to_objects(pd->shapes, items_from_file);
	ft_free_2d_array(&items_from_file, ft_2d_arrlen(items_from_file));
}
