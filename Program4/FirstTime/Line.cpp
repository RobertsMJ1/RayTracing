#include "Line.h"

Line::Line()
{
	world = Matrix(1.0f);
	edge = 1.0;
	height = edge;
	transX = 0;
	transY = 0;
	transZ = 0;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	scaleFactor = 1;
}

Line::~Line()
{
	Line::vbo = 0;
	Line::cbo = 0;
	Line::vLocation = 0;
	Line::cLocation = 0;
	Line::u_projLocation = 0;
	Line::u_modelMatrix = 0;
}

void Line::init(uint* vbo, uint* cbo, uint* vLocation, uint* cLocation, uint* u_projLocation, uint* u_modelMatrix, uint* ibo, uint* nbo, uint* nLocation)
{
	Line::vbo = vbo;
	Line::cbo = cbo;
	Line::vLocation = vLocation;
	Line::cLocation = cLocation;
	Line::u_projLocation = u_projLocation;
	Line::u_modelMatrix = u_modelMatrix;
	Line::ibo = ibo;
	Line::nbo = nbo;
	Line::nLocation = nLocation;

	glm::vec4 points[2] = {
		//Front
		Vec4(0,0,0,1),
		Vec4(1,0,0,1)
	};

	glm::vec4 colors[2] = {
		//Front
		RED,RED
	};

	uint indices[2] = {
		0, 1
	};

	glm::vec4 normals[2] = {
		//front
		glm::vec4(0, 0, 0, 0),
		glm::vec4(0, 0, 0, 0)
	};

	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec4), points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(*vLocation);
	glVertexAttribPointer(*vLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, *cbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec4), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(*cLocation);
	glVertexAttribPointer(*cLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, *nbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec4), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(*nLocation);
	glVertexAttribPointer(*nLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(uint), indices, GL_STATIC_DRAW);
}

void Line::draw()
{
	//Matrix t = glm::translate(Matrix(1.0f), Vec3(transX, transY, transZ));
	//Matrix r = glm::rotate(Matrix(1.0f), rotY, Vec3(0.0f, 1.0f, 0.0f));
	//Matrix s = glm::scale(Matrix(1.0f), Vec3(scaleX, scaleY, scaleZ));
	//
	//world = t * r * s * world;
	//Matrix modelmatrix = Matrix(1.0f);
	//world = glm::rotate(world, i, Vec3(0,1,0));
	//world = world * glm::translate(Matrix(1.0f), Vec3(0, -0.5, 0));
	glUniformMatrix4fv(*u_modelMatrix, 1, GL_FALSE, &world[0][0]);

	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
	//world = Matrix(1.0f);
}