/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_file_correctly_formatted.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:52:37 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/07/07 13:14:35 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "objects.h"
#include "parsing.h"
#include "ft_printf.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct s_obj_type_map
{
	const char			*type_str;
	const t_object_type	type;
}	t_obj_type_map;

int32_t	get_obj_type(const char *str)
{
	size_t						i;
	static const t_obj_type_map	map[] = {
	{SPHERE, sphere},
	{PLANE, plane},
	{CYLINDER, cylinder},
	{CAMERA, camera},
	{AMBIENT_LIGHT, ambient_light},
	{LIGHT, light},
	{DISC, disc},
	};

	i = 0;
	while (i < sizeof(map) / sizeof(t_obj_type_map))
	{
		if (rt_objstrcmp(map[i].type_str, str))
			return (map[i].type);
		i++;
	}
	return (-1);
}

void	check_input_lines(t_line *lines)
{
	int32_t	obj_type;
	size_t	current_line;

	current_line = 0;
	while (lines[current_line].line != NULL)
	{
		obj_type = get_obj_type(lines[current_line].line);
		if (obj_type != -1)
			run_object_checks(obj_type, lines[current_line]);
		else if (ft_strlen(lines[current_line].line) > 1)
		{
			ft_dprintf(2,
				"Error: line %i not object or non-empty line\n",
				lines[current_line].file_line);
			exit(1);
		}
		lines++;
	}
}

// checks if the number of objects for each type are correct.
// also sets the amount_lights and amount_shapes.
void	is_file_correctly_formatted(t_scene *scene, t_line *lines)
{
	check_amount_mandatory(lines, CAMERA, 1, "camera");
	check_amount_mandatory(lines, AMBIENT_LIGHT, 1, "ambient light");
	scene->amount_lights = check_amount_mandatory(lines, LIGHT,
			MAX_LIGHTS, "light");
	scene->amount_shapes = check_amount_generic(lines, SCENE_SHAPES,
			MAX_SHAPES, "shape");
	check_input_lines(lines);
}
