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

	//Vec4 l4(light, 1);
	//l4 = camera * l4;
	//light = Vec3(l4);
	glm::vec4 l(lightX,lightY,lightZ, 1);
	l = camera * l;
	glUniform4fv(u_lightLocation, 1, &l[0]);
	glUniform4fv(u_eyeLocation, 1, &mEyePos[0]);
	
	//box.setWorld(camera);
	//chair.setWorld(camera);
	//table.setWorld(camera);
	//floor.setWorld(camera);
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
	glm::mat4 projection = glm::perspective(45.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 30.0f);
	
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

vec3 MyGLWidget::rayTrace(unsigned int resX, unsigned int resY)
{
	BMP output;
	output.SetSize(resX, resY);
	output.SetBitDepth(24);

	//Generate ray
	//First, calculate m in the view plane
	vec3 m = vec3(0,0,0) - vec3(mEyePos);
	m = glm::normalize(m);

	//c is the vector from the plane to the camera
	vec3 c = m;
	m += vec3(mEyePos);

	//The angle we will use for calculating V & H
	float halfy = 45.0f/2.0f;
	//float halfy = (PI/4.0f)/2.0f;

	//v and h vectors from
	vec3 v = vec3(mUp) * glm::tan(halfy);
	//vec3 v = vec3(0, 1, 0) * glm::tan(halfy);

	//Suggested by boatright, rotate v 90% and scale by aspect ratio
	vec3 h = vec3(glm::rotate(glm::mat4(1.0f), 90.0f, c) * vec4(v, 0));
	h = h * static_cast<float>(resX)/static_cast<float>(resY);

	//Now, generate each ray
	for(unsigned int x = 0; x < resX; x++)
	{
		for(unsigned int y = 0; y < resY; y++)
		{
			vec3 p = m + ((2.0f*x/static_cast<float>(resX-1.0f))-1.0f)*h + ((2.0f*y/static_cast<float>(resY-1.0f))-1.0f)*v;
			
			vec3 D = glm::normalize(p-vec3(mEyePos));

			//So, the ray is defined to have origin of mEyePos and direction D.
			//For each ray, cycle through all geometry and do intersection tests
			float t = geoListRoot->geo->getGeometry()->intersectionTest(vec3(mEyePos), D, camera * geoListRoot->geo->getWorld());
			vec3 col(0, 0, 0);
			for(geoList* c = geoListRoot; c->next != geoListRoot; c = c->next)
			{
				float r = c->geo->getGeometry()->intersectionTest(vec3(mEyePos), D, camera * c->geo->getWorld());
				if(r >= 0/* && r < t*/)
				{
					if(t == -1 || r < t)
					{ 
						t = r;
						col = c->geo->getGeometry()->getColor();
					}
				}
			}

			////Do the shadow feeler ray if the ray hits
			//if(t >= 0) {
			//	//Calculate the intersection point
			//	vec3 point = vec3(mEyePos) + t*D;
			//	vec3 dir = vec3(lightX, lightY, lightZ) - point;

			//	t = geoListRoot->geo->getGeometry()->intersectionTest(p, D, geoListRoot->geo->getWorld());
			//	
			//	for(geoList* c = geoListRoot; c->next != geoListRoot; c = c->next)
			//	{
			//		//if we intersect at a time in (0, 1] short-circuit and set the point to black
			//		float r = c->geo->getGeometry()->intersectionTest(p, D, c->geo->getWorld());
			//		if(r < 1 && r > 0.0001)
			//		{
			//			col = vec3(0, 0, 0);
			//			break;
			//		}
			//	}
			//}
			//col  = vec3(0, 1, 0);
			//Now, draw that color at that pixel?
			output(x, y)->Red = col.r * 255;
			output(x, y)->Green = col.g * 255;
			output(x, y)->Blue = col.b * 255;
		}
	}

	output.WriteToFile("output.bmp");

	return vec3(1, 0, 1);
}

void MyGLWidget::RayTrace()
{
	rayTrace(570, 570);
}

