/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_printing_util.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:59:42 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/22 14:39:27 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pf_util.h"

#include <unistd.h> /* write */

/* for some weird reason, 0x only should be appended when val > 0 */
int	should_prepend_0x(t_printf_args *pfargs, const void *val)
{
	return ((pfargs->hash_flag && *((const unsigned int *)val) > 0)
		|| pfargs->argument_type == 'p');
}

/* writes the special thing in front, such as a +, -, space, or 0x */
void	write_special_front(t_printf_args *pfargs, const void *val,
	int *bytes_written)
{
	char	ox[2];

	if (pfargs->sign_flag != 0)
		*bytes_written += write(pfargs->fd, &pfargs->sign_flag, 1);
	else if (should_prepend_0x(pfargs, val))
	{
		ox[0] = '0';
		ox[1] = 'x';
		if (pfargs->should_uppercase)
			ox[1] = ft_toupper(ox[1]);
		*bytes_written += write(pfargs->fd, ox, 2);
	}
}

/* writes the minimum field */
void	write_minfield(t_printf_args *pfargs, t_printf_lengths *plens,
	int *bytes_written)
{
	int	i;

	i = plens->arg_perceived_len + plens->special_front_len;
	while (i < pfargs->min_field_width)
	{
		*bytes_written += write(pfargs->fd, &pfargs->fw_char, 1);
		i++;
	}
}

/* writes the main argument, plus optional zeroes(precision) */
void	write_main_arg(const char *str, t_printf_args *pfargs,
	t_printf_lengths *plens, int *bytes_written)
{
	int	i;

	i = plens->arg_actual_len;
	while (i < plens->arg_perceived_len)
	{
		*bytes_written += write(pfargs->fd, "0", 1);
		i++;
	}
	*bytes_written += write(pfargs->fd, str, plens->arg_actual_len);
}
