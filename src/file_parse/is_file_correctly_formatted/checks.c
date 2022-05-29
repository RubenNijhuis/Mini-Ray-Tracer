/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/29 16:20:14 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/29 16:26:44 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>

bool	check_rotation(char *settings)
{
	char	**split_settings;
	bool	status;

	status = true;
	split_settings = ft_split(settings, ',');
	if (ft_2d_arrlen(split_settings) != 3)
	{
		printf("Error: rotation vec formatted incorrectly\n");
		status = false;
	}
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
	return (status);
}

bool	check_position(char *settings)
{
	char	**split_settings;
	bool	status;

	status = true;
	split_settings = ft_split(settings, ',');
	if (ft_2d_arrlen(split_settings) != 3)
	{
		printf("Error: position vec formatted incorrectly\n");
		status = false;
	}
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
	return (status);
}

bool	check_color(char *settings)
{
	char	**split_settings;
	bool	status;

	status = true;
	split_settings = ft_split(settings, ',');
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
bool	check_radius(char *settings)
{
	bool	status;

	status = true;
	if (ft_atof(settings) > FLT_MAX)
	{
		printf("Error: radius variable formatted incorrectly\n");
		status = false;
	}
	return (status);
}

// check is in max float min float
// check is only num
bool	check_height(char *settings)
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
bool	check_fov(char *settings)
{
	bool	status;

	status = true;
	if (ft_atof(settings) > FLT_MAX)
	{
		printf("Error: fov variable formatted incorrectly\n");
		status = false;
	}
	return (status);
}

// check is only num
// check is in max float min float
bool	check_brightness(char *settings)
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
