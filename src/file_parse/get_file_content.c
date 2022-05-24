/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_file_content.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 11:44:54 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/24 15:01:57 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "minirt.h"

#include <stdlib.h>	// free
#include <fcntl.h>	// Open

static uint32_t	get_amount_lines(int32_t fd)
{
	uint32_t	amount_lines;
	char		*new_line;

	amount_lines = 0;
	while (1)
	{
		new_line = get_next_line(fd);
		free(new_line);
		if (new_line == NULL)
			break ;
		amount_lines++;
	}
	return (amount_lines);
}

static char	**fill_string_array(uint32_t fd, uint32_t amount_lines_in_file)
{
	char		**total_file;
	uint32_t	current_line;

	current_line = 0;
	total_file = ft_calloc(amount_lines_in_file, sizeof(char *));
	if (total_file == NULL)
		exit(1);
	total_file[amount_lines_in_file] = NULL;
	while (current_line < amount_lines_in_file)
	{
		total_file[current_line] = get_next_line(fd);
		if (total_file[current_line] == NULL)
			exit(1);
		current_line++;
	}
	return (total_file);
}

char	**get_file_content(char *file_name)
{
	int32_t		fd;
	uint32_t	amount_lines_in_file;
	char		**full_file_string;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		exit_error("Error: Couldn't find or open file\n");
	amount_lines_in_file = get_amount_lines(fd);
	if (close(fd) == -1)
		exit_error("Error: Couldn't close file\n");
	fd = open(file_name, O_RDONLY);
	full_file_string = fill_string_array(fd, amount_lines_in_file);
	if (full_file_string == NULL)
		exit_error("Error: Malloc of file went wrong\n");
	if (close(fd) == -1)
		exit_error("Error: Couldn't close file\n");
	return (full_file_string);
}
