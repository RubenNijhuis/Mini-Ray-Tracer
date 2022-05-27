int	intersects(t_vec3f point, t_vec3f sc, float radius)
{
	//vec3f_substract(point, sc);
	vec3f_translate(point, vec3f_negate(sc));
	float dot = vec3f_dot(point, point);
	
}

