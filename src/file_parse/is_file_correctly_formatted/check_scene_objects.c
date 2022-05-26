/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_scene_objects.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 09:43:08 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/26 10:15:53 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "libft.h"

#include <stdlib.h>
#include <stdint.h>

void	check_amount_ambient_lights(char **file_content)
{
	uint32_t	amount_amb_light;
	uint32_t	current_line;

	amount_amb_light = 0;
	current_line = 0;
	while (file_content[current_line] != NULL)
	{
		if (ft_strncmp(&file_content[current_line][0], AMBIENT_LIGHT, 1) == 0)
		{
			amount_amb_light++;
			if (amount_amb_light > 1)
				exit_error("Error: redundant ambient light");
		}
		current_line++;
	}
	if (amount_amb_light == 0)
		exit_error("Error: ambient light not set");
}

void	check_amount_cameras(char **file_content)
{
	uint32_t	amount_camera;
	uint32_t	current_line;

	amount_camera = 0;
	current_line = 0;
	while (file_content[current_line] != NULL)
	{
		if (ft_strncmp(&file_content[current_line][0], CAMERA, 1) == 0)
		{
			amount_camera++;
			if (amount_camera > 1)
				exit_error("Error: redundant camera");
		}
		current_line++;
	}
	if (amount_camera == 0)
		exit_error("Error: camera not set");
}

void	check_amount_lights(char **file_content)
{
	uint32_t	amount_light;
	uint32_t	current_line;

	amount_light = 0;
	current_line = 0;
	while (file_content[current_line] != NULL)
	{
		if (ft_strncmp(&file_content[current_line][0], LIGHT, 1) == 0)
		{
			amount_light++;
			if (BONUS != true && amount_light > 1)
				exit_error("Error: redundant light source");
		}
		current_line++;
	}
	if (amount_light == 0)
		exit_error("Error: no light(s) set");
	if (amount_light > MAX_LIGHTS)
		exit_error("Error: max shapes is 100");
}
