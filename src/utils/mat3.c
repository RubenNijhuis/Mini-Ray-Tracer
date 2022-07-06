/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mat4.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 15:57:36 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/06 16:12:52 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

typedef float t_mat3[3][3];

t_vec3f	vec3f_mult_mat3(t_vec3f v, const t_mat3 m)
{
	v[0] = v[0] * m[0][0] + v[0] * m[0][1] + v[0] * m[0][2];
	v[1] = v[1] * m[1][0] + v[1] * m[1][1] + v[1] * m[1][2];
	v[2] = v[2] * m[2][0] + v[2] * m[2][1] + v[2] * m[2][2];

	return (v);
}

t_mat3	mat3_product(t_mat3 a, t_mat3 b)
{
	t_mat3	res;
	int		row;
	int		col;

	row = 0;
	while (row < 3)
	{
		col = 0;
		while (col < 3)
		{
			res[row][col] = a[row][0] * b[0][col]
				+ a[row][1] * b[1][col]
				+ a[row][2] * b[2][col];
			col++;
		}
		row++;
	}
	return (res);
}
