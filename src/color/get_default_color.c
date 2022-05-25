/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_default_color.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:46:36 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/25 18:46:50 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"
#include "minirt.h"

t_vec3i	get_default_color(t_program_data *pd)
{
	t_vec3i	default_color;

	(void)pd;
	default_color.x = 0;
	default_color.y = 0;
	default_color.z = 0;
	return (default_color);
}
