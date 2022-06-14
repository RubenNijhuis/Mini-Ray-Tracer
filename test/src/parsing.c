/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/04 18:03:38 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/14 19:19:42 by jobvan-d      ########   odam.nl         */
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
	cr_expect(ft_is_object("sp pl", "sp ") == true, "expected sp to be a valid object");
	cr_expect(ft_is_object("sp pl", "spf ") == false, "expected spf not to be a valid object");
	cr_expect(ft_is_object("sp", "sp "), "expected sp to return true");
	cr_expect(ft_is_object("sp pl", "f ") == false, "expected f to be a invalid object");

	cr_expect(!ft_is_object("sp", "L "), "expected that sp isn't a light.");
	cr_expect(ft_is_object("L", "L "), "expected L to be L");
	cr_expect(!ft_is_object("L", "LL "), "expected LL not to be a light");
	cr_expect(!ft_is_object("L", " "), "expected space not to be a light");
	cr_expect(!ft_is_object("L", ""), "expected nothing not to be a light");

	
	cr_expect(ft_is_object("sp cl", "sp "), "expected sp to return true");
	cr_expect(!ft_is_object("sp cl", "L "), "expected that sp isn't a light.");
	cr_expect(ft_is_object("L cl", "L "), "expected L to be L");
	cr_expect(!ft_is_object("L cl", "LL "), "expected LL not to be a light");
	cr_expect(!ft_is_object("L cl", " "), "expected space not to be a light");
	cr_expect(!ft_is_object("L cl", ""), "expected nothing not to be a light");
	cr_expect(ft_is_object("sp pl cl", "f ") == false, "expected f to be invalid object");

	cr_expect(ft_is_object("sp      cl", "cl "), "expected cl to be object");
	cr_expect(ft_is_object("sp      cl    ", "cl "), "expected cl to be object");

	cr_expect(ft_is_object("cl L", "cll") == false, "expected cll to be invalid");
	cr_expect(ft_is_object("L cl", "cll") == false, "expected cll to be invalid");
}

Test(rt_objstrcmp, passing)
{
	cr_expect(rt_objstrcmp("sp", "sp "), "expected sp to return true");
	cr_expect(!rt_objstrcmp("sp", "L "), "expected that sp isn't a light.");
	cr_expect(rt_objstrcmp("L", "L "), "expected L to be L");
	cr_expect(!rt_objstrcmp("L", "LL "), "expected LL not to be a light");
	cr_expect(!rt_objstrcmp("L", " "), "expected space not to be a light");
	cr_expect(!rt_objstrcmp("L", ""), "expected nothing not to be a light");
}
