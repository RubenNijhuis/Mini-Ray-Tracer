/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 19:24:23 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/27 13:26:46 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "libvec.h"
# include <stdint.h>

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
	double r;
	double g;
	double b;
}	t_color;

// Token definitions
typedef enum e_object_type
{
	ambient_light,
	camera,
	light,
	sphere,
	plane,
	cylinder,
}	t_object_type;

// Base object
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

// Util
void	print_shapes(t_object *shapes, uint32_t amount_shapes);
void	print_lights(t_light *lights, uint32_t amount_lights);
void	print_camera(t_camera camvec3iera);
void	print_scene_elements(t_scene *scene);
void	print_object_color(t_color color);

#endif
