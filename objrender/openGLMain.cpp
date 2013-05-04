
#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__ 
	#include <GLUT/GLUT.h>
	#include <OpenGL/gl.h>
#else
	#include <GL/glew.h>
	#include <GL/glut.h>
	#include <GL/gl.h>
#endif

#include <FreeImage.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_inverse.hpp"

#include "shaderProgram.h"
#include "objImporter.h"


#define SCREEN_WIDTH			648
#define SCREEN_HEIGHT			604

#define BUFFER_OFFSET(i)		((char *)NULL + (i))

Mesh *mesh;

// Shader variable locations
GLuint _program, positionID, normalID, vertBuffer, elemBuffer;

// Uniform index.
enum {
    UNIFORM_MODELVIEWPROJECTION_MATRIX,
    UNIFORM_NORMAL_MATRIX,
    UNIFORM_MIRROR_NORMAL,
    UNIFORM_PROJECTOR_REFLEXTION,
    UNIFORM_COLOR,
    NUM_UNIFORMS
};
GLint uniforms[NUM_UNIFORMS];

// Projection matricies
glm::mat4 _modelViewProjectionMatrix;
glm::mat3 _normalMatrix;
float _rotation = 0.0f;
float _projectorDistance = 60.0f;

// timing
int pt = 0;
int elapsedTime = 0;
int curFrame = 0;


void initOpenGL(void)
{
	// Some openGL initialization...probably best to keep
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_CULL_FACE);
    glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_CULL_FACE);
    glHint(GL_POLYGON_SMOOTH, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_MULTISAMPLE_ARB);
}


void loadResources(char *objFile)
{
    // Load the shaders
    _program = setUpAShader((char *)"shaders/VDShader.vsh", (char *)"shaders/Shader.fsh");
    if (!_program) {
        std::cerr << "Error setting up shaders" << std::endl;
        exit(1);
    }

	// Set up program variables
	positionID = glGetAttribLocation(_program, "position");
	normalID = glGetAttribLocation(_program, "normal");

    uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX] = glGetUniformLocation(_program, "modelViewProjectionMatrix");
    uniforms[UNIFORM_NORMAL_MATRIX] = glGetUniformLocation(_program, "normalMatrix");
    uniforms[UNIFORM_MIRROR_NORMAL] = glGetUniformLocation(_program, "mirrorNormal");
    uniforms[UNIFORM_PROJECTOR_REFLEXTION] = glGetUniformLocation(_program, "reflectedP");
    uniforms[UNIFORM_COLOR] = glGetUniformLocation(_program, "color");

    // Load in the object to render
    mesh = importOBJ(objFile);

	// Generate the opengl buffers
	glGenBuffers(1, &vertBuffer);
    glGenBuffers(1, &elemBuffer);

	// Set up the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * mesh->NumVerticies(),
			mesh->Verticies(), GL_STATIC_DRAW);

    // Set up the element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Face) * mesh->NumFaces(),
			mesh->Faces(), GL_STATIC_DRAW);
}


