//
//  Bezier.cpp
//  Bezier
//
//  Created by MBG on 4/12/18.
//  Copyright © 2018 MBG. All rights reserved.
//

#include "Bezier.hpp"

Bezier::Bezier(int deg, Point* points)
{
    tp = 0.0;
    degree = deg;
    ctrlPoints = new Point[degree];
    for(int i = 0; i < degree; i++){
        ctrlPoints[i].x = points[i].x;
        ctrlPoints[i].y = points[i].y;
        ctrlPoints[i].z = points[i].z;
        
        ctrlPoints[i].r = points[i].r;
        ctrlPoints[i].g = points[i].g;
        ctrlPoints[i].b = points[i].b;
        
        ctrlPoints[i].radius = points[i].radius;
    }
}

Bezier:: ~Bezier()
{
    delete ctrlPoints;
}

float Bezier::binomial(int n, int i)
{
    return factorial(n) / (factorial(i) * factorial(n-i));
}

Point Bezier::evalBezier(float t)
{
    Point p;
    p.x = 0; p.y = 0;
    p.b = 1;
    p.r = 0.0;
    p.radius = 0.05;
    for (int i = 0; i<degree; i++)
    {
        p.x = p.x + binomial((float)(degree - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (degree - 1 - i)) * ctrlPoints[i].x;
        p.y = p.y + binomial((float)(degree - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (degree - 1 - i)) * ctrlPoints[i].y;
    }
    return p;
}

int Bezier::factorial(int x){
    if(x <= 1){
        return 1;
    }
    return x * (factorial(x-1));
}



void Bezier::draw()
{
    glPushMatrix();
    {
        for(int i=0; i<degree; i++){
            ctrlPoints[i].draw();
        }
    }
    glPopMatrix();
    glPushMatrix();
    {
        for(double t = 0.0;t <= 1.0; t += 0.1)
        {
            Point p = evalBezier(t);
            p.draw();
        }
    }
    glPopMatrix();
    
    glPushMatrix();
    {
        Point pGreen = evalBezier(tp);
        pGreen.g = 1.0;
        pGreen.b = 0.0;
        pGreen.radius = 0.12;
        if(tp<1)
        {
            tp = tp + 0.001;
        }
        else{
            tp = 0.0;
        }
        pGreen.drawGreen();
    }
    glPopMatrix();
    
}


