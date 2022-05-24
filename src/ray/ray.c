/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/20 16:03:47 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/24 13:38:12 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

/* P(t) = origin + direction * time
 * notice how it's just an y(t) = x(t) + b */

/* so essentially ray is a line. Put in the t in the formula,
 * calculate the value, and translate that by its origin. */
t_vec3f	ray_at(const t_ray *ray, const float t)
{
	t_vec3f	pos;

	pos = ray->direction;
	vec3f_multiply_scalar(&pos, t);
	vec3f_translate(&pos, ray->origin);
	return (pos);
}
