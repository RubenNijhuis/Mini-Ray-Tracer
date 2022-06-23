/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_file_correctly_formatted.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:52:37 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/23 15:02:01 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "objects.h"
#include "parsing.h"
#include "ft_printf.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct ss_obj_type_map
{
	const char			*type_str;
	const t_object_type	type;
}	t_obj_type_map;

int	get_obj_type(const char *str)
{
	static const t_obj_type_map	map[] = {
	{SPHERE, sphere},
	{PLANE, plane},
	{CYLINDER, cylinder},
	{CAMERA, camera},
	{AMBIENT_LIGHT, ambient_light},
	{LIGHT, light}
	};
	size_t						i;

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
	int			obj_type;
	uint32_t	current_line;
	bool		formatted_correctly;

	formatted_correctly = true;
	current_line = 0;
	while (lines[current_line].line != NULL)
	{
		obj_type = get_obj_type(lines[current_line].line);
		if (obj_type != -1)
		{
			if (run_object_checks(obj_type, lines[current_line]) == false)
				formatted_correctly = false;
		}
		else if (ft_strlen(lines[current_line].line) > 1)
		{
			ft_dprintf(2, 
				"Error: line %i not object or non-empty line\n",
				lines[current_line].file_line);
			formatted_correctly = false;
		}
		lines++;
	}
	if (formatted_correctly == false)
		exit(1);
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
