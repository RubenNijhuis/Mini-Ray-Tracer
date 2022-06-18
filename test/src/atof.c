/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   atof.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/18 18:25:01 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/18 18:34:13 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <criterion/criterion.h>

#include <stdlib.h>

#define COMP(s) cr_expect(ft_atof((s)) == atof((s)), "%s not parsing correctly(got %f, expected %f)", (s), ft_atof((s)), atof((s)))

Test(ft_atod, passing)
{
    COMP("\t\v\r    +-.2949");
	COMP("\t\v\r    -.2949");
	COMP("\t\v\r    +.2949");
	COMP("\t\v\r1.000090f");
	COMP("\t\v\r1.000090    \t");	
	COMP("1.");
	COMP(".1");
	COMP("");
	COMP("    \v\t");
	COMP("    \v\t.");
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
	COMP("\t\v\r    -1428.2481");
	COMP("-1999428.248451");
}
