/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_objs_from_string.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 19:37:07 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/14 19:27:51 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "objects.h"
#include "minirt.h"

#include <stdbool.h>	// true false
#include <stdint.h>		// uint32_t

static uint32_t	get_len(const char *str)
{
	uint32_t	i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		i++;
	}
	return (i);
}

// returns wether the current line contains an object from the object string.
// i.e. ft_is_object("sp cl pl", "pl 0,-1,0 (...)")
bool	ft_is_object(const char *object_str, const char *line)
{
	uint32_t	len;

	if (ft_strchr(object_str, ' ') == NULL)
	{
		return (rt_objstrcmp(object_str, line));
	}
	else
	{
		while (*object_str)
		{
			len = get_len(object_str);
			if (ft_strncmp(object_str, line, len) == 0
				&& (line[len] == ' ' || line[len] == '\0'))
			{
				return (true);
			}
			object_str += len;
			while (*object_str == ' ')
			{
				object_str++;
			}
		}
	}
	return (false);
}
