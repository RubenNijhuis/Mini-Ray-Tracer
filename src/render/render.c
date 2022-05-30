/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:55:24 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/30 14:23:42 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "minirt.h"

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
			mlx_put_pixel(pd->img, xpixel, ypixel, col_to_hex(color));
			xpixel++;
		}
		ypixel++;
	}
}
