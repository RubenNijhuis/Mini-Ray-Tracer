/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_file_correctly_formatted.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:52:37 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/26 09:53:09 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "objects.h"

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

// object_have_settings(file_content);
void	is_file_correctly_formatted(char **file_content)
{
	check_amount_cameras(file_content);
	check_amount_ambient_lights(file_content);
	check_amount_lights(file_content);
	check_amount_shapes(file_content);
}
