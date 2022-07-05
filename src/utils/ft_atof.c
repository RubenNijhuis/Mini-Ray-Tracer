/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atof.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 15:27:17 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/05 16:29:59 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static double	atod_postdecimal(const char *str)
{
	double	result;
	double	divisor;

	result = 0.0;
	divisor = 1.0;
	while (*str >= '0' && *str <= '9')
	{
		result *= 10.0;
		divisor *= 10.0;
		result += (double)(*str - '0');
		str++;
	}
	result /= divisor;
	return (result);
}

double	ft_atof(const char *str)
{
	double	result;
	int		is_negative;

	is_negative = 0;
	if (*str == '-')
	{
		is_negative = 1;
		str++;
	}
	else if (*str == '+')
		str++;
	result = 0.0;
	while (*str >= '0' && *str <= '9')
	{
		result *= 10.0;
		result += (double)(*str - '0');
		str++;
	}
	if (*str == '.')
		result += atod_postdecimal(str + 1);
	if (is_negative)
		result = -result;
	return (result);
}
