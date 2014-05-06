#include "Box.h"

Box::Box()
{
	world = Matrix(1.0f);
	edge = 1.0;
	height = edge;
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

Box::~Box()
{
}

void Box::init()
{
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

	//Front
	points[0] = glm::vec4(-0.5, 0, 0.5, 1);
	points[1] = glm::vec4(-0.5, 1, 0.5, 1);
	points[2] = glm::vec4(0.5, 1, 0.5, 1);
	points[3] = glm::vec4(0.5, 0, 0.5, 1);
	
	normals[0] = glm::vec4(0, 0, 1, 0);
	normals[1] = glm::vec4(0, 0, 1, 0);
	normals[2] = glm::vec4(0, 0, 1, 0);
	normals[3] = glm::vec4(0, 0, 1, 0);
	
	//Left
	points[4] = glm::vec4(-0.5, 0, 0.5, 1);
	points[5] = glm::vec4(-0.5, 1, 0.5, 1);
	points[6] = glm::vec4(-0.5, 1, -0.5, 1);
	points[7] = glm::vec4(-0.5, 0, -0.5, 1);
	
	normals[4] = glm::vec4(-1, 0, 0, 0);
	normals[5] = glm::vec4(-1, 0, 0, 0);
	normals[6] = glm::vec4(-1, 0, 0, 0);
	normals[7] = glm::vec4(-1, 0, 0, 0);

	//Right
	points[8] = glm::vec4(0.5, 0, 0.5, 1);
	points[9] = glm::vec4(0.5, 1, 0.5, 1);
	points[10] = glm::vec4(0.5, 1, -0.5, 1);
	points[11] = glm::vec4(0.5, 0, -0.5, 1);
	
	normals[8] = glm::vec4(1, 0, 0, 0);
	normals[9] = glm::vec4(1, 0, 0, 0);
	normals[10] = glm::vec4(1, 0, 0, 0);
	normals[11] = glm::vec4(1, 0, 0, 0);
	
	//Back
	points[12] = glm::vec4(-0.5, 0, -0.5, 1);
	points[13] = glm::vec4(-0.5, 1, -0.5, 1);
	points[14] = glm::vec4(0.5, 1, -0.5, 1);
	points[15] = glm::vec4(0.5, 0, -0.5, 1);

	normals[12] = glm::vec4(0, 0, -1, 0);
	normals[13] = glm::vec4(0, 0, -1, 0);
	normals[14] = glm::vec4(0, 0, -1, 0);
	normals[15] = glm::vec4(0, 0, -1, 0);
	//Bottom
	points[16] = glm::vec4(-0.5, 0, -0.5, 1);
	points[17] = glm::vec4(-0.5, 0, 0.5, 1);
	points[18] = glm::vec4(0.5, 0, 0.5, 1);
	points[19] = glm::vec4(0.5, 0, -0.5, 1);

	normals[16] = glm::vec4(0, -1, 0, 0);
	normals[17] = glm::vec4(0, -1, 0, 0);
	normals[18] = glm::vec4(0, -1, 0, 0);
	normals[19] = glm::vec4(0, -1, 0, 0);

	//Top
	points[20] = glm::vec4(-0.5, 1, -0.5, 1);
	points[21] = glm::vec4(-0.5, 1, 0.5, 1);
	points[22] = glm::vec4(0.5, 1, 0.5, 1);
	points[23] = glm::vec4(0.5, 1, -0.5, 1);

	normals[20] = glm::vec4(0, 1, 0, 0);
	normals[21] = glm::vec4(0, 1, 0, 0);
	normals[22] = glm::vec4(0, 1, 0, 0);
	normals[23] = glm::vec4(0, 1, 0, 0);

	indices[0] = 0;
	indices[1] = 2;
	indices[2] = 1;
	indices[3] = 0;
	indices[4] = 3;
	indices[5] = 2;
	indices[6] = 4;
	indices[7] = 5;
	indices[8] = 6;
	indices[9] = 7;
	indices[10] = 4;
	indices[11] = 6;
	indices[12] = 8;
	indices[13] = 10;
	indices[14] = 9;
	indices[15] = 8;
	indices[16] = 11;
	indices[17] = 10;
	indices[18] = 12;
	indices[19] = 15;
	indices[20] = 14;
	indices[21] = 12;
	indices[22] = 14;
	indices[23] = 13;
	indices[24] = 17;
	indices[25] = 18;
	indices[26] = 16;
	indices[27] = 18;
	indices[28] = 19;
	indices[29] = 16;
	indices[30] = 22;
	indices[31] = 21;
	indices[32] = 20;
	indices[33] = 22;
	indices[34] = 20;
	indices[35] = 23;

	
}

void Box::draw(Vec4 c)
{
	Vec4 color = c; 
	
	if(color == WHITE) {
		color = YELLOW;
	}
	glm::vec4 colors[24] = {
		//Front
		color,color,color,color,
		//Back 
		color,color,color,color,
		//Left
		color,color,color,color,
		//Right
		color,color,color,color,
		//Bottom
		color,color,color,color,
		//Top
		color,color,color,color
	};


	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(glm::vec4), points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(vLocation);
	glVertexAttribPointer(vLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(glm::vec4), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(nLocation);
	glVertexAttribPointer(nLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(glm::vec4), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(cLocation);
	glVertexAttribPointer(cLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	/*glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(glm::vec4), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(cLocation);
	glVertexAttribPointer(cLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);*/

	glUniformMatrix4fv(u_modelMatrix, 1, GL_FALSE, &world[0][0]);
	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

float Box::intersectionTest(const vec3& P, const vec3& V, const mat4& m, vec3& normal)
{
	float result = -1;
	for(int i=0; i<36-2; i+= 3)
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
				if(t < result || result == -1) {
					normal = N;
					result = t;
				}
			}
			//else return -1;
		}
	}
	return result;
}