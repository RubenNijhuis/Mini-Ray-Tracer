/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:43 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/29 18:28:38 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*	t_camera t_ambient_light
 *	t_light t_object
 */

# include "objects.h"
# include "libft.h"

#include <stdlib.h> // uint32_t

# ifndef BONUS
#  define BONUS 0
# endif

typedef struct program_data
{
	t_camera		*camera;

	t_ambient_light	*amb_light;
	t_light			*lights;

	t_object		*shapes;
	uint32_t		amount_shapes;
}	t_program_data;

void	get_objects_from_file(t_program_data *pd, char *file_name);

#endif