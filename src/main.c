/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/30 20:31:40 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "libft.h"	// free_2d_array 2d_arr_len
#include <stdio.h>	// printf

void	setup_scene(t_program_data *pd, char *file_name)
{
	char	*file_content_string;
	char	**file_content;

	file_content_string = get_file_content(file_name);
	file_content = ft_split(file_content_string, '\n');
	// set_lights(pd, file_content);
	// set_camera(pd, file_content);
	// set_ambient_light(pd, file_content);
	set_shapes(pd, file_content);
	ft_free_2d_array(&file_content, ft_2d_arrlen(file_content));
}

int	main(int argc, char **argv)
{
	t_program_data	pd;

	if (argc != 2)
		return (-1);
	setup_scene(&pd, argv[1]);
	print_shapes(pd.shapes, pd.amount_shapes);
	return (0);
}
