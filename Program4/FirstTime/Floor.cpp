#include "Floor.h"


Floor::Floor(void) : Box()
{
	world = Matrix(1.0f);
	scaleFactor = 0.01;
}


Floor::~Floor(void)
{
}

void Floor::init(Box* b, uint* vbo, uint* cbo, uint* vLocation, uint* cLocation, uint* u_projLocation, uint* u_modelMatrix, uint* u_lightLocation)
{
	base = b;
	base->setWorld(Matrix(1.0f));
	Floor::vbo = vbo;
	Floor::cbo = cbo;
	Floor::vLocation = vLocation;
	Floor::cLocation = cLocation;
	Floor::u_projLocation = u_projLocation;
	Floor::u_modelMatrix = u_modelMatrix;
	Floor::u_lightLocation = u_lightLocation;
	scaleFactor = 0.01;
}

void Floor::draw(Vec4 color)
{
	//world = Matrix(0.5, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 1);
	//world = world * glm::scale(Matrix(1.0f), Vec3(scaleX / 4.0, 0.01, scaleZ/4.0));
	base->setWorld(world*transform(scaleX/2.0f, 0, scaleZ/2.0f, 0, scaleX/8.0f, scaleFactor, scaleZ/8.0f));
	//base->setWorld(world*transform(0, 0, 0, 0, scaleX, scaleFactor, scaleZ));
	//base->setWorld(world*transform(0, 0, 0, 0, 1, scaleFactor, 1));
	base->draw(GREEN);
	base->setWorld(world * transform(scaleX/2.0f, 0, scaleZ/2.0f - scaleX/1.5f, 0, scaleX/8.0f, 1, 0.01));
	base->draw(GREEN);
	base->setWorld(world * transform(scaleX/2.0f, 0, scaleZ/2.0f + scaleX/1.5f, 0, scaleX/8.0f, 1, 0.01));
	base->draw(GREEN);
	base->setWorld(world * transform(scaleX/2.0f- scaleZ/1.5f, 0, scaleZ/2.0f , 0, 0.01, 1, scaleZ/8.0f));
	base->draw(GREEN);
	base->setWorld(world * transform(scaleX/2.0f+ scaleZ/1.5f, 0, scaleZ/2.0f , 0, 0.01, 1, scaleZ/8.0f));
	base->draw(GREEN);
	//base->setTransX(scaleZ);
	//base->setWorld(world* transform(0, 0, 0, 0, scaleX, 0.01, scaleZ));
	//base->draw();
	//base->setWorld(world* transform(0, 0.75, 3/scaleZ, 0, scaleX/4.0, 1.5, 0.05));
	//base->draw();
	//base->setWorld(world* transform((3.0/5.0)*scaleX, 0.75, 0, 0, 0.05, 1.5, scaleZ/4.0));
	//base->draw();
	//base->setWorld(world* transform(-3/scaleX, 0.75, 0, 0, 0.05, 1.5, scaleZ/4.0));
	//base->draw();
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