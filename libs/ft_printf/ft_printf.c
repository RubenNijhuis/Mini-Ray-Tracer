/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:59:19 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:59:20 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "pf_util.h"

#include <stdarg.h>
#include <unistd.h>

/* updates format to stop beyond the next argument, and updates pfargs with the
 * new argument just parsed. */
static char	stop_next_arg(const char **format, int *bytes_printed,
	t_printf_args *pfargs)
{
	char	*s;
	size_t	i;

	i = 0;
	s = *((char **)format);
	while (s[i] != 0)
	{
		if (s[i] == '%')
		{
			break ;
		}
		i++;
	}
	*bytes_printed += write(pfargs->fd, s, i);
	if (s[i] != 0)
	{
		*format += i + 1;
		*format += parse_args(*format, pfargs);
		return (pfargs->argument_type);
	}
	return (0);
}

/* TODO: invalid arg? */
static void	loop_args(const char *format, va_list *args, int *bytes_printed,
	const int fd)
{
	char			c;
	t_printf_args	pfargs;

	pfargs.fd = fd;
	while (1)
	{
		c = stop_next_arg(&format, bytes_printed, &pfargs);
		if (c == 0)
			break ;
		else if (c == '%')
			*bytes_printed += print_c(&pfargs, '%');
		else if (c == 'c')
			*bytes_printed += print_c(&pfargs, va_arg(*args, int));
		else if (c == 's')
			*bytes_printed += print_s(&pfargs, va_arg(*args, char *));
		else if (c == 'p')
			*bytes_printed += print_p(&pfargs, va_arg(*args, void *));
		else if (c == 'x')
			*bytes_printed += print_x(&pfargs, va_arg(*args, unsigned int));
		else if (c == 'u')
			*bytes_printed += print_u(&pfargs, va_arg(*args, unsigned int));
		else if (c == 'd' || c == 'i')
			*bytes_printed += print_di(&pfargs, va_arg(*args, int));
	}
}

int	ft_printf(const char *format, ...)
{
	va_list			args;
	int				bytes_printed;

	if (format == NULL)
		return (0);
	bytes_printed = 0;
	va_start(args, format);
	loop_args(format, &args, &bytes_printed, 1);
	va_end(args);
	return (bytes_printed);
}

int	ft_dprintf(const int fd, const char *format, ...)
{
	va_list			args;
	int				bytes_printed;

	if (format == NULL)
		return (0);
	bytes_printed = 0;
	va_start(args, format);
	loop_args(format, &args, &bytes_printed, fd);
	va_end(args);
	return (bytes_printed);
}
