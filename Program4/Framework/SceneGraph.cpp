/* 
	Author: Mitch Roberts
	Course: COMP 361, Computer Graphics 
	Date: Feb. 10, 2014 
	Description: This file defines the generic Node class, as well as the more specialized NodeTransform and 
		NodeGeometry classes to handle the SceneGraph's hierarchy of transformations
*/ 

#include "SceneGraph.h"

SceneGraph::SceneGraph(Geometry* g, int x, int z)
{
	geometry = g;
	width = x;
	depth = z;
	children = new SceneGraph* [width * depth];
	for(int i = 0; i<width*depth; i++)children[i] = 0;
	transX = 0;
	transY = 0;
	transZ = 0;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	g->setScaleY(scaleY);
	selected = false;
	type = FURNITURE;
}

SceneGraph::SceneGraph(Geometry* g, int x, int z, float tx, float ty, float tz, float ry, float sx, float sy, float sz, GEOMETRYTYPE gtype)
{
	geometry = g;
	width = x;
	depth = z;
	children = new SceneGraph* [width * depth];
	for(int i = 0; i<width*depth; i++)children[i] = 0;
	transX = tx;
	transY = ty;
	transZ = tz;
	rotX = 0;
	rotY = ry;
	rotZ = 0;
	scaleX = sx;
	scaleY = sy;
	scaleZ = sz;
	g->setScaleX(scaleX);
	g->setScaleY(scaleY);
	g->setScaleZ(scaleZ);
	selected = false;
	type = gtype;
}


SceneGraph::~SceneGraph(void)
{
	//geometry = 0;
	//delete [] children;
}

void SceneGraph::traverse(Matrix m)
{
	Matrix t = glm::translate(Matrix(1.0f), Vec3(transX, transY, transZ));
	Matrix r = glm::rotate(Matrix(1.0f), rotY, Vec3(0.0f, 1.0f, 0.0f));
	Matrix s = glm::scale(Matrix(1.0f), Vec3(scaleX, scaleY, scaleZ));

	Matrix mat = m * t * r * s;
	//m = s*r*t*m;
	if(geometry != 0)
	{
		geometry->setWorld(mat);
		if(selected) geometry->draw(ORANGE);
		else geometry->draw();
	}

	for(int i=0; i<width*depth; i++)
	{
		if(children[i] != 0) children[i]->traverse(mat);
	}
}

void SceneGraph::addChild(SceneGraph* sg, int x, int z)
{
	if(geometry)
	{
		sg->setTransY(geometry->getHeight());
	}

	if(children[x*depth+z])
	{
		sg->setTransX(0);
		//sg->setTransY(0);
		sg->setTransZ(0);
		children[x*depth+z]->addChild(sg, x, z);
	}
	else
	{
		//sg->setTransX(x+ 0.5f);
		//sg->setTransZ(z + 0.5f);
		children[x*depth+z] = sg;
	}
}