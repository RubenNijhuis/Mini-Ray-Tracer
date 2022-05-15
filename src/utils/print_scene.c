/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:14:12 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/15 11:07:07 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "libft.h"	// ft_strlen

#include "colors.h"
#include <stdio.h>	// printf

void	print_camera(t_camera camera)
{
	t_vec3f	pos;
	t_vec3f	orient;

	pos = camera.position;
	orient = camera.orientation;
	printf(RED "============= CAMERA =============\n\n" RESET);
	printf("Position    • %6.2f %6.2f %6.2f\n", pos.x, pos.y, pos.z);
	printf("Orientation • %6.2f %6.2f %6.2f\n", orient.x, orient.y, orient.z);
	printf("Fov         • %6.2u\n", camera.fov);
	printf("\n");
}

void	print_ambient_light(t_ambient_light ambient_light)
{
	printf("========= AMBIENT LIGHT ==========\n\n");
	printf("Color       • %6.2d %6.2d %6.2d\n", ambient_light.color.r, \
		ambient_light.color.g, ambient_light.color.b);
	printf("Range       • %6.2f\n", ambient_light.range);
	printf("\n");
}

void	print_lights(t_light *lights, uint32_t amount_lights)
{
	uint32_t	current_light;
	t_light		*light;

	current_light = 0;
	if (amount_lights == 1)
		printf(YEL "============= LIGHT ==============\n\n" RESET);
	else
		printf(YEL "============= LIGHTS =============\n\n" RESET);
	while (current_light < amount_lights)
	{
		light = &lights[current_light];
		printf("ID          • %2u\n", current_light);
		printf("Position    • %6.2f %6.2f %6.2f\n", light->position.x, \
			light->position.y, light->position.z);
		printf("Color       • %6.2i %6.2i %6.2i\n", light->color.r, \
			light->color.g, light->color.b);
		printf("Brightness  • %6.2f\n", light->brightness);
		printf("\n");
		current_light++;
	}
}

void	print_shape_base(t_base base)
{
	t_vec3i	color;
	t_vec3f	pos;
	t_vec3f	orient;

	color = base.color;
	pos = base.position;
	orient = base.orientation;
	printf("Position    • %6.2f %6.2f %6.2f\n", pos.x, pos.y, pos.z);
	printf("Orientation • %6.2f %6.2f %6.2f\n", orient.x, orient.y, orient.z);
	printf("Color       • %6.2d %6.2d %6.2d\n", color.r, color.g, color.b);
}

void	print_shape_dimensions(t_object_type type, t_object shape)
{
	if (type == sphere)
		printf("Diameter    • %6.2f\n", shape.sphere.diameter);
	else if (type == cylinder)
	{
		printf("Diameter    • %6.2f\n", shape.cylinder.diameter);
		printf("Height      • %6.2f\n", shape.cylinder.height);
	}
}

void	print_shape_type(t_object_type type, t_object shape)
{
	uint32_t	amount_underline;
	uint32_t	current_line;

	current_line = 0;
	amount_underline = 0;
	if (type == sphere)
		amount_underline = ft_strlen("sphere");
	else if (type == plane)
		amount_underline = ft_strlen("plane");
	else if (type == cylinder)
		amount_underline = ft_strlen("cylinder");
	printf(BLU "%s\n" RESET, get_shape_type_string(shape.base.obj_type));
	while (current_line < amount_underline)
	{
		printf("-");
		current_line++;
	}
	printf("\n");
}

void	print_shapes(t_object *shapes, uint32_t amount_shapes)
{
	uint32_t	current_shape;
	t_base		shape_base;

	current_shape = 0;
	if (amount_shapes == 1)
		printf(CYN "============= SHAPE ==============\n\n" RESET);
	else
		printf(CYN "============= SHAPES =============\n\n" RESET);
	while (current_shape < amount_shapes)
	{
		shape_base = shapes[current_shape].base;
		print_shape_type(shape_base.obj_type, shapes[current_shape]);
		print_shape_base(shape_base);
		print_shape_dimensions(shape_base.obj_type, shapes[current_shape]);
		if (current_shape != amount_shapes - 1)
			printf("\n");
		current_shape++;
	}
}

void	print_scene_elements(t_scene *scene)
{
	print_camera(scene->camera);
	print_ambient_light(scene->amb_light);
	if (scene->amount_lights > 0)
		print_lights(scene->lights, scene->amount_lights);
	if (scene->amount_shapes > 0)
		print_shapes(scene->shapes, scene->amount_shapes);
}
