/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 17:05:54 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/13 17:42:42 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Lib to be tested
#include "minirt.h"
#include "objects.h"
#include "libft.h"

#include <stdbool.h>

// Testing lib
#include <criterion/criterion.h>

Test(ft_anychar_n_str, passing)
{
    cr_expect(ft_anychar_n_str("hallo", " ") == false, "expected hallo not to contain a space");
    cr_expect(ft_anychar_n_str("hallo", "a") == true, "expected hallo to contain 'a'");
    cr_expect(ft_anychar_n_str("hallo", "lllllla") == true, "expected hallo to contain l or a");
    cr_expect(ft_anychar_n_str("hallo", "") == false, "expected hallo not to contain nothing");
    cr_expect(ft_anychar_n_str("hallo", "mnoo") == true, "expected hallo to contain o");
    cr_expect(ft_anychar_n_str("hallo", "muis") == false, "expected hallo not to contain any of muis");
}
