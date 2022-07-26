/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/26 12:03:36 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/07/26 16:00:11 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "ft_printf.h"
#include "parsing.h"

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h> 

bool	check_floats_formatting(char **items)
{
	size_t		cur_float;
	uint32_t	amount_items;

	amount_items = ft_2d_arrlen(items);
	cur_float = 0;
	while (cur_float < amount_items)
	{
		if (is_valid_double_format(items[cur_float]) == false)
			return (false);
		cur_float++;
	}
	return (true);
}

bool	check_ints_formatting(char **items)
{
	size_t		cur_float;
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

bool	check_range_int(char **items, int64_t min, int64_t max)
{
	size_t	arr_len;
	size_t	current_item;
	int64_t	current_val;

	current_item = 0;
	arr_len = ft_2d_arrlen(items);
	while (current_item < arr_len)
	{
		current_val = ft_atoi(items[current_item]);
		if (current_val < min || current_val > max)
			return (false);
		current_item++;
	}
	return (true);
}

bool	check_range_float(char **items, float min, float max)
{
	size_t	arr_len;
	size_t	current_item;
	float	current_val;

	current_item = 0;
	arr_len = ft_2d_arrlen(items);
	while (current_item < arr_len)
	{
		current_val = ft_atof(items[current_item]);
		if (current_val < min || current_val > max)
			return (false);
		current_item++;
	}
	return (true);
}
