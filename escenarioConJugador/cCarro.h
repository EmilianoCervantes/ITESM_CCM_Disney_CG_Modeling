#ifdef _APPLE_
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
//#include "freeglut.h"
#endif

#include <stdio.h>
#include <math.h>
#include "./glm.h"





class Carro{

	long        frames;
	long        time;
	long        timebase;
	float        fps;
	char        bufferFPS[11];    // For on-screen text.
	float        sintel_dims[3];
	float        radius;
	GLMmodel* sintel;

  public:
    float        rotation;
    float        sintel_pos[3];
    Carro(float _x, float _y, float _z, float _f, GLMmodel* _sintel);
    ~Carro();

    void draw();
    void update();
};
