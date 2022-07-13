/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fov.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 14:08:16 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/13 15:12:59 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "libvec.h"

#include <math.h> // tEngenS

void	camera_rotation_setup(t_camera *cam)
{
	cam->fov_tan = tan(cam->fov);
	if (cam->rotation[0] < __FLT_EPSILON__ && cam->rotation[2] < __FLT_EPSILON__)
	{
		cam->pos_x = vec3f(1, 0, 0);
	}
	else
	{
		cam->pos_x = vec3f_cross(vec3f(0, 1, 0), cam->rotation);
	}
	cam->neg_y = vec3f_cross(cam->rotation, cam->pos_x);
}

t_ray	get_camera_ray(uint32_t xpixel, uint32_t ypixel, t_camera *cam)
{
	const double	inv_aspect = (double)WIN_HEIGHT / (double)WIN_WIDTH;
	t_ray			ray;
	float			x;
	float			y;

	ray.origin = cam->position;
	x = cam->fov_tan
		* (((double)xpixel - (double)(WIN_WIDTH / 2)) / (double)WIN_WIDTH);
	y = (cam->fov_tan * inv_aspect)
		* (((double)ypixel - (double)(WIN_HEIGHT / 2)) / (double)WIN_HEIGHT);
	ray.direction = cam->pos_x * x + cam->neg_y * y + cam->rotation;
	vec3f_normalize(&ray.direction);
	return (ray);
}
