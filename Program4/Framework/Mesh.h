#ifndef __MESH_H
/***********************
Author: David Goehring
Course: COMP361
Date: 4/4/14
Description: Mesh Header
***********************/
#define __MESH_H

#pragma once
#define GLEW_STATIC

#include "glew.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <vector>
#include <string>
#include <sstream>
#include "constants.h"
#include "Geometry.h"
using namespace std;


using glm::vec3;
using glm::vec4;
using std::vector;
typedef glm::mat4 matrix;

struct Face {
	Face(vec3 v1, vec3 v2, vec3 v3) {vertices[0] = v1; vertices[1] = v2; vertices[2] = v3;}
	vec3 vertices[3];
	vec3 normal;
};

enum MESHTYPE {EXTRUSION = 0, SURFREV = 1};

class Mesh : public Geometry {

public:
	Mesh();
	~Mesh();
	void init();
	void fileRead(string fileName);
	float getHeight() {return 1;}
	void calculateExtrusion(std::stringstream &s);
	void calculateSurfRev(std::stringstream &s);

	void calculateFace(vec3 v1, vec3 v2, vec3 v3);
	void calculateFace(vec3 v1, vec3 v2, vec3 v3, vec3 v4);

	void surfRevTop(int count, int slices, vector<vec3> vertices);
	void surfRevBottom(int count, int slices, vector<vec3> vertices);
	void surfRevBoth(int count, int slices, vector<vec3> vertices);
	void surfRevNone(int count, int slices, vector<vec3> vertices,bool endcaps);

	void setSelected(bool s) {selected = s;}
	MESHTYPE getMeshType() {return m;}

	vector<vec3> pointsVector;
	vector<vec3> colorsVector;
	vector<vec3> normalsVector;
	vector<unsigned int> indicesVector;
	vector<Face*> faces;

	void draw(vec4 color);

private:

	bool selected;
	MESHTYPE m;


	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	unsigned int vbo, cbo, ibo, nbo;
	unsigned int vLocation, cLocation, nLocation;
	unsigned int u_projLocation, u_modelMatrix, u_lightLocation;
};



#endif