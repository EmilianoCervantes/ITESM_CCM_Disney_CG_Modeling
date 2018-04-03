#pragma once
#ifdef __APPLE__
	// See: http://lnx.cx/docs/opengl-in-xcode/
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	#include "freeglut.h"
#endif
#include <stdio.h>
#include <math.h>

//#include "./cCarro.h"

class cGrupoCarros{
  public:
    cGrupoCarros();
    ~cGrupoCarros();

    void draw();
    void update();

    //float r,g,b;

    //Carro* carros[10];
};
