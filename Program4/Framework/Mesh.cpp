/***********************
Author: David Goehring
Course: COMP361
Date: 4/4/14
Description: Mesh Implementation
***********************/
#include "Mesh.h"

Mesh::Mesh() {

}

Mesh::~Mesh() {

}

void Mesh::calculateExtrusion(std::stringstream& s) {
	int count;
	float height;
	unsigned int indexCount = 0;

	s >> height >> count; 
	count = count - 1;
	vector<vec3> vertices;
	for(int i=0;i<count;i++) {
		float temp1,temp2;
		s >> temp1 >> temp2;
		vec3 tempvec(temp1,0.f,temp2);
		vertices.push_back(tempvec);
	}

	// Convexity Test //
	bool convex;
	vec3 vec1 = vertices[1] - vertices[0];
	vec3 vec2 = vertices[0] - vertices[count-1];
	vec3 n = glm::normalize(glm::cross(vec1,vec2));
	for(int i=1;i<count-1;i++) {
		vec1 = vertices[i+1] - vertices[i];
		vec2 = vertices[i] - vertices[i-1];
		vec3 test = glm::normalize(glm::cross(vec1,vec2));
		if(test != n) {
			convex = false;
			break;
		}
		else convex = true;
	}

	// Create Second Face //
	vector<vec3> vertices2;
	for(int i=0;i<count;i++) {
		vec3 temp(vertices[i].x,height,vertices[i].z);
		vertices2.push_back(temp);
	}

	
	// Triangluate End Faces //
	if(convex) {
		for(int i=1;i<count-1;i++) {
			pointsVector.push_back(vertices[0]);
			pointsVector.push_back(vertices[i]);
			pointsVector.push_back(vertices[i+1]);
			
			calculateFace(vertices[0],vertices[i],vertices[i+1]);

			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+1);
			indicesVector.push_back(indexCount+2);
			indexCount+=3;
		}
		for(int i=1;i<count-1;i++) {
			pointsVector.push_back(vertices2[0]);
			pointsVector.push_back(vertices2[i]);
			pointsVector.push_back(vertices2[i+1]);
			
			calculateFace(vertices2[0],vertices2[i+1],vertices2[i]);

			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+1);
			indicesVector.push_back(indexCount+2);
			indexCount+=3;
		}
	}
	// Triangulate Walls //
	pointsVector.push_back(vertices[count-1]);
	pointsVector.push_back(vertices2[count-1]);
	pointsVector.push_back(vertices2[0]);
	pointsVector.push_back(vertices[0]);

	calculateFace(vertices[count-1],vertices2[count-1],vertices2[0],vertices[0]);

	indicesVector.push_back(indexCount);
	indicesVector.push_back(indexCount+1);
	indicesVector.push_back(indexCount+2);
	indicesVector.push_back(indexCount);
	indicesVector.push_back(indexCount+2);
	indicesVector.push_back(indexCount+3);

	indexCount+=4;

	for(int i=0;i<count-1;i++) {
		pointsVector.push_back(vertices[i]);
		pointsVector.push_back(vertices2[i]);
		pointsVector.push_back(vertices2[i+1]);
		pointsVector.push_back(vertices[i+1]);
		
		calculateFace(vertices[i],vertices2[i],vertices2[i+1],vertices[i+1]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+2);
		indicesVector.push_back(indexCount+3);
		indexCount+=4;
	}


}

void Mesh::calculateSurfRev(std::stringstream& s) {
	int slices;
	int count;
	unsigned int indexCount = 0;
	bool topY = false;
	bool bottomY = false;
	bool endcaps;
	s >> slices >> count;
	vector<vec3> vertices;
	//vector<Face*> faces;

	float temp1, temp2;
	for(int i=0;i<count;i++) {
		s >> temp1 >> temp2;
		if(i==0&&temp1==0) bottomY = true;
		if(i==count-1&&temp1==0) topY = true;
		vertices.push_back(vec3(temp1,temp2,0.f));
	}
	if(vertices[0]==vertices[count-1]) endcaps = false;
	else endcaps = true;

	// Top and Bottom Vertices Touch Y-Axis //
	if(topY && bottomY) {
		surfRevBoth(count,slices,vertices);
	}
	// Only Bottom Vertex Touches Y-Axis //
	else if(bottomY) {
		surfRevBottom(count,slices,vertices);
	}
	//Only Top Vertex Touches Y-Axis //
	else if(topY) {
		surfRevTop(count,slices,vertices);
	}
	// Neither Vertex Touches Y-Axis //
	else {
		surfRevNone(count,slices,vertices,endcaps);
	}

	return;
}

