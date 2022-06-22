/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_print_int.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:59:37 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:59:38 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pf_util.h"

#include <stdlib.h> /* free */

/* because itoa returns a minus as well, and because of a possible
 * precision flag(i.e. %.4d yielding -0042) we remove it here.
 * A bit untidy, but it works. 
 * Also, setting argument type to d, since i and d are the same,
 * you can skip a check later on. */
int	print_di(t_printf_args *pfargs, const int i)
{
	char	*str;
	char	*nstr;

	str = ft_itoa(i);
	if (i < 0 && str != NULL)
	{
		nstr = ft_substr(str, 1, 12);
		if (nstr == NULL)
		{
			nstr = str;
		}
		else
		{
			free(str);
		}
	}
	else
	{
		nstr = str;
	}
	pfargs->argument_type = 'd';
	return (print_arg(pfargs, (const void *)&i, nstr, -1));
}

int	print_u(t_printf_args *pfargs, const unsigned int u)
{
	return (print_arg(pfargs, (const void *)&u, ft_uitoa(u), -1));
}
