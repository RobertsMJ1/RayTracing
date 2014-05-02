/***********************
Author: David Goehring
Course: COMP361
Date: 2/10/14
Description: GLWidget Header
***********************/
#pragma once
#define GLEW_STATIC
#include "glew.h"
#include "../glm/glm.hpp"
#include <QGLWidget>
#include <QObject>
#include <QSlider>
#include <QPushButton>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include "SceneGraph.h"
#include "Mesh.h"
#include "Box.h"
#include "Table.h"
#include "Chair.h"
#include "Floor.h"
#include "constants.h"
using std::string;
using std::stringstream;


using glm::vec4;

#define CONFIG_FILE "config.txt"

#define BLACK_COLOR			vec4( 0.0, 0.0, 0.0, 1.0 )
#define RED_COLOR			vec4( 1.0, 0.0, 0.0, 1.0 )
#define YELLOW_COLOR		vec4( 1.0, 1.0, 0.0, 1.0 )
#define GREEN_COLOR			vec4( 0.0, 1.0, 0.0, 1.0 )
#define BLUE_COLOR			vec4( 0.0, 0.0, 1.0, 1.0 )
#define MAGENTA_COLOR		vec4( 1.0, 0.0, 1.0, 1.0 )
#define WHITE_COLOR			vec4( 1.0, 1.0, 1.0, 1.0 )
#define CYAN_COLOR			vec4( 0.0, 1.0, 1.0, 1.0 )

#define BUFFER_OFFSET(bytes) ((GLvoid*) (bytes))

const int numVertices = 24;


//List of Geometry in Scene; used for manipulation
struct geoList {
	SceneGraph* geo;
	geoList* next;
	geoList* prev;
};



class MyGLWidget : public QGLWidget
{
	Q_OBJECT
public:
	MyGLWidget(QWidget*);
	~MyGLWidget(void);

	void initializeGL(void);
	void paintGL(void);
	void resizeGL(int, int);

	//helper function to read shader source and put it in a char array
	//thanks to Swiftless.com
	char* textFileRead(const char*);

	vec4 points[numVertices];
	vec4 colors[numVertices];

	void fillBuffers();

	void buildProcGeometry();

	void processInput(string fname);
	/*
	vector<vec3> pointsVector;
	vector<vec3> colorsVector;
	vector<vec3> normalsVector;
	vector<unsigned int> indicesVector;
	vector<Face*> faces;
	*/
	vector<Mesh*> meshVec;

	void moveGeometry();

public slots:
	void zoom(int);
	void pitch(int);
	void yaw(int);
	void loadConfig(QString);
	void lightXInc() {lightX+=1.0f;}
	void lightXDec() {lightX-=1.0f;}
	void lightYInc() {lightY+=1.0f;}
	void lightYDec() {lightY-=1.0f;}
	void lightZInc() {lightZ+=1.0f;}
	void lightZDec() {lightZ-=1.0f;}
	void transXInc() {transXValue++; geoListCurrent->geo->setTransX(geoListCurrent->geo->getTransX()+1);}
	void transXDec() {transXValue--; geoListCurrent->geo->setTransX(geoListCurrent->geo->getTransX()-1);}
	void transZInc() {transZValue++; geoListCurrent->geo->setTransZ(geoListCurrent->geo->getTransZ()+1);}
	void transZDec() {transZValue--; geoListCurrent->geo->setTransZ(geoListCurrent->geo->getTransZ()-1);}
	void nextGeo();
	void prevGeo();

private:

	vector<Box*> geometry;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;
	
	unsigned int vbo, cbo, ibo, nbo;
	unsigned int vLocation, cLocation, nLocation;
	unsigned int u_projLocation, u_modelMatrix, u_lightLocation, u_eyeLocation;

	Box box;
	Chair chair;
	Table table;
	Floor floor;

	SceneGraph* root;

	geoList* geoListCurrent;
	geoList* geoListRoot;

	SceneGraph* currentGeo;
	int currentCount;

	float zoomValue;
	float pitchValue;
	float yawValue;

	int transXValue;
	int transZValue;

	float lightX;
	float lightY;
	float lightZ;

	matrix camera; 
	matrix mView, mProj;
	
	vec4 mEyePos;
	vec4 target;
	vec4 mUp;

	Box lBox;

	matrix rotateX;
	matrix rotateY;
	int w,h;
	int numIndices;
	string fileName;
};