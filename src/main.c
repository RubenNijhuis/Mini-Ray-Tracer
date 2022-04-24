/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/24 19:32:04 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "objects.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

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

t_vector	*vec3_from_array(char **values)
{
	t_vector	*vec;
	int			i;

	i = 0;
	vec = ft_calloc(1, sizeof(vec));
	while (values[i] != NULL)
	{
		vec->values[i] = ft_atoi(values[i]);
		i++;
	}
	return (vec);
}

// t_object	make_model_object(char **object_settings)
// {

// }

// t_object	make_scene_object(char **object_settings)
// {
// 	char	*obj_type;
// 	char	**colors

// 	obj_type = object_settings[0];
// 	if (!ft_strncmp(obj_type, AMBIENT_LIGHT, ft_strlen(obj_type)))
// 	{
// 		objects_array[0].type = ambient_light;
// 		colors = ft_split(object_settings[2], ',');
// 		objects_array[0].colors = vec3_from_array(colors);
// 	}
// }

// t_object	object_from_settings(char **object_settings)
// {
// 	/*
// 		if (object.type != A || C || L) -> make model object
// 		else make scene object
// 	*/
// 	char **colors;
// 	if (!ft_strncmp(object_settings[0], CAMERA, ft_strlen(object_settings[0])))
// 	{
// 		objects_array[0].type = ambient_light;
// 		colors = ft_split(object_settings[2], ',');
// 		objects_array[0].colors = vec3_from_array(colors);
// 	}
// }

t_object	*get_objects_from_file(int fd)
{
	t_object		*objects_array;
	char			*file_contents;
	char			**objects_from_file;
	// char			**object_settings;

	file_contents = get_file_contents(fd);
	objects_from_file = ft_split(file_contents, '\n');
	objects_array = ft_calloc(ft_2d_arrlen(objects_from_file), sizeof(t_object));
	object_settings = ft_split(objects_from_file[0], ' ');
	convert_strings_to_objects(objects_array, object_settings);
	free(file_contents);
	ft_free_2d_array(&objects_from_file, ft_2d_arrlen(objects_from_file));
	ft_free_2d_array(&object_settings, ft_2d_arrlen(object_settings));
	return (objects_array);
}

int	main(int argc, char **argv)
{
	(void)argc;
	int			fd;
	t_object	*objs;

	setbuf(stdout, NULL);
	fd = open(argv[1], O_RDONLY);
	objs = get_objects_from_file(fd);
	printf("%ld\n", objs[0].colors->values[0]);
	return (0);
}
