/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_file_correctly_formatted.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:52:37 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/29 16:22:29 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "objects.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

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
				exit_error("Erro: max shapes is 200");
		}
		current_line++;
	}
}

int	get_obj_type(char *str)
{
	char	*substr;

	if (ft_strlen(str) > 2)
	{
		substr = ft_substr(str, 0, 2);
		if (ft_strncmp(substr, SPHERE, 2) == 0)
			return (sphere);
		if (ft_strncmp(substr, PLANE, 2) == 0)
			return (plane);
		if (ft_strncmp(substr, CYLINDER, 2) == 0)
			return (cylinder);
		if (ft_strncmp(substr, CAMERA, 2) == 0)
			return (camera);
		if (ft_strncmp(substr, AMBIENT_LIGHT, 2) == 0)
			return (ambient_light);
		if (ft_strncmp(substr, LIGHT, 2) == 0)
			return (light);
		free(substr);
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
