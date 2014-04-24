#include "Table.h"

Table::Table()
{
	world = Matrix(1.0f);
}

Table::~Table()
{
}

void Table::init(Box* b)
{
	base = b;
	base->setWorld(Matrix(1.0f));
	
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
	Matrix transMat = glm::translate(Matrix(1.0f), Vec3(tX, tY, tZ));
	Matrix rotMat = glm::rotate(Matrix(1.0f), theta, Vec3(0,1,0));
	Matrix scaleMat = glm::scale(Matrix(1.0f), Vec3(sX, sY, sZ));
	tr = transMat * rotMat * scaleMat;
	//tr = scaleMat * rotMat * transMat;

	//modelMatrix = scaleMat;
	return tr;
}