/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shape_settings.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 09:55:21 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/03 13:32:45 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "objects.h"

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
	[ambient_light] =  {2, {brightness, color}},
	[camera] =  {3, {position, rotation, fov}},
	[light] =  {3, {position, brightness, color}},
	[sphere] =  {3, {position, radius, color}},
	[plane] =  {3, {position, rotation, color}},
	[cylinder] =  {5, {position, rotation, height, radius, color}},
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
	[rotation] = &check_rotation,
	[color] = &check_color,
	[radius] = &check_radius,
	[height] = &check_height,
	[fov] = &check_fov,
	[brightness] = &check_brightness,
	};

	return (funcs[comp]);
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
void	run_object_checks(t_object_type obj_type, char *obj_settings)
{
	t_component_list	comps;
	char				**split_settings;
	uint32_t			cur_check;
	uint32_t			amount_checks;

	split_settings = ft_split(obj_settings, ' ');
	comps = get_object_component_list(obj_type);
	cur_check = 0;
	amount_checks = comps.amount_obj_components;
	if ((ft_2d_arrlen(split_settings) - 1) != amount_checks)
		exit_error("Error: object line doesn't contain all mandatory settings");
	while (cur_check < amount_checks)
	{
		if ((get_elem_checker_func(comps.components[cur_check])) \
			(split_settings[cur_check + 1]) == false)
			exit(1);
		cur_check++;
	}
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}
