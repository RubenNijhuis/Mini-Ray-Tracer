/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 22:42:56 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/02 14:07:56 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Lib to be tested
#include "minirt.h"
#include "objects.h"
#include "libft.h"

// Testing lib
#include <criterion/criterion.h>

Test(get_vec3f_from_string, passing) {
	t_vec3f	vec;
	char	*three_floats= "-100.01,2020.3274,-1.1";

	vec = get_vec3f_from_string(three_floats);

	cr_expect(vec[0] == -100.01f, "Expected first value to be -100.01");
	cr_expect(vec[1] == 2020.3274f, "Expected second value to be 2020.3274");
	cr_expect(vec[2] == -1.1f, "Expected third value to be -1");
}
