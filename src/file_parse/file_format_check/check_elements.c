/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_elements.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/29 16:20:14 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/07/26 17:52:31 by jobvan-d      ########   odam.nl         */
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
	if (is_valid_double_format(settings) == false)
	{
		print_err_msg("radius variable", line_pos, format);
		status = false;
	}
	if (ft_atof(settings) < 0)
	{
		print_err_msg("radius variable", line_pos, out_of_range);
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
	if (is_valid_double_format(settings) == false)
	{
		print_err_msg("height variable", line_pos, format);
		status = false;
	}
	if (ft_atof(settings) <= 0)
	{
		print_err_msg("height variable", line_pos, out_of_range);
		status = false;
	}
	return (status);
}

#if BONUS

/**
 * @brief 
 * Checks the fov variable of the camera. For bonus, also allows float format.
 *
 * @param settings 
 * @param line_pos 
 * @return bool
 */
bool	check_fov(char *settings, uint32_t line_pos)
{
	bool	status;

	status = true;
	if (is_valid_double_format(settings) == false)
	{
		print_err_msg("fov variable", line_pos, format);
		status = false;
	}
	if (ft_atof(settings) >= 180.0f || ft_atof(settings) <= 0.0f)
	{
		print_err_msg("fov variable", line_pos, out_of_range);
		status = false;
	}
	return (status);
}

#else

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
		print_err_msg("fov variable", line_pos, format);
		status = false;
	}
	if (ft_atoi(settings) >= 180 || ft_atoi(settings) <= 0)
	{
		print_err_msg("fov variable", line_pos, out_of_range);
		status = false;
	}
	return (status);
}

#endif

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
	if (is_valid_double_format(settings) == false)
	{
		print_err_msg("brightness variable", line_pos, format);
		status = false;
	}
	if (ft_atof(settings) > 1 || ft_atof(settings) < 0)
	{
		print_err_msg("brightness variable", line_pos, out_of_range);
		status = false;
	}
	return (status);
}
