/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_shape_type_string.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 11:27:07 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/25 16:29:03 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <stdlib.h>

char	*get_shape_type_string(t_object_type obj_type)
{
	char	*obj_type_string;

	obj_type_string = NULL;
	if (obj_type == sphere)
		obj_type_string = "Sphere";
	else if (obj_type == plane)
		obj_type_string = "Plane";
	else if (obj_type == cylinder)
		obj_type_string = "Cylinder";
	return (obj_type_string);
}
