/* 
	Author: Mitch Roberts 
	Course: COMP 361, Computer Graphics 
	Date: March 17, 2014 
	Description: floor
*/ 
#pragma once
#define GLEW_STATIC
#include "glew.h"
#include <QGLWidget>
#include <stdlib.h>
#include <QDebug>
#include "../glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "constants.h"
#include "Box.h"

class Floor : public Box
{
public:
	Floor(void);
	~Floor(void);

	void init(Box* b);
	virtual void draw(Vec4 color = GREEN);
	virtual float intersectionTest(const vec3& p, const vec3& v, const mat4& m, vec3& normal);
	float getHeight(){return scaleFactor;}
	virtual vec3 getColor(){return vec3(0, 1, 0);}
	

	Matrix transform(float tX = 0, float tY = 0, float tZ = 0, float theta = 0, float sX=1, float sY=1, float sZ=1);
private:
	Box* base;
	float scaleFactor;
};

