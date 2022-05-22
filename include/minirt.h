/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:43 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/22 10:57:14 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "objects.h"

# include <stdint.h>	// uint32_t
# include <stdbool.h>	// bool

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
#  define HEADLESS 1
# endif

// If rendering without window
# if HEADLESS
#  define WIN_WIDTH 10
# else
#  define WIN_WIDTH 1920
# endif

typedef struct s_mlx
{
	void	*instance;
	void	*win;
	int		width;
	int		height;
}t_mlx;

typedef struct s_program_data
{
	t_scene	scene;
	t_mlx	mlx;
}t_program_data;

// Setup mlx
void		start_mlx(t_mlx *mlx);
int			key_hook(int keycode);

// Vec from string
t_vec3i		get_vec3i_from_string(char *str);
t_vec3f		get_vec3f_from_string(char *str);

// Utils
void		exit_error(char *str);
double		ft_atof(const char *str);
char		**get_file_content(char *file_name);
bool		ft_is_object(const char *haystack, const char *needle);
void		is_file_correctly_formatted(char **file_content);
char		*get_shape_type_string(t_object_type obj_type);
uint32_t	get_amount_objects(char **file_content, char *type);

#endif