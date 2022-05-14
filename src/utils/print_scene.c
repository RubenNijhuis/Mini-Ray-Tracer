/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:14:12 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/14 19:27:59 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "colors.h"

#include <stdio.h>	// printf

void	print_camera(t_camera camera)
{
	printf(RED "============= CAMERA =============\n\n" RESET);
	printf("Position    • %6.2f %6.2f %6.2f\n", camera.position.x, \
		camera.position.y, camera.position.z);
	printf("Orientation • %6.2f %6.2f %6.2f\n", camera.orientation.x, \
		camera.orientation.y, camera.orientation.z);
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
	t_vec3f	position;
	t_vec3f	orientation;

	color = base.color;
	position = base.position;
	orientation = base.orientation;
	printf("Position    • %6.2f %6.2f %6.2f\n", position.x, position.y, position.z);
	printf("Orientation • %6.2f %6.2f %6.2f\n", orientation.x, orientation.y, orientation.z);
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
		printf(BLU "%s\n" RESET, get_shape_type_string(shape_base.obj_type));
		printf("--------\n");
		print_shape_base(shape_base);
		print_shape_dimensions(shape_base.obj_type, shapes[current_shape]);
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
