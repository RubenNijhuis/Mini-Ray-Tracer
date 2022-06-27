/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_file_content.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 11:44:54 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/27 18:44:44 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "minirt.h"
#include "parsing.h"

#include <stdlib.h>	// free
#include <fcntl.h>	// Open

static uint32_t	get_amount_lines(int fd)
{
	uint32_t	amount_lines;
	char		*new_line;

	amount_lines = 0;
	while (1)
	{
		new_line = get_next_line(fd);
		if (new_line == NULL)
			break ;
		free(new_line);
		amount_lines++;
	}
	return (amount_lines);
}

/**
 * Grabs the next string from the file and places it in a t_line struct
 * Also trims the \n and replaces the \t with spaces
 */
static t_line	*get_file_lines(int fd, uint32_t amount_lines_in_file)
{
	t_line		*total_file;
	uint32_t	current_line;

	current_line = 0;
	total_file = ft_calloc(amount_lines_in_file + 1, sizeof(t_line));
	if (total_file == NULL)
		malloc_error();
	while (current_line < amount_lines_in_file)
	{
		total_file[current_line].line = get_next_line(fd);
		total_file[current_line].line[\
			ft_strlen(total_file[current_line].line) - 1] = '\0';
		ft_repl_chr(total_file[current_line].line, '\t', ' ');
		total_file[current_line].file_line = current_line + 1;
		if (total_file[current_line].line == NULL)
			exit_perror("Get Next Line had an issue returning a file line");
		current_line++;
	}
	total_file[amount_lines_in_file].line = NULL;
	return (total_file);
}

t_line	*get_file_content(char *file_name)
{
	int32_t		fd;
	uint32_t	amount_lines_in_file;
	t_line		*full_file_string;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		exit_perror("open");
	amount_lines_in_file = get_amount_lines(fd);
	if (close(fd) == -1)
		exit_perror("close");
	fd = open(file_name, O_RDONLY);
	full_file_string = get_file_lines(fd, amount_lines_in_file);
	if (full_file_string == NULL)
		malloc_error();
	if (close(fd) == -1)
		exit_perror("close");
	return (full_file_string);
}
