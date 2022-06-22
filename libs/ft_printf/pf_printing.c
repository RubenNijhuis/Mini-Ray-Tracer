/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_printing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:59:26 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:59:27 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pf_util.h"

#include <stdlib.h> /* free */

/* the sign flag may be missing when i is negative, or has been set but
 * should not be written because of a negative value.
 * for convenience, we fix it all in this function. */
static void	fix_sign_flag(t_printf_args *pfargs, const void *val)
{
	if (pfargs->argument_type == 'd')
	{
		if (*((const int *)val) < 0)
		{
			pfargs->sign_flag = '-';
		}
	}
	else
	{
		pfargs->sign_flag = 0;
	}
}

static int	write_out(t_printf_args *pfargs, t_printf_lengths *plens,
	char *str, const void *val)
{
	int	bytes_written;

	bytes_written = 0;
	if (pfargs->min_field_width_right)
	{
		write_special_front(pfargs, val, &bytes_written);
		write_main_arg(str, pfargs, plens, &bytes_written);
		write_minfield(pfargs, plens, &bytes_written);
	}
	else
	{
		if (pfargs->fw_char == '0')
		{
			write_special_front(pfargs, val, &bytes_written);
			write_minfield(pfargs, plens, &bytes_written);
			write_main_arg(str, pfargs, plens, &bytes_written);
		}
		else
		{
			write_minfield(pfargs, plens, &bytes_written);
			write_special_front(pfargs, val, &bytes_written);
			write_main_arg(str, pfargs, plens, &bytes_written);
		}
	}
	return (bytes_written);
}

/* printf sometimes has REALLY weird behaviour
 * for example, if there's a precision and the field width contains a 0 flag,
 * it replaces it with a space. Furthermore, if precision is 0, and val is 0,
 * the length should be set to zero. Or if there is a precision, the fw_char
 * should be ' '. Also, calling %c with precision is undefined behaviour. */
void	init_plens(t_printf_lengths *plens, t_printf_args *pfargs,
	const void *val)
{
	if (pfargs->argument_type == 's' && pfargs->precision != -1)
	{
		if (plens->arg_actual_len > pfargs->precision)
			plens->arg_actual_len = pfargs->precision;
		else
			pfargs->precision = plens->arg_actual_len;
	}
	else if (pfargs->precision == 0 && *((const int *)val) == 0)
	{
		plens->arg_actual_len = 0;
	}
	if (plens->arg_actual_len > pfargs->precision)
		plens->arg_perceived_len = plens->arg_actual_len;
	else
		plens->arg_perceived_len = pfargs->precision;
	if (pfargs->fw_char == '0' && pfargs->precision >= 0)
		pfargs->fw_char = ' ';
	plens->special_front_len = (pfargs->sign_flag != 0)
		+ (should_prepend_0x(pfargs, val) * 2);
}

/* IDEA: set str to a message that malloc failed? */
int	print_arg(t_printf_args *pfargs, const void *val, char *str, int len)
{
	int					bytes_written;
	t_printf_lengths	plens;

	if (str == NULL)
		return (0);
	fix_sign_flag(pfargs, val);
	bytes_written = 0;
	if (len == -1)
	{
		len = (int)ft_strlen(str);
	}
	plens.arg_actual_len = len;
	init_plens(&plens, pfargs, val);
	if (pfargs->should_uppercase)
	{
		ft_strtoupper(str);
	}
	bytes_written += write_out(pfargs, &plens, str, val);
	if (!pfargs->should_not_be_freed)
	{
		free(str);
	}
	return (bytes_written);
}
