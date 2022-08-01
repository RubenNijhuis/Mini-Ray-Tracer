/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:43 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/08/01 18:57:12 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "bonus.h"
# include "objects.h"
# include "ray.h"
# include "MLX42/MLX42.h"

# include <stdint.h>
# include <stdbool.h>

// The program can only handle so much ;)
# define MAX_SHAPES 200
# if BONUS
#  define MAX_LIGHTS 100
# else
#  define MAX_LIGHTS 1
# endif

# define WIN_WIDTH (1440)

# define WIN_HEIGHT (1200)

/*
 Main struct that holds all the data in the program
*/
typedef struct s_program_data
{
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_program_data;

/*
 This is what intersection functions return.
 t being the distance from the start of the ray to the intersection point,
 normal is the surface normal of the intersection point.
*/
typedef struct s_intersect
{
	t_vec3f	normal;
	float	t;
}	t_intersect;

/*
 Shape intersect and normal function pointer defines
*/
typedef t_intersect	(*t_intersect_func)(t_ray *, t_shape *);

t_intersect_func	lookup_intersect_function(t_shape *shape);
t_intersect			no_intersect(void);
t_intersect			init_intersect(const float distance, const t_vec3f normal);

/*
 Setup mlx
*/
void				init_mlx(t_program_data *pd);
void				start_mlx(t_program_data *pd);
void				key_hook(mlx_key_data_t keydata, void *param);

/*
 Vec from string
*/
t_color				get_color_from_string(char *str);
t_vec3f				get_vec3f_from_string(char *str);

/*
 Render
*/
void				render(t_program_data *pd);
t_ray				get_camera_ray(float xpixel, float ypixel, \
						t_camera *cam);

/*
 Intersections
*/
t_intersect			intersects_sphere(t_ray *ray, t_shape *shape);
t_intersect			intersects_plane(t_ray *ray, t_shape *shape);
t_intersect			intersects_cylinder(t_ray *ray, t_shape *shape);
t_intersect			intersects_disc(t_ray *ray, t_shape *shape);

t_intersect			get_cap_intersect(t_ray *obj_ray, t_cylinder *cyl);
t_vec3f				cylinder_default_direction(void);

// Normals
t_vec3f				get_cylinder_normal(const t_ray *ray, const float dist,
						t_cylinder *cyl);
t_vec3f				get_plane_normal(t_ray *ray, t_plane *plane);

/*
 Colors
*/
t_color				make_color(double r, double g, double b);
t_color				get_default_color(t_scene *scene);
t_color				get_ray_color(t_ray *ray, t_scene *scene);
void				color_add(t_color *color, const t_color *rhs);
void				color_multiply(t_color *color, const t_color *rhs);
void				color_multiply_scalar(t_color *color, \
						const double scalar);
void				color_clamp(t_color *color);
uint32_t			col_to_hex(const t_color col);
void				render_pixel_color(uint32_t x, uint32_t y, \
						t_color color, t_program_data *pd);
void				ambient_mixin(t_color *col, t_scene *scene);
t_color				lights_mixin(t_scene *scene, t_vec3f p, \
						t_shape *shape, t_vec3f normal);

/* 
 Utils
*/
void				exit_error(const char *msg);
void				exit_perror(const char *msg);
void				malloc_error(void);
double				ft_atof(const char *str);
bool				ft_is_object(const char *haystack, const char *needle);
char				*get_shape_type_string(t_object_type obj_type);

t_color				get_pixel_color(uint32_t px, uint32_t py, \
						t_scene *scene);
void				render_pixel(t_program_data *pd, uint32_t px, \
						uint32_t py);
void				put_pixel(t_program_data *pd, uint32_t px, \
						uint32_t py, uint32_t col);

// Math
float				sq(const float n);
float				deg_to_rad(const float a);
float				rad_to_deg(const float a);

#endif