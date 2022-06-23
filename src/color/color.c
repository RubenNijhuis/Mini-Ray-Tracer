/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/27 13:36:57 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/23 10:32:36 by rubennijhui   ########   odam.nl         */
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

t_color	get_default_color(t_scene *scene)
{
	(void)scene;
	return (make_color(0, 0, 0));
}
