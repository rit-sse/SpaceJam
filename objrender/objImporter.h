/**
 * Imports a Wavefront .obj file as list of verticies
 * and face indicies
 * 
 *   Written by: Sean Congden <stc4700@rit.edu>
 *     Copyright (c) 2012. All rights reserved.
 */

#ifndef __OBJ_IMPORTER_H
#define __OBJ_IMPORTER_H


#include "mesh.h"

Mesh *importOBJ(const char *filename);

#endif
