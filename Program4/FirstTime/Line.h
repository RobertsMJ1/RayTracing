#ifndef LINE_H
#define LINE_H

//#include <QGLWidget>
#define GLEW_STATIC
#include "glew.h"
#include <QGLWidget>
#include <stdlib.h>
#include <QDebug>
#include "../glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "Geometry.h"

class Line : public Geometry
{
public:
	Line();
	~Line();

	void init();
	virtual void draw(Vec4 color = YELLOW);
	virtual float getHeight(){return 0;}

private:
	Vec4 points[2];

	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	unsigned int vbo, cbo, ibo, nbo;
	unsigned int vLocation, cLocation, nLocation;
	unsigned int u_projLocation, u_modelMatrix, u_lightLocation;
};
#endif