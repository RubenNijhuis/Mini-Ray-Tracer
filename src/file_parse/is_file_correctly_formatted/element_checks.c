/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   element_checks.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/29 16:20:14 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/22 14:47:22 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "parsing.h"

// needed ?
#include <float.h>

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

// It not worky
bool	check_arr_values_range_float(char **items, float min, float max)
{
	size_t	arr_len;
	size_t	current_item;
	bool	status;
	float	current_val;

	status = true;
	current_item = 0;
	arr_len = ft_2d_arrlen(items);
	while (current_item < arr_len)
	{
		current_val = ft_atof(items[current_item]);
		if (current_val < min || current_val > max)
		{
			printf("%f - %s\n", current_val, items[current_item]);
			status = false;
			break;
		}
		current_item++;
	}
	return (status);
}

bool	check_arr_values_range_int(char **items, int64_t min, int64_t max)
{
	size_t	arr_len;
	size_t	current_item;
	bool	status;
	int64_t	current_val;

	status = true;
	current_item = 0;
	arr_len = ft_2d_arrlen(items);
	while (current_item < arr_len)
	{
		current_val = ft_atoi(items[current_item]);
		if (current_val < min || current_val > max)
		{
			status = false;
			break;
		}
		current_item++;
	}
	return (status);
}

/**
 * @brief 
 * Checks if the position is formatted correctly.
 * Returns a bool - true if correct, false otherwise
 * 
 * @param settings 
 * @return bool
 */
bool	check_position(char *settings, uint32_t line_pos)
{
	char	**split_settings;
	bool	status;

	status = true;
	split_settings = ft_split(settings, ',');
	// if (check_arr_values_range_float(split_settings, -FLT_MIN, FLT_MAX) == false)
	// {
	// 	printf("Error: position vec values out of range (-FLT_MIN - FLT_MAX)\n");
	// 	status = false;
	// }
	if (ft_2d_arrlen(split_settings) != 3)
	{
		printf("Error: position vec on line %i doesn't contain 3 values\n", line_pos);
		status = false;
	}
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
	return (status);
}

/**
 * @brief 
 * Checks if the rotation vector is formatted correctly.
 * Returns a bool - true if correct, false otherwise
 * 
 * @param settings 
 * @return bool
 */
bool	check_rotation(char *settings, uint32_t line_pos)
{
	char	**split_settings;
	bool	status;

	status = true;
	split_settings = ft_split(settings, ',');
	if (ft_2d_arrlen(split_settings) != 3)
	{
		printf("Error: rotation vec on line %i formatted incorrectly\n", line_pos);
		status = false;
	}
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
	return (status);
}

bool	check_color(char *settings, uint32_t line_pos)
{
	char	**split_settings;
	bool	status;

	status = true;
	split_settings = ft_split(settings, ',');
	if (check_arr_values_range_int(split_settings, 0, 255) == false)
	{
		printf("Error: color vec values on line %i out of range\n", line_pos);
		status = false;
	}
	if (ft_2d_arrlen(split_settings) != 3)
	{
		printf("Error: color vec on line %i formatted incorrectly\n", line_pos);
		status = false;
	}
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
	return (status);
}

// check is only num
// check is in max float min float
bool	check_radius(char *settings, uint32_t line_pos)
{
	bool	status;

	status = true;
	if (ft_atof(settings) > FLT_MAX || ft_atof(settings) < 0)
	{
		printf("Error: radius variable on line %i formatted incorrectly\n", line_pos);
		status = false;
	}
	return (status);
}

// check is in max float min float
// check is only num
bool	check_height(char *settings, uint32_t line_pos)
{
	bool	status;

	status = true;
	if (ft_atof(settings) > FLT_MAX || ft_atof(settings) < 0)
	{
		printf("Error: height variable on line %i formatted incorrectly\n", line_pos);
		status = false;
	}
	return (status);
}

// check is only num
// check if is int and nog bigger than 180 or smaller than 1
bool	check_fov(char *settings, uint32_t line_pos)
{
	bool	status;

	status = true;
	if (ft_atoi(settings) > 180 || ft_atoi(settings) < 0)
	{
		printf("Error: fov variable on line %i out of range\n", line_pos);
		status = false;
	}
	return (status);
}

// check is only num
// check is in max float min float
bool	check_brightness(char *settings, uint32_t line_pos)
{
	bool	status;

	status = true;
	if (ft_atof(settings) > FLT_MAX)
	{
		printf("Error: brightness variable on line %i formatted incorrectly\n", line_pos);
		status = false;
	}
	return (status);
}
