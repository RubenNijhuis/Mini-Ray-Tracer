/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_file_contents.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 20:15:56 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/30 20:31:56 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

#include <fcntl.h> // Open

char	*get_file_content(char *file_name)
{
	char	*total_string;
	char	*new_str;
	char	*tmp;
	int		fd;

	fd = open(file_name, O_RDONLY);
	total_string = ft_calloc(1, sizeof(char));
	tmp = ft_calloc(1, sizeof(char));
	while (1)
	{
		new_str = get_next_line(fd);
		if (new_str == NULL)
			break ;
		free(total_string);
		total_string = ft_strjoin(tmp, new_str);
		free(tmp);
		free(new_str);
		tmp = ft_strdup(total_string);
	}
	free(tmp);
	free(new_str);
	return (total_string);
}
