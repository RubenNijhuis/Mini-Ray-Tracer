/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_objs_from_file.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 19:37:07 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/13 15:59:16 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "objects.h"
#include "minirt.h"

#include <stdbool.h>	// true false
#include <stdlib.h>		// uint32_t
#include <stdio.h>		// printf

/*
	Checks wether a char of a string is in another string
	Loops through string one and compares if a char in 
	string two is equal to the current char in string one
 */
bool	ft_anychar_n_str(char *h, char *n)
{
	int	i;

	i = 0;
	while (h[i] != '\0')
	{
		if (ft_strncmp(&h[i], n, 1) == 0)
			return (true);
		i++;
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