void calcRotation(void)
{
    _normalMatrix = glm::mat3(1.0f);
    _modelViewProjectionMatrix = glm::mat4(1.0f);

    float aspect = fabsf(648.0f / 604.0f);
    glm::mat4 projectionMatrix = glm::perspective(60.0f, aspect, 0.1f, 100.0f);

    glm::mat4 baseModelViewMatrix = glm::translate(glm::mat4(1.0f),
            glm::vec3(0.0f, 0.0f, -6.0f));
    baseModelViewMatrix = glm::rotate(baseModelViewMatrix,
            _rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    baseModelViewMatrix = glm::rotate(baseModelViewMatrix,
            _rotation, glm::vec3(0.0f, -1.0f, 0.0f));

    // Compute the model view matrix for the object rendered with GLKit
    glm::mat4 modelViewMatrix = glm::translate(glm::mat4(1.0f),
            glm::vec3(0.0f, 0.0f, 0.0f));
    modelViewMatrix = baseModelViewMatrix * modelViewMatrix;
    
    _normalMatrix = glm::inverseTranspose(glm::mat3(modelViewMatrix));
    _modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;
    
    _rotation += 360.0f / 96.0f;
}


void saveImage(int frame) {
    GLubyte pixels[SCREEN_WIDTH * SCREEN_HEIGHT * 3];
    glReadPixels(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, GL_RGB, GL_UNSIGNED_BYTE, &pixels);

    BYTE bytes[SCREEN_WIDTH * SCREEN_HEIGHT * 3];
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT * 3; i++) {
        bytes[i] = pixels[i]; 
    }

    FIBITMAP* image = FreeImage_ConvertFromRawBits(bytes, SCREEN_WIDTH, SCREEN_HEIGHT,
            SCREEN_WIDTH * 3, 24, 0x0000FF, 0xFF0000, 0x00FF00, FALSE);

    char filename[18];
    sprintf(filename, "output/%03d.bmp", frame);
    FreeImage_Save(FIF_BMP, image, filename, 0);
    FreeImage_Unload(image);
}


void drawFrame(void)
{
    glUseProgram(_program);

    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemBuffer);

    // Set up vertex positions attributes
    glEnableVertexAttribArray(positionID);
    glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE,
			sizeof(VertexData), BUFFER_OFFSET(0));

    // Set up vertex normals attributes
    glEnableVertexAttribArray(normalID);
    glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE,
			sizeof(VertexData), BUFFER_OFFSET(sizeof(float) * 3));


    glUniformMatrix4fv(uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX], 1, 0, glm::value_ptr(_modelViewProjectionMatrix));
    glUniformMatrix3fv(uniforms[UNIFORM_NORMAL_MATRIX], 1, 0, glm::value_ptr(_normalMatrix));

    // Object Distortion
    float rot_cos = cos(_rotation * M_PI / 180.0f);
    float rot_sin = sin(_rotation * M_PI / 180.0f);
    glUniform4f(uniforms[UNIFORM_MIRROR_NORMAL], rot_sin, 1.0f, rot_cos, 0.0f); // Mirror Normal
    glUniform4f(uniforms[UNIFORM_PROJECTOR_REFLEXTION], -rot_sin * _projectorDistance, 1.0f,
            -rot_cos * _projectorDistance, 0.0f); // reflected projector position P’


    // Draw in fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPolygonOffset(0.0, 0.0);
    glUniform4f(uniforms[UNIFORM_COLOR], 0.0f, 0.0f, 0.0f, 1.0f);
    glDrawElements(GL_TRIANGLES, mesh->NumFaces() * 3,
			GL_UNSIGNED_SHORT, (void *)0);

    // Draw in wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonOffset(2.0, 2.0);
    glUniform4f(uniforms[UNIFORM_COLOR], 1.0f, 1.0f, 1.0f, 1.0f);
    glDrawElements(GL_TRIANGLES, mesh->NumFaces() * 3,
			GL_UNSIGNED_SHORT, (void *)0);

    if (curFrame < 96) {
        saveImage(curFrame);

        curFrame++;

        calcRotation();
        glutPostRedisplay();
    } else if (curFrame == 96) {
        exit(0);
    }
}


void display(void)
{
    // clear and draw params..keep these
	// for this assignment, we will continue to use wireframe
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_BACK);

	// Draw the scene objects
    drawFrame();

    // swap the buffers
    glutSwapBuffers();
}


void printUsage(void)
{
    printf("usage: objrender <obj file>\n\
            \tTakes an obj file and renders it as a lightcrafter pattern\n\
            \tsequence. Output is placed in the output directory");
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printUsage();
        return 1;
    }

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Volumetric Display");

#ifndef __APPLE__
    glewInit();
#endif

    initOpenGL();
    loadResources(argv[1]);
    calcRotation();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

