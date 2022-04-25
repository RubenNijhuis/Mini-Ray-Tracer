/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/25 22:24:44 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"

#include <stdio.h>  // printf
#include <fcntl.h>  // open
#include <stdlib.h> // exit

int	main(int argc, char **argv)
{
	int				fd;
	t_program_data	pd;

	if (argc != 2)
		exit(-1);
	setbuf(stdout, NULL);
	fd = open(argv[1], O_RDONLY);
	pd-> = get_objects_from_file(fd);
	printf("%ld\n", objs[0].colors->values[0]);
	return (0);
}
