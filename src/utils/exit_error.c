/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:46:29 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/22 14:59:20 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> /* exit */
#include <stdio.h> /* perror */

#include "ft_printf.h"

/**
 * @brief 
 * Exits the program displaying the error and 
 * exits with status code 1
 * @param msg 
 */
void	exit_error(const char *msg)
{
	ft_dprintf(2, "%s\n", msg);
	exit(1);
}

// perrors and exitst the program
void	exit_perror(const char *msg)
{
	perror(msg);
	exit(1);
}

void	malloc_error(void)
{
	exit_perror("malloc");
}
