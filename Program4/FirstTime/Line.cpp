#include "Line.h"

Line::Line()
{
	world = Matrix(1.0f);
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

Line::~Line()
{
}

void Line::init()
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
	points[0] = glm::vec4(0, 0, 0, 1);
	points[1] = glm::vec4(1, 0, 0, 1);
	
	
}

void Line::draw(Vec4 color)
{
	glm::vec4 colors[2] = {
		//Front
		color,color
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec4), points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(vLocation);
	glVertexAttribPointer(vLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec4), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(cLocation);
	glVertexAttribPointer(cLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glUniformMatrix4fv(u_modelMatrix, 1, GL_FALSE, &world[0][0]);
	
	glDrawElements(GL_LINE, 2, GL_UNSIGNED_INT, 0);
}