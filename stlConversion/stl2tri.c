#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int size;
    float* elms;
    int curr;
} DynArr;

void makeVertArray();
void add_ints(DynArr* da, float e, float f, float g);

// main application
int main() {

    makeVertArray();

}

/* add_ints
 * adds several integers intelligently to array
 */
void add_ints(DynArr* da, float e, float f, float g) {

    if(da->curr == da->size) {
        //remalloc
        float* newArr;
        newArr = malloc( 2 * da->size * sizeof(float) );
        memcpy( newArr, da->elms, sizeof(newArr) );
        free( da-> elms );
        da->elms = newArr;
        da->size = 2*da->size;
    }

    da->elms[da->curr] = e;
    da->elms[da->curr] = f;
    da->elms[da->curr] = g;
    da->curr += 3;

}

/* makeVertArray()
 * read in ASCII stl file
 * and turn it into a list of verts 
 */
void makeVertArray() {

    char *line = NULL;
    size_t size;
    DynArr* vertList;
    vertList = malloc( sizeof( DynArr ) );

    float x, y, z;
    char test[50];
    while(getline(&line, &size, stdin) != EOF) {
        if(line[0]=='v') {
            sscanf(line, "%*s %f %f %f", x, y, z);
            printf("%f, %f, %f\n", x, y, z);
            add_ints(vertList, x, y, z);
        }
    }
}
