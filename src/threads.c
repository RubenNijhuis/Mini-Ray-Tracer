/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 12:50:04 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/08 19:15:47 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

#if BONUS

# include "threading.h"
# include "minirt.h"

# include <pthread.h>

void	render_block(t_block *block, t_scene *scene)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < block->height)
	{
		x = 0;
		while (x < block->width)
		{
			block->pixel_buf[y * block->height + x] = col_to_hex(
					get_pixel_color(x + block->x, y + block->y, scene)
					);
			x++;
		}
		y++;
	}
}

void	put_block(t_block *block, t_program_data *pd)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < block->height)
	{
		x = 0;
		while (x < block->width)
		{
			put_pixel(pd, x + block->x, y + block->y,
				block->pixel_buf[y * block->height + x]);
			x++;
		}
		y++;
	}
}

void	update_block(t_block *block, uint32_t px, uint32_t py)
{
	block->x = px;
	block->y = py;
	block->width = BLOCK_SIZE;
	if (block->x + block->width > WIN_WIDTH)
	{
		block->width = WIN_WIDTH - block->x;
	}
	block->height = BLOCK_SIZE;
	if (block->y + block->height > WIN_HEIGHT)
	{
		block->height = WIN_HEIGHT - block->y;
	}
}

void	render(t_program_data *pd)
{
	uint32_t	buf[BLOCK_SIZE * BLOCK_SIZE];
	t_block		block;
	uint32_t	x;
	uint32_t	y;

	block.pixel_buf = buf;
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
}

#endif
