/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/25 17:54:37 by jobvan-d      ########   odam.nl         */
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

float	intersects_sphere(t_ray *ray, t_object *shape)
{
	t_sphere *sphere = &shape->sphere;
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

float	intersects_plane(t_ray *ray, t_object *shape)
{
	(void)ray;
	t_plane *plane = &shape->plane;
	(void)plane;

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

/**
 * Checks if the distance from origin to the current object is smaller
 * than the current record. If so -> update the record and update the color
*/
void	update_color_from_dist(float *hit_dist_record, float cur_hit_dist, \
	t_vec3i *color, t_vec3i new_color)
{
	if (cur_hit_dist != -1 && cur_hit_dist < *hit_dist_record)
	{
		*hit_dist_record = cur_hit_dist;
		*color = new_color;
	}
}

typedef float (*t_intersect_func_ptr)(t_ray *, t_object *);

typedef struct s_intersect_func
{
	t_object_type type;
	t_intersect_func_ptr	func;
}	t_intersect_func;

static t_intersect_func_ptr	lookup_intersect_function(t_object *shape)
{
	size_t					i;
	const t_intersect_func	funcs[] = {
	{sphere, &intersects_sphere},
	{plane, &intersects_plane},
	};

	i = 0;
	while (i < sizeof(funcs) / sizeof(t_intersect_func))
	{
		if (funcs[i].type == shape->base.obj_type)
			return (funcs[i].func);
		i++;
	}
	return (NULL);
}

/*
 * Loops through the shapes array and checks if the ray intersects
 * If it intersects it returns the current hit distance and applies color if needed
 * NOTE: Uses a function roulette to acces the correct intersection func
*/
t_vec3i	get_ray_color(t_ray *ray, uint32_t x, uint32_t y, t_program_data *pd)
{
	uint32_t	current_shape;
	t_object	*cur_shape_struct;
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
		cur_shape_struct = &pd->scene.shapes[current_shape];
		cur_hit_dist = (*lookup_intersect_function(cur_shape_struct))(ray, cur_shape_struct);
		update_color_from_dist(&hit_dist_record, cur_hit_dist, &color, cur_shape_struct->base.color);
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
