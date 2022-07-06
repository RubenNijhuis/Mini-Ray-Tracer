/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fov.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 14:08:16 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/06 17:03:16 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"

#include <math.h> // tEngenS

t_vec3f	rotate_z(t_vec3f dir, float angle);

// TODO: verify
t_ray	get_camera_ray(uint32_t xpixel, uint32_t ypixel, t_camera *cam)
{
	const double	inv_aspect = (double)WIN_HEIGHT / (double)WIN_WIDTH;
	t_ray			ray;

	ray.origin = cam->position;
	ray.direction[0] = tan(cam->fov * 0.5f)
		* (((double)xpixel - (double)(WIN_WIDTH / 2)) / (double)WIN_WIDTH);
	ray.direction[1] = (tan(cam->fov * 0.5f) * inv_aspect)
		* (((double)ypixel - (double)(WIN_HEIGHT / 2)) / (double)WIN_HEIGHT);
	ray.direction[2] = 1;
	ray.direction = rotate_z(ray.direction, deg_to_rad(45));
	vec3f_normalize(&ray.direction);
	return (ray);
}
