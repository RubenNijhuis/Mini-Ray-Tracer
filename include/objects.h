/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 19:24:23 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/04/24 19:25:25 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

// Special chars
# define CAMERA "A"
# define AMBIENT_LIGHT "A"
# define LIGHT "L"
# define PLANE "pl"
# define SPHERE "sp"
# define CYLINDER "cy"

// Token definitions
typedef enum e_object_type {
	ambient_light,
	camera,
	light,
	sphere,
	plane,
	cylinder,
}	t_object_type;

typedef struct s_vector
{
	long		values[3];
}t_vector;

typedef struct s_object
{
	t_object_type	type;
	t_vector		*position;
	t_vector		*orientation;
	t_vector		*colors;
	t_vector		*scale;
}t_object;

typedef struct s_camera
{
	t_vector	*position;
	t_vector	*orientation;
	int			fov;
}t_camera;

#endif