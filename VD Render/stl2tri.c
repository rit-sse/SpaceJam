/* STL CONVERTER TO SPECIAL TRI ARRAY
 * created by Jesse Jurman and Lee Avital
 * for use with the SpaceJam 3D Display Software
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stl2tri.h"


typedef struct {
    
} LinkList;

// main application
DynArr load(FILE *file) {

    // create a dynamic array (defined above)
    DynArr* vertList;
    vertList = malloc( sizeof( DynArr ) );
    // setup array for 3 values (we'll add more in add_ints)
    vertList->size=3;
    vertList->elms = malloc( 3*sizeof(float) );

    // read in from stdin and add values
    makeVertArray(vertList, *file);
    return *vertList;
}

/* add_ints()
 * adds several integers intelligently to array
 */
void add_ints(DynArr* da, float e, float f, float g) {

    if(da->curr == da->size) {
        //remalloc
        float* newArr;
        newArr = malloc( 2 * da->size * sizeof(float) );
        memcpy( newArr, da->elms, da->size );
        free( da->elms );
        da->elms = newArr;
        da->size = 2*da->size;
    }

    da->elms[da->curr++] = e;
    da->elms[da->curr++] = f;
    da->elms[da->curr++] = g;

}

/* makeVertArray()
 * read in ASCII stl file
 * and turn it into a list of verts 
 */
void makeVertArray(DynArr* da, FILE file) {

    char *line = NULL;
    size_t size;

    float x, y, z;
    while(getline(&line, &size, &file) != EOF) {
        if(line[0]=='v') {
            sscanf(line, "%*s %f %f %f", &x, &y, &z);
//            printf("%f, %f, %f\n", x, y, z);
            add_ints(da, x, y, z);
        }
    }
}
