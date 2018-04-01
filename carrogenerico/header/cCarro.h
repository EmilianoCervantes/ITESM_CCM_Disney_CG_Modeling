#ifdef _APPLE_
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include "freeglut.h"
#endif

#include <stdio.h>
#include <math.h>
#include "./glm.h"





class Carro{

	long        frames;
	long        time;
	long        timebase;
	float        fps;
	float        rotation;

	char        bufferFPS[11];    // For on-screen text.
	GLMmodel*    sintel;

	float        sintel_pos[3];
	float        sintel_dims[3];
	float        radius;

  public:
    Carro(float _x, float _y, float _z, float _f);
    ~Carro();

    void draw();
    void update();
};
