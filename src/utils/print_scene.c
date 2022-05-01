/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:14:12 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/01 11:48:07 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"

#include <stdio.h>	// printf

void	print_camera(t_camera camera)
{
	printf("============= CAMERA =============\n\n");
	printf("Position    • %6.2f %6.2f %6.2f\n", camera.position.x, \
		camera.position.y, camera.position.z);
	printf("Orientation • %6.2f %6.2f %6.2f\n", camera.orientation.x, \
		camera.orientation.y, camera.orientation.z);
	printf("Fov         • %6.2u\n", camera.fov);
	printf("\n");
}

void	print_ambient_light(t_ambient_light ambient_light)
{
	printf("========== AMBIENT LIGHT ==========\n\n");
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
		printf("============= LIGHT ==============\n\n");
	else
		printf("============= LIGHTS =============\n\n");
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

void	print_shapes(t_object *shapes, uint32_t amount_shapes)
{
	uint32_t	current_shape;
	t_base		shape_base;

	current_shape = 0;
	if (amount_shapes == 1)
		printf("============= SHAPE ==============\n\n");
	else
		printf("============= SHAPES =============\n\n");
	while (current_shape < amount_shapes)
	{
		shape_base = shapes[current_shape].base;
		printf("%s\n", get_shape_type_string(shape_base.obj_type));
		printf("--------\n");
		printf("Position    • %6.2f %6.2f %6.2f\n", shape_base.position.x, \
			shape_base.position.y, shape_base.position.z);
		printf("Orientation • %6.2f %6.2f %6.2f\n", \
			shape_base.orientation.x, shape_base.orientation.y, \
			shape_base.orientation.z);
		printf("Color       • %6.2d %6.2d %6.2d\n", shape_base.color.r, \
			shape_base.color.g, shape_base.color.b);
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
