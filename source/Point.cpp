#include "Point.h"

Point::Point()
{
    x = 0;
    y = 0;
    z = 0;
    r = 1.0;
    g = 0;
    b = 0;
    radius = 0.08;
}

Point::Point(float _x, float _y, float _z, float _r, float _g, float _b, float _radius)
{
    x = _x; y =_y; z = _z;
    r = _r; g =_g; b = _b;
    radius = _radius;
}

Point:: ~Point(){
}

void Point::draw()
{
    glPushMatrix();
    {
        glTranslatef(x, y, z);
        glColor3f(r, g, b);
        glutSolidSphere(radius, 10, 10);
    }
    glPopMatrix();
}

void Point::drawGreen()
{
    glPushMatrix();
    {
        //glTranslatef(x, y, z);
        glColor3f(r, g, b);
        glLineWidth(5);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 10; i++)   {
            float theta = 2.0f * 3.1415926f * float(i) / float(10);
            float xc = radius * cosf(theta);
            float yc = radius * sinf(theta);
            glVertex2f(x + xc, y + yc);
        }
        glEnd();
    }
    glPopMatrix();
}
