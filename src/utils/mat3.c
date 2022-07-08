/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mat3.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 15:57:36 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/08 10:21:42 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libvec.h"
#include <stdio.h>

typedef float	t_mat3[3][3];

t_mat3	*get_rotation_matrix(t_rotation_type type, float angle)
{
	t_mat3			*tmat;
	const t_mat3	matrix_list[] = {
	[rotate_x] = {
	[0] = {cos(angle), 0, -sin(angle)},
	[1] = {0, 1, 0},
	[2] = {sin(angle), 0, cos(angle)}
	},
	[rotate_y] = {
	[0] = {1, 0, 0},
	[1] = {0, cos(angle), sin(angle)},
	[2] = {0, -1.0 * sin(angle), cos(angle)},
	},
	[rotate_z] = {
	[0] = {cos(angle), sin(angle), 0},
	[1] = {sin(angle), cos(angle), 0},
	[2] = {0, 0, 1}
	}
	};

	tmat = (t_mat3 *)&matrix_list[type];
	return (tmat);
}

t_vec3f	vec3f_mult_mat3(t_vec3f v, t_mat3 m)
{
	v[0] = v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2];
	v[1] = v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2];
	v[2] = v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2];
	return (v);
}

t_vec3f	rotate(t_rotation_type rotation, t_vec3f dir, float angle)
{
	dir = vec3f_mult_mat3(dir, *get_rotation_matrix(rotation, angle));
	return (dir);
}
