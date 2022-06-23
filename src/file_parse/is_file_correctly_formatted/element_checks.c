/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   element_checks.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/29 16:20:14 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/23 14:43:41 by rubennijhui   ########   odam.nl         */
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

bool	is_float_format(char *digit)
{
	uint32_t	current_char;
	bool		has_dot;
	bool		format_status;

	has_dot = false;
	format_status = true;
	current_char = 0;
	if (ft_strlen(digit) > 14)
		return (false);
	if (digit[current_char] == '-')
		current_char++;
	while (digit[current_char] != '\0')
	{
		if ((digit[current_char] < '0' || digit[current_char] > '9') && \
			digit[current_char] != '.')
			format_status = false;
		else if (digit[current_char] == '.' && has_dot == false)
			has_dot = true;
		current_char++;
	}
	return (format_status);
}

bool	is_integer_format(char *digit)
{
	uint32_t	current_char;
	bool		format_status;

	format_status = true;
	current_char = 0;
	if (ft_strlen(digit) > 14)
		return (false);
	if (digit[current_char] == '-')
		current_char++;
	while (digit[current_char] != '\0')
	{
		if (digit[current_char] < '0' || digit[current_char] > '9')
			format_status = false;
		current_char++;
	}
	return (format_status);
}

void	print_err_msg(char *data_type, char *issue, uint32_t line)
{
	ft_dprintf(2, "Error: %s %s on line %i\n", data_type, issue, line);
}

// It not worky
bool	check_values_range_float(char **items, float min, float max)
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
			break ;
		}
		current_item++;
	}
	return (status);
}

bool	check_floats_formatting(char **items)
{
	uint32_t	cur_float;

	cur_float = 0;
	while (cur_float < 3)
	{
		if (is_float_format(items[cur_float]) == false)
			return (false);
		cur_float++;
	}
	return (true);
}

bool	check_ints_formatting(char **items)
{
	uint32_t	cur_float;

	cur_float = 0;
	while (cur_float < 3)
	{
		if (is_float_format(items[cur_float]) == false)
			return (false);
		cur_float++;
	}
	return (true);
}

bool	check_values_range_int(char **items, int64_t min, int64_t max)
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
			break ;
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
	// if (check_values_range_float(split_settings, -FLT_MIN, FLT_MAX) == false)
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
	if (check_values_range_float(split_settings, -1, 1) == false)
	{
		print_err_msg("orientation vec", "values out of range", line_pos);
		status = false;
	}
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
	if (check_values_range_int(split_settings, 0, 255) == false)
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
	if (is_float_format(settings) == false)
	{
		print_err_msg("radius variable", "value formatted incorrectly", line_pos);
		status = false;
	}
	if (ft_atof(settings) > FLT_MAX || ft_atof(settings) < 0)
	{
		print_err_msg("radius variable", "value out of range", line_pos);
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
	if (is_float_format(settings) == false)
	{
		print_err_msg("height variable", "value formatted incorrectly", line_pos);
		status = false;
	}
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
		print_err_msg("fov variable", "value out of range", line_pos);
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
	if (is_float_format(settings) == false)
	{
		print_err_msg("brightness variable", "value formatted incorrectly", line_pos);
		status = false;
	}
	if (ft_atof(settings) > 1 || ft_atof(settings) < 0)
	{
		print_err_msg("brightness variable", "value out of range", line_pos);
		status = false;
	}
	return (status);
}
