/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:43 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/23 10:30:39 by rubennijhui   ########   odam.nl         */
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

# ifndef HEADLESS
#  define HEADLESS 0
# endif

// If rendering without window
# if HEADLESS
#  define WIN_WIDTH 10
# else
#  define WIN_WIDTH 1240
# endif

# define WIN_HEIGHT (WIN_WIDTH)

typedef struct s_program_data
{
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_program_data;

typedef float	(*t_intersect_func)(t_ray *, t_object *);
typedef t_vec3f	(*t_normal_func_ptr)(const t_ray *, const float, t_object *);

t_intersect_func	lookup_intersect_function(t_object *shape);

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
t_ray				get_camera_ray(uint32_t xpixel, uint32_t ypixel, \
						t_camera *cam);

/*
 Intersections
*/
float				intersects_sphere(t_ray *ray, t_object *shape);
float				intersects_plane(t_ray *ray, t_object *shape);

t_vec3f				get_sphere_normal(const t_ray *ray, const float dist,
						t_object *shape);
t_vec3f				get_plane_normal(const t_ray *ray, const float dist,
						t_object *shape);

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
						t_object *shape, t_vec3f normal);

/* 
 Utils
*/
void				exit_error(const char *msg);
void				exit_perror(const char *msg);
void				malloc_error(void);
double				ft_atof(const char *str);
int					is_valid_double_format(char *str);
bool				ft_is_object(const char *haystack, const char *needle);
char				*get_shape_type_string(t_object_type obj_type);

float				deg_to_rad(const float a);
float				rad_to_deg(const float a);

t_color				get_pixel_color(uint32_t px, uint32_t py, \
						t_scene *scene);
void				render_pixel(t_program_data *pd, uint32_t px, \
						uint32_t py);
void				put_pixel(t_program_data *pd, uint32_t px, \
						uint32_t py, uint32_t col);
#endif