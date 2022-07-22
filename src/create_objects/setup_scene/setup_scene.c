/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 11:20:43 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/07/22 19:02:25 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"
#include "libft.h"
#include "parsing.h"
#include "ft_printf.h"

#include <stdlib.h>

typedef struct s_create_shape_func
{
	const char	*name;
	void		(*obj_func)(t_shape *, char *);
}	t_create_shape_func;

static void	lookup_shape_creation_func(t_shape *shape, char *name)
{
	size_t						i;
	const t_create_shape_func	funcs[] = {
	{SPHERE, &make_sphere},
	{PLANE, &make_plane},
	{CYLINDER, &make_cylinder},
	{DISC, &make_disc}
	};

	i = 0;
	while (i < sizeof(funcs) / sizeof(t_create_shape_func))
	{
		if (ft_strncmp(name, funcs[i].name, 2) == 0)
			(*funcs[i].obj_func)(shape, name);
		i++;
	}
}

/**
 * @brief 
 * Goes through the strings of a file and checks wether 
 * a string is a type of shape. If so create an object 
 * based on the object function.
 * 
 * @param shapes 
 * @param objects 
 */
static void	convert_strings_to_shapes(t_shape *shapes, t_line *lines)
{
	uint32_t	amount_objects;
	size_t		current_line;

	amount_objects = 0;
	current_line = 0;
	while (lines[current_line].line != NULL)
	{
		if (lines[current_line].type == comment)
		{
		}
		else if (ft_is_object(SCENE_SHAPES, lines[current_line].line))
		{
			lookup_shape_creation_func(&shapes[amount_objects], \
				lines[current_line].line);
			amount_objects++;
		}
		else if (!ft_is_object(SCENE_ELEMENTS, lines[current_line].line)
			&& lines[current_line].line[0] != '\0')
		{
			ft_dprintf(2, "Error: unrecognized object on line %u\n",
				lines[current_line].file_line);
			exit(1);
		}
		lines++;
	}
}

void	set_shapes(t_scene *scene, t_line *file_content)
{
	scene->shapes = ft_calloc(scene->amount_shapes, sizeof(t_shape));
	if (scene->shapes == NULL)
		malloc_error();
	convert_strings_to_shapes(scene->shapes, file_content);
}
