/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fov.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 14:08:16 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/08 17:42:11 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "libvec.h"
#include <math.h> // tEngenS

// TODO: verify
// Test
t_ray	get_camera_ray(uint32_t xpixel, uint32_t ypixel, t_camera *cam)
{
	const double	inv_aspect = (double)WIN_HEIGHT / (double)WIN_WIDTH;
	const float		fov_tan = tan(cam->fov * 0.5f); // TODO: cache this thing, put it into camera
	t_ray			ray;

	ray.origin = cam->position;
	ray.direction[0] = fov_tan
		* (((double)xpixel - (double)(WIN_WIDTH / 2)) / (double)WIN_WIDTH);
	ray.direction[1] = (fov_tan * inv_aspect)
		* (((double)ypixel - (double)(WIN_HEIGHT / 2)) / (double)WIN_HEIGHT);
	ray.direction[2] = 1;
	// ray.direction = rotate(rotate_x, ray.direction, deg_to_rad(60));
	// ray.direction = rotate(rotate_y, ray.direction, deg_to_rad(0));
	vec3f_normalize(&ray.direction);
	return (ray);
}
