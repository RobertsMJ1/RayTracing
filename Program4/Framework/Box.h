/* 
	Author: Mitch Roberts 
	Course: COMP 361, Computer Graphics 
	Date: March 17, 2014 
	Description: Box class, base of all other box-based objects
*/ 
#ifndef BOX_H
#define BOX_H

#pragma once
#define GLEW_STATIC
#include "glew.h"
#include <QGLWidget>
#include <stdlib.h>
#include <QDebug>
#include "../glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "Geometry.h"

class Box : public Geometry
{
public:
	Box();
	~Box();

	virtual void init();
	virtual void draw(Vec4 color = YELLOW);
	virtual float getHeight(){return 1;}
	virtual float intersectionTest(const vec3& p, const vec3& v, const mat4& m);
	virtual vec3 getColor(){return vec3(YELLOW);}

private:
	Vec4 points[24];
	unsigned int indices[36];
	Vec4 normals[24];
	float edge;

	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	unsigned int vbo, cbo, ibo, nbo;
	unsigned int vLocation, cLocation, nLocation;
	unsigned int u_projLocation, u_modelMatrix, u_lightLocation;
};

#endif