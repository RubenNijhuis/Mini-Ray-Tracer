/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/02 11:26:46 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "libft.h"	// free_2d_array 2d_arr_len
#include "mlx.h"
#include <stdio.h> // debug printf

int	main(int argc, char **argv)
{
	t_program_data	*pd;

	if (argc != 2)
	{
		printf("Usage: minirt [path-to-file]\n");
		return (1);
	}
	pd = ft_calloc(1, sizeof(t_program_data));
	if (!pd)
		exit_error("couldn't allocate program data struct");
	setup_scene(&pd->scene, argv[1]);
	print_scene_elements(&pd->scene);
	start_mlx(&pd->mlx);
	return (0);
}
