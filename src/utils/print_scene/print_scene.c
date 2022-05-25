/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 23:14:12 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/25 15:42:24 by jobvan-d      ########   odam.nl         */
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
	printf("Value type  •   X      Y      Z\n");
	printf("Position    • %6.2f %6.2f %6.2f\n", pos[0], pos[1], pos[2]);
	printf("Orientation • %6.2f %6.2f %6.2f\n", orient[0], orient[1], orient[2]);
	printf("Fov         • %6.2u\n", camera.fov);
	printf("\n");
}

void	print_ambient_light(t_ambient_light ambient_light)
{
	printf("========= AMBIENT LIGHT ==========\n\n");
	print_object_color(ambient_light.color);
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
		printf("ID          •  %2u\n", current_light);
		printf("Value type  •   X      Y      Z\n");
		printf("Position    • %6.2f %6.2f %6.2f\n", light->position[0], \
			light->position[1], light->position[2]);
		print_object_color(light->color);
		printf("Brightness  • %6.2f\n", light->brightness);
		printf("\n");
		current_light++;
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
