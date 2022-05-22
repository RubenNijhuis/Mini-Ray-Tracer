/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 11:26:51 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/05/22 10:58:44 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "mlx.h"

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
	char	**file_content;

	file_content = get_file_content(file_name);
	is_file_correctly_formatted(file_content);
	set_camera(scene, file_content);
	set_lights(scene, file_content);
	set_ambient_light(scene, file_content);
	set_shapes(scene, file_content);
	ft_free_2d_array(&file_content, ft_2d_arrlen(file_content));
}
