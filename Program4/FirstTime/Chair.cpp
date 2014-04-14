#include "Chair.h"

Chair::Chair()
{
	world = Matrix(1.0f);
}

Chair::~Chair()
{
	Chair::base = 0;
	Chair::vbo = 0;
	Chair::cbo = 0;
	Chair::vLocation = 0;
	Chair::cLocation = 0;
	Chair::u_projLocation = 0;
	Chair::u_modelMatrix = 0;
	scaleFactor = 0;
}

void Chair::init(Box* b, uint* vbo, uint* cbo, uint* vLocation, uint* cLocation, uint* u_projLocation, uint* u_modelMatrix, uint* u_lightLocation)
{
	base = b;
	base->setWorld(Matrix(1.0f));
	Chair::vbo = vbo;
	Chair::cbo = cbo;
	Chair::vLocation = vLocation;
	Chair::cLocation = cLocation;
	Chair::u_projLocation = u_projLocation;
	Chair::u_modelMatrix = u_modelMatrix;
	Chair::u_lightLocation = u_lightLocation;
	
	scaleFactor = 0.25;
}

void Chair::draw(Vec4 color)
{
	//world = Matrix(0.5, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 1);
	world = world * glm::scale(Matrix(1.0f), Vec3(scaleFactor, scaleFactor, scaleFactor));
	base->setWorld(world*transform(0, 2, 0, 0, 2.5, 0.1, 2.5));
	base->draw(BLUE);
	base->setWorld(world*transform(-1, 0, -1, 0, 0.5, 2, 0.5));
	base->draw(BLUE);
	base->setWorld(world*transform(-1, 0, 1, 0, 0.5, 2, 0.5));
	base->draw(BLUE);
	base->setWorld(world*transform(1, 0, -1, 0, 0.5, 2, 0.5));
	base->draw(BLUE);
	base->setWorld(world*transform(1, 0, 1, 0, 0.5, 2, 0.5));
	base->draw(BLUE);
	base->setWorld(world*transform(0, 2, -1.2, 0, 2.5, 2.5, 0.1));
	base->draw(BLUE);
	base->setWorld(Matrix(1.0f));
	world = Matrix(1.0f);
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