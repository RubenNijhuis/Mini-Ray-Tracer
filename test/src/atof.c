/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   atof.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/18 18:25:01 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/18 18:41:14 by jobvan-d      ########   odam.nl         */
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
	COMP("100.0");
	COMP("1.24");
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
