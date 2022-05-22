/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_vec_from_string.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 15:51:11 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/13 17:46:39 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libvec.h"
#include "minirt.h"

t_vec3i	get_vec3i_from_string(char *str)
{
	t_vec3i		vec;
	char		**split_vec;

	split_vec = ft_split(str, ',');
	vec.x = ft_atoi(split_vec[0]);
	vec.y = ft_atoi(split_vec[1]);
	vec.z = ft_atoi(split_vec[2]);
	ft_free_2d_array(&split_vec, 3);
	return (vec);
}

t_vec3f	get_vec3f_from_string(char *str)
{
	t_vec3f		vec;
	char		**split_vec;

	split_vec = ft_split(str, ',');
	vec.x = ft_atof(split_vec[0]);
	vec.y = ft_atof(split_vec[1]);
	vec.z = ft_atof(split_vec[2]);
	ft_free_2d_array(&split_vec, 3);
	return (vec);
}