void Mesh::calculateFace(vec3 v1, vec3 v2, vec3 v3) {
	faces.push_back(new Face(v1,v2,v3));
		
	vec3 temp1 = v2 - v1;
	vec3 temp2 = v3 - v1;
	vec3 normal = glm::normalize(glm::cross(temp1,temp2));
	for(int j=0;j<3;j++) normalsVector.push_back(normal);
}

void Mesh::calculateFace(vec3 v1, vec3 v2, vec3 v3, vec3 v4) {
	faces.push_back(new Face(v1,v2,v3));
	faces.push_back(new Face(v1,v3,v4));

	vec3 temp1 = v2 - v1;
	vec3 temp2 = v4 - v1;
	vec3 normal = glm::normalize(glm::cross(temp1,temp2));
	for(int j=0;j<4;j++) normalsVector.push_back(normal);
}

void Mesh::surfRevTop(int count, int slices, vector<vec3> vertices) {
	float step = 360.0f / (float)slices;
	unsigned int indexCount = 0;
	for(int i=1;i<slices;i++) {
		for(int j=0;j<count-1;j++) {
			vec4 temp = vec4(vertices[j].x, vertices[j].y, vertices[j].z, 1.0f);
			matrix rot = glm::rotate(matrix(1.0f),i*step,vec3(0,1,0));
			temp = temp*rot;
			vertices.push_back(vec3(temp.x,temp.y,temp.z));
		}
	}
	// Bottom Shape //
	for(int i=0;i<slices-2;i++) {
		pointsVector.push_back(vertices[0]);
		pointsVector.push_back(vertices[count+(i)*(count-1)]);
		pointsVector.push_back(vertices[count+(i+1)*(count-1)]);

		calculateFace(vertices[0],vertices[count+(i)*(count-1)],vertices[count+(i+1)*(count-1)]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indexCount+=3;
	}
	// Walls //
	for(int i=0;i<count-2;i++) {
		pointsVector.push_back(vertices[i+1]);
		pointsVector.push_back(vertices[i]);
		pointsVector.push_back(vertices[(slices-2)*(count-1)+count+i]);
		pointsVector.push_back(vertices[(slices-2)*(count-1)+count+i+1]);

		calculateFace(vertices[i+1],vertices[i],vertices[(slices-2)*(count-1)+count+i],vertices[(slices-2)*(count-1)+count+i+1]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+2);
		indicesVector.push_back(indexCount+3);
		indexCount+=4;
	}
	for(int i=0;i<count-2;i++) {
		pointsVector.push_back(vertices[count+i+1]);
		pointsVector.push_back(vertices[count+i]);
		pointsVector.push_back(vertices[i]);
		pointsVector.push_back(vertices[i+1]);

		calculateFace(vertices[count+i+1],vertices[count+i],vertices[i],vertices[i+1]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+2);
		indicesVector.push_back(indexCount+3);
		indexCount+=4;
	}
	for(int i=0;i<slices-2;i++) {
		for(int j=0;j<count-2;j++) {
				
			pointsVector.push_back(vertices[count+(i+1)*(count-1)+j+1]);
			pointsVector.push_back(vertices[count+(i+1)*(count-1)+j]);
			pointsVector.push_back(vertices[count+(i)*(count-1)+j]);
			pointsVector.push_back(vertices[count+(i)*(count-1)+j+1]);

			calculateFace(vertices[count+(i+1)*(count-1)+j+1],vertices[count+(i+1)*(count-1)+j],
			vertices[count+(i)*(count-1)+j],vertices[count+(i)*(count-1)+j+1]);

			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+1);
			indicesVector.push_back(indexCount+2);
			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+2);
			indicesVector.push_back(indexCount+3);
			indexCount+=4;
		}
	}
	// Top of Shape //
		
		
	pointsVector.push_back(vertices[count-2]);
	pointsVector.push_back(vertices[count+(count-1)*(slices-1)-1]);
	pointsVector.push_back(vertices[count-1]);

	calculateFace(vertices[count-2],vertices[count+(count-1)*(slices-1)-1],vertices[count-1]);

	indicesVector.push_back(indexCount);
	indicesVector.push_back(indexCount+1);
	indicesVector.push_back(indexCount+2);
	indexCount+=3;


		
		
	pointsVector.push_back(vertices[count-1]);
	pointsVector.push_back(vertices[count+(count-1)-1]);
	pointsVector.push_back(vertices[count-2]);

	calculateFace(vertices[count-1],vertices[count+(count-1)-1],vertices[count-2]);

	indicesVector.push_back(indexCount);
	indicesVector.push_back(indexCount+1);
	indicesVector.push_back(indexCount+2);
	indexCount+=3;

	for(int i=1;i<slices-1;i++) {
		pointsVector.push_back(vertices[count-1]);
		pointsVector.push_back(vertices[count-1+(i+1)*(count-1)]);
		pointsVector.push_back(vertices[count-1+(i)*(count-1)]);

		calculateFace(vertices[count-1],vertices[count-i+(i+1)*(count-1)],vertices[count-1+(i)*(count-1)]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indexCount+=3;
	}
}

