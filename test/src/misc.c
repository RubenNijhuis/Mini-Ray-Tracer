/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 17:05:54 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/17 12:28:14 by jobvan-d      ########   odam.nl         */
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

Test(deg_to_rad, passing)
{
	cr_expect(deg_to_rad(0.0f) == 0.0f, "expected 0 deg to be 0");
	cr_expect(deg_to_rad(180.0f) == (float)M_PI, "expected 180 deg to be pi");
	cr_expect(deg_to_rad(360.0f) == (float)M_PI * 2.0f, "expected 360 deg to be 2 pi");
}

Test(rad_to_deg, passing)
{
	cr_expect(rad_to_deg(0.0f) == 0.0f, "expected 0 deg to be 0");
	cr_expect(rad_to_deg((float)M_PI) == 180.0f, "expected 180 deg to be pi");
	cr_expect(rad_to_deg((float)M_PI * 2.0f) == 360.0f, "expected 360 deg to be 2 pi");
}

Test(get_color_from_string, passing)
{
	t_color	c = get_color_from_string("255,0,12");
	cr_expect(c.r == 1.0, "expected r to be 1.0");
	cr_expect(c.g == 0, "expected g to be 0");
	cr_expect(c.b == 12.0 / 255.0, "expected b to be ~0.047");
}

Test(ray_at, passing)
{
	t_ray	ray;
	t_vec3f	pos;

	ray.origin = vec3f(2, 1, -4);
	ray.direction = vec3f(0, 1, 0);
	pos = ray_at(&ray, 5);
	cr_expect(vec_eq(pos, vec3f(2, 6, -4)), "ray_at failure");
}
