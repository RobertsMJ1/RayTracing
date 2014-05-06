/***********************
Author: David Goehring
Course: COMP361
Date: 3/18/14
Description: GLWidget Implementation
***********************/
#include "MyGLWidget.h"
#include "../glm/gtc/matrix_transform.hpp"
using glm::inverse;
using glm::dot;
using glm::cross;
using glm::normalize;
using glm::length;
using glm::mat3;
using glm::determinant;

#include "EasyBMP.h"



MyGLWidget::MyGLWidget(QWidget* parent) : QGLWidget(parent) {
	epsilon = 0.001;
}

MyGLWidget::~MyGLWidget() {
	glDetachShader(shaderProgram,fragmentShader);
	glDetachShader(shaderProgram,vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &nbo);
	glDeleteBuffers(1, &cbo);
	glDeleteBuffers(1, &ibo);
}

void MyGLWidget::initializeGL() {
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0);
	zoomValue = 0;
	pitchValue = 0;
	yawValue = 0;
	lightX = 0;
	lightY = 5.0f;
	lightZ = 0;
	currentCount = 0;
	camera = matrix(1.0f);
	rotateX = matrix(1.0f);
	rotateY = matrix(1.0f);

	target = Vec4(0,0,0, 1);
	mUp = Vec4(0,1,0, 0);
	fileName = CONFIG_FILE;
	
	/* Parse Config Files */
	//fileName = "extrusion1.dat";
	//buildProcGeometry();
	
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
	/*
	//Do something similar to this to get the location of "u_modelMatrix"
	u_projLocation = glGetUniformLocation(shaderProgram, "u_projMatrix");
	u_modelLocation = glGetUniformLocation(shaderProgram, "u_modelMatrix");
	u_lightPos = glGetUniformLocation(shaderProgram, "u_lightPos");

	glUseProgram(shaderProgram);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	vLocation = glGetAttribLocation(shaderProgram, "vs_position");
	glEnableVertexAttribArray(vLocation);
	glVertexAttribPointer(vLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &cbo);
	glBindBuffer(GL_ARRAY_BUFFER,cbo);
	vColor = glGetAttribLocation(shaderProgram, "vs_color");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor,4,GL_FLOAT,GL_FALSE,0, 0);

	glGenBuffers(1, &nbo);
	glBindBuffer(GL_ARRAY_BUFFER,nbo);
	vNormal = glGetAttribLocation(shaderProgram, "vs_normal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal,4,GL_FLOAT,GL_FALSE,0,0);

	glGenBuffers(1, &ibo);
	
	fillBuffers();
	*/
	vLocation = glGetAttribLocation(shaderProgram, "vs_position");
	cLocation = glGetAttribLocation(shaderProgram, "vs_color");
	nLocation = glGetAttribLocation(shaderProgram, "vs_normal");
	u_projLocation = glGetUniformLocation(shaderProgram, "u_projMatrix");
	u_modelMatrix = glGetUniformLocation(shaderProgram, "u_modelMatrix");
	u_lightLocation = glGetUniformLocation(shaderProgram, "u_lightPos");
	u_eyeLocation = glGetUniformLocation(shaderProgram, "u_eye");

	glUseProgram(shaderProgram);

	box.init();
	chair.init(&box);
	table.init(&box);
	floor.init(&box);
	lBox.init();

	processInput(CONFIG_FILE);


	//Initial camera positioning
	pitchValue = -50;
	zoomValue = -6;

}

void MyGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);

	matrix rotX = glm::rotate(matrix(1.0f), pitchValue, vec3(1, 0, 0));
	matrix rotY = glm::rotate(matrix(1.0f), yawValue, vec3(0, 1, 0));

	mEyePos = rotY * rotX * vec4(0, 0, -zoomValue, 1);
	mUp = rotY * rotX * vec4(0, 1, 0, 0);

	camera = glm::lookAt(vec3(mEyePos.x, mEyePos.y, mEyePos.z), vec3(0, 0, 0), vec3(mUp.x, mUp.y, mUp.z));

	vec4 l(lightX,lightY,lightZ, 1);
	l = camera * l;

	glUniform4fv(u_lightLocation, 1, &l[0]);
	glUniform4fv(u_eyeLocation, 1, &mEyePos[0]);
	
	
	lBox.setWorld(camera*glm::translate(glm::mat4(1.0f),vec3(lightX,lightY-2,lightZ)));
	lBox.draw();
	root->traverse(camera);
	//root->traverse(Matrix(1.0f));
	update();
	glFlush();
}

