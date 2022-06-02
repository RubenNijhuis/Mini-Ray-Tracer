/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 22:42:56 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/06/02 14:21:12 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Lib to be tested
#include "minirt.h"
#include "objects.h"
#include "libft.h"

// Testing lib
#include <criterion/criterion.h>

Test(make_sphere_from_string, passing) {
	t_object	sphere_obj;
	char		*sphere_string = "sp  0,0,20  20  255,0,0";
	make_sphere(&sphere_obj, sphere_string);

	cr_expect(sphere_obj.base.obj_type == sphere, "Expected object type to be sphere");
	cr_expect(sphere_obj.sphere.radius == 20 / 2, "Expected sphere diameter to be 10");
	cr_expect(sphere_obj.base.position[2] == 20.0f, "Expected position z to be 20");
	cr_expect(sphere_obj.base.color.r == 1.0f, "Expected sphere color r to be 1.0");
}

Test(make_cylinder_from_string, passing) {
	t_object	cylinder_obj;
	char		*cylinder_string = "cy  50.0,0.0,20.6  0,0,1.0  14.2  21.42  10,0,255";
	make_cylinder(&cylinder_obj, cylinder_string);

	cr_expect(cylinder_obj.base.obj_type == cylinder, "Expected object type to be cylinder");
	cr_expect(cylinder_obj.cylinder.height == 21.42f, "Expected cylinder height to be 21.42");
	cr_expect(cylinder_obj.base.position[2] == 20.6f, "Expected position z to be 20.6");
	cr_expect(cylinder_obj.base.color.r == (10.0 / 255.0), "Expected cylinder color r to be ~0.03");
}

Test(make_light_from_string, passing) {
	t_light		light;
	char		*light_settings = "L  -40,0,30  0.7  255,255,255";
	make_light(&light, light_settings);
	
	cr_expect(light.position[0] == -40, "Expected light position x to be 40");
	cr_expect(light.brightness == 0.7f, "Expected brightness to be 0.7");
	cr_expect(light.color.r == 1.0f, "Expected light color r to be 255");
}

Test(make_camera_from_string, passing) {
	t_scene		scene;
	char		*cam_settings = "C   -50,0,20         0,1,0      70";
	char		**file_content = ft_split(cam_settings, '\n');
	set_camera(&scene, file_content);
	
	cr_expect(scene.camera.position[0] == -50, "Expected camera position x to be -50");
	cr_expect(scene.camera.orientation[1] == 1, "Expected camera orientation y to be 1");
	cr_expect(scene.camera.fov == deg_to_rad(70), "Expected camera FOV to be 70, was %f", deg_to_rad(scene.camera.fov));
	ft_free_2d_array(&file_content, ft_2d_arrlen(file_content));
}
