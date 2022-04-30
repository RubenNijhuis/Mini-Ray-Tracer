/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atof.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 22:21:41 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/30 22:21:56 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Credits -> abba
double	ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;

	if (!str)
		return (0);
	c = (char *)str;
	res = (double)ft_atoi(c);
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	res2 = (double)ft_atoi(c);
	len = ft_strlen(c);
	while (len--)
		res2 /= 10;
	if (res >= 0)
	{
		return (res + res2);
	}
	return (res - res2);
}
