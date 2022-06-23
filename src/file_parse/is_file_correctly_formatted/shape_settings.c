/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shape_settings.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 09:55:21 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/23 13:21:15 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "objects.h"
#include "parsing.h"
#include "ft_printf.h"

#include <stdlib.h>
#include <float.h>
#include <stdio.h>

/**
 * @brief 
 * Returns a struct that describes the components/elements of an object
 * based on the corresponding object type
 * 
 * @param type 
 * @return t_component_list 
 */
t_component_list	get_object_component_list(t_object_type type)
{
	static const t_component_list	components_check[] = {
	[ambient_light] = {2, {brightness, color}},
	[camera] = {3, {position, orientation, fov}},
	[light] = {3, {position, brightness, color}},
	[sphere] = {3, {position, radius, color}},
	[plane] = {3, {position, orientation, color}},
	[cylinder] = {5, {position, orientation, height, radius, color}},
	};

	return (components_check[type]);
}

// { bmp_map,    &check_bpm_map},
// { material,   &check_material},
/**
 * @brief 
 * Returns a function pointer that will check whether the settings
 * are formatted correctly. Requires the corresponding element
 * component
 * 
 * @param comp 
 * @return t_comp_checker_func 
 */
t_comp_checker_func	get_elem_checker_func(t_element_component comp)
{
	static const t_comp_checker_func	funcs[] = {
	[position] = &check_position,
	[orientation] = &check_orientation,
	[color] = &check_color,
	[radius] = &check_radius,
	[height] = &check_height,
	[fov] = &check_fov,
	[brightness] = &check_brightness,
	};

	return (funcs[comp]);
}

bool	check_amount_settings(uint32_t arr_len, uint32_t amount_checks, t_line line)
{
	if (arr_len != amount_checks)
	{
		ft_dprintf(2, "Error: line %i incorrect settings\n", line.file_line);
		return (false);
	}
	return (true);
}

/**
 * @brief 
 * Goes through each objects elements and runs the corresponding
 * function on the setting to check if it's formatted correctly
 * Will exit with an error message upon incorrect formatting
 * 
 * @param obj_type 
 * @param obj_settings 
 */
bool	run_object_checks(t_object_type obj_type, t_line line)
{
	t_component_list	comps;
	char				**split_settings;
	uint32_t			cur_check;
	uint32_t			amount_checks;
	bool				check_status;

	check_status = true;
	split_settings = ft_split(line.line, ' ');
	comps = get_object_component_list(obj_type);
	cur_check = 0;
	amount_checks = comps.amount_obj_components;
	if (check_amount_settings(ft_2d_arrlen(split_settings) - 1, amount_checks, line) == false)
		check_status = false;
	while (cur_check < amount_checks)
	{
		if ((get_elem_checker_func(comps.components[cur_check])) \
			(split_settings[cur_check + 1], line.file_line) == false)
			check_status = false;
		cur_check++;
	}
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
	return (check_status);
}
