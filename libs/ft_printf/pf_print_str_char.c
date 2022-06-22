/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_print_str_char.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:59:40 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:59:41 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pf_util.h"

int	print_s(t_printf_args *pfargs, const char *s)
{
	if (s == (char *)0)
	{
		s = FT_PRINTF_NULL_MESSAGE;
	}
	pfargs->should_not_be_freed = 1;
	return (print_arg(pfargs, (const void *)s, (char *)s, -1));
}

int	print_c(t_printf_args *pfargs, const char c)
{
	pfargs->should_not_be_freed = 1;
	pfargs->precision = -1;
	return (print_arg(pfargs, (const void *)&c, (char *)&c, 1));
}
