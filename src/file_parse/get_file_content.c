/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_file_content.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 11:44:54 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/27 16:29:27 by rnijhuis      ########   odam.nl         */
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

void	replace_chars(char *line, char cur, char new)
{
	uint32_t	cur_char;

	cur_char = 0;
	while (line[cur_char] != '\0')
	{
		if (line[cur_char] == cur)
			line[cur_char] = new;
		cur_char++;
	}
}

/**
 * Grabs the next string from the file and places it in a t_line struct
 * Also trims the \n and replaces the \t with spaces
 */
static t_line	*fill_string_array(int fd, uint32_t amount_lines_in_file)
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
		replace_chars(total_file[current_line].line, '\t', ' ');
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
	full_file_string = fill_string_array(fd, amount_lines_in_file);
	if (full_file_string == NULL)
		malloc_error();
	if (close(fd) == -1)
		exit_perror("close");
	return (full_file_string);
}
