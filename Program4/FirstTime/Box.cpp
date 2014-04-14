#include "Box.h"

Box::Box()
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

Box::~Box()
{
	Box::vbo = 0;
	Box::cbo = 0;
	Box::vLocation = 0;
	Box::cLocation = 0;
	Box::u_projLocation = 0;
	Box::u_modelMatrix = 0;
}

void Box::init(uint* vbo, uint* cbo, uint* vLocation, uint* cLocation, uint* u_projLocation, uint* u_modelMatrix, uint* u_lightLocation, uint* ibo, uint* nbo, uint* nLocation)
{
	Box::vbo = vbo;
	Box::cbo = cbo;
	Box::vLocation = vLocation;
	Box::cLocation = cLocation;
	Box::u_projLocation = u_projLocation;
	Box::u_modelMatrix = u_modelMatrix;
	Box::ibo = ibo;
	Box::nbo = nbo;
	Box::nLocation = nLocation;
	Box::u_lightLocation = u_lightLocation;

	glm::vec4 points[24] = {
		//Front
		glm::vec4(-0.5, 0, 0.5, 1),
		glm::vec4(-0.5, 1, 0.5, 1),
		glm::vec4(0.5, 1, 0.5, 1),
		glm::vec4(0.5, 0, 0.5, 1),
		//Left
		glm::vec4(-0.5, 0, 0.5, 1),
		glm::vec4(-0.5, 1, 0.5, 1),
		glm::vec4(-0.5, 1, -0.5, 1),
		glm::vec4(-0.5, 0, -0.5, 1),
		//Right
		glm::vec4(0.5, 0, 0.5, 1),
		glm::vec4(0.5, 1, 0.5, 1),
		glm::vec4(0.5, 1, -0.5, 1),
		glm::vec4(0.5, 0, -0.5, 1),
		//Back
		glm::vec4(-0.5, 0, -0.5, 1),
		glm::vec4(-0.5, 1, -0.5, 1),
		glm::vec4(0.5, 1, -0.5, 1),
		glm::vec4(0.5, 0, -0.5, 1),
		//Bottom
		glm::vec4(-0.5, 0, -0.5, 1),
		glm::vec4(-0.5, 0, 0.5, 1),
		glm::vec4(0.5, 0, 0.5, 1),
		glm::vec4(0.5, 0, -0.5, 1),
		//Top
		glm::vec4(-0.5, 1, -0.5, 1),
		glm::vec4(-0.5, 1, 0.5, 1),
		glm::vec4(0.5, 1, 0.5, 1),
		glm::vec4(0.5, 1, -0.5, 1)
	};

	

	uint indices[36] = {
		0, 2, 1,
		0, 3, 2,
		4, 5, 6,
		7, 4, 6,
		8, 10, 9,
		8, 11, 10,
		12, 15, 14,
		12, 14, 13,
		17, 18, 16,
		18, 19, 16,
		22, 21, 20,
		22, 20, 23
	};

	glm::vec4 normals[24] = {
		//front
		glm::vec4(0, 0, 1, 0),
		glm::vec4(0, 0, 1, 0),
		glm::vec4(0, 0, 1, 0),
		glm::vec4(0, 0, 1, 0),
		//left		
		glm::vec4(-1, 0, 0, 0),
		glm::vec4(-1, 0, 0, 0),
		glm::vec4(-1, 0, 0, 0),
		glm::vec4(-1, 0, 0, 0),
		//right
		glm::vec4(1, 0, 0, 0),
		glm::vec4(1, 0, 0, 0),
		glm::vec4(1, 0, 0, 0),
		glm::vec4(1, 0, 0, 0),
		//back
		glm::vec4(0, 0, -1, 0),
		glm::vec4(0, 0, -1, 0),
		glm::vec4(0, 0, -1, 0),
		glm::vec4(0, 0, -1, 0),
		//bot
		glm::vec4(0, -1, 0, 0),
		glm::vec4(0, -1, 0, 0),
		glm::vec4(0, -1, 0, 0),
		glm::vec4(0, -1, 0, 0),
		//top
		glm::vec4(0, 1, 0, 0),
		glm::vec4(0, 1, 0, 0),
		glm::vec4(0, 1, 0, 0),
		glm::vec4(0, 1, 0, 0)
	};

	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(glm::vec4), points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(*vLocation);
	glVertexAttribPointer(*vLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	

	glBindBuffer(GL_ARRAY_BUFFER, *nbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(glm::vec4), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(*nLocation);
	glVertexAttribPointer(*nLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(uint), indices, GL_STATIC_DRAW);
}

void Box::draw(Vec4 color)
{
	glm::vec4 colors[24] = {
		//Front
		color,color,color,color,
		//Back 
		color,color,color,color,
		//Left
		color,color,color,color,
		//Right
		color,color,color,color,
		//Bottom
		color,color,color,color,
		//Top
		color,color,color,color
	};

	//world = world * ;

	glBindBuffer(GL_ARRAY_BUFFER, *cbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(glm::vec4), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(*cLocation);
	glVertexAttribPointer(*cLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glUniformMatrix4fv(*u_modelMatrix, 1, GL_FALSE, &world[0][0]);
	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}