/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   disc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 12:54:10 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/07 14:15:33 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "libvec.h"
#include "ray.h"

// NOTE: get_disc_normal is missing here because it's the same a plane,
// so that one is used instead. 

// essentially, same as a plane interesection, except if there's an
// interesection, we check if the intersected point is within the radius.
float	intersects_disc(t_ray *ray, t_shape *shape)
{
	t_disc	*disc;
	t_vec3f	intersect_point;
	float	t;

	disc = &shape->disc;
	t = intersects_plane(ray, (t_shape *)&disc->base);
	if (t >= 0.0f)
	{
		intersect_point = ray_at(ray, t);
		if (vec3f_len_sq(intersect_point - disc->base.position)
			> disc->radius * disc->radius)
		{
			t = -1.0f;
		}
	}
	return (t);
}
