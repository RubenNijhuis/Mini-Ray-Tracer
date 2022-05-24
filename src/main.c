/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
<<<<<<< Updated upstream
/*   Updated: 2022/05/24 14:21:11 by rnijhuis      ########   odam.nl         */
=======
/*   Updated: 2022/05/24 14:22:41 by jobvan-d      ########   odam.nl         */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <stdio.h> // debug printf

#include <stdbool.h>
#include <math.h>

#include <stdlib.h> // exit

#include "libvec.h"

void	init_mlx(t_program_data *pd)
{
	pd->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "miniRT", true);
	if (!pd->mlx)
	{
		// TODO: stderr
		printf("mlx init failed!\n");
		exit(1);
	}
	pd->img = mlx_new_image(pd->mlx, WIN_WIDTH, WIN_HEIGHT);
	ft_memset(pd->img->pixels, 128, pd->img->width * pd->img->height * sizeof(int));
}

void	start_mlx(t_program_data *pd)
{
	//mlx_loop_hook(pd->mlx, &key_hook, pd->mlx);
	mlx_image_to_window(pd->mlx, pd->img, 0, 0);
	mlx_loop(pd->mlx);
}

int	main(int argc, char **argv)
{
	t_program_data	pd;

	if (argc != 2)
	{
		// TODO: stderr
		printf("Usage: minirt [path-to-file]\n");
		return (1);
	}
	ft_memset(&pd, 0, sizeof(t_program_data));
	setup_scene(&pd.scene, argv[1]);
	init_mlx(&pd);

	// Sphere origin + radius
	t_vec3f so;
	so.x = 0;
	so.y = 0;
	so.z = 10;
	float r = 1;

	// Camera origin
	t_vec3f ro;
	ro.x = 0;
	ro.y = 0;
	ro.z = 0;

	// Direction vector
	t_vec3f v;
	v.x = 0;
	v.y = 0;
	v.z = 1;

	vec3f_normalize(&v);
	printf("%f %f %f normalized vec\n", v.x, v.y, v.z);

	// t
	// lengte van vector tot aan parallel van sphere origin
	t_vec3f temp = vec3f_subtract(so, ro);
	float t = vec3f_dot(temp, v);

	// p
	// length
	vec3f_multiply_scalar(&v, t);
	t_vec3f p = vec3f_sum(ro, v);

	// y
	float y = vec3f_length(vec3f_subtract(so, p));

	bool isinsphere = y <= r;
	printf("intersect ? %s\n", isinsphere ? "yes" : "no");

	if (isinsphere == true)
	{
		// find intersection point
		float x = sqrt((r * r) - (y * y));
		float ip1 = t - x;
		float ip2 = t + x;
		printf("%f intersection point front\n", ip1);
		printf("%f intersection point back\n", ip2);
	}

	start_mlx(&pd);
	// print_scene_elements(&pd->scene);
	return (0);
}
