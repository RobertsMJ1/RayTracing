#include "Chair.h"

Chair::Chair()
{
	world = Matrix(1.0f);
}

Chair::~Chair()
{
	scaleFactor = 0;
}

void Chair::init(Box* b)
{
	base = b;
	base->setWorld(Matrix(1.0f));
	
	scaleFactor = 0.25;
}

void Chair::draw(Vec4 c)
{
	Vec4 color = c;
	if(color == WHITE) {
		color = BLUE;
	}
	//world = Matrix(0.5, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 1);
	world = world * glm::scale(Matrix(1.0f), Vec3(scaleFactor, scaleFactor, scaleFactor));
	base->setWorld(world*transform(0, 2, 0, 0, 2.5, 0.1, 2.5));
	base->draw(color);
	base->setWorld(world*transform(-1, 0, -1, 0, 0.5, 2, 0.5));
	base->draw(color);
	base->setWorld(world*transform(-1, 0, 1, 0, 0.5, 2, 0.5));//
	base->draw(color);
	base->setWorld(world*transform(1, 0, -1, 0, 0.5, 2, 0.5));//
	base->draw(color);
	base->setWorld(world*transform(1, 0, 1, 0, 0.5, 2, 0.5));//
	base->draw(color);
	base->setWorld(world*transform(0, 2, -1.2, 0, 2.5, 2.5, 0.1));
	base->draw(color);
	base->setWorld(Matrix(1.0f));
	//world = Matrix(1.0f);
}

Matrix Chair::transform(float tX, float tY, float tZ, float theta, float sX, float sY, float sZ)
{
	Matrix tr = Matrix(1.0f);
	glm::mat4 transMat = glm::translate(Matrix(1.0f), Vec3(tX, tY, tZ));
	glm::mat4 rotMat = glm::rotate(Matrix(1.0f), theta, Vec3(0,1,0));
	glm::mat4 scaleMat = glm::scale(Matrix(1.0f), Vec3(sX, sY, sZ));
	tr = transMat * rotMat * scaleMat;
	//tr = scaleMat * rotMat * transMat;

	//modelMatrix = scaleMat;
	return tr;
}

float Chair::intersectionTest(const vec3& p, const vec3& v, const mat4& m)
{
	float result = -1;
	float r = base->intersectionTest(p, v, m*world*transform(0, 2, 0, 0, 2.5, 0.1, 2.5));
	if(r >= 0) result = r;

	r = base->intersectionTest(p, v, m*world*transform(-1, 0, -1, 0, 0.5, 2, 0.5));
	if(result == -1 || (r <= result && r > 0)) result = r;

	r = base->intersectionTest(p, v, m*world*transform(-1, 0, 1, 0, 0.5, 2, 0.5));//
	if(result == -1 || (r <= result && r > 0)) result = r;

	r = base->intersectionTest(p, v, m*world*transform(1, 0, -1, 0, 0.5, 2, 0.5));//
	if(result == -1 || (r <= result && r > 0)) result = r;

	r = base->intersectionTest(p, v, m*world*transform(1, 0, 1, 0, 0.5, 2, 0.5));//
	if(result == -1 || (r <= result && r > 0)) result = r;

	r = base->intersectionTest(p, v, m*world*transform(0, 2, -1.2, 0, 2.5, 2.5, 0.1));
	if(result == -1 || (r <= result && r > 0)) result = r;

	return result;
}