/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_obj_from_str.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 10:50:32 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/27 23:00:01 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "libft.h"
#include "libvec.h"
#include "minirt.h"

void	make_sphere(t_object *obj, char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ' ');
	if (split_settings == NULL)
		malloc_error();
	obj->sphere.base.obj_type = sphere;
	obj->sphere.base.position = get_vec3f_from_string(split_settings[1]);
	obj->sphere.base.color = get_color_from_string(split_settings[3]);
	obj->sphere.radius = ft_atof(split_settings[2]) / 2;
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}

void	make_cylinder(t_object *obj, char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ' ');
	if (split_settings == NULL)
		malloc_error();
	obj->cylinder.base.obj_type = cylinder;
	obj->cylinder.base.position = get_vec3f_from_string(split_settings[1]);
	obj->cylinder.base.rotation = get_vec3f_from_string(split_settings[2]);
	obj->cylinder.base.color = get_color_from_string(split_settings[5]);
	obj->cylinder.radius = ft_atof(split_settings[3]) / 2.0f;
	obj->cylinder.height = ft_atof(split_settings[4]);
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}

void	make_plane(t_object *obj, char *settings)
{
	char	**split_settings;

	split_settings = ft_split(settings, ' ');
	if (split_settings == NULL)
		malloc_error();
	obj->plane.base.obj_type = plane;
	obj->plane.base.position = get_vec3f_from_string(split_settings[1]);
	obj->plane.base.rotation = get_vec3f_from_string(split_settings[2]);
	vec3f_normalize(&obj->plane.base.rotation);
	obj->plane.base.color = get_color_from_string(split_settings[3]);
	ft_free_2d_array(&split_settings, ft_2d_arrlen(split_settings));
}
