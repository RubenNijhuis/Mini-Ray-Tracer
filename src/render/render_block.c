/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_block.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 19:44:55 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/10 17:51:08 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "threading.h"
#include "minirt.h"

#include <stdlib.h> // malloc

// creates a buffer for a block.
uint32_t	*create_block_buffer(void)
{
	uint32_t	*buf;

	buf = malloc(BLOCK_SIZE * BLOCK_SIZE * sizeof(uint32_t));
	if (buf == NULL)
	{
		malloc_error();
	}
	return (buf);
}

// renders a block, stores it into the block pixel buffer.
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
			block->pixel_buf[y * BLOCK_SIZE + x] = col_to_hex(
					get_pixel_color(x + block->x, y + block->y, scene)
					);
			x++;
		}
		y++;
	}
}

// displays a block to the program's image.
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
				block->pixel_buf[y * BLOCK_SIZE + x]);
			x++;
		}
		y++;
	}
}

// sets the block to desired x/y coords. The buffer is
// recyled and left untouched
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
	if (block->y > WIN_HEIGHT)
	{
		block->y = 0;
	}
	else if (block->y + block->height > WIN_HEIGHT)
	{
		block->height = WIN_HEIGHT - block->y;
	}
}
