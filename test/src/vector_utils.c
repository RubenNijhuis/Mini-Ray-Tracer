/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 22:42:56 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/07/22 14:09:24 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Lib to be tested
#include "minirt.h"
#include "objects.h"
#include "libft.h"

// Testing lib
#include <criterion/criterion.h>

void	vec3f_from_string_test(char* input, float expected[3])
{
	t_vec3f	vec;

	vec = get_vec3f_from_string(input);
	cr_expect(vec[0] == expected[0], "Expected first value to be %f but got %f", expected[0], vec[0]);
	cr_expect(vec[1] == expected[1], "Expected second value to be %f but got %f", expected[1], vec[2]);
	cr_expect(vec[2] == expected[2], "Expected third value to be %f but got %f", expected[2], vec[2]);
}

Test(get_vec3f_from_string, passing) {
	float	test_values1[3] = {-100.01, 2020.3274, -1.1};
	vec3f_from_string_test("-100.01,2020.3274,-1.1", test_values1);

	float	test_values2[3] = {0, 0, 0};
	vec3f_from_string_test("0,0,0", test_values2);

	float	test_values3[3] = {15, 69.1234, 4020.212};
	vec3f_from_string_test("15,69.1234,4020.212", test_values3);

	float	test_values4[3] = {-100.01, 2020.3274, -1.1};
	vec3f_from_string_test("-100.01,2020.3274,-1.1", test_values4);

	float	test_values5[3] = {1.0101, 12.1212, 8};
	vec3f_from_string_test("1.0101,12.1212,8", test_values5);
}
