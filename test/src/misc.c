/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 17:05:54 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/30 13:15:50 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Lib to be tested
#include "minirt.h"
#include "objects.h"
#include "libft.h"

#include <stdbool.h>

#include <math.h>

// Testing lib
#include <criterion/criterion.h>

Test(ft_is_object, passing)
{
	// TODO: WTF are these descriptions?
	cr_expect(ft_is_object("ps pl pa", " ") == false, "expected hallo not to contain a space");
	cr_expect(ft_is_object("ps pl pa", "pa") == true, "expected hallo to contain 'al'");
	cr_expect(ft_is_object("ps pl pa", "pl") == true, "expected hallo to contain l or a");
	cr_expect(ft_is_object("ps pl pa", "") == false, "expected hallo not to contain nothing");
	cr_expect(ft_is_object("ps pl pa", "ps") == true, "expected hallo to contain o");
	cr_expect(ft_is_object("ps pl pa", "muis") == false, "expected hallo not to contain any of muis");
}

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
