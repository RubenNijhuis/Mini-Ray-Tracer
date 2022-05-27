/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/27 13:36:57 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/27 20:47:01 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <math.h>

// TODO: mutliply scalar that kind of stuff.
t_color	make_color(double r, double g, double b)
{
	t_color	col;

	col.r = r;
	col.g = g;
	col.b = b;
	return (col);
}

t_color	get_default_color(t_program_data *pd)
{
	(void)pd;
	return (make_color(0, 0, 0));
}

/* converts a color to a uint32_t RGBA(what MLX42 uses) */
uint32_t	col_to_hex(const t_color col)
{
	uint32_t	result;

	result = (uint32_t)round(col.r * 255.0) & 0xff;
	result <<= 8;
	result += (uint32_t)round(col.g * 255.0) & 0xff;
	result <<= 8;
	result += (uint32_t)round(col.b * 255.0) & 0xff;
	result <<= 8;
	result |= 0xff;
	return (result);
}
