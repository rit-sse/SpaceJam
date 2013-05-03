//
//  stl2tri.h
//  VD Render
//
//  Created by Michael Timbrook on 5/2/13.
//  Copyright (c) 2013 MichaelTimbrook. All rights reserved.
//

#ifndef VD_Render_stl2tri_h
#define VD_Render_stl2tri_h

typedef struct {
    int size;
    float* elms;
    int curr;
} DynArr;

DynArr load(FILE *file);
void makeVertArray(DynArr* da, FILE file);
void add_ints(DynArr* da, float e, float f, float g);

#endif
