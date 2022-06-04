/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 11:26:51 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/04 21:00:04 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "MLX42/MLX42.h"
#include "MLX42/MLX42_Input.h"

#include <stdlib.h> // exit

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_program_data	*pd;

	pd = (t_program_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(pd->mlx);
		exit(0);
	}
}

// TODO: stderr
void	init_mlx(t_program_data *pd)
{
	pd->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "miniRT", true);
	if (!pd->mlx)
		exit_error("Error: couldn't start mlx");
	pd->img = mlx_new_image(pd->mlx, WIN_WIDTH, WIN_HEIGHT);
	ft_memset(pd->img->pixels, 0,
		pd->img->width * pd->img->height * sizeof(int));
}

/* starts rendering of the window and such */
void	start_mlx(t_program_data *pd)
{
	mlx_key_hook(pd->mlx, &key_hook, pd);
	mlx_image_to_window(pd->mlx, pd->img, 0, 0);
	mlx_loop(pd->mlx);
}

void	setup_scene(t_scene *scene, char *file_name)
{
	char	**file_content;

	file_content = get_file_content(file_name);
	is_file_correctly_formatted(file_content);
	set_camera(scene, file_content);
	set_lights(scene, file_content);
	set_ambient_light(scene, file_content);
	set_shapes(scene, file_content);
	ft_free_2d_array(&file_content, ft_2d_arrlen(file_content));
}
