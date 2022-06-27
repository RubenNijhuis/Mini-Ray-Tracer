/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 17:05:54 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/27 12:27:28 by rnijhuis      ########   odam.nl         */
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

/*
 Test functions
*/
void	deg_to_rad_test(const float input, const float expected)
{
	float output = deg_to_rad(input);

	cr_assert(output == expected, \
		"Submitted: %s and expected `deg_to_rad` to return %i", input, expected);
}

void	rad_to_deg_test(const float input, const float expected)
{
	float output = rad_to_deg(input);

	cr_assert(output == expected, \
		"Submitted: %s and expected `rad_to_deg` to return %i", input, expected);
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

void	get_color_from_string_test(const char *str, double r, double g, double b)
{
	t_color	c = get_color_from_string(str);

	cr_expect(c.r == (double)r / 255, "Expected r to be %f but got %f", r / 255, c.r);
	cr_expect(c.g == (double)g / 255, "Expected g to be %f but got %f", g / 255, c.g);
	cr_expect(c.b == (double)b / 255, "Expected b to be %f but got %f", b / 255, c.b);
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
	get_color_from_string_test("255,0,12", 255.0, 0, 12.0);
	get_color_from_string_test("0,0,0", 0, 0, 0);
	get_color_from_string_test("255,255,255", 255, 255, 255);
	get_color_from_string_test("7,3,52", 7, 3, 52);
}

Test(ray_at, passing)
{
	ray_at_test(vec3f(2, 1, -4), vec3f(0, 1, 0), vec3f(2, 6, -4));
}
