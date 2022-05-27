/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:43 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/27 13:32:43 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "objects.h"
# include "ray.h"
# include "MLX42/MLX42.h"

# include <stdint.h>
# include <stdbool.h>

// If rendering in bonus mode
# ifndef BONUS
#  define BONUS 1
# endif

// The program can only handle so much ;)
# define MAX_SHAPES 200
# define MAX_LIGHTS 100

// MLX Stuff
# define WIN_RATIO 0.5625

# ifndef HEADLESS
#  define HEADLESS 0
# endif

// If rendering without window
# if HEADLESS
#  define WIN_WIDTH 10
# else
#  define WIN_WIDTH 1080
# endif

# define WIN_HEIGHT (1080)

typedef struct s_program_data
{
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*img;
}t_program_data;

// typedef union u_color
// {
// 	struct s_color
// 	{
// 		double r;
// 		double g;
// 		double b;
// 	}	c;
// 	double arr[3];
// }	t_color;

// Setup mlx
void		init_mlx(t_program_data *pd);
void		start_mlx(t_program_data *pd);
void		key_hook(mlx_key_data_t keydata, void *param);

// Vec from string
t_color		get_color_from_string(char *str);
t_vec3f		get_vec3f_from_string(char *str);

// Render
void		render(t_program_data *pd);

// Intersections
float		intersects_sphere(t_ray *ray, t_object *shape);
float		intersects_plane(t_ray *ray, t_object *shape);

// Colors
t_color		get_default_color(t_program_data *pd);
t_color		get_ray_color(t_ray *ray, uint32_t x, \
				uint32_t y, t_program_data *pd);
void		render_pixel_color(uint32_t x, uint32_t y, \
				t_color color, t_program_data *pd);

// Utils
void		exit_error(char *str);
double		ft_atof(const char *str);
char		**get_file_content(char *file_name);
bool		ft_is_object(const char *haystack, const char *needle);
void		is_file_correctly_formatted(char **file_content);
char		*get_shape_type_string(t_object_type obj_type);
uint32_t	get_amount_objects(char **file_content, char *type);

uint32_t	col_to_hex(const t_color col);

// File parsing
void		check_amount_lights(char **file_content);
void		check_amount_cameras(char **file_content);
void		check_amount_ambient_lights(char **file_content);

#endif