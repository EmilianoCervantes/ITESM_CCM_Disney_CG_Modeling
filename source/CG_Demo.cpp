/*
* Oscar Emiliano Cervantes del Valle A01332891
* Alison Ricardo González Cortés A01064754
* Alfredo Puente Vasconcelos A01332573
* Irvin Uriel Mundo Rivera A01333820
*/

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

//#include "cWheel.h"
//#include "cCar.h"
#include "../header/cRobot.h"

//Wheel *w1, *w2, *w3, *w4;   //w points to an object of type Wheel
//Car* car;	//Car ownes wheels
Robot* robot;

void init() // FOR GLUT LOOP
{
	//car = new Car(0,1,0);
	/*w1 = new Wheel(-1, 0, -1, 0, 1, 1);    //Deletes the memory and assings new values
	w2 = new Wheel(-1, 0, 1, 0, 1, 1);
	w3 = new Wheel(1, 0, -1, 0, 1, 1);
	w4 = new Wheel(1, 0, 1, 0, 1, 1);*/

	robot = new Robot();
	glEnable(GL_DEPTH_TEST);            // Enable check for close and far objects.
	glClearColor(0.3, 0.3, 0.3, 1.0);   // Clear the color state.
	glMatrixMode(GL_MODELVIEW);         // Go to 3D mode.
	glLoadIdentity();                   // Reset 3D view matrix.
}

void axes()
{
	glLineWidth(5);
	glBegin(GL_LINES);
	{
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1);
	}
	glEnd();
	glLineWidth(1);
}

void display()                            // Called for each frame (about 60 times per second).
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                // Clear color and depth buffers.
	//axes();
	//car->draw();
	/*w1->draw();    //Like point in Java
	w2->draw();
	w3->draw();
	w4->draw();*/

	robot->draw();
	glutSwapBuffers();                                                // Swap the hidden and visible buffers.
}

void idle()                                                            // Called when drawing is finished.
{
	//car->update();
	/*w1->update();
	w2->update();
	w3->update();
	w4->update();*/

	robot->update();
	glutPostRedisplay();                                            // Display again.
}

void reshape(int x, int y)                                            // Called when the window geometry changes.
{
	glMatrixMode(GL_PROJECTION);                                    // Go to 2D mode.
	glLoadIdentity();                                                // Reset the 2D matrix.
	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 50.0);        // Configure the camera lens aperture.
	glMatrixMode(GL_MODELVIEW);                                        // Go to 3D mode.
	glLoadIdentity();                                                // Reset the 3D matrix.
	glViewport(0, 0, x, y);                                            // Configure the camera frame dimensions.
	gluLookAt(5.0, 5.0, 5.0,                                        // Where the camera is.
		0.0, 0.0, 0.0,                                                // To where the camera points at.
		0.0, 1.0, 0.0);                                                // "UP" vector.
	display();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);                                            // Init GLUT with command line parameters.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);        // Use 2 buffers (hidden and visible). Use the depth buffer. Use 3 color channels.
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG_DEMO");

	init();
	glutReshapeFunc(reshape);                                        // Reshape CALLBACK function.
	glutDisplayFunc(display);                                        // Display CALLBACK function.
	glutIdleFunc(idle);                                                // Idle CALLBACK function.
	glutMainLoop();                                                    // Begin graphics program.
	return 0;                                                        // ANSI C requires a return value.
}
