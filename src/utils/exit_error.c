/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:46:29 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/10 17:43:46 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief 
 * Exits the program displaying the error and 
 * exits with status code 1
 * @param msg 
 */
// TODO: print to STDERR instead
void	exit_error(const char *msg)
{
	printf("%s\n", msg);
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
