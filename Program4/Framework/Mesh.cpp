/***********************
Author: David Goehring
Course: COMP361
Date: 4/4/14
Description: Mesh Implementation
Half-Edge by James McKay
***********************/
#include "Mesh.h"

Mesh::Mesh()
{
	this->pointsInIndex = 0;

	transX = 0;
	transY = 0;
	transZ = 0;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
}

void Mesh::init() {
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &cbo);
	glGenBuffers(1, &ibo);
	glGenBuffers(1, &nbo);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();

	const char* vertexSource = textFileRead(VERTEX_SHADER);
	const char* fragmentSource = textFileRead(FRAGMENT_SHADER);
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
}
Mesh::Mesh(QString filename)
{
	faces = new NewFace[1000];
	int startFace = 0;
	int slices;
	float height;
	faceCount = 0;

	ifstream reader(filename.toStdString());
	unsigned int count;
	string kind ="asd";

	reader >> kind;
	extruding = false;
	if (kind == "extrusion")
	{
		extruding = true;
		reader >> height;
	}
	else
	{
		reader >> slices;
	}

	reader >> count;
	faces[startFace].edgeCount = 0;
	faces[startFace].edge = new HalfEdge;
	faceCount++;
	HalfEdge *refEdge = faces[startFace].edge;
	refEdge->face = &faces[startFace];

	for(unsigned int i = 0; i < count; i++) {
		float x, y, z;
		if (extruding)
		{
			y = 0.0;
			reader >> x >> z;
		}
		else
		{
			z = 0;
			reader >> x >> y;
		}

		refEdge->face = &faces[startFace];
		refEdge->vertex = new Vertex;
		refEdge->vertex->color = glm::vec3(1,0,0);
		refEdge->vertex->position = vec4(x,y,z,1.0f);
		if (i < count - 1)
		{
			refEdge->next = new HalfEdge;
			refEdge->next->prev = refEdge;
			refEdge = refEdge->next;
		}
		else
		{
			refEdge->next = faces[0].edge;
			faces[startFace].edge->prev = refEdge;
		}
	}
	faces[startFace].edgeCount = count;

	faces[faceCount].edge = new HalfEdge;
	faces[faceCount].edge->face = &faces[faceCount];
	faces[faceCount].edgeCount = 0;
	refEdge = faces[faceCount].edge;

	HalfEdge *oldRef = faces[0].edge;
	for(unsigned int i = 0; i < count; i++) {

		refEdge->face = &faces[faceCount];
		refEdge->vertex = new Vertex;
		refEdge->vertex->color = glm::vec3(1,0,0);
		refEdge->vertex->position = vec4(oldRef->vertex->position.x, oldRef->vertex->position.y + height, oldRef->vertex->position.z,1.0f);
		if (i < count - 1)
		{
			refEdge->next = new HalfEdge;
			refEdge->next->prev = refEdge;
			refEdge = refEdge->next;
			oldRef = oldRef->next;
		}
		else
		{
			refEdge->next = faces[faceCount].edge;
			faces[faceCount].edge->prev = refEdge;
		}
	}

	faces[faceCount].edgeCount = count;
	faceCount++;

	HalfEdge *botRef, *topRef;
	botRef = faces[0].edge;
	topRef = faces[1].edge;
	HalfEdge *find = botRef->next->next;

	for(int i = 0; i < count; i++)
	{
		faces[faceCount].edge = new HalfEdge;
		refEdge = faces[faceCount].edge;
		refEdge->face = &faces[faceCount];

		if (i > 0)
		{
			refEdge->sym = faces[faceCount-1].edge->next->next;
			faces[faceCount-1].edge->next->next->sym = refEdge;
		}

		refEdge->vertex = new Vertex;
		refEdge->vertex->color = glm::vec3(1,0,0);
		refEdge->vertex->position = botRef->vertex->position;
		refEdge->next = new HalfEdge;
		refEdge->next->prev = refEdge;
		refEdge = refEdge->next;

		refEdge->face = &faces[faceCount];
		refEdge->vertex = new Vertex;
		refEdge->vertex->color = glm::vec3(1,0,0);
		refEdge->vertex->position = botRef->next->vertex->position;
		refEdge->sym = find;
		find->sym = refEdge;
		find = find->next;
		refEdge->next = new HalfEdge;
		refEdge->next->prev = refEdge;
		refEdge = refEdge->next;

		refEdge->face = &faces[faceCount];
		refEdge->vertex = new Vertex;
		refEdge->vertex->color = glm::vec3(1,0,0);
		refEdge->vertex->position = topRef->next->vertex->position;
		if (i == count-1)
		{
			refEdge->sym = faces[startFace+2].edge;
			faces[startFace+2].edge->sym = refEdge;
		}
		refEdge->next = new HalfEdge;
		refEdge->next->prev = refEdge;
		refEdge = refEdge->next;

		refEdge->face = &faces[faceCount];
		refEdge->vertex = new Vertex;
		refEdge->vertex->color = glm::vec3(1,0,0);
		refEdge->vertex->position = topRef->vertex->position;
		refEdge->next = faces[faceCount].edge;
		refEdge->next->prev = refEdge;

		topRef = topRef->next;
		botRef = botRef->next;
		
		faces[faceCount].edgeCount = 4;
		faceCount++;
	}

	
	HalfEdge *temp;
	refEdge = faces[1].edge;
	temp = refEdge->next;
	refEdge->next = refEdge->prev;
	refEdge->prev = temp;
	refEdge->sym = faces[startFace + 2].edge->next->next->next;
	faces[startFace + 2].edge->next->next->next->sym = refEdge;

	for (int i = 0; i < faces[1].edgeCount-1; i++)
	{
		refEdge = refEdge->next;
		refEdge->sym = faces[startFace + 3 + i].edge->next->next->next;
		faces[startFace + 3 + i].edge->next->next->next->sym = refEdge;
		temp = refEdge->next;
		refEdge->next = refEdge->prev;
		refEdge->prev = temp;
	}
}