void MyGLWidget::resizeGL(int width, int height) {
	glViewport(0, 0, width, height);
	w = width;
	h = height;
	//Here's how to make matrices for transformations, check the documentation of GLM for rotation, scaling, and translation
	glm::mat4 projection = glm::perspective(60.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 30.0f);
	
	//Do something similar for u_modelMatrix before rendering things
	glUniformMatrix4fv(u_projLocation, 1, GL_FALSE, &projection[0][0]);
}

//from swiftless.com
char* MyGLWidget::textFileRead(const char* fileName) {
    char* text;
    
    if (fileName != NULL) {
        FILE *file = fopen(fileName, "rt");
        
        if (file != NULL) {
            fseek(file, 0, SEEK_END);
            int count = ftell(file);
            rewind(file);
            
            if (count > 0) {
                text = (char*)malloc(sizeof(char) * (count + 1));
                count = fread(text, sizeof(char), count, file);
                text[count] = '\0';	//cap off the string with a terminal symbol, fixed by Cory
            }
            fclose(file);
        }
    }
    return text;
}

void MyGLWidget::zoom(int x) {
	zoomValue = (x/10.0f)-1;
}

void MyGLWidget::pitch(int x) {
	pitchValue=x;
	rotateY = matrix(1.0f);
	rotateY = glm::rotate(rotateY,(float)x,glm::vec3(1.0f,0.0f,0.0f));

}

void MyGLWidget::yaw(int x) {
	yawValue = x;
	rotateX = matrix(1.0f);
	rotateX = glm::rotate(rotateX,(float)x,glm::vec3(0.0f,1.0f,0.0f));
}

void MyGLWidget::loadConfig(QString x) {
	QByteArray ba = x.toLatin1();
	const char* temp = ba.data();
	fileName = temp;
	if(fopen(fileName.c_str(),"r")) {
		processInput(fileName);
		rotateX = matrix(1.0f);
		rotateY = matrix(1.0f);
		camera = matrix(1.0f);
		pitchValue = -50;
		zoomValue = -6;
		yawValue = 0;
	}
}

void MyGLWidget::fillBuffers() {
	/*int vertexCount = 0;
	int indicesCount = 0;
	for(int i=0;i<meshVec.size();i++) {
		vertexCount += meshVec[i]->pointsVector.size();
		indicesCount += meshVec[i]->indicesVector.size();
	}
	// Fill Vertex Buffer //
	vec4* bufferPoints;
	bufferPoints = new vec4[vertexCount];
	int count = 0;
	for(int j=0;j<meshVec.size();j++) {
		for(int i=0;i<meshVec[j]->pointsVector.size();i++) {
			bufferPoints[count] = vec4(meshVec[j]->pointsVector[i].x,meshVec[j]->pointsVector[i].y,meshVec[j]->pointsVector[i].z,1.f);
			count++;
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount*sizeof(vec4), bufferPoints, GL_STATIC_DRAW);


	// Fill Color Buffer //
	vec4* bufferColor;
	bufferColor = new vec4[vertexCount];
	count = 0;
	for(int j=0;j<meshVec.size();j++) {
		for(int i=0;i<meshVec[j]->pointsVector.size();i++) {
			bufferColor[count] = vec4(0.5f,0.0f,0.5f,1.0f);
			count++;
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount*sizeof(vec4), bufferColor, GL_STATIC_DRAW);

	// Fill Normal Buffer //
	vec4* bufferNormals;
	bufferNormals = new vec4[vertexCount];
	count = 0;
	for(int j=0;j<meshVec.size();j++) {
		for(int i=0;i<meshVec[j]->normalsVector.size();i++) {
			bufferNormals[count] = vec4(meshVec[j]->normalsVector[i].x,meshVec[j]->normalsVector[i].y,meshVec[j]->normalsVector[i].z,0.f);
			count++;
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount*sizeof(vec4), bufferNormals, GL_STATIC_DRAW);
		
	// Fill Index Buffer //
	unsigned int* bufferIndices;
	bufferIndices = new unsigned int[indicesCount];
	count = 0;
	for(int j=0;j<meshVec.size();j++) {
		for(int i=0;i<meshVec[j]->indicesVector.size();i++) {
			bufferIndices[count] = meshVec[j]->indicesVector[i];
			count++;
		}
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount*sizeof(unsigned int), bufferIndices, GL_STATIC_DRAW);

	numIndices = indicesCount;

	delete bufferPoints;
	delete bufferColor;
	delete bufferNormals;
	delete bufferIndices;
	return;*/
}

