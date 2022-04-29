/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:43 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/29 11:35:23 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "objects.h"
# include "libft.h"

# ifndef BONUS
#  define BONUS 0
# endif

typedef struct program_data
{
	t_camera		*camera;
	t_ambient_light	*amb_light;
	t_light			*lights;
	t_object		*objs;
}	t_program_data;

t_object	*get_objects_from_file(char *file_name);

#endif