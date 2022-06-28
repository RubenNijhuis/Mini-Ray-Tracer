/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 10:55:16 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/28 10:58:41 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
