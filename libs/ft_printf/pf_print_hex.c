/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_print_hex.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:59:15 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:59:17 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pf_util.h"

/* for some weird reason, the 0x only needs to be prepended when i > 0 */
int	print_x(t_printf_args *pfargs, const unsigned int i)
{
	return (print_arg(pfargs, (const void *)&i, ft_itoa_hex_size_t(i), -1));
}
