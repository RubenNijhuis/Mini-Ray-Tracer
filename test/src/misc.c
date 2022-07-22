/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 17:05:54 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/22 18:45:17 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Lib to be tested
#include "minirt.h"
#include "objects.h"
#include "libft.h"
#include "ray.h"
#include "libvec.h"

#include <stdbool.h>
#include <math.h>

// Testing lib
#include <criterion/criterion.h>

bool	color_eq(t_color col1, t_color col2);

/*
 Test functions
*/
void	deg_to_rad_test(const float input, const float expected)
{
	float output = deg_to_rad(input);

	cr_assert(output == expected, \
		"Submitted: %f and expected `deg_to_rad` to return %f", input, expected);
}

void	rad_to_deg_test(const float input, const float expected)
{
	float output = rad_to_deg(input);

	cr_assert(output == expected, \
		"Submitted: %f and expected `rad_to_deg` to return %f", input, expected);
}

void	ray_at_test(t_vec3f origin, t_vec3f direction, t_vec3f expected)
{
	t_ray	ray;
	t_vec3f	pos;

	ray.origin = origin;
	ray.direction = direction;
	pos = ray_at(&ray, 5);
	cr_expect(vec3f_eq(pos, expected), "Expected proper ray at function");
}

void	get_color_from_string_test(char *str, t_color col)
{
	t_color	c = get_color_from_string(str);

	color_eq(c, col);
}

/*
 Suites
*/
Test(deg_to_rad, passing)
{
	deg_to_rad_test(0.0f, 0.0f);
	deg_to_rad_test(180.0f, (float)M_PI);
	deg_to_rad_test(360.0f, (float)M_PI * 2.0f);
}

Test(rad_to_deg, passing)
{
	rad_to_deg_test(0.0f, 0.0f);
	rad_to_deg_test((float)M_PI, 180.0f);
	rad_to_deg_test((float)M_PI * 2.0f, 360.0f);
}

Test(get_color_from_string, passing)
{
	get_color_from_string_test("255,0,12", make_color(255.0, 0, 12.0));
	get_color_from_string_test("0,0,0", make_color(0, 0, 0));
	get_color_from_string_test("255,255,255", make_color(255, 255, 255));
	get_color_from_string_test("7,3,52", make_color(7, 3, 52));
}

Test(ray_at, passing)
{
	ray_at_test(vec3f(2, 1, -4), vec3f(0, 1, 0), vec3f(2, 6, -4));
}

Test(ray_closest_point, passing)
{
	t_ray	ray;
	t_vec3f	p;

	ray.origin = vec3f(2, -2, 2);
	ray.direction = vec3f(0, 1, 0);
	p = vec3f(-1, 5, 3);
	cr_assert(vec3f_eq(ray_closest_point(&ray, p), vec3f(2, 5, 2)), "wrong ray closest point");
}

void	print_vec(t_vec3f v)
{
	printf("%f, %f, %f\n", v[0], v[1], v[2]);
}

Test(get_cylinder_normal, passing)
{
	t_cylinder	cyl;
	t_ray		ray;
	float		t;
	const float	y = -20.0f;

	ray.direction = vec3f(1, 0, 0);
	ray.origin = vec3f(-4 + y, 4 + y, 2);
	cyl.base.position = vec3f(3, 2, 2);
	cyl.base.rotation = vec3f(1, 1, 0);
	vec3f_normalize(&cyl.base.rotation);

	t = 8.0f;
	t_vec3f norm = get_cylinder_normal(&ray, t, &cyl);
	// print_vec(norm);
	norm *= 10000.0f;
	vec3f_round(&norm);
	norm /= 10000.0f;

	cr_assert(vec3f_eq(norm, vec3f(-0.7071, 0.7071, 0)), "invalid cylinder normal");
}
