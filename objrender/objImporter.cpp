/**
 * Imports a Wavefront .obj file as list of verticies
 * and face indicies
 * 
 *   Written by: Sean Congden <stc4700@rit.edu>
 *     Copyright (c) 2012. All rights reserved.
 */


#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "mesh.h"
#include "objImporter.h"


#define LINE_SIZE					256


void loadFace(char *faceString, Mesh *mesh)
{
	// Get tokens for each index set
	std::vector<char *> tokens;
	char *curToken = strtok(faceString, " \t\n");
	while (curToken != NULL) {
		char *token = (char *)malloc(sizeof(char) * strlen(curToken));
		strcpy(token, curToken);
		tokens.push_back(token);
		curToken = strtok(NULL, " \t\n");
	}


	// Parse the indicies
	std::vector<unsigned int> vertIndicies;
	std::vector<unsigned int> texIndicies;
	std::vector<unsigned int> normIndicies;

	for (int i = 0; i < tokens.size(); i++) {
		// Load the vertex index
		char *index = tokens.at(i);
		unsigned int str_size = strlen(index);
		unsigned int loc = strcspn(index, "/");
		index[loc] = '\0';

		if (loc > 0) {
			unsigned int vertex;
			sscanf(index, "%u", &vertex);
			vertIndicies.push_back(vertex);
		}

		if (loc == str_size)
			continue;


		// Load the texture index
		index = index + loc + 1;
		str_size = strlen(index);
		loc = strcspn(index, "/");
		index[loc] = '\0';

		if (loc > 0) {
			unsigned int texture;
			sscanf(index, "%u", &texture);
			texIndicies.push_back(texture);
		}

		if (loc == str_size)
			continue;

		// Load the normal index
		index = index + loc + 1;
		str_size = strlen(index);
		loc = strcspn(index, "/");
		index[loc] = '\0';

		if (loc > 0) {
			unsigned int normal;
			sscanf(index, "%u", &normal);
			normIndicies.push_back(normal);
		}
	}

	// Free memory
	for (int i = 0; i < tokens.size(); i++) {
		free(tokens.at(i));
	}

	Face *textures = NULL;
	if (texIndicies.size() > 0) {
		textures = (Face *)malloc(sizeof(Face));
		*textures = ((Face) {texIndicies[0] - 1,
			texIndicies[1] - 1, texIndicies[2] - 1});
	}

	Face *normals = NULL;
	if (normIndicies.size() > 0) {
		normals = (Face *)malloc(sizeof(Face));
		*normals = ((Face) {normIndicies[0] - 1,
			normIndicies[1] - 1, normIndicies[2] - 1});
	}

	mesh->AddFace((Face) {vertIndicies[0] - 1,
			vertIndicies[1] - 1, vertIndicies[2] - 1}, textures, normals);
}


Mesh *importOBJ(const char *filename)
{
	FILE *objFile;
	char line[LINE_SIZE];
	//int curObj = -1;

	// Open the file
	objFile = fopen(filename, "r");
	if (objFile == NULL) return NULL;


	// Create a new mesh	
	Mesh *object = new Mesh();

	while (fgets(line, LINE_SIZE, objFile) != NULL) {
		if (line[0] == 'o') {
			// Go to the next object
		} else if (line[0] == 'v') {
			if (line[1] == 'n') {
				float x, y, z;
				sscanf(line, "vn %f %f %f", &x, &y, &z);

				object->AddNormal(glm::vec3(x, y, z));
			} else if (line[1] == 't') {
				float x, y;
				sscanf(line, "vt %f %f", &x, &y);

				object->AddTextureCoord(x, y);
			} else {
				float x, y, z;
				sscanf(line, "v %f %f %f", &x, &y, &z);

				object->AddPosition(glm::vec3(x, y, z));
			}
		} else if (line[0] == 'f') {
			if (line[1] == ' ')
				loadFace(line + 2, object);

		} else if (line[0] == 's') {
			// Switch smoothing on or off?
		}
	}

    fclose(objFile);

	return object;
}
