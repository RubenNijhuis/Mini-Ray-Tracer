/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_obj_from_str.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 10:50:32 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/30 11:06:23 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "libft.h"
#include "libvec.h"
#include "minirt.h"

t_vec	get_vec_from_string(char *str)
{
	uint32_t	i;
	t_vec		vec;
	char		**split_vec;

	split_vec = ft_split(str, ',');
	i = 0;
	while (i < 3)
	{
		vec.values[i] = ft_atoi(split_vec[i]);
		i++;
	}
	ft_free_2d_array(&split_vec, 3);
	return (vec);
}

void make_sphere(t_object *obj, char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ' ');
	obj->sphere.base.obj_type = sphere;
	obj->sphere.base.position = get_vec_from_string(split_settings[1]);
	obj->sphere.base.color = get_vec_from_string(split_settings[3]);
	obj->sphere.diameter = ft_atoi(split_settings[2]);
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}

void	make_cylinder(t_object *obj, char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ' ');
	obj->cylinder.base.obj_type = cylinder;
	obj->cylinder.base.position = get_vec_from_string(split_settings[1]);
	obj->cylinder.base.orientation = get_vec_from_string(split_settings[2]);
	obj->cylinder.base.color = get_vec_from_string(split_settings[5]);
	obj->cylinder.diameter = ft_atoi(split_settings[3]);
	obj->cylinder.height = ft_atoi(split_settings[4]);
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}

void	make_plane(t_object *obj, char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ' ');
	obj->plane.base.obj_type = plane;
	obj->plane.base.position = get_vec_from_string(split_settings[1]);
	obj->plane.base.orientation = get_vec_from_string(split_settings[2]);
	obj->plane.base.color = get_vec_from_string(split_settings[3]);
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}
