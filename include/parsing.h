/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 23:23:47 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/30 21:17:58 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"
# include "objects.h"

# include <stdbool.h>
# include <stdint.h>

/*
 Error enum
*/
typedef enum s_error_type
{
	out_of_range,
	format,
	amount_values
}	t_error_type;

/**
 * Struct that gives context to a line in the file.
 * Keeps track of it's actual position in the file
 * to create more descriptive error messages
 */
typedef struct s_line
{
	char		*line;
	uint32_t	file_line;
}	t_line;

/* 
 Component checker function definition
*/
typedef bool	(*t_comp_checker_func)(char *settings, uint32_t line_pos);

/*
 Main functions
*/
void		is_file_correctly_formatted(t_scene *scene, t_line *lines);
t_line		*get_file_content(char *file_name);
t_line		*find_obj_in_file(char *definition, t_line *file_content);
void		free_file_content(t_line *lines);

/*
 Setup objects
*/
void		set_lights(t_scene *scene, t_line *file_content);
void		set_shapes(t_scene *scene, t_line *file_content);
void		setup_scene(t_scene *scene, char *file_name);

/*
 Input checking
*/
void		run_object_checks(t_object_type obj_type, t_line line);

// Simple elements
bool		check_radius(char *settings, uint32_t line_pos);
bool		check_height(char *settings, uint32_t line_pos);
bool		check_fov(char *settings, uint32_t line_pos);
bool		check_brightness(char *settings, uint32_t line_pos);

// Vectors
bool		check_position(char *settings, uint32_t line_pos);
bool		check_rotation(char *settings, uint32_t line_pos);
bool		check_color(char *settings, uint32_t line_pos);

// Number format
bool		is_integer_format(char *digit);
bool		is_float_format(char *digit);
bool		check_ints_formatting(char **items);
bool		check_floats_formatting(char **items);

// Range checking
bool		check_values_range_int(char **items, int64_t min, int64_t max);
bool		check_values_range_float(char **items, float min, float max);

/*
 Utils
*/
// Object checking in file
uint32_t	check_amount_generic(t_line *lines, char *obj_type,
				uint32_t max, char *object_noun);
uint32_t	check_amount_mandatory(t_line *lines, char *obj_type,
				uint32_t max, char *object_noun);

// File format checking
void		check_amount_lights(t_line *lines);
void		check_amount_cameras(t_line *lines);
void		check_amount_ambient_lights(t_line *lines);

// Parse messages
void		print_err_msg(char *data_type, uint32_t line, t_error_type error);

#endif