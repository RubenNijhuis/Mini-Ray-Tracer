/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_obj_from_str.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 10:50:32 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/30 22:23:29 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
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

void	make_sphere(t_object *obj, char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ' ');
	obj->sphere.base.obj_type = sphere;
	obj->sphere.base.position = get_vec3f_from_string(split_settings[1]);
	obj->sphere.base.color = get_vec3i_from_string(split_settings[3]);
	obj->sphere.diameter = ft_atoi(split_settings[2]);
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}

void	make_cylinder(t_object *obj, char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ' ');
	obj->cylinder.base.obj_type = cylinder;
	obj->cylinder.base.position = get_vec3f_from_string(split_settings[1]);
	obj->cylinder.base.orientation = get_vec3f_from_string(split_settings[2]);
	obj->cylinder.base.color = get_vec3i_from_string(split_settings[5]);
	obj->cylinder.diameter = ft_atoi(split_settings[3]);
	obj->cylinder.height = ft_atoi(split_settings[4]);
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}

void	make_plane(t_object *obj, char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ' ');
	obj->plane.base.obj_type = plane;
	obj->plane.base.position = get_vec3f_from_string(split_settings[1]);
	obj->plane.base.orientation = get_vec3f_from_string(split_settings[2]);
	obj->plane.base.color = get_vec3i_from_string(split_settings[3]);
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}
