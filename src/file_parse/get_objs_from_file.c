/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_objs_from_file.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 19:37:07 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/30 20:33:55 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "objects.h"
#include "minirt.h"

#include <stdbool.h>// true false
#include <stdlib.h> // uint32_t

/*
	Checks wether a char of a string is in another string
	Loops through string one and compares if a char in 
	string two is equal to the current char in string one
 */
bool	ft_char_of_str_n_str(char *h, char *n)
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
		if (ft_char_of_str_n_str(type, file_contents[i]) == true)
			amount_objects++;
		i++;
	}
	return (amount_objects);
}

void	convert_strings_to_objects(t_object *shapes, char **objects)
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

void	set_shapes(t_program_data *pd, char **file_content)
{
	pd->amount_shapes = get_amount_objects(file_content, SCENE_SHAPES);
	pd->shapes = ft_calloc(pd->amount_shapes, sizeof(t_object));
	convert_strings_to_objects(pd->shapes, file_content);
}
