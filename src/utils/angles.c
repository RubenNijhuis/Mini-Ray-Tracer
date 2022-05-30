/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   angles.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 12:55:31 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/30 13:14:15 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

float	deg_to_rad(const float a)
{
	return (a / 360.0f * 2.0f * M_PI);
}

float	rad_to_deg(const float a)
{
	return (a / (2.0f * M_PI) * 360.0f);
}
