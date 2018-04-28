//
//  Point.hpp
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
#include <math.h>

#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>

#endif /* Point_hpp */

class Point
{
public:
    Point();
    Point(float _x, float _y, float _z, float _r, float _g, float _b, float _radius);
    ~Point();
    
    void draw();
    void drawGreen();
    float x, y, z;
    float r, g, b;
    float radius;
};
