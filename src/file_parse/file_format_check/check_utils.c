/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/26 12:03:36 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/26 13:56:32 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h> 

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

void	print_err_msg(char *data_type, char *issue, uint32_t line)
{
	ft_dprintf(2, "Error: %s %s on line %i\n", data_type, issue, line);
}

bool	check_values_range_float(char **items, float min, float max)
{
	size_t	arr_len;
	size_t	current_item;
	bool	status;
	float	current_val;

	status = true;
	current_item = 0;
	arr_len = ft_2d_arrlen(items);
	while (current_item < arr_len)
	{
		current_val = ft_atof(items[current_item]);
		if (current_val < min || current_val > max)
		{
			status = false;
			break ;
		}
		current_item++;
	}
	return (status);
}

bool	check_floats_formatting(char **items)
{
	uint32_t	cur_float;
	uint32_t	amount_items;

	amount_items = ft_2d_arrlen(items);
	cur_float = 0;
	while (cur_float < amount_items)
	{
		if (is_float_format(items[cur_float]) == false)
			return (false);
		cur_float++;
	}
	return (true);
}

bool	check_ints_formatting(char **items)
{
	uint32_t	cur_float;
	uint32_t	amount_items;

	cur_float = 0;
	amount_items = ft_2d_arrlen(items);
	while (cur_float < amount_items)
	{
		if (is_integer_format(items[cur_float]) == false)
			return (false);
		cur_float++;
	}
	return (true);
}

bool	check_values_range_int(char **items, int64_t min, int64_t max)
{
	size_t	arr_len;
	size_t	current_item;
	bool	status;
	int64_t	current_val;

	status = true;
	current_item = 0;
	arr_len = ft_2d_arrlen(items);
	while (current_item < arr_len)
	{
		current_val = ft_atoi(items[current_item]);
		if (current_val < min || current_val > max)
		{
			status = false;
			break ;
		}
		current_item++;
	}
	return (status);
}
