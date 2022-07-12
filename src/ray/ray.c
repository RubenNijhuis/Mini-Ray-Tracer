/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/20 16:03:47 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/12 14:17:01 by jobvan-d      ########   odam.nl         */
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

	pos = ray->direction * t + ray->origin;
	return (pos);
}

// rotates a ray so that it matches the direciton.
// All vectors should be unit vectors.
// IMPORTANT: Assumes the ray has been translated by the object's position in
// question. i.e. obj at (2,0,2) and ray origin at (3,0,5) results in
// ray origin (1,0,3)
// his is easier and it makes that the ray can be properly rotated.
// ray is modified, so better make a copy of it.
void	ray_rotate(t_ray *ray, t_vec3f default_dir, t_vec3f desired_dir)
{
	float	angle;
	t_vec3f	rotation_axis;

	angle = vec3f_unit_get_angle(default_dir, desired_dir);
	rotation_axis = vec3f_cross(desired_dir, default_dir);
	ray->direction = vec3f_rotate_axis(ray->direction, rotation_axis, angle);
	ray->origin = vec3f_rotate_axis(ray->origin, rotation_axis, angle);
}
