/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_shapes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 11:35:59 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/27 13:48:17 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "libft.h"	// ft_strlen

#include "colors.h"
#include <stdio.h>	// printf

void	print_object_color(t_color color)
{
	printf("Color       • ");
	printf(RED "%6.2f" RESET, color.r);
	printf(GRN "%8.2f" RESET, color.g);
	printf(CYN "%8.2f" RESET "\n", color.b);
}

static void	print_shape_base(t_base base)
{
	t_color	color;
	t_vec3f	pos;
	t_vec3f	orient;

	color = base.color;
	pos = base.position;
	orient = base.orientation;
	printf("Value type  •    X       Y       Z\n");
	printf("Position    • %6.2f  %6.2f  %6.2f\n", pos[0], pos[1], pos[2]);
	printf("Orientation • %6.2f  %6.2f  %6.2f\n", \
		orient[0], orient[1], orient[2]);
	print_object_color(color);
}

static void	print_shape_dimensions(t_object_type type, t_object shape)
{
	if (type == sphere)
		printf("Diameter    • %6.2f\n", shape.sphere.radius * 2);
	else if (type == cylinder)
	{
		printf("Diameter    • %6.2f\n", shape.cylinder.radius * 2);
		printf("Height      • %6.2f\n", shape.cylinder.height);
	}
}

static void	print_shape_type(t_object_type type, t_object shape)
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
