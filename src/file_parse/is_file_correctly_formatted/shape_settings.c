/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shape_settings.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 09:55:21 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/28 02:10:21 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "objects.h"

#include <stdio.h>

bool	check_rotation(char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ',');
	if (ft_2d_arrlen(split_settings) != 1)
		printf("Error: rotation vec formatted incorrectly\n");
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
	return (true);
}

bool	check_position(char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ',');
	if (ft_2d_arrlen(split_settings) != 1)
		printf("Error: position vec formatted incorrectly\n");
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
	return (true);
}

bool	check_color(char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ',');
	if (ft_2d_arrlen(split_settings) != 1)
		printf("Error: color vec formatted incorrectly\n");
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
	return (true);
}

// char		**split_settings;
// split_settings = ft_split(obj_settings, ' ');
void	run_object_checks(t_object_type obj_type, char *obj_settings, \
	const t_component_list *object_components, \
	const t_component_checker *component_checkers)
{
	// uint32_t	current_check;
	// uint32_t	amount_checks;
	// int i = 0;
	// char *split_settings;

	(void)obj_settings;
	(void)obj_type;
	(void)object_components;
	// split_settings = ft_split(obj_settings, ' ');
	// (void)component_checkers;
	// i = 0;
	// amount_checks = object_components[2].amount_obj_components;
	// amount_checks = 3;
	// printf("%i", amount_checks);
	for (int i = 0; i < 3; i++)
		(*component_checkers[i].func) \
			("WHT,HELLO,BONJOUR");
}
