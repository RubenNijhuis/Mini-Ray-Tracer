/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_normal.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 17:00:04 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/20 16:35:08 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "libvec.h"
#include "ray.h"

t_vec3f	get_cylinder_normal(const t_ray *ray, const float dist,
	t_cylinder *cyl)
{
	t_vec3f		p;
	t_vec3f		closest_point;
	t_ray		cyl_ray;

	cyl_ray = ray_init(cyl->base.position, cyl->base.rotation);
	p = ray_at(ray, dist);
	closest_point = ray_closest_point(&cyl_ray, p);
	p = p - closest_point;
	vec3f_normalize(&p);
	return (p);
}
