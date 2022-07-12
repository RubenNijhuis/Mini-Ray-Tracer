/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fov.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 14:08:16 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/12 12:40:36 by jobvan-d      ########   odam.nl         */
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
	t_vec3f			old_pos;

	ray.origin = cam->position;
	ray.direction[0] = fov_tan
		* (((double)xpixel - (double)(WIN_WIDTH / 2)) / (double)WIN_WIDTH);
	ray.direction[1] = (fov_tan * inv_aspect)
		* (((double)ypixel - (double)(WIN_HEIGHT / 2)) / (double)WIN_HEIGHT);
	ray.direction[2] = 1;

	old_pos = cam->position;
	vec3f_normalize(&ray.direction);
	vec3f_normalize(&cam->rotation);
	
	ray_rotate(&ray, vec3f(0, 0, 1), cam->rotation);
	cam->position = old_pos;
	return (ray);
}
