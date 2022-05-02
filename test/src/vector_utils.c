/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 22:42:56 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/02 16:09:53 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Lib to be tested
#include "minirt.h"
#include "objects.h"
#include "libft.h"

// Testing lib
#include <criterion/criterion.h>

Test(get_vec3f_from_string, passing) {
	t_vec3f	vec3f;
	char	*three_floats= "-100.01,2020.3274,-1.1";

	vec3f = get_vec3f_from_string(three_floats);

	cr_expect(vec3f.x == -100.01f, "Expected first value to be -100.01");
	cr_expect(vec3f.y == 2020.3274f, "Expected second value to be 2020.3274");
	cr_expect(vec3f.z == -1.1f, "Expected third value to be -1");
}

Test(get_vec3i_from_string, passing) {
	t_vec3i	vec3i;
	char	*three_ints= "10,         -15, 1010";

	vec3i = get_vec3i_from_string(three_ints);

	cr_expect(vec3i.x == 10, "Expected first value to be 10");
	cr_expect(vec3i.y == -15, "Expected second value to be -15");
	cr_expect(vec3i.z == 1010, "Expected third value to be 1010");
}
