/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   number_format.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 17:08:27 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/30 21:19:58 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>

#include <stddef.h>

bool	is_float_format(char *digit)
{
	size_t	current_char;
	bool	has_dot;

	has_dot = false;
	current_char = 0;
	if (digit[current_char] == '-')
		current_char++;
	while (digit[current_char] != '\0')
	{
		if ((digit[current_char] < '0' || digit[current_char] > '9') && \
			digit[current_char] != '.')
			return (true);
		else if (digit[current_char] == '.' && has_dot == false)
			has_dot = true;
		current_char++;
	}
	return (false);
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
