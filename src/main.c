/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/01 23:02:26 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "libft.h"	// free_2d_array 2d_arr_len
#include "mlx.h"
#include <stdio.h> // debug printf

int	key_hook(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

void	start_mlx(t_mlx *mlx)
{
	mlx->width = WIN_WIDTH;
	mlx->height = WIN_WIDTH * WIN_RATIO;
	mlx->instance = mlx_init();
	mlx->win = mlx_new_window(mlx->instance, mlx->width, mlx->height, "MiniRT");
	mlx_key_hook(mlx->win, key_hook, mlx);
	if (!HEADLESS)
	{
		mlx_loop_hook(mlx->instance, NULL, mlx);
		mlx_loop(mlx->instance);
	}
}

void	setup_scene(t_scene *scene, char *file_name)
{
	char	*file_content_string;
	char	**file_content;

	file_content_string = get_file_content(file_name);
	file_content = ft_split(file_content_string, '\n');
	if (!file_content)
		exit_error("couldn't allocate split file content");
	is_correctly_formatted(file_content);
	set_camera(scene, file_content);
	set_lights(scene, file_content);
	set_ambient_light(scene, file_content);
	set_shapes(scene, file_content);
	ft_free_2d_array(&file_content, ft_2d_arrlen(file_content));
	free(file_content_string);
}

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
