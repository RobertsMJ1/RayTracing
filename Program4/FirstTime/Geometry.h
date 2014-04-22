#pragma once
#include "../glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "constants.h"
#include <stdlib.h>
#include <fstream>
using std::ifstream;
#include <stdio.h>

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
	virtual void draw(Vec4 color = YELLOW) = 0;
	virtual float getHeight() = 0;

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

protected:

	Matrix world;
	float transX, transY, transZ;
	float rotX, rotY, rotZ;
	float scaleX, scaleY, scaleZ;

	float height;
};

