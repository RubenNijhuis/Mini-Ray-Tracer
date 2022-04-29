/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_objs_from_file.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 19:37:07 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/29 11:43:15 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "objects.h"

#include <fcntl.h>  // open
#include <stdio.h> // printf

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

t_object	create_object_from_type(char *settings)
{
	
}

void	convert_strings_to_objects(t_object *objects_array, char **objects);

t_object	*get_objects_from_file(char *file_name)
{
	t_object		*objects_array;
	char			*file_contents;
	char			**objects_from_file;
	int				amount_objects;

	int fd = open(file_name, O_RDONLY);

	file_contents = get_file_contents(fd);
	objects_from_file = ft_split(file_contents, '\n');
	amount_objects = ft_2d_arrlen(objects_from_file);
	objects_array = ft_calloc(amount_objects, sizeof(t_object));
	printf("%s", objects_from_file[0]);
	// convert_strings_to_objects(objects_array, objects_from_file);
	// free(file_contents);
	// ft_free_2d_array(&objects_from_file, ft_2d_arrlen(objects_from_file));
	return (objects_array);
}
