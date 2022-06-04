/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/04 18:03:38 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/04 18:43:17 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Lib to be tested
#include "minirt.h"
#include "objects.h"
#include "libft.h"

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

Test(illegal_entry, passing)
{
	cr_expect(ft_is_object("sp pl", "sp ") == true, "expected sp to be true");
	cr_expect(ft_is_object("sp pl", "spf ") == false, "expected spf to be false");
	cr_expect(ft_is_object("sp pl", "f ") == false, "expected f to be false");
}
