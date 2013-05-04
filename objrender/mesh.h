#ifndef __MESH_H
#define __MESH_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>


#define AUTO_SMOOTH_MAX					35.0	// in degrees


typedef struct {
	float x, y, z;
	float nX, nY, nZ;
	float tX, tY;
} VertexData;

typedef struct {
	unsigned short index1, index2, index3;
} Face;


class Mesh {
public:
	Mesh(void);
	virtual ~Mesh(void);

	unsigned int AddPosition(float x, float y, float z);
	unsigned int AddPosition(glm::vec3 position);

	unsigned int AddNormal(glm::vec3 normal);

	void AddTextureCoord(float x, float y);

	void AddFace(Face face, bool smooth = false);
	void AddFace(Face face, Face *texture, Face *normal);

	unsigned int AddVertex(glm::vec3 position,
						   glm::vec3 normal,
						   bool smooth = false);

	void AddTriangle(float x1, float y1, float z1,
					 float x2, float y2, float z2,
					 float x3, float y3, float z3);

	Face *Faces(void);
	unsigned int NumFaces(void);

	VertexData *Verticies(void);
	unsigned int NumVerticies(void);

	glm::mat4 GetTransform(void);
	void SetTransform(glm::mat4 transform);

private:
	std::vector<glm::vec3> *verticies;
	std::vector<glm::vec3> *normals;
	std::vector<glm::vec2> *texture;
	std::vector<Face> *faces;
	std::vector<Face *> *normIndicies;
	std::vector<Face *> *texIndicies;

	VertexData *vertBuffer;
	Face *elemBuffer;

	glm::mat4 transform;
};


#endif
