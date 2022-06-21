/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 23:23:47 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/21 23:36:02 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "minirt.h"
#include <stdint.h>

/**
 * Struct that gives context to a line in the file.
 * Keeps track of it's actual position in the file
 * to create more descriptive error messages
 */
typedef struct	s_line
{
	char		*line;
	uint32_t	file_line;
	uint32_t	data_line;
}	t_line;

/*
 Main functions
*/
void	is_file_correctly_formatted(t_scene *scene, char **lines);

/*
 Utils
*/

#endif