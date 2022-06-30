/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_rt.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 11:26:51 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/06/30 20:30:29 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "parsing.h"
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

void	init_mlx(t_program_data *pd)
{
	pd->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "miniRT", true);
	if (!pd->mlx)
		exit_error("Error: couldn't start mlx");
	pd->img = mlx_new_image(pd->mlx, WIN_WIDTH, WIN_HEIGHT);
	ft_memset(pd->img->pixels, 0,
		pd->img->width * pd->img->height * sizeof(int));
	mlx_key_hook(pd->mlx, &key_hook, pd);
	mlx_image_to_window(pd->mlx, pd->img, 0, 0);
}

/* starts rendering of the window and such */
void	start_mlx(t_program_data *pd)
{
	mlx_loop(pd->mlx);
}

void	check_file_name(char *file_name)
{
	size_t	str_len;

	str_len = ft_strlen(file_name);
	if (str_len < 4)
		exit_error("Error: file name too short, this can't possibly be a real file");
	if (ft_strncmp(ft_substr(file_name, str_len - 3, 3), ".rt", 3) != 0)
		exit_error("Error: file name must end on '.rt'");
}

void	setup_scene(t_scene *scene, char *file_name)
{
	t_line	*file_content;

	check_file_name(file_name);
	file_content = get_file_content(file_name);
	scene->amount_lights = check_amount_mandatory(file_content, LIGHT,
			MAX_LIGHTS, "light");
	scene->amount_shapes = check_amount_generic(file_content, SCENE_SHAPES,
			MAX_SHAPES, "shape");
	is_file_correctly_formatted(scene, file_content);
	set_camera(&scene->camera, find_obj_in_file(CAMERA, file_content)->line);
	set_ambient_light(&scene->amb_light, \
		find_obj_in_file(AMBIENT_LIGHT, file_content)->line);
	set_lights(scene, file_content);
	set_shapes(scene, file_content);
	free_file_content(file_content);
}
