//
//  Bezier.cpp
//  Bezier
#include "Bezier.h"

Bezier::Bezier(int deg, Point points[10])
{
	tp = 0.0;
	degree = deg;
	ctrlPoints = new Point[degree];
	for (int i = 0; i < degree; i++) {
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
	return factorial(n) / (factorial(i) * factorial(n - i));
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

int Bezier::factorial(int x) {
	if (x <= 1) {
		return 1;
	}
	return x * (factorial(x - 1));
}



void Bezier::draw()
{
	glPushMatrix();
	{
		Point pGreen = evalBezier(tp);
		float carroX, carroZ;
		carroX = pGreen.x;
		carroZ = pGreen.y;
		GLMmodel* sintel;
		sintel = glmReadOBJ("./assets/blue_car.obj");
		Carro* carro = new Carro(pGreen.x, 0, pGreen.y, 90, sintel);
		/*pGreen.g = 1.0;
		pGreen.b = 0.0;
		pGreen.radius = 0.12;*/
		if (tp<1)
		{
			tp = tp + 0.01;
		}
		/*else{
		tp = 0.0;
		}*/
		//pGreen.drawGreen();
		carro->draw();
	}
	glPopMatrix();

}