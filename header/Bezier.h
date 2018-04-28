//
//  Bezier.hpp
//  Bezier
//
//  Created by MBG on 4/12/18.
//  Copyright © 2018 MBG. All rights reserved.
//

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
#include "Point.hpp"

#endif /* Bezier_hpp */
class Bezier{
public:
    Bezier (int deg, Point* points);
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
