//
//  ImportSTL.c
//  VD Render
//
//  Created by Michael Timbrook on 5/2/13.
//  Copyright (c) 2013 MichaelTimbrook. All rights reserved.
//

#include <stdio.h>
#include "ImportSTL.h"

typedef struct node {
    GLfloat data;
    struct node *next;
} node;


GLfloat* loadSTL(FILE *file) {
    
    node *HEAD;
    int size = 0;
    
    char *line = NULL;
    size_t s;
    
    GLfloat x, y, z;
    
    while (getline(&line, &s, file) != EOF) {
        if(line[0]=='v') {
            sscanf(line, "%*s %f %f %f", &x, &y, &z);
            
            node *n1 = (node*)calloc(1, sizeof(node));
            n1->data = z;
            n1->next = HEAD;
            
            node *n2 = (node*)calloc(1, sizeof(node));
            n2->data = y;
            n2->next = n1;
            
            node *n3 = (node*)calloc(1, sizeof(node));
            n3->data = x;
            n3->next = n2;
            
            HEAD = n3;
            size += 3;
            
        }
        
    }
    
    float vert[size];
    for (int i = size - 1; i >= 0; i--) {
        vert[i] = HEAD->data;
        HEAD = HEAD->next;
    }
    
    return vert;
}




