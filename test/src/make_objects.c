/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 22:42:56 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/07/05 20:31:39 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Lib to be tested
#include "minirt.h"
#include "objects.h"
#include "libft.h"
#include "parsing.h"

// Testing lib
#include <criterion/criterion.h>

bool	color_eq(t_color col1, t_color col2)
{
	bool rEq = col1.r == (double)col2.r / 255;
	bool gEq = col1.g == (double)col2.g / 255;
	bool bEq = col1.b == (double)col2.b / 255;

	return (rEq && gEq && bEq);
}

/*
 Tests
*/
void	make_sphere_from_str_test(char *settings, float radius, t_vec3f pos, t_color col)
{
	t_shape	sphere_obj;
	make_sphere(&sphere_obj, settings);

	bool colorEq = color_eq(sphere_obj.base.color, col);
	bool posEq = vec3f_eq(pos, sphere_obj.base.position);
	cr_expect(sphere_obj.base.obj_type == sphere, "Expected object type to be sphere");
	cr_expect(sphere_obj.sphere.radius == (float)radius / 2, "Expected sphere diameter to be %f but got %f", radius, sphere_obj.sphere.radius);
	cr_expect(posEq == true, "Expected position to match");
	cr_expect(colorEq == true, "Expected sphere color to match");
}

void	make_cylinder_from_str_test(char *settings, t_vec3f pos, t_vec3f rotation, float radius, float height, t_color color)
{
	t_shape	obj;

	make_cylinder(&obj, settings);

	cr_expect(obj.base.obj_type == cylinder, "Expected object type to be cylinder");
	cr_expect(obj.cylinder.radius == radius / 2, "Expected cylinder radius to be %f but got %f", radius, obj.cylinder.radius);
	cr_expect(obj.cylinder.height == height, "Expected cylinder height to be %f but got %f", height, obj.cylinder.height);
	cr_expect(obj.base.position[2] == pos[2], "Expected position z to be %f but got %f", pos[2], obj.base.position[2]);
	cr_expect(obj.base.rotation[2] == rotation[2], "Expected rotation z to be %f but got %f", rotation[2], obj.base.rotation[2]);
	cr_expect(color_eq(obj.base.color, color), "Expected colors to match");
}

void	make_cam_from_str_test(char *settings, t_vec3f pos, t_vec3f rotation, float fov)
{
	t_camera	cam;
	set_camera(&cam, settings);
	
	cr_expect(cam.position[0] == pos[0], "Expected camera position x to be %f but got %f", pos[0], cam.position[0]);
	cr_expect(cam.rotation[1] == 1, "Expected camera rotation y to be %f but got %f", rotation[1], cam.rotation[1]);
	cr_expect(cam.fov == deg_to_rad(70), "Expected camera FOV to be %f, was %f %f", fov, deg_to_rad(cam.fov), cam.fov);
}

void	make_light_from_str_test(char *settings, t_vec3f pos, float brightness, t_color color)
{
	t_light		light;
	make_light(&light, settings);
	
	cr_expect(light.position[0] == pos[0], "Expected light position x to be 40");
	cr_expect(light.brightness == brightness, "Expected brightness to be 0.7");
	cr_expect(color_eq(light.color, color) == true, "Expected light color r to be %f but got %f", (float)color.r / 255, light.color.r);
}

/*
 Suites
*/
Test(make_sphere_from_string, passing) {
	make_sphere_from_str_test("sp  0,0,20   20   255,0,0", 20,  vec3f(0,0,20),  make_color(255,0,0));
	make_sphere_from_str_test("sp  0,50,20  200  255,0,10", 200, vec3f(0,50,20), make_color(255,0,10));
	make_sphere_from_str_test("sp  0,0,0  0  0,0,0", 0, vec3f(0,0,0), make_color(0,0,0));
}

Test(make_cylinder_from_string, passing) {
	make_cylinder_from_str_test("cy  50.0,0.0,20.6  0,0,1.0  14.2  21.42  10,0,255", vec3f(50,0,20.6), vec3f(0,0,1), 14.2, 21.42, make_color(10,0,255));
}

Test(make_light_from_string, passing) {
	make_light_from_str_test("L  -40,0,30  0.7  255,255,255", vec3f(-40,0,30), 0.7, make_color(255,255,255));
	make_light_from_str_test("L  0,0,0  0  0,0,0", vec3f(0,0,0), 0, make_color(0,0,0));
	make_light_from_str_test("L  10,10,30  1  155,0,155", vec3f(10,10,30), 1, make_color(155,0,155));
}

// FT_STRNCMP ISSUES???
// Test(make_camera_from_string, passing) {
// 	make_cam_from_str_test("C   -50,0,20         0,1,0      70", vec3f(-50,0,20), vec3f(0,1,0), 70);
// 	make_cam_from_str_test("C   -10,5,0         1,1,1      20", vec3f(-10,5,0), vec3f(1,1,1), 20);
// }
