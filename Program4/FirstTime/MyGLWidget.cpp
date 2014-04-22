/* 
	Author: Mitch Roberts 
	Course: COMP 361, Computer Graphics 
	Date: March 17, 2014 
	Description: All of the stuff to run everything
*/ 
#include "MyGLWidget.h"
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
using glm::translate;
using glm::normalize;
using glm::rotate;



MyGLWidget::MyGLWidget(QWidget* parent) : QGLWidget(parent), 
	mRadius(10.0f), mTheta(0.0f), mPhi(PI * 0.4f)
{;
	light = Vec3(5.0f, 5.0f, 0.0f);
	target = Vec4(0,0,0, 1);
	mUp = Vec4(0,1,0, 0);
}


MyGLWidget::~MyGLWidget(void)
{
}

void MyGLWidget::initializeGL() {
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &cbo);
	glGenBuffers(1, &ibo);
	glGenBuffers(1, &nbo);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();

	const char* vertexSource = textFileRead("lambert.vert");
	const char* fragmentSource = textFileRead("lambert.frag");
	glShaderSource(vertexShader, 1, &vertexSource, 0);
	glShaderSource(fragmentShader, 1, &fragmentSource, 0);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	vLocation = glGetAttribLocation(shaderProgram, "vs_position");
	cLocation = glGetAttribLocation(shaderProgram, "vs_color");
	nLocation = glGetAttribLocation(shaderProgram, "vs_normal");
	u_projLocation = glGetUniformLocation(shaderProgram, "u_projMatrix");
	u_modelMatrix = glGetUniformLocation(shaderProgram, "u_modelMatrix");
	u_lightLocation = glGetUniformLocation(shaderProgram, "u_lightPos");

	glUseProgram(shaderProgram);

	box.init();
	poly.init();
	chair.init(&box);
	table.init(&box);
	floor.init(&box);
	//chair.init(&box, &vbo, &cbo, &vLocation, &cLocation, &u_projLocation, &u_modelMatrix, &u_lightLocation);
	//table.init(&box, &vbo, &cbo, &vLocation, &cLocation, &u_projLocation, &u_modelMatrix, &u_lightLocation);
	//floor.init(&box, &vbo, &cbo, &vLocation, &cLocation, &u_projLocation, &u_modelMatrix, &u_lightLocation);
	//lBox.init(&vbo, &cbo, &vLocation, &cLocation, &u_projLocation, &u_modelMatrix, &u_lightLocation, &ibo, &nbo, &nLocation);

	/*****************************************Here*****************************************************/
	processInput("testScene.txt");
	/**************************************************************************************************/
}

void MyGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);

	Matrix rotX = rotate(Matrix(1.0f), mTheta, Vec3(1, 0, 0));
	Matrix rotY = rotate(Matrix(1.0f), mPhi, Vec3(0, 1, 0));

	mEyePos = rotY * rotX * Vec4(0, 0, mRadius, 1);
	mUp = rotY * rotX * Vec4(0, 1, 0, 0);

	Matrix camera = glm::lookAt(Vec3(mEyePos), Vec3(0, 0, 0), Vec3(0, 1, 0));

	//Vec4 l4(light, 1);
	//l4 = camera * l4;
	//light = Vec3(l4);
	glm::vec4 l(1, 1, 1, 1);
	l = camera * l;
	//glm::vec4 l = camera * Vec4(light, 1.0f);
	glUniform4fv(u_lightLocation, 1, &l[0]);

	
	box.setWorld(camera);
	box.draw();
	poly.setWorld(camera);
	poly.draw();
	chair.setWorld(camera);
	chair.draw();
	
	root->traverse(camera);

	glFlush();
}

void MyGLWidget::resizeGL(int width, int height) {
	glViewport(0, 0, width, height);
	//Here's how to make matrices for transformations, check the documentation of GLM for rotation, scaling, and translation
	glm::mat4 projection = glm::perspective(45.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 30.0f);
	
	//Do something similar for u_modelMatrix before rendering things
	glUniformMatrix4fv(u_projLocation, 1, GL_FALSE, &projection[0][0]);
}

