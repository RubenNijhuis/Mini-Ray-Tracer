/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:55:24 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/08 19:15:03 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "minirt.h"

t_color	get_pixel_color(uint32_t px, uint32_t py, t_scene *scene)
{
	t_ray	ray;
	t_color	color;

	ray = get_camera_ray(px, py, &scene->camera);
	color = get_ray_color(&ray, scene);
	return (color);
}

void	render_pixel(t_program_data *pd, uint32_t px, uint32_t py)
{
	put_pixel(pd, px, py, col_to_hex(get_pixel_color(px, py, &pd->scene)));
}

void	put_pixel(t_program_data *pd, uint32_t px, uint32_t py, uint32_t col)
{
	mlx_put_pixel(pd->img, px, (WIN_HEIGHT - 1) - py, col);
}

/**
 * @brief 
 * Renders the scene. It shoots a ray for each pixel which will in turn
 * make calculations to determine the pixel color
 * 
 * @param pd 
 */
#if BONUS==0

void	render(t_program_data *pd)
{
	uint32_t	xpixel;
	uint32_t	ypixel;

	ypixel = 0;
	while (ypixel < WIN_HEIGHT)
	{
		xpixel = 0;
		while (xpixel < WIN_WIDTH)
		{
			render_pixel(pd, xpixel, ypixel);
			xpixel++;
		}
		ypixel++;
	}
}
#endif
