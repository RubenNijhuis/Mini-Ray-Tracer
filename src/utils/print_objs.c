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

void	print_shapes(t_object *shapes, uint32_t amount_shapes)
{
	uint32_t	current_shape;
	t_base		shape_base;
	current_shape = 0;
	printf("=========== SHAPES ===========\n");
	while (current_shape < amount_shapes)
	{
		shape_base = shapes[current_shape].base;
		printf("Shape type  • %s\n", get_shape_type_string(shape_base.obj_type));
		printf("Position    • %.2f %.2f %.2f\n", shape_base.position.x, shape_base.position.y, shape_base.position.z);
		printf("Orientation • %.2f %.2f %.2f\n", shape_base.orientation.x, shape_base.orientation.y, shape_base.orientation.z);
		printf("Color       • %d %d %d\n", shape_base.color.r, shape_base.color.g, shape_base.color.b);

		if (current_shape < amount_shapes - 1)
			printf("\n");
		current_shape++;
	}
	printf("=========== SHAPES ===========\n");
}