void Mesh::fillBuffers()
{
	faceCount--;
	pointsInBuffer = 0;
	pointsInIndex = 0;
	for (int i = 0; i < faceCount; i++)
	{
		pointsInIndex += (faces[i].edgeCount-2)*3;
		pointsInBuffer += faces[i].edgeCount;
	}

	points = new glm::vec4[pointsInBuffer];
	normals = new glm::vec4[pointsInBuffer];
	colors = new glm::vec3[pointsInBuffer];
	indices = new unsigned int[pointsInIndex];

	int startIndex = 0;
	int rollingIndex = 0;
	int buffIndex = 0;

	for (int i = 0; i < faceCount; i++)
	{
		HalfEdge *refEdge = faces[i].edge;

		glm::vec3 first(refEdge->next->vertex->position - refEdge->vertex->position);
		glm::vec3 second(refEdge->next->next->vertex->position - refEdge->next->vertex->position);
		glm::vec3 normalTemp = glm::cross(first,second);

		glm::vec4 normal = glm::vec4(normalTemp.x,normalTemp.y,normalTemp.z,0);
		if (normal.x == 0 && normal.y == 0 && normal.z == 0)
		{
			first = glm::vec3(refEdge->next->next->vertex->position - refEdge->next->vertex->position);
			second = glm::vec3(refEdge->next->next->next->vertex->position - refEdge->next->next->vertex->position);
			normalTemp = glm::vec3(glm::cross(first,second));

			normal = glm::vec4(normalTemp.x,normalTemp.y,normalTemp.z,0);
		}
		normal = glm::normalize(normal);

		faces[i].normal = normal;
	}
	for(int i = 0; i < faceCount; i++)
	{
		HalfEdge *refEdge = faces[i].edge;

		glm::vec3 first(refEdge->next->vertex->position - refEdge->vertex->position);
		glm::vec3 second(refEdge->next->next->vertex->position - refEdge->next->vertex->position);
		glm::vec3 normalTemp = glm::cross(first,second);

		glm::vec4 normal = glm::vec4(normalTemp.x,normalTemp.y,normalTemp.z,0);

		refEdge->vertex->normal = refEdge->face->normal;

		HalfEdge *edgeP = refEdge->next;

		points[buffIndex] = refEdge->vertex->position;
		normals[buffIndex] = refEdge->vertex->normal;
		colors[buffIndex] = refEdge->vertex->color;
		buffIndex++;
		while(edgeP != refEdge)
		{
			edgeP->vertex->normal = normal;

			edgeP->face = &faces[i];

			points[buffIndex] = edgeP->vertex->position;
			normals[buffIndex] = edgeP->vertex->normal;
			colors[buffIndex] = edgeP->vertex->color;
			buffIndex++;

			edgeP = edgeP->next;
		}

		for(int j = 0; j < faces[i].edgeCount-2; j++)
		{
			indices[rollingIndex] = startIndex;
			rollingIndex++;
			indices[rollingIndex] = startIndex+j+1;
			rollingIndex++;
			indices[rollingIndex] = startIndex+j+2;
			rollingIndex++;
		}

		startIndex += faces[i].edgeCount;
	}
}

void Mesh::draw(Vec4 c) {
	

	// Fill Vertex Buffer //
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, pointsInBuffer*sizeof(vec4), points, GL_STATIC_DRAW);


	// Fill Color Buffer //
	vec4* bufferColor;
	bufferColor = new vec4[pointsInBuffer];
	for(int i=0;i<pointsInBuffer;i++) {
		if(selected) {
			bufferColor[i] = ORANGE;
		}
		else {
			bufferColor[i] = c;
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, pointsInBuffer*sizeof(vec4), bufferColor, GL_STATIC_DRAW);

	// Fill Normal Buffer //
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, pointsInBuffer*sizeof(vec4), normals, GL_STATIC_DRAW);

	// Fill Index Buffer //
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pointsInIndex*sizeof(unsigned int), indices, GL_STATIC_DRAW);

	delete bufferColor;

	glUniformMatrix4fv(u_modelMatrix, 1, GL_FALSE, &world[0][0]);
	
	glDrawElements(GL_TRIANGLES, pointsInIndex, GL_UNSIGNED_INT, 0);
}

float Mesh::intersectionTest(const vec3& P, const vec3& V, const mat4& m, vec3& normal)
{
	float result = -1;
	for(int i=0; i<pointsInIndex-2; i+= 3)
	{
		vec4 tp1 = points[indices[i]];
		vec4 tp2 = points[indices[i+1]];
		vec4 tp3 = points[indices[i+2]];
		vec3 p1 = vec3(tp1.x, tp1.y, tp1.z);
		vec3 p2 = vec3(tp2.x, tp2.y, tp2.z);
		vec3 p3 = vec3(tp3.x, tp3.y, tp3.z);
		// TODO fill this in.
		// See the documentation of this function in stubs.h.
		float t = 1e26;
		vec4 p4(P, 1);
		vec4 v4(V, 0);
		p4 = inverse(m) * p4;
		v4 = inverse(m) * v4;
		vec3 s(p4.x, p4.y, p4.z);
		vec3 v(v4.x, v4.y, v4.z);

		vec3 N = cross(p3-p1, p2-p1);
		N = normalize(N);
	
		double denominator = dot(N, v);
		//denominator = abs(denominator);
		float epsilon = 0.0001;
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
				//return t;
				if(t < result || result == -1) result = t;
			}
			//else return -1;
		}
	}
	return result;
}