float MyGLWidget::RaySphereIntersect(const vec3& P0, const vec3& V0, const Matrix& T) {
	// TODO fill this in.
	// See the documentation of this function in stubs.h.
	float t1 = 1e26, t2 = 1e26;
	vec4 p4(P0, 1);
	vec4 v4(V0, 0);
	p4 = inverse(T) * p4;
	v4 = inverse(T) * v4;
	vec3 s(p4.x, p4.y, p4.z);
	vec3 v(v4.x, v4.y, v4.z);

	double a = 1.0f;
	double b = dot(2.0f*v, s);
	double c = pow(length(s), 2) - 1;
	
	double d = pow(b, 2) - (4*a*c);

	if(d >= 0)t1 = (-b + sqrt(d))/(2*a);
	if(d >= 0)t2 = (-b - sqrt(d))/(2*a);

	if(d >= 0 - epsilon && d <= 0 + epsilon) return 1e26;
	if(t1 < 0 && t2 < 0) return -1;
	if(t1 > 0 || t2 > 0) 
	{
		if(t1 < 0) return t2;
		if(t2 < 0) return t1;
		return std::min(t1, t2);
	}
	//else return min(t1, t2);
}
float MyGLWidget::RayPolyIntersect(const vec3& P0, const vec3& V0, const vec3& p1, const vec3& p2, const vec3& p3, const Matrix& T) {
	// TODO fill this in.
	// See the documentation of this function in stubs.h.
	float t = 1e26;
	vec4 p4(P0, 1);
	vec4 v4(V0, 0);
	p4 = inverse(T) * p4;
	v4 = inverse(T) * v4;
	vec3 s(p4.x, p4.y, p4.z);
	vec3 v(v4.x, v4.y, v4.z);

	vec3 N = cross(p3-p1, p2-p1);
	N = normalize(N);
	
	double denominator = dot(N, v);
	//denominator = abs(denominator);
	if(abs(denominator) >= 0)
	{
		t = (dot(N, p1-s))/denominator;
		vec3 p = s + t*v;
		
		double area_whole = triangleArea(p1, p2, p3);
		double area1 = triangleArea(p, p2, p3)/area_whole;
		double area2 = triangleArea(p, p3, p1)/area_whole;
		double area3 = triangleArea(p, p1, p2)/area_whole;
		if(area1 + area2 + area3 <= 1 + epsilon && area1 + area2 + area3 >= 1 - epsilon)
		{
			return t;
		}
		else return -1;
	}

	return -1;
}
float MyGLWidget::triangleArea(const vec3& p0, const vec3& p1, const vec3& p2)
{
	mat3 m1(p0.y, p1.y, p2.y,
			p0.z, p1.z, p2.z,
			1,    1,    1);
	mat3 m2(p0.z, p1.z, p2.z,
			p0.x, p1.x, p2.x,
			1,    1,    1);
	mat3 m3(p0.x, p1.x, p2.x,
			p0.y, p1.y, p2.y,
			1,    1,    1);
	return sqrt(pow(determinant(m1), 2) + pow(determinant(m2),2) + pow(determinant(m3), 2))/2.0f;
}
float MyGLWidget::RayCubeIntersect(const vec3& P0, const vec3& V0, const Matrix& T) {
	// TODO fill this in.
	// See the documentation of this function in stubs.h.
	float t = -1;
	vec4 p4(P0, 1);
	vec4 v4(V0, 0);
	p4 = inverse(T) * p4;
	v4 = inverse(T) * v4;
	vec3 s(p4.x, p4.y, p4.z);
	vec3 v(v4.x, v4.y, v4.z);

	double tnear = -1e26;
	double tfar = 1e26;

	//x-plane
	if(v.x != 0)
	{
		double t1 = (-0.5-s.x) / v.x;
		double t2 = (0.5 - s.x) / v.x;
		if(t1 > t2)
		{
			double temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if(t1 > tnear) tnear = t1;
		if(t2 < tfar) tfar = t2;
		if(tnear > tfar) 
			return t;
		if(tfar < 0) 
			return t;
	}
	//y-plane
	if(v.y != 0)
	{
		double t1 = (-0.5-s.y) / v.y;
		double t2 = (0.5 - s.y) / v.y;
		if(t1 > t2)
		{
			double temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if(t1 > tnear) tnear = t1;
		if(t2 < tfar) tfar = t2;
		if(tnear > tfar) 
			return t;
		if(tfar < 0) 
			return t;
	}
	//z-plane
	if(v.z != 0)
	{
		double t1 = (-0.5-s.z) / v.z;
		double t2 = (0.5 - s.z) / v.z;
		if(t1 > t2)
		{
			double temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if(t1 > tnear) tnear = t1;
		if(t2 < tfar) tfar = t2;
		if(tnear > tfar)
			return t;
		if(tfar < 0) 
			return t;
	}

	if(tnear < -1e25) return -1;

	vec3 finalpt = s + ((float)tnear * v);
	if(finalpt.x > 0.5 + epsilon || finalpt.x < -0.5 - epsilon || finalpt.y > 0.5 + epsilon || finalpt.y < -0.5 - epsilon || finalpt.z > 0.5 + epsilon || finalpt.z < -0.5 - epsilon) 
		return -1;

	return tnear;
}
