#ifdef __APPLE__
// See: http://lnx.cx/docs/opengl-in-xcode/
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#else
#include "freeglut.h"
#endif

#include <stdio.h>
#include <math.h> //powf

#ifndef Bezier_hpp
#define Bezier_hpp

#include <stdio.h>
#include "Point.h"
#include "cCarro.h"

#endif /* Bezier_hpp */
class Bezier {
public:
	Bezier(int deg, Point points[10]);
	~Bezier();
	int factorial(int x);
	float binomial(int n, int i);
	Point evalBezier(float t);
	void draw();

	Point* ctrlPoints; //control points;
	int degree;
	float* coefficients; // Array to pre-compute coefficient.
	float tp; // time of point movement
};
