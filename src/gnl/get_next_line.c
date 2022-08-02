/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/17 18:02:57 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/08/02 12:20:25 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

#include <unistd.h> /* read */
#include <stdlib.h> /* free */

/* copies a new line and returns it, shifts the rest to the beginning. */
static char	*generate_line(char **sto, ssize_t *len, ssize_t *status)
{
	char	*ret;
	size_t	index;

	ret = NULL;
	index = (size_t)ft_protec_strchr(*sto, '\n');
	if (index == 0)
	{
		if (**sto != 0)
			ret = ft_strndup_unsafe(*sto, *len);
		*status = *len;
		*len = 0;
		free(*sto);
		*sto = NULL;
	}
	else
	{
		index -= ((size_t)(*sto));
		*status = index + 1;
		ret = ft_strndup_unsafe(*sto, *status);
		ft_memcpy(*sto, *sto + *status, *len + 1 - *status);
		*len -= *status;
	}
	return (ret);
}

/* reads until a newline or EOF, stores it in s with the length in len. */
static ssize_t	read_until_newline(const int fd, char **s, ssize_t *len)
{
	char	buf[GNL_BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = 0;
	while (ft_protec_strchr(*s, '\n') == 0)
	{
		bytes_read = read(fd, buf, GNL_BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			return (bytes_read);
		}
		buf[bytes_read] = 0;
		*len += bytes_read;
		*s = gnl_strfjoin(*s, buf);
	}
	return (bytes_read);
}

/* gets the next line of a file fd. Status is -1 on error, otherwise
 * the length of the line returned. */
char	*get_next_line(const int fd, ssize_t *status)
{
	static char		*sto = NULL;
	static ssize_t	len = 0;
	ssize_t			bytes_read;

	*status = 0;
	if (ft_protec_strchr(sto, '\n') == 0)
	{
		bytes_read = read_until_newline(fd, &sto, &len);
		if (bytes_read == 0 && sto == NULL)
		{
			return (NULL);
		}
		else if (bytes_read == -1)
		{
			*status = -1;
			return (NULL);
		}
	}
	return (generate_line(&sto, &len, status));
}
