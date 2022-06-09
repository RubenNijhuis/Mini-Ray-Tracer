/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:55:24 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/09 17:44:44 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "minirt.h"

#if BONUS == 0
# include "threading.h" // render block

# include <stdlib.h> // free
#endif

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
	t_block		block;
	uint32_t	x;
	uint32_t	y;

	block.pixel_buf = create_block_buffer();
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			update_block(&block, x, y);
			render_block(&block, &pd->scene);
			put_block(&block, pd);
			mlx_force_draw(pd->mlx);
			x += BLOCK_SIZE;
		}
		y += BLOCK_SIZE;
	}
	free(block.pixel_buf);
}

#endif
