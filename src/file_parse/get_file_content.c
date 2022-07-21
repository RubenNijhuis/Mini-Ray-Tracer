/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_file_content.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 11:44:54 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/07/21 17:19:42 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "minirt.h"
#include "parsing.h"

#include <stdlib.h>	// free
#include <fcntl.h>	// Open

static size_t	get_amount_lines(int fd)
{
	size_t	amount_lines;
	char	*new_line;

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

void	create_lines_context(t_line *lines)
{
	size_t	cur_line;
	char	*trimmed_str;

	cur_line = 0;
	while (lines[cur_line].line != NULL)
	{
		trimmed_str = ft_strtrim(lines[cur_line].line, "\t\n ");
		free(lines[cur_line].line);
		lines[cur_line].line = trimmed_str;
		ft_repl_chr(lines[cur_line].line, '\t', ' ');
		if (lines[cur_line].line[0] == '#')
			lines[cur_line].type = comment;
		lines[cur_line].file_line = cur_line + 1;
		cur_line++;
	}
}

/**
 * Grabs the next string from the file and places it in a t_line struct
 * Also trims the \n and replaces the \t with spaces
 */
static t_line	*get_file_lines(int fd, uint32_t amount_lines_in_file)
{
	t_line	*total_file;
	size_t	current_line;

	current_line = 0;
	total_file = ft_calloc(amount_lines_in_file + 1, sizeof(t_line));
	if (total_file == NULL)
		malloc_error();
	while (current_line < amount_lines_in_file)
	{
		total_file[current_line].line = get_next_line(fd);
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
	t_line		*file_content;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		exit_perror("Open error");
	amount_lines_in_file = get_amount_lines(fd);
	if (close(fd) == -1)
		exit_perror("Close error");
	fd = open(file_name, O_RDONLY);
	file_content = get_file_lines(fd, amount_lines_in_file);
	if (file_content == NULL)
		malloc_error();
	create_lines_context(file_content);
	if (close(fd) == -1)
		exit_perror("Close error");
	return (file_content);
}
