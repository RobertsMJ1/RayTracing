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

class Mesh: public Box
{
public:
	Mesh(void);
	~Mesh(void);

	void init(uint* vbo, uint* cbo, uint* vLocation, uint* cLocation, uint* u_projLocation, uint* u_modelMatrix, uint* u_lightLocation, uint* ibo, uint* nbo, uint* nLocation);
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
	vector<uint> indices;
	vector<Vec4> normals;

	ifstream fin;
	bool inited;
};

