
#include <vector>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "mesh.h"


Mesh::Mesh(void)
	: vertBuffer(0)
	, elemBuffer(0)
	, transform(1.0f)
{
	verticies = new std::vector<glm::vec3>();
	normals = new std::vector<glm::vec3>();
	texture = new std::vector<glm::vec2>();
	faces = new std::vector<Face>();
	texIndicies = new std::vector<Face *>();
	normIndicies = new std::vector<Face *>();
}


Mesh::~Mesh(void)
{
	// Clear the element buffer if it exists
	if (elemBuffer) {
		delete elemBuffer;
	}

	// Clear the vertex buffer if it exists
	if (vertBuffer) {
		delete vertBuffer;
	}

	for (int i = 0; i < texIndicies->size(); i++) {
		free(texIndicies->at(i));
	}

	for (int i = 0; i < normIndicies->size(); i++) {
		free(normIndicies->at(i));
	}

	delete verticies;
	delete normals;
	delete texture;
	delete faces;
	delete texIndicies;
	delete normIndicies;
}


unsigned int Mesh::AddPosition(float x, float y, float z)
{
	normals->push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	return AddPosition(glm::vec3(x, y, z));
}


unsigned int Mesh::AddPosition(glm::vec3 position)
{
	unsigned int index = verticies->size();
	verticies->push_back(position);

	return index;
}


unsigned int Mesh::AddNormal(glm::vec3 normal)
{
	unsigned int index = normals->size();
	normals->push_back(normal);

	return index;
}


void Mesh::AddFace(Face face, bool smooth)
{
	faces->push_back(face);

	glm::vec3 normal = glm::normalize(glm::cross(
		(verticies->at(face.index3) - verticies->at(face.index1)),
		(verticies->at(face.index2) - verticies->at(face.index1))));
	
	normals->at(face.index1) += normal;
	normals->at(face.index2) += normal;
	normals->at(face.index3) += normal;
}


void Mesh::AddFace(Face face, Face *texture, Face *normal)
{
	faces->push_back(face);

	if (texture != NULL)
		texIndicies->push_back(texture);

	if (normal != NULL)
		normIndicies->push_back(normal);
}


void Mesh::AddTextureCoord(float x, float y)
{
	texture->push_back(glm::vec2(x, y));
}


unsigned int Mesh::AddVertex(glm::vec3 position, glm::vec3 normal, bool smooth)
{
	if (smooth) {
		for (int i = 0; i < verticies->size(); i++) {
			if (verticies->at(i) == position) {
				float angle = glm::angle(normals->at(i), normal);
				
				if ((angle < 45.0) || (angle != angle)) {
					normals->at(i) += normal;
					return i;
				}
			}
		}
	}

	// If there is no existing vertex, add it
	unsigned int index = verticies->size();

	verticies->push_back(position);
	normals->push_back(normal);

	return index;
}


void Mesh::AddTriangle(float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3)
{
	glm::vec3 position1(x1, y1, z1);
	glm::vec3 position2(x2, y2, z2);
	glm::vec3 position3(x3, y3, z3);

	glm::vec3 normal = glm::normalize(glm::cross(
		(position3 - position1), (position2 - position1)));


	unsigned int index1 = AddVertex(position1, normal, false);
	unsigned int index2 = AddVertex(position2, normal, false);
	unsigned int index3 = AddVertex(position3, normal, false);


	Face face = {index1, index2, index3};
	faces->push_back(face);
}


Face *Mesh::Faces(void)
{
	// Clear the old buffer if it exists
	if (elemBuffer) {
		delete elemBuffer;
	}

	elemBuffer = new Face[faces->size()];
	
	for (int i = 0; i < faces->size(); ++i) {
		elemBuffer[i] = faces->at(i);
	}

	return elemBuffer;
}


unsigned int Mesh::NumFaces(void)
{
	return faces->size();
}


VertexData *Mesh::Verticies(void)
{
	// Clear the old buffer if it exists
	if (vertBuffer)
		delete vertBuffer;


	// Create a new buffer to hold the verticies
	vertBuffer = new VertexData[verticies->size()];


	// Load in position data
	for (int i = 0; i < verticies->size(); ++i) {
		glm::vec3 position = verticies->at(i);

		vertBuffer[i] = (VertexData){ position.x, position.y, position.z,
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	}


	// Load texture data into correct spots if needed
	if (texIndicies->size() > 0) {
		for (int i = 0; i < texIndicies->size(); ++i) {
			vertBuffer[faces->at(i).index1].tX =
					texture->at(texIndicies->at(i)->index1).x;
			vertBuffer[faces->at(i).index1].tY =
					texture->at(texIndicies->at(i)->index1).y;

			vertBuffer[faces->at(i).index2].tX =
					texture->at(texIndicies->at(i)->index2).x;
			vertBuffer[faces->at(i).index2].tY =
					texture->at(texIndicies->at(i)->index2).y;

			vertBuffer[faces->at(i).index3].tX =
					texture->at(texIndicies->at(i)->index3).x;
			vertBuffer[faces->at(i).index3].tY =
					texture->at(texIndicies->at(i)->index3).y;
		}
	} else if (texture->size() > 0) {
		for (int i = 0; i < texture->size(); ++i) {
			vertBuffer[i].tX = texture->at(i).x;
			vertBuffer[i].tY = texture->at(i).y;
		}
	}


	// Normalize the normals
	std::vector<glm::vec3>::iterator iter;
	for (iter = normals->begin(); iter != normals->end(); iter++) {
		*iter = glm::normalize(*iter);
	}


	// Load normal data into correct spots if needed
	if (normIndicies->size() > 0) {
		for (int i = 0; i < normIndicies->size(); ++i) {
			vertBuffer[faces->at(i).index1].nX =
					normals->at(normIndicies->at(i)->index1).x;
			vertBuffer[faces->at(i).index1].nY =
					normals->at(normIndicies->at(i)->index1).y;
			vertBuffer[faces->at(i).index1].nZ =
					normals->at(normIndicies->at(i)->index1).z;


			vertBuffer[faces->at(i).index2].nX =
					normals->at(normIndicies->at(i)->index2).x;
			vertBuffer[faces->at(i).index2].nY =
					normals->at(normIndicies->at(i)->index2).y;
			vertBuffer[faces->at(i).index2].nZ =
					normals->at(normIndicies->at(i)->index2).z;


			vertBuffer[faces->at(i).index3].nX =
					normals->at(normIndicies->at(i)->index3).x;
			vertBuffer[faces->at(i).index3].nY =
					normals->at(normIndicies->at(i)->index3).y;
			vertBuffer[faces->at(i).index3].nZ =
					normals->at(normIndicies->at(i)->index3).z;

		}
	} else if (normals->size() > 0) {
		for (int i = 0; i < normals->size(); ++i) {
			vertBuffer[i].nX = normals->at(i).x;
			vertBuffer[i].nY = normals->at(i).y;
			vertBuffer[i].nZ = normals->at(i).z;
		}
	}


	return vertBuffer;
}

unsigned int Mesh::NumVerticies(void)
{
	return verticies->size();
}


glm::mat4 Mesh::GetTransform(void)
{
	return transform;
}


void Mesh::SetTransform(glm::mat4 transform)
{
	this->transform = transform;
}
