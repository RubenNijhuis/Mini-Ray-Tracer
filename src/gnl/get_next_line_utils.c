/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/17 18:03:01 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/08/02 12:14:36 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

#include <stdlib.h> /* malloc, free */

/* this is a strdup which stops at len characters.]
 * it duplicates string s1 with len characters. Returns NULL on malloc fail.
 * it does NO BOUNDS CHECKING. If you give a len greater than its
 * string length, it will access memory it's not supposed to. */
char	*ft_strndup_unsafe(const char *s1, const size_t len)
{
	char	*s2;

	s2 = malloc((len + 1) * sizeof(char));
	if (s2 != NULL)
	{
		ft_memcpy(s2, s1, len);
		s2[len] = 0;
	}
	return (s2);
}

/* locates memory location of char c in s, returns NULL if not found.
 * it is protected, s may be null. */
char	*ft_protec_strchr(const char *s, const int c)
{
	if (s == NULL)
		return ((char *)s);
	while (*s != 0)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if ((char)c == 0)
	{
		return ((char *)s);
	}
	return (NULL);
}

/* modified strjoin which frees s1. s1 may be NULL,
 * s2 never should be. */
char	*gnl_strfjoin(char *s1, char const *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;

	s2_len = ft_strlen(s2);
	if (s1 == NULL)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	res = malloc(s1_len + s2_len + 1);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, s1, s1_len);
	ft_memcpy(res + s1_len, s2, s2_len);
	if (s1 != NULL)
		free(s1);
	res[s2_len + s1_len] = 0;
	return (res);
}
