/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fov.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 14:08:16 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/13 14:15:57 by jobvan-d      ########   odam.nl         */
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
	t_ray			ray;
	t_vec3f			init_pos;

	ray.origin = cam->position;
	init_pos = vec3f(cam->fov_tan
		* (((double)xpixel - (double)(WIN_WIDTH / 2)) / (double)WIN_WIDTH),
		(cam->fov_tan * inv_aspect)
		* (((double)ypixel - (double)(WIN_HEIGHT / 2)) / (double)WIN_HEIGHT),
		0
	);
	t_vec3f	pos_x = vec3f_cross(vec3f(0, 1, 0), cam->rotation);
	t_vec3f	neg_y = vec3f_cross(cam->rotation, pos_x);
	pos_x *= -init_pos[0];
	neg_y *= init_pos[1];
	ray.direction = pos_x + neg_y + cam->rotation;
	vec3f_normalize(&ray.direction);
	return (ray);
}
