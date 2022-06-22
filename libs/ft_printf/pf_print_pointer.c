/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_print_pointer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:59:39 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:59:40 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pf_util.h"

int	print_p(t_printf_args *pfargs, const void *p)
{
	return (print_arg(pfargs, p, ft_itoa_hex_size_t((size_t)p), -1));
}
