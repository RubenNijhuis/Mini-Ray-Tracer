/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   number_format.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 17:08:27 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/07/05 16:33:12 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>

#include <stddef.h>

bool	is_valid_double_format(const char *str)
{
	const char	*str_before_numberskip;
	int			number_before_dot;

	if (*str == '-' || *str == '+')
		str++;
	str_before_numberskip = str;
	while (*str >= '0' && *str <= '9')
		str++;
	number_before_dot = str_before_numberskip < str;
	if (*str == 0 && number_before_dot)
		return (true);
	if (*str != '.')
		return (false);
	str++;
	str_before_numberskip = str;
	while (*str >= '0' && *str <= '9')
		str++;
	if (str_before_numberskip == str && !number_before_dot)
		return (false);
	while (*str == ' ')
		str++;
	return (*str == 0);
}

bool	is_integer_format(char *digit)
{
	size_t	current_char;

	current_char = 0;
	if (digit[current_char] == '-')
		current_char++;
	while (digit[current_char] != '\0')
	{
		if (digit[current_char] < '0' || digit[current_char] > '9')
			return (false);
		current_char++;
	}
	return (true);
}
