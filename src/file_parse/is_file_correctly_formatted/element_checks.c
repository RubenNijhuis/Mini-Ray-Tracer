/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   element_checks.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/29 16:20:14 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/22 15:17:54 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "parsing.h"
#include "ft_printf.h"

// needed ?
#include <float.h>

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

void	print_err_msg(char *data_type, char *issue, uint32_t line)
{
	ft_dprintf(2, "Error: %s %s on line %i\n", data_type, issue, line);
}

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
		print_err_msg("position vec", "doesn't contain 3 values", line_pos);
		status = false;
	}
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
	return (status);
}

/**
 * @brief 
 * Checks if the orientation vector is formatted correctly.
 * Returns a bool - true if correct, false otherwise
 * 
 * @param settings 
 * @return bool
 */
bool	check_orientation(char *settings, uint32_t line_pos)
{
	char	**split_settings;
	bool	status;

	status = true;
	split_settings = ft_split(settings, ',');
	if (ft_2d_arrlen(split_settings) != 3)
	{
		print_err_msg("orientation vec", "doesn't contain 3 values", line_pos);
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
		print_err_msg("color vec", "values out of range", line_pos);
		status = false;
	}
	if (ft_2d_arrlen(split_settings) != 3)
	{
		print_err_msg("color vec", "doesn't contain 3 values", line_pos);
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
		print_err_msg("radius variable", "out of range", line_pos);
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
		print_err_msg("height variable", "value out of range", line_pos);
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
		print_err_msg("fov variable", "out of range", line_pos);
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
		print_err_msg("brightness variable", "out of range", line_pos);
		status = false;
	}
	return (status);
}
