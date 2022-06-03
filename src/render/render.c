/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:55:24 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/03 15:58:45 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "minirt.h"

/**
 * @brief 
 * Renders the scene. It shoots a ray for each pixel which will in turn
 * make calculations to determine the pixel color
 * 
 * @param pd 
 */
void	render(t_program_data *pd)
{
	uint32_t	xpixel;
	uint32_t	ypixel;
	t_ray		ray;
	t_color		color;

	ypixel = 0;
	while (ypixel < WIN_HEIGHT)
	{
		xpixel = 0;
		while (xpixel < WIN_WIDTH)
		{
			ray = get_camera_ray(xpixel, ypixel, &pd->scene.camera);
			color = get_ray_color(&ray, xpixel, ypixel, pd);
			mlx_put_pixel(pd->img, xpixel, (WIN_HEIGHT - 1) - ypixel,
				col_to_hex(color));
			xpixel++;
		}
		ypixel++;
	}
}
