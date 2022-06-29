/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 10:55:16 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/29 18:00:24 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft_printf.h"

#include <stdint.h>
#include <stdlib.h>

void	free_file_content(t_line *file_content)
{
	uint32_t	cur_line;

	cur_line = 0;
	while (file_content[cur_line].line != NULL)
	{
		free(file_content[cur_line].line);
		cur_line++;
	}
	free(file_content);
}

char	*get_error_string(t_error_type err)
{
	static const char	*messages[] = {
	[out_of_range] = "value out of range",
	[format] = "value formatted incorrectly",
	[amount_values] = "incorrect amount of values"
	};

	return ((char *)messages[err]);
}

void	print_err_msg(char *data_type, uint32_t line, t_error_type error)
{
	ft_dprintf(2, "Error: ");
	ft_dprintf(2, "%s %s", data_type, get_error_string(error));
	ft_dprintf(2, " on line %i\n", line);
}
