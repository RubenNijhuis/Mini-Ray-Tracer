/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   atof.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/18 18:25:01 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/24 13:43:13 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <criterion/criterion.h>

#include <stdlib.h>

#define COMP(s) cr_expect(ft_atof((s)) == atof((s)), "%s not parsing correctly(got %f, expected %f)", (s), ft_atof((s)), atof((s)))

Test(ft_atod, passing)
{
    COMP("+-.2949");
	COMP("-.2949");
	COMP("+.2949");
	COMP("1.000090f");
	COMP("1.000090    ");	
	COMP("1.");
	COMP(".1");
	COMP("");
	COMP(".0");
	COMP("0.0");
	COMP("1.0");
	COMP("+1");
	COMP("-1");
	COMP("100.0");
	COMP("1.24");
	COMP("987971.24589575176816");
	COMP("1.1");
	COMP("1.14025");
	COMP("-23451.9095");
	COMP("100.101");
	COMP("-100.101");
	COMP("a-100.101");
	COMP("a-100.b101");
	COMP("-100.b101");
	COMP("-10b30.101");
	COMP("-1030....101");
	COMP("-1428.2481");
	COMP("-1999428.248451");
	cr_expect(ft_atof("    5.0") == 0, "expected preceeding spaces to not work");
}

#define COMPF(s, ex) cr_expect(is_valid_double_format((s)) == (ex), "%s should/shouldn't be accepted(got %d, expected %d)", (s), is_valid_double_format((s)), ex)

Test(is_valid_double_format, passing)
{
	COMPF("+-.2949", 0);
	COMPF("-.2949", 1);
	COMPF("+.2949", 1);
	COMPF("a1.000090", 0);
	COMPF("1.000090f", 0);
	COMPF("1.000090    ", 1);
	COMPF("     1.000090", 0);	
	COMPF("1.", 1);
	COMPF(".1", 1);
	COMPF("", 0);
	COMPF(".0", 1);
	COMPF("0.0", 1);
	COMPF("1.0", 1);
	COMPF("+1", 1);
	COMPF("-1", 1);
	COMPF("100.0", 1);
	COMPF("1.24", 1);
	COMPF("1.1", 1);
	COMPF("1.14025", 1);
	COMPF("-23451.9095", 1);
	COMPF("100.101", 1);
	COMPF("-100.101", 1);
	COMPF("a-100.101", 0);
	COMPF("a-100.b101", 0);
	COMPF("-100.b101", 0);
	COMPF("-10b30.101", 0);
	COMPF("-1030....101", 0);
	COMPF("-1428.2481", 1);
	COMPF("-1999428.248451", 1);
}
