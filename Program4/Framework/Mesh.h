#ifndef __MESH_H
/***********************
Author: David Goehring
Course: COMP361
Date: 4/4/14
Description: Mesh Header
***********************/
#define __MESH_H

#include "glew.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "qstring.h"


using glm::vec3;
using glm::vec4;
using std::vector;
using std::ifstream;
using std::string;
typedef glm::mat4 matrix;

struct NewFace;
struct Vertex
{
	glm::vec4 position;
	glm::vec4 normal;
	glm::vec3 color;
};
struct HalfEdge
{
	HalfEdge(){sym = 0; next = 0; face = 0; vertex = 0;}
	HalfEdge *sym, *next, *prev;
	NewFace* face;
	Vertex* vertex;
};
struct NewFace
{
	NewFace(){edge = 0; edgeCount = 0;}
	HalfEdge* edge;
	unsigned int edgeCount;
	glm::vec4 normal;
};

struct Mesh
{
	NewFace *faces;
	int faceCount;
	int pointsInBuffer;
	int pointsInIndex;
	bool extruding;

	glm::vec4 *points;
	glm::vec4 *normals;
	glm::vec3 *colors;
	unsigned int *indices;

	Mesh();
	Mesh(QString filename);
	void fillBuffers();
};

#endif