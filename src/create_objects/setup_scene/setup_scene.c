/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 11:20:43 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/25 19:46:10 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"
#include "libft.h"

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
