/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   number_format.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 17:08:27 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/27 17:13:27 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>

bool	is_float_format(char *digit)
{
	uint32_t	current_char;
	bool		has_dot;
	bool		format_status;

	has_dot = false;
	format_status = true;
	current_char = 0;
	if (digit[current_char] == '-')
		current_char++;
	while (digit[current_char] != '\0')
	{
		if ((digit[current_char] < '0' || digit[current_char] > '9') && \
			digit[current_char] != '.')
			format_status = false;
		else if (digit[current_char] == '.' && has_dot == false)
			has_dot = true;
		current_char++;
	}
	return (format_status);
}

bool	is_integer_format(char *digit)
{
	uint32_t	current_char;
	bool		format_status;

	format_status = true;
	current_char = 0;
	if (digit[current_char] == '-')
		current_char++;
	while (digit[current_char] != '\0')
	{
		if (digit[current_char] < '0' || digit[current_char] > '9')
			format_status = false;
		current_char++;
	}
	return (format_status);
}
