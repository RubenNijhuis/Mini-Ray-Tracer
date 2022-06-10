/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_vec_from_string.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 15:51:11 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/10 17:44:23 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libvec.h"
#include "minirt.h"

t_color	get_color_from_string(char *str)
{
	t_color		col;
	char		**split_vec;

	split_vec = ft_split(str, ',');
	if (split_vec == NULL)
		malloc_error();
	col.r = (double)ft_atoi(split_vec[0]) / 255.0;
	col.g = (double)ft_atoi(split_vec[1]) / 255.0;
	col.b = (double)ft_atoi(split_vec[2]) / 255.0;
	ft_free_2d_array(&split_vec, 3);
	return (col);
}

t_vec3f	get_vec3f_from_string(char *str)
{
	t_vec3f		vec;
	char		**split_vec;

	split_vec = ft_split(str, ',');
	if (split_vec == NULL)
		malloc_error();
	vec = vec3f(
			ft_atof(split_vec[0]),
			ft_atof(split_vec[1]),
			ft_atof(split_vec[2])
			);
	ft_free_2d_array(&split_vec, 3);
	return (vec);
}
