/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_parsing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 22:42:56 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/30 10:49:05 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Lib to be tested
#include "minirt.h"
#include "objects.h"

// Testing lib
#include <criterion/criterion.h>

Test(Make_obj_from_string, basic) {
	
}

Test(ft_itoa, basic) {
	cr_expect(strcmp(ft_itoa(100), "100") == 0, "Expected '100'");
	cr_expect(strcmp(ft_itoa(-1231), "-1231") == 0, "Expected '-1231'");
	cr_expect(strcmp(ft_itoa(-1), "-1") == 0, "Expected '-1'");
	cr_expect(strcmp(ft_itoa(54857483), "54857483") == 0, "Expected '54857483'");
}
