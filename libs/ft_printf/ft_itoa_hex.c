/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_hex.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:53:03 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/22 15:04:46 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h> /* malloc */

/* this is a strdup which stops at len characters.
 * it duplicates string s1 with len characters. Returns NULL on malloc fail.
 * it does NO BOUNDS CHECKING. If you give a len greater than its
 * string length, it will access memory it's not supposed to. */
static char	*ft_strndup_unsafe(const char *s1, const size_t len)
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

/* sets a hex string to s based on single byte b.
 * At the first char we merely need to shift it as the
 * result of shifting itself removes the other nibble. */
static void	m_itoa_hex_byte(char *s, const unsigned char b)
{
	const char	*hex = "0123456789abcdef";

	s[0] = hex[b >> 4];
	s[1] = hex[b & 0x0f];
}

/* does itoa for a size_t, but in hexadecimal. */
char	*ft_itoa_hex_size_t(size_t nbr)
{
	char	s[sizeof(size_t) * 2];
	size_t	i;
	size_t	j;

	i = 0;
	j = (sizeof(size_t) - 1) * 2;
	while (i < sizeof(size_t))
	{
		m_itoa_hex_byte((s + j), ((unsigned char *)&nbr)[i]);
		i++;
		j -= 2;
	}
	i = 0;
	while (i < sizeof(size_t) * 2 - 1 && s[i] == '0')
	{
		i++;
	}
	return (ft_strndup_unsafe(s + i, sizeof(size_t) * 2 - i));
}
