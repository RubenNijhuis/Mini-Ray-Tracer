/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:14:12 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/30 23:39:12 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include <stdio.h>

char	*get_shape_type_string(t_object_type obj_type)
{
	char	*obj_type_string;

	obj_type_string = NULL;
	if (obj_type == sphere)
		obj_type_string = "Sphere";
	else if (obj_type == plane)
		obj_type_string = "Plane";
	else if (obj_type == cylinder)
		obj_type_string = "Cylinder";
	return (obj_type_string);
}

void	print_camera(t_camera camera)
{
	printf("=========== CAMERA ===========\n\n");
	printf("Position    • %6.2f %6.2f %6.2f\n", camera.position.x, camera.position.y, camera.position.z);
	printf("Orientation • %6.2f %6.2f %6.2f\n", camera.orientation.x, camera.orientation.y, camera.orientation.z);
	printf("Fov         • %6.2u\n", camera.fov);
	printf("\n");
}

void	print_lights(t_light *lights, uint32_t amount_lights)
{
	uint32_t	current_light;
	t_light		*light;

	current_light = 0;
	printf("=========== LIGHTS ===========\n\n");
	while (current_light < amount_lights)
	{
		light = &lights[current_light];
		printf("---- Light • %u ----\n", current_light);
		printf("Position    • %6.2f %6.2f %6.2f\n", light->position.x, light->position.y, light->position.z);
		printf("Color       • %6.2i %6.2i %6.2i\n", light->color.r, light->color.g, light->color.b);
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
	printf("=========== SHAPES ===========\n\n");
	while (current_shape < amount_shapes)
	{
		shape_base = shapes[current_shape].base;
		printf("%s\n", get_shape_type_string(shape_base.obj_type));
		printf("--------\n");
		printf("Position    • %6.2f %6.2f %6.2f\n", shape_base.position.x, shape_base.position.y, shape_base.position.z);
		printf("Orientation • %6.2f %6.2f %6.2f\n", shape_base.orientation.x, shape_base.orientation.y, shape_base.orientation.z);
		printf("Color       • %6.2d %6.2d %6.2d\n", shape_base.color.r, shape_base.color.g, shape_base.color.b);
		printf("\n");
		current_shape++;
	}
}

void	print_scene_elements(t_program_data *pd)
{
	print_camera(pd->camera);
	print_lights(pd->lights, pd->amount_lights);
	print_shapes(pd->shapes, pd->amount_shapes);
}
