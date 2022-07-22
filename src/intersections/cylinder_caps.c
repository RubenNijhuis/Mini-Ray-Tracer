/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_caps.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 17:00:04 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/22 16:34:10 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "libvec.h"
#include "ray.h"

t_intersect	get_cap_intersect(t_ray *obj_ray, t_cylinder *cyl)
{
	t_disc		disc;
	t_intersect	i;
	float		prev_t;

	disc.base.rotation = cylinder_default_direction();
	disc.base.position = disc.base.rotation * (cyl->height * 0.5f);
	disc.radius = cyl->radius;
	i = intersects_disc(obj_ray, (t_shape *)&disc);
	prev_t = i.t;
	disc.base.position = -disc.base.position;
	i = intersects_disc(obj_ray, (t_shape *)&disc);
	if (i.t <= 0.0f || (prev_t >= 0.0f && prev_t < i.t))
	{
		i.t = prev_t;
	}
	return (i);
}
