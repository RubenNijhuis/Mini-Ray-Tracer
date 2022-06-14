/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_objstrcmp.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 18:21:58 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/14 18:39:55 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

// this is a special strcmp. s1 is what it should be(i.e. CAMERA, SPHERE etc.)
// s2 is the beginning of the line/user input
// it is assumed it is followed by a space.
// returns true if it's a correct input, otherwise returns false.
bool	rt_objstrcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 == 0 && *s2 == ' ');
}
