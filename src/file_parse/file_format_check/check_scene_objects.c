/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_scene_objects.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 09:43:08 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/30 20:32:52 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "libft.h"
#include "parsing.h"

// checks wether the file doesn't contain too many objects.
// obj_type is the obj_type, i.e. SCENE_SHAPES or LIGHT.
// max is the maximum allowed. object_noun is for the error message,
// i.e. "light" for a light.
uint32_t	check_amount_generic(t_line *lines, char *obj_type,
	uint32_t max, char *object_noun)
{
	uint32_t	n;
	size_t		current_line;

	current_line = 0;
	n = 0;
	while (lines[current_line].line != NULL)
	{
		if (ft_is_object(obj_type, lines[current_line].line))
		{
			n++;
			if (n > max)
			{
				ft_putstr_fd("Error: too many ", 2);
				ft_putstr_fd(object_noun, 2);
				ft_putstr_fd("s(max ", 2);
				ft_putnbr_fd(max, 2);
				exit_error(")");
			}
		}
		lines++;
	}
	return (n);
}

// same as check_amount_generic, except this one checks if at least
// one object is present.
uint32_t	check_amount_mandatory(t_line *lines, char *obj_type,
	uint32_t max, char *object_noun)
{
	uint32_t	n;

	n = check_amount_generic(lines, obj_type, max, object_noun);
	if (n == 0)
	{
		ft_putstr_fd("Error: missing ", 2);
		ft_putstr_fd(object_noun, 2);
		exit_error("");
	}
	return (n);
}
