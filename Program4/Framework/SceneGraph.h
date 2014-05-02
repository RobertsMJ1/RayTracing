/* 
	Author: Mitch Roberts 
	Course: COMP 361, Computer Graphics 
	Date: March 17, 2014 
	Description: Made the scene graph not completely stupid
*/ 


#pragma once
#define GLEW_STATIC
#include "glew.h"
#include <QGLWidget>
#include <stdlib.h>
#include <QDebug>

#include <vector>
using std::vector;
#include "../glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <list>
using std::list;

#include "Geometry.h"

class SceneGraph
{
public:
	SceneGraph(Geometry* g, int x, int z);
	SceneGraph(Geometry* g, int x, int z, float tx, float ty, float tz, float ry, float sx, float sy, float sz);
	~SceneGraph(void);
	//The scene graph is a rough wrapper to contain the root and the rest of the tree.
	//Node* root;

	void traverse(Matrix m);/*{root->traverse(glm::mat4(1.0));}*/
	void addChild(SceneGraph* sg, int x, int z);

#pragma region Mutators and Accessors
	void setTransform(float tx, float ty, float tz, float ry, float sx, float sy, float sz);

	void setTransX(float t){transX = t;}
	void setTransY(float t){transY = t;}
	void setTransZ(float t){transZ = t;}

	float getTransX() {return transX;}
	float getTransY() {return transY;}
	float getTransZ() {return transZ;}

	void setRotX(float r){rotX = r;}
	void setRotY(float r){rotY = r;}
	void setRotZ(float r){rotZ = r;}

	float getRotX() {return rotX;}
	float getRotY() {return rotY;}
	float getRotZ() {return rotZ;}

	void setScaleX(float s){scaleX = s;}
	void setScaleY(float s){scaleY = s;}
	void setScaleZ(float s){scaleZ = s;}

	float getScaleX() {return scaleX;}
	float getScaleY() {return scaleY;}
	float getScaleZ() {return scaleZ;}

	void setGeometry(Geometry* b){geometry = b;}

	void setSelected(bool s) {selected = s;}

	SceneGraph** getChildren() {return children;}
#pragma endregion

private:
	Geometry* geometry;
	SceneGraph** children;
	int width, depth;

	bool selected;

	float transX, transY, transZ;
	float rotX, rotY, rotZ;
	float scaleX, scaleY, scaleZ;
};