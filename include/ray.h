/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/20 18:26:15 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/12 12:34:06 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "libvec.h"

typedef struct s_ray {
	t_vec3f	origin;
	t_vec3f	direction;
}	t_ray;

t_vec3f	ray_at(const t_ray *ray, const float t);

void	ray_rotate(t_ray *ray, t_vec3f default_dir, t_vec3f desired_dir);

#endif
