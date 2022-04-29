/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/29 11:40:54 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"

#include <stdio.h>  // printf
#include <fcntl.h>  // open

// setbuf(stdout, NULL);

void	setup_scene(t_program_data *pd, char *file_name)
{
	pd->objs = get_objects_from_file(file_name);
}

int	main(int argc, char **argv)
{
	t_program_data	pd;

	if (argc != 2)
		return (-1);
	setup_scene(&pd, argv[1]);
	// printf("%ld\n", pd.objs[0].base.color.values[0]);
	return (0);
}
