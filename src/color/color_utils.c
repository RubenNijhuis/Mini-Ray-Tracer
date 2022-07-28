/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/27 13:36:57 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/28 14:14:12 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <math.h>

void	color_add(t_color *color, const t_color *rhs)
{
	color->r += rhs->r;
	color->g += rhs->g;
	color->b += rhs->b;
}

void	color_multiply(t_color *color, const t_color *rhs)
{
	color->r *= rhs->r;
	color->g *= rhs->g;
	color->b *= rhs->b;
}

void	color_multiply_scalar(t_color *color, const double scalar)
{
	color->r *= scalar;
	color->g *= scalar;
	color->b *= scalar;
}

void	color_clamp(t_color *color)
{
	if (color->r > 1.0f)
	{
		color->r = 1.0f;
	}
	if (color->g > 1.0f)
	{
		color->g = 1.0f;
	}
	if (color->b > 1.0f)
	{
		color->b = 1.0f;
	}
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
