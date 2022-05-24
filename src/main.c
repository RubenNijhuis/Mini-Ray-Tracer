/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 16:38:00 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/05/23 22:21:03 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <stdio.h> // debug printf

#include <stdbool.h>
#include <math.h>

#include "libvec.h"

float	vec3f_dot_prod(const t_vec3f a, const t_vec3f b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

int	main(int argc, char **argv)
{
	t_program_data	*pd;

	if (argc != 2)
	{
		printf("Usage: minirt [path-to-file]\n");
		return (1);
	}
	pd = ft_calloc(1, sizeof(t_program_data));
	if (!pd)
		exit_error("couldn't allocate program data struct");
	setup_scene(&pd->scene, argv[1]);

	// Sphere origin + radius
	t_vec3f so;
	so.x = 0;
	so.y = 0;
	so.z = 100;
	float r = 1;

	// Camera origin
	t_vec3f ro;
	ro.x = 0;
	ro.y = 0;
	ro.z = 0;

	// Direction vector
	t_vec3f v;
	v.x = 0;
	v.y = 0.01;
	v.z = 1;

	vec3f_normalize(&v);
	printf("%f %f %f normalized vec\n", v.x, v.y, v.z);

	// t
	t_vec3f temp = vec3f_subtract(so, ro);
	float t = vec3f_dot_prod(temp, v);

	// p
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

	// print_scene_elements(&pd->scene);
	start_mlx(&pd->mlx);
	return (0);
}