void Mesh::surfRevBottom(int count, int slices, vector<vec3> vertices) {
	float step = 360.0f / (float)slices;
	unsigned int indexCount = 0;
	for(int i=1;i<slices;i++) {
		for(int j=1;j<count;j++) {
			vec4 temp = vec4(vertices[j].x, vertices[j].y, vertices[j].z, 1.0f);
			matrix rot = glm::rotate(matrix(1.0f),i*step,vec3(0,1,0));
			temp = temp*rot;
			vertices.push_back(vec3(temp.x,temp.y,temp.z));
		}
	}
	// Top Shape //
	for(int i=1;i<slices-1;i++) {
		pointsVector.push_back(vertices[count-1]);
		pointsVector.push_back(vertices[count-1+(i+1)*(count-1)]);
		pointsVector.push_back(vertices[count-1+(i)*(count-1)]);
			

		calculateFace(vertices[count-1],vertices[count-1+(i+1)*(count-1)],vertices[count-i+(i)*(count-1)]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indexCount+=3;
	}
	// Walls //
	for(int i=1;i<count-1;i++) {
		pointsVector.push_back(vertices[i]);
		pointsVector.push_back(vertices[i+1]);
		pointsVector.push_back(vertices[count+i]);
		pointsVector.push_back(vertices[count-1+i]);

		calculateFace(vertices[i],vertices[i+1],vertices[count+i],vertices[count-1+i]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+2);
		indicesVector.push_back(indexCount+3);
		indexCount+=4;
	}
	for(int i=1;i<count-1;i++) {
		pointsVector.push_back(vertices[(slices-2)*(count-1)+count+i-1]);
		pointsVector.push_back(vertices[(slices-2)*(count-1)+count+i]);
		pointsVector.push_back(vertices[i+1]);
		pointsVector.push_back(vertices[i]);

		calculateFace(vertices[(slices-2)*(count-1)+count+i-1],vertices[(slices-2)*(count-1)+count+i],vertices[i+1],vertices[i]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+2);
		indicesVector.push_back(indexCount+3);
		indexCount+=4;
	}
	for(int i=0;i<slices-2;i++) {
		for(int j=0;j<count-2;j++) {
				
			pointsVector.push_back(vertices[count+(i+1)*(count-1)+j+1]);
			pointsVector.push_back(vertices[count+(i+1)*(count-1)+j]);
			pointsVector.push_back(vertices[count+(i)*(count-1)+j]);
			pointsVector.push_back(vertices[count+(i)*(count-1)+j+1]);

			calculateFace(vertices[count+(i+1)*(count-1)+j+1],vertices[count+(i+1)*(count-1)+j],
			vertices[count+(i)*(count-1)+j],vertices[count+(i)*(count-1)+j+1]);

			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+1);
			indicesVector.push_back(indexCount+2);
			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+2);
			indicesVector.push_back(indexCount+3);
			indexCount+=4;
		}
	}
	// Bottom of Shape //
	pointsVector.push_back(vertices[0]);
	pointsVector.push_back(vertices[count+(count-1)*(slices-2)]);
	pointsVector.push_back(vertices[1]);

	calculateFace(vertices[0],vertices[count+(count-1)*(slices-1)-1],vertices[1]);

	indicesVector.push_back(indexCount);
	indicesVector.push_back(indexCount+1);
	indicesVector.push_back(indexCount+2);
	indexCount+=3;

	pointsVector.push_back(vertices[0]);
	pointsVector.push_back(vertices[1]);
	pointsVector.push_back(vertices[count]);

	calculateFace(vertices[0],vertices[1],vertices[count]);

	indicesVector.push_back(indexCount);
	indicesVector.push_back(indexCount+1);
	indicesVector.push_back(indexCount+2);
	indexCount+=3;

	for(int i=0;i<slices-2;i++) {
		pointsVector.push_back(vertices[0]);
		pointsVector.push_back(vertices[count+(i)*(count-1)]);
		pointsVector.push_back(vertices[count+(i+1)*(count-1)]);

		calculateFace(vertices[0],vertices[count+(i)*(count-1)],vertices[count+(i+1)*(count-1)]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indexCount+=3;
	}
}

