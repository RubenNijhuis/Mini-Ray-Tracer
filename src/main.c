/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/25 15:08:23 by rnijhuis      ########   odam.nl         */
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

float	intersects_sphere(t_ray *ray, t_sphere *sphere)
{
	t_vec3f	v = ray->direction;
	float	r = sphere->diameter / 2;
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

	bool isinsphere = y <= r;

	if (isinsphere == true)
	{
		// find intersection point
		float x = sqrt((r * r) - (y * y));
		float ip1 = t - x;
		// float ip2 = t + x;
		
		// TODO: return closest value but only if not negative
		return (ip1);
	}
	return (-1);
}

float mapx(int input)
{
	return ((input - 0) * (0.1 - -0.1) / (WIN_WIDTH - 1 -  0) + -0.1);
}

float mapy(int input)
{
	return -1*((input - 0) * (0.1 - -0.1) / (WIN_HEIGHT - 1 - 0) + -0.1);
}

t_vec3i	get_default_color(t_program_data *pd)
{
	(void)pd;
	t_vec3i	default_color;

	default_color.x = 0;
	default_color.y = 0;
	default_color.z = 0;
	return (default_color);
}

t_vec3i	get_ray_color(t_ray *ray, uint32_t x, uint32_t y, t_program_data *pd)
{
	uint32_t	current_shape;
	t_object	*current_shape_struct;
	float		hit_dist_record;
	float		cur_hit_dist;
	t_vec3i		color;

	(void)x;
	(void)y;
	current_shape = 0;
	color = get_default_color(pd);
	hit_dist_record = 100000; // Set to infinity
	while (current_shape < pd->scene.amount_shapes)
	{
		current_shape_struct = &pd->scene.shapes[current_shape];
		if (current_shape_struct->base.obj_type == sphere)
		{
			cur_hit_dist = intersects_sphere(ray, &current_shape_struct->sphere);
			if (cur_hit_dist != -1 && cur_hit_dist < hit_dist_record)
			{
				hit_dist_record = cur_hit_dist;
				color = current_shape_struct->base.color;
			}
		}
		current_shape++;
	}
	return (color);
}

void	render_pixel_color(uint32_t x, uint32_t y, t_vec3i color, t_program_data *pd)
{
	mlx_put_pixel(pd->img, x, y, col_to_hex(color));
}

void	render(t_program_data *pd)
{
	uint32_t	xpixel;
	uint32_t	ypixel;
	t_ray		ray;
	t_vec3i		color;

	ray.origin = vec3f(0, 0, 0);
	ypixel = 0;
	while (ypixel < WIN_HEIGHT)
	{
		xpixel = 0;
		while (xpixel < WIN_WIDTH)
		{
			ray.direction = vec3f(mapx(xpixel), mapy(ypixel), 1);
			vec3f_normalize(&ray.direction);
			color = get_ray_color(&ray, xpixel, ypixel, pd);
			render_pixel_color(xpixel, ypixel, color, pd);
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
	(void)argv;

	print_scene_elements(&pd.scene);
	init_mlx(&pd);
	render(&pd);
	start_mlx(&pd);
	return (0);
}
