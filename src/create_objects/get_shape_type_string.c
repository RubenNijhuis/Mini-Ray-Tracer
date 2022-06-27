/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_shape_type_string.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 11:27:07 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/27 17:07:35 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <stdlib.h>

typedef struct s_obj_type_name
{
	t_object_type	obj_type;
	char			*name;
}	t_obj_type_name;

char	*get_shape_type_string(t_object_type obj_type)
{
	size_t					i;
	const t_obj_type_name	names[] = {
	{sphere, "Sphere"},
	{plane, "Plane"},
	{cylinder, "Cylinder"}
	};

	i = 0;
	while (i < sizeof(names) / sizeof(t_obj_type_name))
	{
		if (names[i].obj_type == obj_type)
			return (names[i].name);
		i++;
	}
	return (NULL);
}
