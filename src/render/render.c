/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:55:24 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/27 15:50:06 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "minirt.h"

float	mapx(int input)
{
	return ((input - 0) * (0.1 - -0.1) / (WIN_WIDTH - 1 - 0) + -0.1);
}

float	mapy(int input)
{
	return (-1 * ((input - 0) * (0.1 - -0.1) / (WIN_HEIGHT - 1 - 0) + -0.1));
}

void	render(t_program_data *pd)
{
	uint32_t	xpixel;
	uint32_t	ypixel;
	t_ray		ray;
	t_color		color;

	ray.origin = vec3f(0, 0, 0);
	ypixel = 0;
	while (ypixel < WIN_HEIGHT)
	{
		xpixel = 0;
		while (xpixel < WIN_WIDTH)
		{
			ray.direction = vec3f(mapx(xpixel), mapy(ypixel), 1);
			vec3f_normalize(&ray.direction);
			color = get_ray_color(&ray, xpixel, ypixel, pd);
			mlx_put_pixel(pd->img, xpixel, ypixel, col_to_hex(color));
			xpixel++;
		}
		ypixel++;
	}
}
