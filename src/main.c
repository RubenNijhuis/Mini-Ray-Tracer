/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/28 02:12:07 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // debug printf

#include "objects.h"
#include "minirt.h"
#include "libft.h"

void	setup_object_component_lists(t_program_data *pd)
{
	const t_component_list	components_check[] = {
	{ambient_light, 2, {brightness, color}},
	{camera, 3, {position, rotation, fov}},
	{light, 3, {position, brightness, color}},
	{sphere, 3, {rotation, position, color}},
	{plane, 3, {position, rotation, color}},
	{cylinder, 5, {position, rotation, height, radius, color}},
	};

	pd->components_check = components_check;
}

// { radius,     &check_radius},
// { height,     &check_height},
// { fov,        &check_fov},
// { range,      &check_range},
// { brightness, &check_brightness},
// { bmp_map,    &check_bpm_map},
// { material,   &check_material},
void	setup_object_component_checkers(t_program_data *pd)
{
	const t_component_checker	components_checker[] = {
	{color, &check_color},
	{rotation, &check_rotation},
	{position, &check_position},
	};

	pd->components_checker = components_checker;
}

// TODO: stderr
int	main(int argc, char **argv)
{
	t_program_data	pd;

	if (argc != 2)
	{
		printf("Usage: minirt [path-to-file]\n");
		return (1);
	}
	ft_memset(&pd, 0, sizeof(t_program_data));
	setup_scene(&pd.scene, argv[1]);
	// setup_object_component_lists(&pd);
	// setup_object_component_checkers(&pd);
	// run_object_checks(sphere, "sp 0,0,20 20 255,0,0", \
	// 	pd.components_check, pd.components_checker);
	print_scene_elements(&pd.scene);
	init_mlx(&pd);
	render(&pd);
	start_mlx(&pd);
	return (0);
}
