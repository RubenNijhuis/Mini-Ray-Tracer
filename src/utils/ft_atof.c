/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atod.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 15:27:17 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/18 18:31:26 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static void	skip_whitespace(char **str)
{
	while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
	{
		(*str)++;
	}
}

static double	atod_postdecimal(const char *str)
{
	double		result;
	double		divisor;

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

	skip_whitespace((char **)&str);
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

int	is_valid_double_format(char *str)
{
	char	*str_before_numberskip;
	int		number_before_dot;

	skip_whitespace(&str);
	if (*str == '-' || *str == '+')
		str++;
	str_before_numberskip = str;
	while (*str >= '0' && *str <= '9')
		str++;
	number_before_dot = str_before_numberskip < str;
	if (*str == 0 && number_before_dot)
		return (1);
	if (*str != '.')
		return (0);
	str++;
	str_before_numberskip = str;
	while (*str >= '0' && *str <= '9')
		str++;
	if (str_before_numberskip == str && !number_before_dot)
		return (0);
	skip_whitespace(&str);
	return (*str == 0);
}
