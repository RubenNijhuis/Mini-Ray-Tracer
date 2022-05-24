/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/24 18:01:38 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <stdio.h> // debug printf

#include <stdbool.h>
#include <math.h>

#include <stdlib.h> // exit

#include "libvec.h"
#include "ray.h"

void	init_mlx(t_program_data *pd)
{
	pd->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "miniRT", true);
	if (!pd->mlx)
	{
		// TODO: stderr
		printf("mlx init failed!\n");
		exit(1);
	}
	pd->img = mlx_new_image(pd->mlx, WIN_WIDTH, WIN_HEIGHT);
	ft_memset(pd->img->pixels, 0, pd->img->width * pd->img->height * sizeof(int));
}

void	start_mlx(t_program_data *pd)
{
	//mlx_loop_hook(pd->mlx, &key_hook, pd->mlx);
	mlx_image_to_window(pd->mlx, pd->img, 0, 0);
	mlx_loop(pd->mlx);
}

bool	intersects_sphere(t_ray *ray, t_sphere *sphere)
{
	t_vec3f	v = ray->direction;

	// t
	// lengte van vector tot aan parallel van sphere origin
	t_vec3f temp = vec3f_subtract(sphere->base.position, ray->origin);
	float t = vec3f_dot(temp, ray->direction);

	// p
	// length
	vec3f_multiply_scalar(&v, t);
	t_vec3f p = vec3f_sum(ray->origin, v);

	// y
	float y = vec3f_length(vec3f_subtract(sphere->base.position, p));

	bool isinsphere = y <= sphere->diameter / 2;

	// if (isinsphere == true)
	// {
	// 	// find intersection point
	// 	float x = sqrt((r * r) - (y * y));
	// 	float ip1 = t - x;
	// 	float ip2 = t + x;
	// 	printf("%f intersection point front\n", ip1);
	// 	printf("%f intersection point back\n", ip2);
	// }
	return (isinsphere);
}

float mapx(int input)
{
	return ((input - 0) * (0.1 - -0.1) / (WIN_WIDTH - 1 -  0) + -0.1);
}

float mapy(int input)
{
	return ((input - 0) * (0.1 - -0.1) / (WIN_HEIGHT - 1 - 0) + -0.1);
}

void	render(t_program_data *pd)
{
	int			xpixel;
	int			ypixel;
	t_ray		ray;

	t_sphere	sphere1;
	t_sphere	sphere2;
 
	ray.direction = vec3f(0, 0, 1);

	ft_memset(&sphere1, 0, sizeof(sphere));
	ft_memset(&sphere2, 0, sizeof(sphere));
	sphere1.base.position = vec3f(5, 0, 100);
	sphere2.base.position = vec3f(0, 0, 300);
	sphere1.diameter = 10;
	sphere2.diameter = 10;

	ypixel = 0;
	while (ypixel < WIN_HEIGHT)
	{
		xpixel = 0;
		while (xpixel < WIN_WIDTH)
		{
			// ray.origin = vec3f(xpixel - WIN_WIDTH / 2, ypixel - WIN_HEIGHT / 2, 0);
			ray.origin = vec3f(0, 0, 0);

			ray.direction = vec3f(mapx(xpixel), mapy(ypixel), 1);
			vec3f_normalize(&ray.direction);
			if (intersects_sphere(&ray, &sphere2))
			{
				mlx_put_pixel(pd->img, xpixel, ypixel, 0xffffffff);
			}
			if (intersects_sphere(&ray, &sphere1))
			{
				mlx_put_pixel(pd->img, xpixel, ypixel, 0xff00ffff);
			}
			xpixel++;
		}
		ypixel++;
	}
}

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
	init_mlx(&pd);

	render(&pd);
	start_mlx(&pd);
	// print_scene_elements(&pd->scene);
	return (0);
}
