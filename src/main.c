/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/25 18:55:20 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // debug printf

#include "minirt.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_program_data	pd;

	if (argc != 2)
	{
		// TODO: stderr
		printf("Usage: minirt [path-to-file]\n");
		return (1);
	}
	ft_memset(&pd, 0, sizeof(t_program_data));
	setup_scene(&pd.scene, argv[1]);
	print_scene_elements(&pd.scene);
	init_mlx(&pd);
	render(&pd);
	start_mlx(&pd);
	return (0);
}
