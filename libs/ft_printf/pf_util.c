/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_util.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:42:42 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/22 13:45:46 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_cisupper(const int c)
{
	return ((const unsigned char)c >= 'A'
		&& (const unsigned char)c <= 'Z');
}
