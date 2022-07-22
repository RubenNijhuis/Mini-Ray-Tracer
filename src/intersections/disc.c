/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   disc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 12:54:10 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/22 19:05:01 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "libvec.h"
#include "ray.h"

// essentially, same as a plane interesection, except if there's an
// interesection, we check if the intersected point is within the radius.
t_intersect	intersects_disc(t_ray *ray, t_shape *shape)
{
	t_disc		*disc;
	t_vec3f		intersect_point;
	t_intersect	i;

	disc = &shape->disc;
	i = intersects_plane(ray, (t_shape *)&disc->base);
	if (i.t >= 0.0f)
	{
		intersect_point = ray_at(ray, i.t);
		if (vec3f_len_sq(intersect_point - disc->base.position)
			> sq(disc->radius))
		{
			i.t = -1.0f;
		}
	}
	return (i);
}
