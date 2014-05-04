#include "Geometry.h"

float triangleArea(const vec3& p0, const vec3& p1, const vec3& p2)
{
	mat3 m1(p0.y, p1.y, p2.y,
			p0.z, p1.z, p2.z,
			1,    1,    1);
	mat3 m2(p0.z, p1.z, p2.z,
			p0.x, p1.x, p2.x,
			1,    1,    1);
	mat3 m3(p0.x, p1.x, p2.x,
			p0.y, p1.y, p2.y,
			1,    1,    1);
	return sqrt(pow(determinant(m1), 2) + pow(determinant(m2),2) + pow(determinant(m3), 2))/2.0f;
}