void MyGLWidget::buildProcGeometry() {
	/*
	string text = textFileRead(fileName.c_str());
	stringstream s(text);
	string type;
	s >> type;
	meshVec.push_back(new Mesh());

	if(type == "extrusion") {
		meshVec[0]->calculateExtrusion(s);
	}
	else if(type == "surfrev") {
		meshVec[0]->calculateSurfRev(s);
	}
	fillBuffers();
	delete meshVec[0];
	meshVec.pop_back();*/
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
	w = floorx;
	h = floorz;
	string name;
	string meshFile;
	float transx, transz;
	float theta;
	float scalex, scaley, scalez;

	geoList* temp = new geoList();
	geoList* temp2;
	geoListRoot = temp;
	for(int i=0; i<iter; i++)
	{
		fin >> name;
		
		if(name == "table"){
			fin >> transx >> transz >> theta >> scalex >> scaley >> scalez;
			SceneGraph* s = new SceneGraph(&table, floorx, floorz, transx, 0, transz, theta, scalex, scaley, scalez, FURNITURE);
			temp2 = temp;
			temp->next = new geoList();
			temp->geo = s;
			temp = temp->next;
			temp->prev = temp2;
			root->addChild(s, transx, transz);
			currentCount++;
		}
		else if (name == "chair"){
			fin >> transx >> transz >> theta >> scalex >> scaley >> scalez;
			SceneGraph* s = new SceneGraph(&chair, floorx, floorz, transx, 0, transz, theta, scalex, scaley, scalez, FURNITURE);
			temp2 = temp;
			temp->next = new geoList();
			temp->geo = s;
			temp = temp->next;
			temp->prev = temp2;
			root->addChild(s, transx, transz);
			currentCount++;
		}
		else if (name == "box"){
			fin >> transx >> transz >> theta >> scalex >> scaley >> scalez;
			SceneGraph* s = new SceneGraph(&box, floorx, floorz, transx, 0, transz, theta, scalex, scaley, scalez, FURNITURE);
			temp2 = temp;
			temp->next = new geoList();
			temp->geo = s;
			temp = temp->next;
			temp->prev = temp2;
			root->addChild(s, transx, transz);
			currentCount++;
		}
		else if (name == "mesh") {
			int idk;
			fin >> meshFile >> idk >> transx >> transz >> theta >> scalex >> scaley >> scalez;
			Mesh* tempMesh = new Mesh(QString(meshFile.c_str()));
			tempMesh->init();
			tempMesh->fillBuffers();

			//tempMesh->init();
			//tempMesh->fileRead(meshFile);
			SceneGraph* s = new SceneGraph(tempMesh,floorx, floorz, transx, 0, transz, theta, scalex, scaley, scalez, MESH);
			temp2 = temp;
			temp->next = new geoList();
			temp->geo = s;
			temp = temp->next;
			temp->prev = temp2;
			root->addChild(s, transx, transz);
			currentCount++;
		}
	}
	temp = temp->prev;
	temp->next = geoListRoot;
	temp2 = temp;
	temp = temp->next;
	temp->prev = temp2;
	geoListCurrent = geoListRoot;
	temp->geo->setSelected(false);
	temp=temp->next;
	while(temp != geoListRoot) {
		temp->geo->setSelected(false);
		temp = temp->next;
	}
	geoListCurrent->geo->setSelected(true);

}


void MyGLWidget::nextGeo() {
	geoListCurrent->geo->setSelected(false); 
	geoListCurrent = geoListCurrent->next; 
	geoListCurrent->geo->setSelected(true);
	transXValue = 0;
	transZValue = 0;
}
void MyGLWidget:: prevGeo() {
	geoListCurrent->geo->setSelected(false); 
	geoListCurrent = geoListCurrent->prev; 
	geoListCurrent->geo->setSelected(true);
	transXValue = 0;
	transZValue = 0;
}

