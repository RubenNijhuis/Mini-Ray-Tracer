/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 23:23:47 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/22 00:17:08 by rubennijhui   ########   odam.nl         */
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
}	t_line;

/*
 Main functions
*/
void		is_file_correctly_formatted(t_scene *scene, t_line *lines);
t_line		*get_file_content(char *file_name);
void		free_file_content(t_line *lines);

/*
 Utils
*/
uint32_t	check_amount_generic(t_line *lines, char *obj_type,
				uint32_t max, char *object_noun);
uint32_t	check_amount_mandatory(t_line *lines, char *obj_type,
				uint32_t max, char *object_noun);
void		check_amount_lights(t_line *lines);
void		check_amount_cameras(t_line *lines);
void		check_amount_ambient_lights(t_line *lines);

#endif