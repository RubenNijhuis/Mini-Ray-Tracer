/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   element_checks.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/29 16:20:14 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/26 13:57:18 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "parsing.h"
#include "ft_printf.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

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
	if (check_floats_formatting(split_settings) == false)
	{
		print_err_msg("orientation vec", "values formatted incorrectly", \
			line_pos);
		status = false;
	}
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
	if (check_floats_formatting(split_settings) == false)
	{
		print_err_msg("orientation vec", "values formatted incorrectly", \
			line_pos);
		status = false;
	}
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

/**
 * @brief 
 * Checks the color vector of an object. Only allows rgb values 
 * (3 values between 0 - 255). Will return false if any other number 
 * or character is found.
 * @param settings 
 * @param line_pos 
 * @return bool
 */
bool	check_color(char *settings, uint32_t line_pos)
{
	char	**split_settings;
	bool	status;

	status = true;
	split_settings = ft_split(settings, ',');
	if (check_ints_formatting(split_settings) == false)
	{
		print_err_msg("color vec", "values formatted incorrectly", line_pos);
		status = false;
	}
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

/**
 * @brief 
 * Checks the radius of an object and only allows proper 
 * float formatting.
 * @param settings 
 * @param line_pos 
 * @return bool
 */
bool	check_radius(char *settings, uint32_t line_pos)
{
	bool	status;

	status = true;
	if (is_float_format(settings) == false)
	{
		print_err_msg("radius variable", "value formatted incorrectly", \
			line_pos);
		status = false;
	}
	if (ft_atof(settings) < 0)
	{
		print_err_msg("radius variable", "value out of range", line_pos);
		status = false;
	}
	return (status);
}

/**
 * @brief 
 * Checks the height of the object. Only allows proper float format
 * 
 * @param settings 
 * @param line_pos 
 * @return bool
 */
bool	check_height(char *settings, uint32_t line_pos)
{
	bool	status;

	status = true;
	if (is_float_format(settings) == false)
	{
		print_err_msg("height variable", "value formatted incorrectly", \
			line_pos);
		status = false;
	}
	if (ft_atof(settings) <= 0)
	{
		print_err_msg("height variable", "value out of range", line_pos);
		status = false;
	}
	return (status);
}

/**
 * @brief 
 * Checks the fov variable of the camera. Only allows proper integer format
 *
 * @param settings 
 * @param line_pos 
 * @return bool
 */
bool	check_fov(char *settings, uint32_t line_pos)
{
	bool	status;

	status = true;
	if (is_integer_format(settings) == false)
	{
		print_err_msg("fov variable", "value formatted incorrectly", line_pos);
		status = false;
	}
	if (ft_atoi(settings) > 180 || ft_atoi(settings) < 0)
	{
		print_err_msg("fov variable", "value out of range", line_pos);
		status = false;
	}
	return (status);
}

/**
 * @brief
 * Checks the value of the brightness variable. Only allows proper float format
 * and values in between (0, 1)
 *
 * @param settings
 * @param line_pos
 * @return bool
 */
bool	check_brightness(char *settings, uint32_t line_pos)
{
	bool	status;

	status = true;
	if (is_float_format(settings) == false)
	{
		print_err_msg("brightness variable", "value formatted incorrectly", \
			line_pos);
		status = false;
	}
	if (ft_atof(settings) > 1 || ft_atof(settings) < 0)
	{
		print_err_msg("brightness variable", "value out of range", line_pos);
		status = false;
	}
	return (status);
}
