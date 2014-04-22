/* 
	Author: Mitch Roberts 
	Course: COMP 361, Computer Graphics 
	Date: March 17, 2014 
	Description: Declaring all of the stuff to run everything
*/ 
#pragma once
#define GLEW_STATIC
#include "glew.h"
#include <QGLWidget>
#include "../glm/glm.hpp"
#include <stdlib.h>
#include <QDebug>
#include <qtextedit.h>
#include "SceneGraph.h"
#include "Box.h"
#include "Chair.h"
#include "Table.h"
#include "Floor.h"
#include "constants.h"
#include <string>
using std::string;
#include "Line.h"
#include "Mesh.h"



class MyGLWidget : public QGLWidget {
	Q_OBJECT
public:
	MyGLWidget(QWidget*);
	~MyGLWidget(void);

	void initializeGL(void);
	void paintGL(void);
	void resizeGL(int, int);

	//helper function to read shader source and put it in a char array
	//thanks to Swiftless.com
	//char* textFileRead(const char*);

	//some other helper functions
	void printLinkInfoLog(int);
	void printShaderInfoLog(int);

	void processInput(string fname);

public slots:
	void up(void);
	void left(void);
	void down(void);
	void right(void);
	void zoomIn(void);
	void zoomOut(void);
	void py(void);
	void my(void);
	void px(void);
	void mx(void);
	void pz(void);
	void mz(void);
	void loadFile(QString);

private:

	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	unsigned int vbo, cbo, ibo, nbo;
	unsigned int vLocation, cLocation, nLocation;
	unsigned int u_projLocation, u_modelMatrix, u_lightLocation;

	Box box;
	Chair chair;
	Table table;
	Floor floor;

	SceneGraph* root;

	Vec3 light;
	Box lBox;

	Matrix mCamera;
	Vec4 mEyePos;
	float mRadius;
	float mTheta;
	float mPhi;
	Matrix mView, mProj;
	
	Vec4 target;
	Vec4 mUp;

	

	Mesh poly;
};