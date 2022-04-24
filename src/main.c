/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/24 19:54:55 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "objects.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

int	main(int argc, char **argv)
{
	// int			fd;
	// t_object	*objs;

	if (argc != 2)
		exit(-1);
	(void)argv;
	// setbuf(stdout, NULL);
	// fd = open(argv[1], O_RDONLY);
	// objs = get_objects_from_file(fd);
	// printf("%ld\n", objs[0].colors->values[0]);
	return (0);
}
