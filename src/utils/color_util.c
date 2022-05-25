/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 13:27:03 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/25 13:32:40 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* converts a vec3i color to a uint32_t RGBA(what MLX42 uses) */
uint32_t	col_to_hex(const t_vec3i col)
{
	uint32_t	result;

	result = col.r;
	result <<= 8;
	result += col.g;
	result <<= 8;
	result += col.b;
	result <<= 8;
	result |= 0xff;
	return (result);
}
