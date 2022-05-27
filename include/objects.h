/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 19:24:23 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/28 01:46:22 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "libvec.h"
# include <stdint.h>
# include <stdbool.h>

// Special chars
# define CAMERA "C"
# define AMBIENT_LIGHT "A"
# define LIGHT "L"

# define PLANE "pl"
# define SPHERE "sp"
# define CYLINDER "cy"

# define SCENE_ELEMENTS "C A L"
# define SCENE_SHAPES "pl sp cy"

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

/* Object element types */
/**
 * Defining the "shape" of an object we
 * can check if the input settings contain
 * all those settings. The program will run 
 * a checker function per component to determin
 * whether it was formatted correctly in the file
 */
typedef enum e_element_component
{
	position,
	rotation,
	color,
	radius,
	height,
	fov,
	range,
	brightness,
	bmp_map,
	material,
	amount_components
}	t_element_component;

// Token definitions
typedef enum e_object_type
{
	ambient_light,
	camera,
	light,
	sphere,
	plane,
	cylinder,
	amount_objects
}	t_object_type;

typedef struct s_component_list
{
	t_object_type		obj_type;
	uint32_t			amount_obj_components;
	t_element_component	components[10];
}	t_component_list;

typedef bool	(*t_comp_checker_func)(char *str);

typedef struct s_component_checker
{
	t_element_component	type;
	t_comp_checker_func	func;
}	t_component_checker;
// Base objec3t
typedef struct s_base
{
	t_object_type	obj_type;
	t_vec3f			position;
	t_vec3f			orientation;
	t_color			color;
}	t_base;

// Scene elements
typedef struct s_camera
{
	t_vec3f		position;
	t_vec3f		orientation;
	uint32_t	fov;
}	t_camera;

typedef struct s_ambient_light
{
	t_color	color;
	float	range;
}	t_ambient_light;

typedef struct s_light
{
	t_vec3f	position;
	t_color	color;
	float	brightness;
}	t_light;

// Scene objects
typedef struct s_sphere
{
	t_base	base;
	float	radius;
}	t_sphere;

typedef struct s_plane
{
	t_base	base;
}	t_plane;

typedef struct s_cylinder
{
	t_base	base;
	float	diameter;
	float	height;
}	t_cylinder;

typedef union u_object
{
	t_base		base;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_object;

typedef struct t_scene
{
	t_camera		camera;

	t_ambient_light	amb_light;

	t_light			*lights;
	uint32_t		amount_lights;

	t_object		*shapes;
	uint32_t		amount_shapes;
}	t_scene;

// Setup components
void	set_camera(t_scene *scene, char **file_content);
void	set_lights(t_scene *scene, char **file_content);
void	set_shapes(t_scene *scene, char **file_content);
void	set_ambient_light(t_scene *scene, char **file_content);
void	setup_scene(t_scene *scene, char *file_name);

// Create objects
void	make_plane(t_object *obj, char *settings);
void	make_cylinder(t_object *obj, char *settings);
void	make_sphere(t_object *obj, char *settings);

// Create scene objects
void	make_light(t_light *light, char *settings);

bool	check_position(char *str);
bool	check_rotation(char *str);
bool	check_color(char *str);

void	run_object_checks(t_object_type obj_type, char *obj_settings,
			const t_component_list *object_components, \
			const t_component_checker *component_checkers);

// Util
void	print_shapes(t_object *shapes, uint32_t amount_shapes);
void	print_lights(t_light *lights, uint32_t amount_lights);
void	print_camera(t_camera camvec3iera);
void	print_scene_elements(t_scene *scene);
void	print_object_color(t_color color);

#endif