////from swiftless.com
//char* MyGLWidget::textFileRead(const char* fileName) {
//    char* text;
//    
//    if (fileName != NULL) {
//        FILE *file = fopen(fileName, "rt");
//        
//        if (file != NULL) {
//            fseek(file, 0, SEEK_END);
//            int count = ftell(file);
//            rewind(file);
//            
//            if (count > 0) {
//                text = (char*)malloc(sizeof(char) * (count + 1));
//                count = fread(text, sizeof(char), count, file);
//                text[count] = '\0';	//cap off the string with a terminal symbol, fixed by Cory
//            }
//            fclose(file);
//        }
//    }
//    return text;
//}

void MyGLWidget::printLinkInfoLog(int prog) 
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLogLen);

	// should additionally check for OpenGL errors here

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];
		// error check for fail to allocate memory omitted
		glGetProgramInfoLog(prog,infoLogLen, &charsWritten, infoLog);
		qDebug() << "InfoLog:" << endl << infoLog << endl;
		delete [] infoLog;
	}
}

void MyGLWidget::printShaderInfoLog(int shader)
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

	// should additionally check for OpenGL errors here

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];
		// error check for fail to allocate memory omitted
		glGetShaderInfoLog(shader,infoLogLen, &charsWritten, infoLog);
		qDebug() << "InfoLog:" << endl << infoLog << endl;
		
		
	delete [] infoLog;
	}

	// should additionally check for OpenGL errors here
}

void MyGLWidget::processInput(string fname)
{
	glFlush();
	ifstream fin;
	fin.open(fname);
	if(fin.fail()) exit(1);

	int iter;
	int floorx, floorz;

	fin >> floorx >> floorz >> iter;
	floor.setScaleX(floorx);
	floor.setScaleZ(floorz);
	root = new SceneGraph(&floor, floorx, floorz);
	root->setTransX(-floorx/2.0);
	root->setTransZ(-floorz/2.0);

	string name;
	float transx, transz;
	float theta;
	float scalex, scaley, scalez;
	for(int i=0; i<iter; i++)
	{
		fin >> name >> transx >> transz >> theta >> scalex >> scaley >> scalez;
		
		if(name == "table"){
			root->addChild(new SceneGraph(&table, floorx, floorz, transx, 0, transz, theta, scalex, scaley, scalez), transx, transz);
		}
		else if (name == "chair"){
			root->addChild(new SceneGraph(&chair, floorx, floorz, transx, 0, transz, theta, scalex, scaley, scalez), transx, transz);
		}
		else if (name == "box"){
			root->addChild(new SceneGraph(&box, floorx, floorz, transx, -0.5, transz, theta, scalex, scaley, scalez), transx, transz);
		}
	}
}

void MyGLWidget::up() {
	mTheta -= 5.0f;
	repaint();
}
void MyGLWidget::down() {
	mTheta += 5.0f;
	repaint();
}
void MyGLWidget::left() {
	mPhi += 5.0f;
	repaint();
}
void MyGLWidget::right() {
	mPhi -= 5.0f;   
	repaint();
}

void MyGLWidget::zoomIn() {
	mRadius -= 0.5f;
	repaint();
}

void MyGLWidget::zoomOut() {
	mRadius += 0.5f;
	repaint();
}

void MyGLWidget::py()
{
	light.y++;
	repaint();
}
void MyGLWidget::my()
{
	light.y--;
	repaint();
}
void MyGLWidget::px()
{
	light.x++;
	repaint();
}
void MyGLWidget::mx()
{
	light.x--;
	repaint();
}
void MyGLWidget::pz()
{
	light.z++;
	repaint();
}
void MyGLWidget::mz()
{
	light.z--;
	repaint();
}

void MyGLWidget::loadFile(QString filename)
{
	//processInput(filename.toStdString());
	poly.init();
	repaint();
}