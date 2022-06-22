/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_uitoa.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:54:26 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:54:27 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h> /* malloc */

#define MAX_INT_STRING_LEN (12)

/* CURSED IMPLEMENTATION: I don't want to write the same code twice,
 * but I cannot use malloc for putnbr, so I came up with a struct
 * instead. Note: length does NOT include null terminator('\0'). */
typedef struct s_itoa_str
{
	char		data[MAX_INT_STRING_LEN];
	int			length;
}				t_itoa_str;

static void	m_inverse_string(char *s, int len)
{
	int		i;
	int		j;
	char	t;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		t = s[i];
		s[i] = s[j];
		s[j] = t;
		i++;
		j--;
	}
}

static int	m_uitoa_set_data(unsigned int n, t_itoa_str *t)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		t->data[i] = '0';
		i++;
	}
	while (n > 0)
	{
		t->data[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	return (i);
}

static t_itoa_str	m_uitoa(unsigned int n)
{
	t_itoa_str		t;
	unsigned int	i;

	i = m_uitoa_set_data(n, &t);
	t.data[i] = 0;
	m_inverse_string((char *)&t.data, i);
	t.length = i;
	return (t);
}

/* converts uint n to a freeable char* */
char	*ft_uitoa(unsigned int n)
{
	t_itoa_str	t;
	char		*ret;

	t = m_uitoa(n);
	t.length++;
	ret = malloc(t.length);
	if (ret == NULL)
		return (ret);
	return (ft_memcpy(ret, (char *)&t.data, t.length));
}

#undef MAX_INT_STRING_LEN
