/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 11:20:43 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/30 20:32:15 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"
#include "libft.h"
#include "parsing.h"

typedef struct s_make_func
{
	const char	*name;
	void		(*obj_func)(t_shape *, char *);
}	t_make_func;

static void	lookup_shape_function(t_shape *shape, char *name)
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
static void	convert_strings_to_shapes(t_shape *shapes, t_line *object_strings)
{
	uint32_t	amount_objects;
	size_t		current_line;

	amount_objects = 0;
	current_line = 0;
	while (object_strings[current_line].line != NULL)
	{
		if (ft_is_object(SCENE_SHAPES, object_strings[current_line].line))
		{
			lookup_shape_function(&shapes[amount_objects], \
				object_strings[current_line].line);
			amount_objects++;
		}
		object_strings++;
	}
}

void	set_shapes(t_scene *scene, t_line *file_content)
{
	scene->shapes = ft_calloc(scene->amount_shapes, sizeof(t_shape));
	if (scene->shapes == NULL)
		malloc_error();
	convert_strings_to_shapes(scene->shapes, file_content);
}
