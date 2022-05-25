/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_pixel_color.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:52:54 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/25 18:53:20 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libvec.h"
#include <stdint.h>

void	render_pixel_color(uint32_t x, uint32_t y, \
	t_vec3i color, t_program_data *pd)
{
	mlx_put_pixel(pd->img, x, y, col_to_hex(color));
}
