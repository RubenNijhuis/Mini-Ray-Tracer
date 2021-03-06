/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fov.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 14:08:16 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/26 17:34:16 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "libvec.h"

#include <math.h> // tEngenS

void	camera_rotation_setup(t_camera *cam)
{
	cam->fov_tan = tan(cam->fov * 0.5f);
	if (cam->rotation[0] >= 0.0f && cam->rotation[0] < __FLT_EPSILON__
		&& cam->rotation[2] >= 0.0f && cam->rotation[2] < __FLT_EPSILON__)
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
	const double	aspect = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	t_ray			ray;
	float			x;
	float			y;

	ray.origin = cam->position;
	x = aspect * (((2.0f * cam->fov_tan) * ((double)xpixel / (double)WIN_WIDTH))
			- cam->fov_tan);
	y = ((2.0f * cam->fov_tan) * ((double)ypixel / (double)WIN_HEIGHT))
		- cam->fov_tan;
	ray.direction = cam->pos_x * x + cam->neg_y * y + cam->rotation;
	vec3f_normalize(&ray.direction);
	return (ray);
}
