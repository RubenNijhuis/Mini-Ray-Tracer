/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/07/27 13:31:12 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"
#include "libft.h"
#include "parsing.h"

int32_t	main(int argc, char **argv)
{
	t_program_data	pd;

	if (argc != 2)
		exit_error("Usage: minirt [path-to-file]");
	ft_memset(&pd, 0, sizeof(t_program_data));
	setup_scene(&pd.scene, argv[1]);
	if (DEBUG)
	{
		print_scene_elements(&pd.scene);
	}
	init_mlx(&pd);
	render(&pd);
	start_mlx(&pd);
	return (0);
}
