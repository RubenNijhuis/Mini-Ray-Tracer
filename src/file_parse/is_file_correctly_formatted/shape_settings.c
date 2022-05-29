/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shape_settings.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 09:55:21 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/29 16:22:49 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "objects.h"

#include <stdlib.h>
#include <float.h>
#include <stdio.h>

t_component_list	get_object_component_list(uint32_t type)
{
	const t_component_list	components_check[] = {
	{ambient_light, 2, {brightness, color}},
	{camera, 3, {position, rotation, fov}},
	{light, 3, {position, brightness, color}},
	{sphere, 3, {position, radius, color}},
	{plane, 3, {position, rotation, color}},
	{cylinder, 5, {position, rotation, height, radius, color}},
	};

	return (components_check[type]);
}

// { bmp_map,    &check_bpm_map},
// { material,   &check_material},
t_comp_checker_func	get_object_checker_func(uint32_t check)
{
	size_t						i;
	const t_component_checker	funcs[] = {
	{position, &check_position},
	{rotation, &check_rotation},
	{color, &check_color},
	{radius, &check_radius},
	{height, &check_height},
	{fov, &check_fov},
	{brightness, &check_brightness},
	};

	i = 0;
	while (i < sizeof(funcs) / sizeof(t_component_checker))
	{
		if (funcs[i].type == check)
			return (funcs[i].func);
		i++;
	}
	return (NULL);
}

void	run_object_checks(t_object_type obj_type, char *obj_settings)
{
	t_component_list	comps;
	char				**split_settings;
	uint32_t			current_check;
	uint32_t			amount_checks;

	split_settings = ft_split(obj_settings, ' ');
	comps = get_object_component_list(obj_type);
	current_check = 0;
	amount_checks = comps.amount_obj_components;
	if (ft_2d_arrlen(split_settings) - 1 != amount_checks)
		exit_error("Error: object line doesn't contain all mandatory settings");
	while (current_check < amount_checks)
	{
		if ((get_object_checker_func(comps.components[current_check])) \
			(split_settings[current_check + 1]) == false)
			exit(-1);
		current_check++;
	}
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}
