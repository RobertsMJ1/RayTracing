#pragma once
#define GLEW_STATIC

#include "../glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "constants.h"
#include <stdlib.h>
#include <fstream>
using std::ifstream;
#include <stdio.h>
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;
using glm::inverse;
using glm::dot;
using glm::cross;
using glm::normalize;
using glm::determinant;


inline char* textFileRead(const char* fileName) {
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

class Geometry
{
public:
	virtual void init() = 0;
	virtual void draw(Vec4 color = WHITE) = 0;
	virtual float getHeight() = 0;
	virtual float intersectionTest(const vec3& p, const vec3& v, const mat4& m) = 0;
	virtual vec3 getColor() = 0;

	void setTransX(float t){transX = t;}
	void setTransY(float t){transY = t;}
	void setTransZ(float t){transZ = t;}
	float getTransX(){return transX;}
	float getTransY(){return transY;}
	float getTransZ(){return transZ;}

	void setRotX(float r){rotX = r;}
	void setRotY(float r){rotY = r;}
	void setRotZ(float r){rotZ = r;}
	float getRotX(){return rotX;}
	float getRotY(){return rotY;}
	float getRotZ(){return rotZ;}

	void setScaleX(float s){scaleX = s;}
	void setScaleY(float s){scaleY = s;}
	void setScaleZ(float s){scaleZ = s;}
	float getScaleX(){return scaleX;}
	float getScaleY(){return scaleY;}
	float getScaleZ(){return scaleZ;}

	Matrix getWorld(){return world;}
	void setWorld(Matrix w){world = w;}

	void setReflectivity(float r){reflectivity = r;}
	float getReflectivity(){return reflectivity;}



protected:

	Matrix world;
	float transX, transY, transZ;
	float rotX, rotY, rotZ;
	float scaleX, scaleY, scaleZ;

	float height;

	float reflectivity;
};

float triangleArea(const vec3& p0, const vec3& p1, const vec3& p2);