void Mesh::surfRevBoth(int count, int slices, vector<vec3> vertices) {
	float step = 360.0f / (float)slices;
	unsigned int indexCount = 0;
	for(int i=1;i<slices;i++) {
			for(int j=1;j<count-1;j++) {
				vec4 temp = vec4(vertices[j].x, vertices[j].y, vertices[j].z, 1.0f);
				matrix rot = glm::rotate(matrix(1.0f),i*step,vec3(0,1,0));
				temp = temp*rot;
				vertices.push_back(vec3(temp.x,temp.y,temp.z));
			}
		}

		// Bottom of Shape //
		pointsVector.push_back(vertices[0]);
		pointsVector.push_back(vertices[count+(count-2)*(slices-2)]);
		pointsVector.push_back(vertices[1]);

		calculateFace(vertices[0],vertices[count+(count-2)*(slices-2)],vertices[1]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indexCount+=3;

		pointsVector.push_back(vertices[0]);
		pointsVector.push_back(vertices[1]);
		pointsVector.push_back(vertices[count]);

		calculateFace(vertices[0],vertices[1],vertices[count]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indexCount+=3;
		
		for(int i=count;i<(count+(count-2)*(slices-2));i+=(count-2)) {
			pointsVector.push_back(vertices[0]);
			pointsVector.push_back(vertices[i]);
			pointsVector.push_back(vertices[i+(count-2)]);

			calculateFace(vertices[0],vertices[i],vertices[i+(count-2)]);

			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+1);
			indicesVector.push_back(indexCount+2);
			indexCount+=3;
		}

		// Walls of Shape //
		// Sets Vertical Stripes //

		for(int i=1;i<count-2;i++) {
			
			pointsVector.push_back(vertices[i+1]);
			pointsVector.push_back(vertices[i]);
			pointsVector.push_back(vertices[(slices-2)*(count-2)+count+i-1]);
			pointsVector.push_back(vertices[(slices-2)*(count-2)+count+i]);

			calculateFace(vertices[i+1],vertices[i],vertices[(slices-2)*(count-2)+count+i-1],vertices[(slices-2)*(count-2)+count+i]);

			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+1);
			indicesVector.push_back(indexCount+2);
			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+2);
			indicesVector.push_back(indexCount+3);
			indexCount+=4;
		}
		for(int i=1;i<count-2;i++) {
			pointsVector.push_back(vertices[count+i]);
			pointsVector.push_back(vertices[count+i-1]);
			pointsVector.push_back(vertices[i]);
			pointsVector.push_back(vertices[i+1]);

			calculateFace(vertices[count+i],vertices[count+i-1],vertices[i],vertices[i+1]);

			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+1);
			indicesVector.push_back(indexCount+2);
			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+2);
			indicesVector.push_back(indexCount+3);
			indexCount+=4;
		}

		for(int i=0;i<slices-2;i++) {
			for(int j=1;j<count-2;j++) {
				
				pointsVector.push_back(vertices[count+(i+1)*(count-2)+j]);
				pointsVector.push_back(vertices[count+(i+1)*(count-2)+j-1]);
				pointsVector.push_back(vertices[count+i*(count-2)+j-1]);
				pointsVector.push_back(vertices[count+i*(count-2)+j]);

				calculateFace(vertices[count+(i+1)*(count-2)+j],vertices[count+(i+1)*(count-2)+j-1],
				vertices[count+i*(count-2)+j-1],vertices[count+i*(count-2)+j]);

				indicesVector.push_back(indexCount);
				indicesVector.push_back(indexCount+1);
				indicesVector.push_back(indexCount+2);
				indicesVector.push_back(indexCount);
				indicesVector.push_back(indexCount+2);
				indicesVector.push_back(indexCount+3);
				indexCount+=4;
			}
		}

		// Top of Shape //
		pointsVector.push_back(vertices[count-1]);
		pointsVector.push_back(vertices[count-2]);
		pointsVector.push_back(vertices[count+(count-2)*(slices-1)-1]);

		calculateFace(vertices[count-1],vertices[count-2],vertices[count+(count-2)*(slices-1)-1]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indexCount+=3;

		pointsVector.push_back(vertices[count-1]);
		pointsVector.push_back(vertices[count+(count-2)-1]);
		pointsVector.push_back(vertices[count-2]);

		calculateFace(vertices[count-1],vertices[count+(count-2)-1],vertices[count-2]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indexCount+=3;

		for(int i=count-1;i<(count+(count-2)*(slices-2)-1);i+=(count-2)) {
			pointsVector.push_back(vertices[count-1]);
			pointsVector.push_back(vertices[i+(count-2)*2]);
			pointsVector.push_back(vertices[i+(count-2)]);
			
			calculateFace(vertices[count-1],vertices[i+(count-2)*2],vertices[i+(count-2)]);

			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+1);
			indicesVector.push_back(indexCount+2);
			indexCount+=3;
		}
}

