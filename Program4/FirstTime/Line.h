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

#include "constants.h"

class Line
{
public:
	Line();
	~Line();

	void init(uint* vbo, uint* cbo, uint* vLocation, uint* cLocation, uint* u_projLocation, uint* u_modelMatrix, uint* ibo, uint* nbo, uint* nLocation);
	virtual void draw();
	virtual float getHeight(){return scaleFactor;}

	Matrix getWorld(){return world;}
	void setWorld(Matrix w){world = w;}

	void setTransX(float t){transX = t;}
	void setTransY(float t){transY = t;}
	void setTransZ(float t){transZ = t;}
	float getTransX(){return transX;}
	float getTransY(){return transY;}
	float getTransZ(){return transZ;}

	void setRotX(float r){rotX = r;}
	void setRotY(float r){rotY = r;}
	void setRotZ(float r){rotZ = r;}
	float getRotX(){return rotX;}
	float getRotY(){return rotY;}
	float getRotZ(){return rotZ;}

	void setScaleX(float s){scaleX = s;}
	void setScaleY(float s){scaleY = s;}
	void setScaleZ(float s){scaleZ = s;}
	float getScaleX(){return scaleX;}
	float getScaleY(){return scaleY;}
	float getScaleZ(){return scaleZ;}

protected:
	Matrix world;
	float transX, transY, transZ;
	float rotX, rotY, rotZ;
	float scaleX, scaleY, scaleZ;

	//unsigned int* shaderProgram;
	unsigned int *vbo, *cbo, *ibo, *nbo;
	unsigned int *vLocation, *cLocation, *nLocation;
	unsigned int *u_projLocation, *u_modelMatrix;
	float height;
	float scaleFactor;

private:
	float edge;
};
#endif