void MyGLWidget::GenerateRays(unsigned int resX, unsigned int resY)
{
	BMP output;
	output.SetSize(resX, resY);
	output.SetBitDepth(24);

	matrix rotX = glm::rotate(matrix(1.0f), pitchValue, vec3(1, 0, 0));
	matrix rotY = glm::rotate(matrix(1.0f), yawValue, vec3(0, 1, 0));

	mEyePos = rotY * rotX * vec4(0, 0, -zoomValue, 1);
	mUp = rotY * rotX * vec4(0, 1, 0, 0);

	//Generate rays	
	vec3 eyePos(mEyePos.x, mEyePos.y, mEyePos.z);

	//First, calculate m in the view plane
	vec3 M = vec3(0,0,0) - eyePos;
	M = normalize(M);


	//c is the vector from the plane to the camera
	vec3 C = M;

	//The angle we will use for calculating V & H
	float phi = 90.0f/2.0f;
	//float phi = 17.0f;

	//v and h vectors from
	vec3 V = vec3(mUp) * glm::tan(phi);
	V = -V;
	vec3 H = vec3(glm::rotate(glm::mat4(1.0f), -90.0f, C) * vec4(V.x, V.y, V.z, 0));
	H = H * (static_cast<float>(w)/static_cast<float>(h));

	//Now, generate each ray
	for(unsigned int x = 0; x < resX; x++)
	{
		for(unsigned int y = 0; y < resY; y++)
		{
			vec3 P = M + ((((2*x)/((float)(resX-1)))-1.0f)*H) + ((((2*y)/((float)(resY-1)))-1)*V);
			vec3 D = normalize(P - eyePos);

			vec3 color = rayTrace(eyePos, D, 0);

			output(x, y)->Red = color.r * 255;
			output(x, y)->Green = color.g * 255;
			output(x, y)->Blue = color.b * 255;
		}
	}

	output.WriteToFile("output.bmp");
}
vec3 MyGLWidget::rayTrace(vec3 p, vec3 v, int depth)
{
	vec3 col(0, 0, 0);
	vec3 normal(0, 0, 0);

	//float t = geoListRoot->geo->getGeometry()->intersectionTest(p, v, camera * geoListRoot->geo->getWorld(), normal);
	float t = root->getGeometry()->intersectionTest(p, v, camera * root->getWorld(), normal);
	if (t > 0) col = root->getGeometry()->getColor();

	int i = 0;
	for(geoList* c = geoListRoot; i < currentCount; i++)
	{
		vec3 localNormal(0, 0, 0);
		float r = c->geo->getGeometry()->intersectionTest(p, v, camera * c->geo->getWorld(), localNormal);
		if(r >= 0.0001/* && r < t*/)
		{
			if(t == -1 || r < t)
			{ 
				t = r;
				col = c->geo->getGeometry()->getColor();
				vec4 temp = camera * c->geo->getWorld() * vec4(localNormal.x, localNormal.y, localNormal.z, 0);
				normal = normalize(vec3(temp.x, temp.y, temp.z));
			}
		}
		c = c->next;
	}


	//Do the shadow feeler ray if the ray hits
	//Calculate the intersection point
	vec3 pt = p + t*v;
	vec3 dir = vec3(lightX, lightY, lightZ) - pt;

	if(t >= 0) {
		t = root->getGeometry()->intersectionTest(p, v, camera * root->getWorld(), normal);
		if (t > 0 && t < 1.0001) col = vec3(0,0,0);
		i = 0;
		for(geoList* c = geoListRoot; i < currentCount; i++)
		{
			vec3 localNormal(0, 0, 0);
			float r = c->geo->getGeometry()->intersectionTest(pt, dir, camera * c->geo->getWorld(), localNormal);
			if(r >= 0.01)
			{
				if(t == -1)
				{ 
					col = vec3(0,0,0);
					break;
				}
			}
			c = c->next;
		}
	}
	vec4 l(lightX,lightY,lightZ, 1);
	l = camera * l;
	vec3 lpos(l.x, l.y, l.z);
	vec3 lVec = normalize(lpos - pt);
	vec3 vVec = normalize(p - pt);
	vec3 hVec = normalize(lVec + vVec);
	
	float diffuseTerm = std::max(dot(lpos, normal), 0.0f);
	float specTerm = pow(std::max(glm::dot(hVec, normal), 0.0f), 128);

	//if(depth == 3 || t < 0) return col;

	//vec4 rotatedV = glm::rotate(mat4(1.0f), 180.0f, normal) * vec4(v.x, v.y, v.z, 0);
	//vec3 rV(rotatedV.x, rotatedV.y, rotatedV.z);
	//return rayTrace(pt, rV, depth+1) * diffuseTerm + vec3(1, 1, 1) * specTerm;
	return col * diffuseTerm + vec3(1, 1, 1) * specTerm;
}
void MyGLWidget::RayTrace()
{
	GenerateRays(150, 150);
}
void MyGLWidget::subdivide() {
	geoListCurrent->geo->subdivide();
}