void Mesh::surfRevNone(int count, int slices, vector<vec3> vertices, bool endcaps) {
	float step = 360.0f / (float)slices;
	unsigned int indexCount = 0;
	for(int i=1;i<slices;i++) {
		for(int j=0;j<count;j++) {
			vec4 temp = vec4(vertices[j].x, vertices[j].y, vertices[j].z, 1.0f);
			matrix rot = glm::rotate(matrix(1.0f),i*step,vec3(0,1,0));
			temp = temp*rot;
			vertices.push_back(vec3(temp.x,temp.y,temp.z));
		}
	}
	// Bottom Face //
	if(endcaps) {
		for(int i=0;i<slices-2;i++) {
			pointsVector.push_back(vertices[0]);
			pointsVector.push_back(vertices[count+(i)*(count)]);
			pointsVector.push_back(vertices[count+(i+1)*(count)]);

			calculateFace(vertices[0],vertices[count+(i)*(count)],vertices[count+(i+1)*(count)]);

			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+1);
			indicesVector.push_back(indexCount+2);
			indexCount+=3;
		}
	}

	// Walls //
	for(int i=0;i<count-1;i++) {
		pointsVector.push_back(vertices[i+1]);
		pointsVector.push_back(vertices[i]);
		pointsVector.push_back(vertices[(slices-2)*(count)+count+i]);
		pointsVector.push_back(vertices[(slices-2)*(count)+count+i+1]);

		calculateFace(vertices[i+1],vertices[i],vertices[(slices-2)*(count)+count+i],vertices[(slices-2)*(count)+count+i+1]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+2);
		indicesVector.push_back(indexCount+3);
		indexCount+=4;
	}
	for(int i=0;i<count-1;i++) {
		pointsVector.push_back(vertices[count+i+1]);
		pointsVector.push_back(vertices[count+i]);
		pointsVector.push_back(vertices[i]);
		pointsVector.push_back(vertices[i+1]);

		calculateFace(vertices[count+i+1],vertices[count+i],vertices[i],vertices[i+1]);

		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+1);
		indicesVector.push_back(indexCount+2);
		indicesVector.push_back(indexCount);
		indicesVector.push_back(indexCount+2);
		indicesVector.push_back(indexCount+3);
		indexCount+=4;
	}
	for(int i=0;i<slices-2;i++) {
		for(int j=0;j<count-1;j++) {
				
			pointsVector.push_back(vertices[count+(i+1)*(count)+j+1]);
			pointsVector.push_back(vertices[count+(i+1)*(count)+j]);
			pointsVector.push_back(vertices[count+(i)*(count)+j]);
			pointsVector.push_back(vertices[count+(i)*(count)+j+1]);

			calculateFace(vertices[count+(i+1)*(count)+j+1],vertices[count+(i+1)*(count)+j],
			vertices[count+(i)*(count)+j],vertices[count+(i)*(count)+j+1]);

			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+1);
			indicesVector.push_back(indexCount+2);
			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+2);
			indicesVector.push_back(indexCount+3);
			indexCount+=4;
		}
	}
	// Top Face //
	if(endcaps) {
		for(int i=1;i<slices-1;i++) {
			pointsVector.push_back(vertices[count-1]);
			pointsVector.push_back(vertices[count-1+(i+1)*(count)]);
			pointsVector.push_back(vertices[count-1+(i)*(count)]);
			

			calculateFace(vertices[count-1],vertices[count-1+(i+1)*(count)],vertices[count-i+(i)*(count)]);

			indicesVector.push_back(indexCount);
			indicesVector.push_back(indexCount+1);
			indicesVector.push_back(indexCount+2);
			indexCount+=3;
		}
	}
}