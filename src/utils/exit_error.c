/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:46:29 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/26 09:33:23 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// exit
#include <stdio.h>	// printf

/**
 * @brief 
 * Exits the program displaying the error and returning 
 * exit code 1
 * @param str 
 */
void	exit_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}
