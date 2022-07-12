/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 19:24:23 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/07/12 15:49:56 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "bonus.h"
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
# define DISC "di"

# define SCENE_ELEMENTS "C A L"

# if BONUS
#  define SCENE_SHAPES "pl sp cy di"
# else
#  define SCENE_SHAPES "pl sp cy"
# endif

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

typedef enum e_object_type
{
	ambient_light,
	camera,
	light,
	sphere,
	plane,
	cylinder,
	disc,
	amount_objects
}	t_object_type;

typedef struct s_component_list
{
	uint32_t			amount_obj_components;
	t_element_component	components[10];
}	t_component_list;

// Base objec3t
typedef struct s_base
{
	t_object_type	obj_type;
	t_vec3f			position;
	t_vec3f			rotation;
	t_color			color;
}	t_base;

// Scene elements
typedef struct s_camera
{
	t_vec3f		position;
	t_vec3f		rotation;
	float		fov;
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
	float	radius;
	float	height;
}	t_cylinder;

// The sphere shares everything similar with a disc.
// therefore, just copy the type instead.
typedef t_sphere	t_disc;

typedef union u_shape
{
	t_base		base;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	t_disc		disc;
}	t_shape;

typedef struct s_scene
{
	t_camera		camera;

	t_ambient_light	amb_light;

	t_light			*lights;
	uint32_t		amount_lights;

	t_shape			*shapes;
	uint32_t		amount_shapes;
}	t_scene;

/* 
 Create objects
*/
void	make_plane(t_shape *obj, char *settings);
void	make_cylinder(t_shape *obj, char *settings);
void	make_sphere(t_shape *obj, char *settings);
void	make_disc(t_shape *obj, char *settings);
void	make_light(t_light *light, char *settings);

void	set_camera(t_camera *cam, char *settings);
void	set_ambient_light(t_ambient_light *amb, char *settings);

// Util
int		get_obj_type(const char *str);
bool	rt_objstrcmp(const char *s1, const char *s2);

void	print_shapes(t_shape *shapes, uint32_t amount_shapes);
void	print_lights(t_light *lights, uint32_t amount_lights);
void	print_camera(t_camera camvec3iera);
void	print_scene_elements(t_scene *scene);
void	print_object_color(t_color color);

#endif
