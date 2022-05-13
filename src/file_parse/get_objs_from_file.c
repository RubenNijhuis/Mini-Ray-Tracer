/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_objs_from_file.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 19:37:07 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/13 17:42:54 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "objects.h"
#include "minirt.h"

#include <stdbool.h>	// true false
#include <stdlib.h>		// uint32_t
#include <stdio.h>		// printf

/*
	Returns true if any character in needle is present in haystack.
	If needle "", returns false.
 */
bool	ft_anychar_n_str(const char *haystack, const char *needle)
{
	size_t	i;

	while (*haystack != '\0')
	{
		i = 0;
		while (needle[i] != '\0')
		{
			if (*haystack == needle[i])
			{
				return (true);
			}
			i++;
		}
		haystack++;
	}
	return (false);
}

uint32_t	get_amount_objects(char **file_content, char *type)
{
	uint32_t	amount_objects;
	uint32_t	i;

	i = 0;
	amount_objects = 0;
	while (file_content[i] != NULL)
	{
		if (ft_anychar_n_str(type, file_content[i]) == true)
			amount_objects++;
		i++;
	}
	return (amount_objects);
}
