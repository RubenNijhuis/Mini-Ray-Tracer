/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_correctly_formatted.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:52:37 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/01 23:03:01 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "objects.h"

#include <stdbool.h>	// Bool
#include <stdlib.h>		// uint32_t
#include <stdio.h>		// printf

static void	one_ambient_light(char **file_content)
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
				exit_error("redundant ambient light");
		}
		current_line++;
	}
	if (amount_amb_light == 0)
		exit_error("no ambient light set");
}

static void	one_camera(char **file_content)
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
				exit_error("redundant camera");
		}
		current_line++;
	}
	if (amount_camera == 0)
		exit_error("no camera set");
}

static void	one_light(char **file_content)
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
				exit_error("redundant light");
		}
		current_line++;
	}
	if (amount_light == 0)
		exit_error("no light set");
	if (amount_light > MAX_LIGHTS)
		exit_error("way too many lights");
}

static void	amount_shapes(char **file_content)
{
	uint32_t	amount_shapes;
	uint32_t	current_line;

	amount_shapes = 0;
	current_line = 0;
	while (file_content[current_line] != NULL)
	{
		if (ft_char_of_str_n_str(SCENE_SHAPES, \
			file_content[current_line]) == true)
		{
			amount_shapes++;
			if (amount_shapes > MAX_SHAPES)
				exit_error("way too many shapes");
		}
		current_line++;
	}
}

// object_have_settings(file_content);
void	is_correctly_formatted(char **file_content)
{
	one_camera(file_content);
	one_ambient_light(file_content);
	one_light(file_content);
	amount_shapes(file_content);
}
