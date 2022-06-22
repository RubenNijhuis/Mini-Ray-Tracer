/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_parsing.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:59:25 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/22 13:42:08 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pf_util.h"

/* because fd is the only argument that persists throughout the entire
 * process, we need to keep it despite setting the rest. It looks kind of
 * ugly, but it works and it is easy. */
static void	init_pfargs(t_printf_args *pfargs)
{
	int	fd;

	fd = pfargs->fd;
	ft_memset(pfargs, 0, sizeof(t_printf_args));
	pfargs->fw_char = ' ';
	pfargs->precision = -1;
	pfargs->fd = fd;
}

/* parses a flag and puts it into pfargs */
static void	parse_flag(const char flag, t_printf_args *pfargs)
{
	if (flag == '#')
	{
		pfargs->hash_flag = 1;
	}
	else if (flag == '+'
		|| (flag == ' ' && pfargs->sign_flag != '+'))
	{
		pfargs->sign_flag = flag;
	}
	else if (flag == '-')
	{
		pfargs->min_field_width_right = 1;
		pfargs->fw_char = ' ';
	}
	else if (flag == '0' && !pfargs->min_field_width_right)
	{
		pfargs->fw_char = flag;
	}
}

/* calling atoi like that is safe, as its behaviour is designed
 * to stop at any non-digit. */
static void	parse_number(size_t *i, const char *s, int *field)
{
	if (!ft_isdigit(s[*i]))
	{
		return ;
	}
	*field = ft_atoi((char *)(s + *i));
	while (ft_isdigit(s[*i]))
	{
		(*i)++;
	}
}

/* parses the flags and the number and precision. */
static size_t	parse_flags_front(const char *s, t_printf_args *pfargs)
{
	size_t	i;

	i = 0;
	while (ft_str_contains_char(FT_PRINTF_VALID_FLAGS, s[i]))
	{
		parse_flag(s[i], pfargs);
		i++;
	}
	parse_number(&i, s, &pfargs->min_field_width);
	if (s[i] == '.')
	{
		i++;
		pfargs->precision = 0;
		parse_number(&i, s, &pfargs->precision);
	}
	return (i);
}

int	parse_args(const char *s, t_printf_args *pfargs)
{
	size_t	i;

	init_pfargs(pfargs);
	if (*s == '%')
	{
		pfargs->argument_type = *s;
		return (1);
	}
	i = parse_flags_front(s, pfargs);
	if (ft_str_contains_char(FT_PRINTF_VALID_ARGS, s[i]))
	{
		pfargs->argument_type = s[i];
		if (ft_cisupper(pfargs->argument_type))
		{
			pfargs->should_uppercase = 1;
			pfargs->argument_type = ft_tolower(pfargs->argument_type);
		}
		i++;
	}
	else
	{
		pfargs->argument_type = '\07';
		return (0);
	}
	return (i);
}
