/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_vectors.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 17:11:35 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/27 17:13:18 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "ft_printf.h"
#include "parsing.h"

#include <stdbool.h>
#include <stdint.h>

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
