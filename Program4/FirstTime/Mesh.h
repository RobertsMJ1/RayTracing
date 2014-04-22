/* 
	Author: Mitch Roberts
	Course: COMP 361, Computer Graphics 
	Date: April 1, 2014
	Description: Basis for the mesh class. Will be undergoing revisions in the future, along with all other geometry.
*/
#pragma once
#include "Box.h"
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <vector>
using std::vector;

#include "Geometry.h"

class Mesh: public Geometry
{
public:
	Mesh(void);
	~Mesh(void);

	void init();
	virtual void draw(Vec4 color = YELLOW);
	
	virtual float getHeight(){return 0;}

	bool isInit(){return inited;}

private:
	//Extract base vertices from input file
	string getParams(string fname);

	void extGetBase();
	void extGetCap();
	void extGetSides();
	void extGetIndices();
	void extCalcNormals();
	bool convexityTest();

	void revGetBase();
	void revGetPoints();
	void revGetIndices();
	void revCalcNormals();

	int size;
	int nFaces;
	float disp;

	vector<Vec4> points;
	vector<unsigned int> indices;
	vector<Vec4> normals;

	ifstream fin;
	bool inited;

	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	unsigned int vbo, cbo, ibo, nbo;
	unsigned int vLocation, cLocation, nLocation;
	unsigned int u_projLocation, u_modelMatrix, u_lightLocation;
};

