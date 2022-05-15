/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 17:05:54 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/15 11:08:22 by rubennijhui   ########   odam.nl         */
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
	cr_expect(ft_is_object("ps pl pa", " ") == false, "expected hallo not to contain a space");
	cr_expect(ft_is_object("ps pl pa", "pa") == true, "expected hallo to contain 'al'");
	cr_expect(ft_is_object("ps pl pa", "pl") == true, "expected hallo to contain l or a");
	cr_expect(ft_is_object("ps pl pa", "") == false, "expected hallo not to contain nothing");
	cr_expect(ft_is_object("ps pl pa", "ps") == true, "expected hallo to contain o");
	cr_expect(ft_is_object("ps pl pa", "muis") == false, "expected hallo not to contain any of muis");
}
