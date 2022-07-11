/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersection.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 18:19:33 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/11 18:31:19 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief 
 * Retrieves the intersection function based on the shape object type
 * @param shape 
 * @return t_intersect_func 
 */
t_intersect_func	lookup_intersect_function(t_shape *shape)
{
	static const t_intersect_func	funcs[] = {
	[sphere] = &intersects_sphere,
	[plane] = &intersects_plane,
	[cylinder] = &intersects_cylinder,
	[disc] = &intersects_disc,
	};

	return (funcs[shape->base.obj_type]);
}

// creates an t_intersect.
t_intersect	init_intersect(const float distance, const t_vec3f normal)
{
	t_intersect	i;

	i.t = distance;
	i.normal = normal;
	return (i);
}

// returns an intersection which is invalid(negative distance), i.e. an
// intersection that does not intersect.
t_intersect	no_intersect(void)
{
	static const t_intersect	ret = {
	{0, 0, 0, 0},
		-1.0f // <-- NORM!!! WHYYYYY SO WEIRD ON THE TABS???!
	};

	return (ret);
}
