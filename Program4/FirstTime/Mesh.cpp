/* 
	Author: Mitch Roberts
	Course: COMP 361, Computer Graphics 
	Date: April 1, 2014
	Description: Implementation of the mesh class.
		Handles input from files and all of the other business for the creation of a mesh.
*/
#include "Mesh.h"

Mesh::Mesh(void)
{
	size = 0;
	nFaces = 0;
	inited = false;
}


Mesh::~Mesh(void)
{
}

void Mesh::init(uint* vbo, uint* cbo, uint* vLocation, uint* cLocation, uint* u_projLocation, uint* u_modelMatrix, uint* u_lightLocation, uint* ibo, uint* nbo, uint* nLocation)
{
	Mesh::vbo = vbo;
	Mesh::cbo = cbo;
	Mesh::vLocation = vLocation;
	Mesh::cLocation = cLocation;
	Mesh::u_projLocation = u_projLocation;
	Mesh::u_modelMatrix = u_modelMatrix;
	Mesh::ibo = ibo;
	Mesh::nbo = nbo;
	Mesh::nLocation = nLocation;
	Mesh::u_lightLocation = u_lightLocation;
	
	float dump;
	
	//if(fname == "") return;

	string type = getParams("surfrev2.dat");
	
	if(type == "extrusion")
	{
		extGetBase();

		extGetCap();

		bool convex = convexityTest();

		extGetSides();

		extGetIndices();

		extCalcNormals();

		if(!convex)
		{
			//adjust the indices and normals to remove the base and cap
			for(int i=0; i<6*(nFaces-2); i++)
			{
				//6*nFace-2 = index where the sides begin
				//0-3*nFaces-2 is the base
				//3*nFaces-2 - 2*(3*nFaces-2) is the cap
				indices[i] = indices[i + 6*(nFaces-2)];
				normals[i] = normals[i + 6*(nFaces-2)];
				//indices[i] = 0;
				//normals[i] = Vec4(0, 0, 0, 0);
			}
		}
	}

	else if (type == "surfrev")
	{
		//if we are doing a surface rev, disp will hold the number of rotations
		//and we must extract
		revGetBase();

		revGetPoints();

		revGetIndices();

		revCalcNormals();
	}

	Vec4* pts = new Vec4[points.size()];
	for(int i=0; i<points.size(); i++) pts[i] = points[i];
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec4), pts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(*vLocation);
	glVertexAttribPointer(*vLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	Vec4* norm = new Vec4[normals.size()];
	for(int i=0; i<normals.size(); i++) norm[i] = normals[i];
	glBindBuffer(GL_ARRAY_BUFFER, *nbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec4), norm, GL_STATIC_DRAW);
	glEnableVertexAttribArray(*nLocation);
	glVertexAttribPointer(*nLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	uint* ind = new unsigned int[indices.size()];
	for(int i=0; i<indices.size(); i++)ind[i] = indices[i];
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), ind, GL_STATIC_DRAW);
	size = indices.size();
	inited = true;
}

