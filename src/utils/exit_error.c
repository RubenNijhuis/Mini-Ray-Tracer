/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:46:29 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/01 11:47:48 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// exit
#include <stdio.h>	// printf

void	exit_error(char *str)
{
	printf("Error: %s\n", str);
	exit(1);
}
