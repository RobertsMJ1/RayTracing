#include "Table.h"

Table::Table()
{
	world = Matrix(1.0f);
}

Table::~Table()
{
	Table::base = 0;
	Table::vbo = 0;
	Table::cbo = 0;
	Table::vLocation = 0;
	Table::cLocation = 0;
	Table::u_projLocation = 0;
	Table::u_modelMatrix = 0;
}

void Table::init(Box* b, uint* vbo, uint* cbo, uint* vLocation, uint* cLocation, uint* u_projLocation, uint* u_modelMatrix, uint* u_lightLocation)
{
	base = b;
	base->setWorld(Matrix(1.0f));
	
	Table::vbo = vbo;
	Table::cbo = cbo;
	Table::vLocation = vLocation;
	Table::cLocation = cLocation;
	Table::u_projLocation = u_projLocation;
	Table::u_modelMatrix = u_modelMatrix;
	Table::u_lightLocation = u_lightLocation;
	scaleFactor = 0.25;
}

void Table::draw(Vec4 color)
{
	//world = Matrix(0.5, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 1);
	world = world * glm::scale(Matrix(1.0f), Vec3(scaleFactor, scaleFactor, scaleFactor));
	base->setWorld(world*transform(0, 2, 0, 0, 2.5, 0.1, 2.5));
	base->draw(RED);
	base->setWorld(world*transform(-1, 0, -1, 0, 0.5, 2, 0.5));
	base->draw(RED);
	base->setWorld(world*transform(-1, 0, 1, 0, 0.5, 2, 0.5));
	base->draw(RED);
	base->setWorld(world*transform(1, 0, -1, 0, 0.5, 2, 0.5));
	base->draw(RED);
	base->setWorld(world*transform(1, 0, 1, 0, 0.5, 2, 0.5));
	base->draw(RED);
	base->setWorld(Matrix(1.0f));
	//world = Matrix(1.0f);
}

Matrix Table::transform(float tX, float tY, float tZ, float theta, float sX, float sY, float sZ)
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