/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 19:24:23 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/30 20:49:59 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "libvec.h"
# include <stdlib.h>

// Special chars
# define CAMERA "C"
# define AMBIENT_LIGHT "A"
# define LIGHT "L"
# define PLANE "pl"
# define SPHERE "sp"
# define CYLINDER "cy"

# define SCENE_ELEMENTS "C A L"
# define SCENE_SHAPES "pl sp cy"

// Token definitions
typedef enum e_object_type {
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
	t_vec3i			color;
}t_base;

// Scene elements
typedef struct s_camera
{
	t_vec3f		position;
	t_vec3f		orientation;
	uint32_t	fov;
}t_camera;

typedef struct s_ambient_light
{
	t_vec3i	color;
	float	range;
}t_ambient_light;

typedef struct s_light
{
	t_vec3f	position;
	t_vec3i	color;
	float	brightness;
}t_light;

// Scene objects
typedef struct s_sphere
{
	t_base	base;
	int32_t	diameter;
}t_sphere;

typedef struct s_plane
{
	t_base	base;
}t_plane;

typedef struct s_cylinder
{
	t_base	base;
	int32_t	diameter;
	int32_t	height;
}t_cylinder;

typedef union u_object {
	t_base		base;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_object;

// Create objects
void	make_plane(t_object *obj, char *settings);
void	make_cylinder(t_object *obj, char *settings);
void	make_sphere(t_object *obj, char *settings);

// Utils
void	print_shapes(t_object *shapes, uint32_t amount_shapes);

#endif
