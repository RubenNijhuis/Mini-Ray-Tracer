/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shape_settings.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 09:55:21 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/27 15:38:36 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

void	check_rotation_vec(char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ',');
	if (ft_2d_arrlen(split_settings) != 3)
		exit_error("Error: rotation vec formatted incorrectly");
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}

void	check_position_vec(char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ',');
	if (ft_2d_arrlen(split_settings) != 3)
		exit_error("Error: rotation vec formatted incorrectly");
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}

void	check_color_vec(char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ',');
	if (ft_2d_arrlen(split_settings) != 3)
		exit_error("Error: rotation vec formatted incorrectly");
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}