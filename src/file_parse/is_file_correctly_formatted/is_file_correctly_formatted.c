/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_file_correctly_formatted.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:52:37 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/04 16:37:06 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "objects.h"

#include <stdbool.h>
#include <stdint.h>

static void	check_amount_shapes(char **file_content)
{
	uint32_t	amount_shapes;
	uint32_t	current_line;

	amount_shapes = 0;
	current_line = 0;
	while (file_content[current_line] != NULL)
	{
		if (ft_is_object(SCENE_SHAPES, \
			file_content[current_line]) == true)
		{
			amount_shapes++;
			if (amount_shapes > MAX_SHAPES)
			{
				ft_putstr_fd("Error: too many shapes(max ", 2);
				ft_putnbr_fd(MAX_SHAPES, 2);
				exit_error(")");
			}
		}
		current_line++;
	}
}

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
		if (ft_strncmp(str, map[i].type_str, 2) == 0)
		{
			return (map[i].type);
		}
		i++;
	}
	return (-1);
}

void	check_input_lines(char **lines)
{
	uint32_t		current_line;
	int				obj_type;

	current_line = 0;
	while (lines[current_line] != NULL)
	{
		obj_type = get_obj_type(lines[current_line]);
		if (obj_type != -1)
			run_object_checks(obj_type, lines[current_line]);
		current_line++;
	}
}

// object_have_settings(file_content);
void	is_file_correctly_formatted(char **file_content)
{
	check_amount_cameras(file_content);
	check_amount_ambient_lights(file_content);
	check_amount_lights(file_content);
	check_amount_shapes(file_content);
	check_input_lines(file_content);
}