void Mesh::draw(Vec4 color)
{
	Vec4* colors = new Vec4[size];
	for(int i=0; i<size; i++)
	{
		colors[i] = color;
	}
	//glm::vec4 colors[24] = {
	//	//Front
	//	color,color,color,color,
	//	//Back 
	//	color,color,color,color,
	//	//Left
	//	color,color,color,color,
	//	//Right
	//	color,color,color,color,
	//	//Bottom
	//	color,color,color,color,
	//	//Top
	//	color,color,color,color
	//};

	//world = world * ;

	glBindBuffer(GL_ARRAY_BUFFER, *cbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(glm::vec4), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(*cLocation);
	glVertexAttribPointer(*cLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glUniformMatrix4fv(*u_modelMatrix, 1, GL_FALSE, &world[0][0]);
	
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
}

bool Mesh::convexityTest()
{
	Vec3 n = glm::cross(Vec3(points[1] - points[0]), Vec3(points[points.size()-1] - points[0]));
	for(int i=1; i<points.size(); i++)
	{
		Vec3 u = glm::cross(Vec3(points[(i+1) % points.size()] - points[i]), Vec3(points[i-1]-points[i]));
		if(glm::normalize(n) != glm::normalize(u)) return false;
	}
	return true;
}

string Mesh::getParams(string fname)
{
	fin.open(fname);

	string type;
	int nVerts;

	fin >> type >> disp >> nVerts;
	nFaces = nVerts-1;

	return type;
}

void Mesh::extGetBase()
{
	float x, z;
	for(int i=0; i<nFaces; i++)
	{
		fin >> x >> z;
		points.push_back(Vec4(x, 0, z, 1));
	}

	fin.close();
}

void Mesh::extGetCap()
{
	//translate base
	for(int i=0; i<nFaces; i++)
	{
		points.push_back(Vec4(points[i].x, disp, points[i].z, 1));
	}
}

void Mesh::extGetSides()
{
	//define side verts
	for(int i=0; i<nFaces; i++)
	{
		points.push_back(points[i]);
		points.push_back(points[(i+1)%nFaces]);
		points.push_back(points[i+nFaces]);
		points.push_back(points[((i+1)%nFaces)+nFaces]);
	}
}

void Mesh::extGetIndices()
{
	//base triangulated indices
	for(int i=0; i<nFaces-2; i++)
	{
		indices.push_back(0);
		indices.push_back(i+1);
		indices.push_back(i+2);
	}
	//cap triangulated indices
	for(int i=0; i < nFaces-2; i++)
	{
		indices.push_back(nFaces);
		indices.push_back(nFaces+i+1);
		indices.push_back(nFaces+i+2);
	}
	//side faces
	for(int i=2*nFaces; i<6*nFaces; i+=4)
	{
		indices.push_back(i);
		indices.push_back(i+1);
		indices.push_back(i+2);

		indices.push_back(i+3);
		indices.push_back(i+2);
		indices.push_back(i+1);
	}
}

void Mesh::extCalcNormals()
{
	//base normals
	for(int i=0; i<3*(nFaces-2); i+=3)
	{
		Vec4 v = points[indices[i+2]] - points[indices[i]];
		Vec4 u = points[indices[i+1]] - points[indices[i]];
		Vec3 n = glm::cross(Vec3(v.x, v.y, v.z), Vec3(u.x, u.y, u.z));
		Vec4 n4(n.x, n.y, n.z, 0);
		n4 = glm::normalize(n4);

		normals.push_back(n4);
		normals.push_back(n4);
		normals.push_back(n4);
	}
	//cap normals
	for(int i=3*(nFaces-2); i<2*3*(nFaces-2); i+=3)
	{
		Vec4 v = points[indices[i+1]] - points[indices[i]];
		Vec4 u = points[indices[i+2]] - points[indices[i]];
		Vec3 n = glm::cross(Vec3(v.x, v.y, v.z), Vec3(u.x, u.y, u.z));
		Vec4 n4(n.x, n.y, n.z, 0);
		n4 = glm::normalize(n4);
		
		normals.push_back(n4);
		normals.push_back(n4);
		normals.push_back(n4);
	}
	//side normals
	for(int i=2*3*(nFaces-2); i<indices.size()-2; i+=3)
	{
		glm::vec4 v = points[indices[i+2]] - points[indices[i]];
		Vec4 u = points[indices[i+1]] - points[indices[i]];
		Vec3 n = glm::cross(Vec3(v.x, v.y, v.z), Vec3(u.x, u.y, u.z));
		Vec4 n4(n.x, n.y, n.z, 0);
		n4 = glm::normalize(n4);

		normals.push_back(n4);
		normals.push_back(n4);
		normals.push_back(n4);
	}
}

void Mesh::revGetBase()
{
	float x, y;
	for(int i=0; i<nFaces+1; i++)
	{
		fin >> x >> y;
		points.push_back(Vec4(x, y, 0, 1));
	}

	fin.close();
}

void Mesh::revGetPoints()
{
	float theta = 360.0f/disp;
	for(int i=1; i<disp; i++)
	{
		Matrix rotate = glm::rotate(Matrix(1.0f), i*theta, Vec3(0, 1, 0));
		for(int i=0; i<nFaces+1; i++)
		{
			points.push_back(points[i] * rotate);
		}
	}
}

void Mesh::revGetIndices()
{
	for(int i=0; i<(disp+1) * nFaces; i++)
	{
		if(points[i].x == 0) //triangle
		{
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back((i + 1 + nFaces)%points.size());
		}
		else //quad
		{
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back((i + nFaces + 1)%points.size());

			indices.push_back((i + 1 + nFaces + 1)%points.size());
			indices.push_back((i + 1 + nFaces)%points.size());
			indices.push_back(i + 1);
		}
	}
}

void Mesh::revCalcNormals()
{
	for(int i=0; i<indices.size()-2; i+=3)
	{
		Vec4 n = points[indices[i+2]] - points[indices[i]];
		Vec4 u = points[indices[i+1]] - points[indices[i]];
		Vec3 v = glm::cross(Vec3(n), Vec3(u));
		Vec4 norm(n.x, n.y, n.z, 0);
		norm = glm::normalize(norm);

		normals.push_back(norm);
		normals.push_back(norm);
		normals.push_back(norm);
		//normals.push_back(Vec4(0, 1, 0, 0));
		//normals.push_back(Vec4(0, 1, 0, 0));
		//normals.push_back(Vec4(0, 1, 0, 0));
	}
}