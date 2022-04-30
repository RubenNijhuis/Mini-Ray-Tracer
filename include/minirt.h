/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:43 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/30 20:45:53 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

//	t_camera t_ambient_light
//	t_light t_object
# include "objects.h"

// uint32_t
#include <stdlib.h>

# ifndef BONUS
#  define BONUS 0
# endif

#define MAX_SHAPES 100
#define MAX_LIGHTS 100

typedef struct program_data
{
	t_camera		*camera;

	t_ambient_light	*amb_light;
	t_light			*lights;

	t_object		*shapes;
	uint32_t		amount_shapes;
}	t_program_data;

void	set_shapes(t_program_data *pd, char **file_content);
char	*get_file_content(char *file_name);

#endif