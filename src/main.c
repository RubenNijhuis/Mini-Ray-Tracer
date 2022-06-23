/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/23 10:31:31 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"
#include "libft.h"
#include "parsing.h"

// TODO: Remove debug or only run on debug mode
int	main(int argc, char **argv)
{
	t_program_data	pd;

	if (argc != 2)
		exit_error("Usage: minirt [path-to-file]\n");
	ft_memset(&pd, 0, sizeof(t_program_data));
	setup_scene(&pd.scene, argv[1]);
	print_scene_elements(&pd.scene);
	init_mlx(&pd);
	render(&pd);
	start_mlx(&pd);
	return (0);
}
