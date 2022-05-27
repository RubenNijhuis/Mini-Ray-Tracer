/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shape_settings.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 09:55:21 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/28 01:56:37 by rubennijhui   ########   odam.nl         */
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
	if (ft_2d_arrlen(split_settings) != 3)
		printf("Error: rotation vec formatted incorrectly\n");
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
	return (true);
}

bool	check_position(char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ',');
	if (ft_2d_arrlen(split_settings) != 3)
		printf("Error: position vec formatted incorrectly\n");
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
	return (true);
}

bool	check_color(char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ',');
	if (ft_2d_arrlen(split_settings) != 3)
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
	// int	amount_checks;
	// int i = 0;

	(void)obj_settings;
	(void)obj_type;
	(void)object_components;
	// (void)component_checkers;
	// i = 0;
	// amount_checks = object_components[obj_type].amount_obj_components;
	// amount_checks = 3;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0 && (*component_checkers[2].func)("WHT,HELLO,BONJOUR") == false)
			printf("WHAT");
		if (i == 1 && (*component_checkers[1].func)("WHT,HELLO,BONJOUR") == false)
			printf("WHAT");
		// if (i == 2 && (*component_checkers[2].func)("WHT,HELLO,BONJOUR") == false)
		// 	printf("WHAT");
	}
}
