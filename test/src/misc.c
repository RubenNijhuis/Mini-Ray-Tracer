/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 17:05:54 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/14 19:00:48 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Lib to be tested
#include "minirt.h"
#include "objects.h"
#include "libft.h"

#include <stdbool.h>

// Testing lib
#include <criterion/criterion.h>

Test(ft_is_object, passing)
{
	cr_expect(ft_is_object("hallo", " ") == false, "expected hallo not to contain a space");
	cr_expect(ft_is_object("hallo", "a") == true, "expected hallo to contain 'a'");
	cr_expect(ft_is_object("hallo", "lllllla") == true, "expected hallo to contain l or a");
	cr_expect(ft_is_object("hallo", "") == false, "expected hallo not to contain nothing");
	cr_expect(ft_is_object("hallo", "mnoo") == true, "expected hallo to contain o");
	cr_expect(ft_is_object("hallo", "muis") == false, "expected hallo not to contain any of muis");
}
