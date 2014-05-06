#include "Floor.h"


Floor::Floor(void) : Box()
{
	world = Matrix(1.0f);
	scaleFactor = 0.01;
}


Floor::~Floor(void)
{
}

void Floor::init(Box* b)
{
	base = b;
	base->setWorld(Matrix(1.0f));
	scaleFactor = 0.01;
}

void Floor::draw(Vec4 color)
{
	base->setWorld(world*transform(scaleX/2.0f, 0, scaleZ/2.0f, 0, scaleX/4.0f, scaleFactor, scaleZ/4.0f));
	
	base->draw(GREEN);
	//base->setWorld(world * transform(scaleX/2.0f, 0, -scaleZ/4.0f, 0, scaleX/4.0f, 1, 0.01));
	//base->draw(GREEN);
	//base->setWorld(world * transform(scaleX/2.0f, 0, scaleZ/2.0f + scaleX/1.5f, 0, scaleX/4.0f, 1, 0.01));
	//base->draw(GREEN);
	//base->setWorld(world * transform(scaleX/2.0f- scaleZ/1.5f, 0, scaleZ/2.0f , 0, 0.01, 1, scaleZ/4.0f));
	//base->draw(GREEN);
	//base->setWorld(world * transform(scaleX/2.0f+ scaleZ/1.5f, 0, scaleZ/2.0f , 0, 0.01, 1, scaleZ/4.0f));
	//base->draw(GREEN);

	world = Matrix(1.0f);
}

Matrix Floor::transform(float tX, float tY, float tZ, float theta, float sX, float sY, float sZ)
{
	Matrix tr = Matrix(1.0f);
	glm::mat4 transMat = glm::translate(Matrix(1.0f), Vec3(tX, tY, tZ));
	glm::mat4 rotMat = glm::rotate(Matrix(1.0f), theta, Vec3(0,1,0));
	glm::mat4 scaleMat = glm::scale(Matrix(1.0f), Vec3(sX * scaleX, sY, sZ * scaleZ));
	tr = transMat * rotMat * scaleMat;
	//tr = scaleMat * rotMat * transMat;

	//modelMatrix = scaleMat;
	return tr;
}

float Floor::intersectionTest(const vec3& p, const vec3& v, const mat4& m, vec3& normal)
{
	float result = -1;
	vec3 lNormal(0,0,0);
	float r = base->intersectionTest(p, v, m*world*transform(scaleX/2.0f, 0, scaleZ/2.0f, 0, scaleX/8.0f, scaleFactor, scaleZ/8.0f), lNormal);
	if(r >= 0) result = r;

	return result;
}