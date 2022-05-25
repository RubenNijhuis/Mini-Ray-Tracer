/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:44:59 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/25 18:45:29 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"
#include "libvec.h"
#include "ray.h"

float	intersects_plane(t_ray *ray, t_object *shape)
{
	t_plane	*plane;

	(void)ray;
	plane = &shape->plane;
	(void)plane;
	return (-1);
}
