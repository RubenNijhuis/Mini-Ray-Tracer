/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   element_checks.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/29 16:20:14 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/22 00:24:03 by rubennijhui   ########   odam.nl         */
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
	size_t arr_len;
	size_t current_item;
	bool status;
	float current_val;

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
bool	check_position(t_line *settings)
{
	char	**split_settings;
	bool	status;

	status = true;
	split_settings = ft_split(settings->line, ',');
	// if (check_arr_values_range_float(split_settings, -FLT_MIN, FLT_MAX) == false)
	// {
	// 	printf("Error: position vec values out of range (-FLT_MIN - FLT_MAX)\n");
	// 	status = false;
	// }
	if (ft_2d_arrlen(split_settings) != 3)
	{
		printf("Error: position vec on line %i doesn't contain 3 values\n", settings->file_line);
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
bool	check_rotation(t_line *settings)
{
	char	**split_settings;
	bool	status;

	status = true;
	split_settings = ft_split(settings->line, ',');
	if (ft_2d_arrlen(split_settings) != 3)
	{
		printf("Error: rotation vec on line %i formatted incorrectly\n", settings->file_line);
		status = false;
	}
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
	return (status);
}

bool	check_color(t_line *settings)
{
	char	**split_settings;
	bool	status;

	status = true;
	split_settings = ft_split(settings->line, ',');
	if (check_arr_values_range_int(split_settings, 0, 255) == false)
	{
		printf("Error: color vec values on line %i out of range\n", settings->file_line);
		status = false;
	}
	if (ft_2d_arrlen(split_settings) != 3)
	{
		printf("Error: color vec formatted incorrectly\n");
		status = false;
	}
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
	return (status);
}

// check is only num
// check is in max float min float
bool	check_radius(t_line *settings)
{
	bool	status;

	status = true;
	if (ft_atof(settings->line) > FLT_MAX)
	{
		printf("Error: radius variable formatted incorrectly\n");
		status = false;
	}
	return (status);
}

// check is in max float min float
// check is only num
bool	check_height(t_line *settings)
{
	bool	status;

	status = true;
	if (ft_atof(settings) > FLT_MAX)
	{
		printf("Error: height variable formatted incorrectly\n");
		status = false;
	}
	return (status);
}

// check is only num
// check if is int and nog bigger than 180 or smaller than 1
bool	check_fov(t_line *settings)
{
	bool	status;

	status = true;
	if (ft_atoi(settings) > 180 || ft_atoi(settings) < 1)
	{
		printf("Error: fov variable out of range\n");
		status = false;
	}
	return (status);
}

// check is only num
// check is in max float min float
bool	check_brightness(t_line *settings)
{
	bool	status;

	status = true;
	if (ft_atof(settings) > FLT_MAX)
	{
		printf("Error: brightness variable formatted incorrectly\n");
		status = false;
	}
	return (status);
}
