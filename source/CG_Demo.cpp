﻿/*
Oscar Emiliano Cervantes del Valle A01332891
*/

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include "freeglut.h"
#endif

#include <stdio.h>
#include <math.h>
#include "glm.h"

long		frames;
long		time;
long		timebase;
float		fps;
float		rotation;
GLfloat*	global_ambient;

char		bufferFPS[11];	// For on-screen text.

GLMmodel*	sintel;

float		sintel_pos[3];
float		sintel_dims[3];
float		radius;

/*
Display mode:
0: Vertices.
1: Flat.
2: Smooth.
3: Textured.
*/
int mode;

// Display text:
void displayText(int x, int y, char* txt);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0, 1, 2, 0, 0, 0, 0, 1, 0);

	//Edit
	glPushMatrix();
	{
		glRotatef(rotation, 0.0f, 1.0f, 0.0f);
		glTranslatef(sintel_pos[0], sintel_pos[1], sintel_pos[2]);

		switch (mode)
		{
		case 0:
			glmDraw(sintel, GLM_NONE);
			break;
		case 1:
			glmDraw(sintel, GLM_FLAT);
			break;
		case 2:
			glmDraw(sintel, GLM_SMOOTH);
			break;
		case 3:
			glmDraw(sintel, GLM_SMOOTH | GLM_TEXTURE);
			break;
		default:
			break;
		}
	}
	glPopMatrix();

	displayText(5, 20, bufferFPS);

	glutSwapBuffers();
}

void idle(void)
{
	// Compute frames per second:
	frames++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000)
	{
		fps = frames * 1000.0f / (time - timebase);
		sprintf(bufferFPS, "FPS:%4.2f\n", fps);
		timebase = time;
		frames = 0;
	}

	rotation += 0.05f;
	if (rotation > 360.0f)
	{
		rotation = 0.0f;
	}
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, w / h * 1.0, 0.01, 1024.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	frames = 0;
	time = 0;
	timebase = 0;
	fps = 0.0f;
	rotation = 0.0f;
	mode = 0;
	radius = 0;
	sintel_pos[0] = 0.0f;
	sintel_pos[1] = 0.0f;
	sintel_pos[2] = 0.0f;

	//Edit
	sintel = glmReadOBJ("assets/Sintel_Lite257b.obj");
	glmUnitize(sintel);
	glmFacetNormals(sintel);
	glmDimensions(sintel, sintel_dims);
	float center[3] = {
		sintel_pos[0] + sintel_dims[0] / 2.0f,
		sintel_pos[1] + sintel_dims[1] / 2.0f,
		sintel_pos[2] + sintel_dims[2] / 2.0f
	};
	radius = sqrt(
		center[0] * center[0] +
		center[1] * center[2] +
		center[1] * center[2]
	);

	printf("SINTEL_DIMS={%.3f,%.3f,%.3f}\n", sintel_dims[0], sintel_dims[1], sintel_dims[2]);
	printf("RADUIS=%.3f\n", radius);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat diffusel0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambientl0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularl0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position[4] = { 2.0f, 0.5f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientl0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffusel0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularl0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	global_ambient = new GLfloat[4];
	global_ambient[0] = 0.3f;
	global_ambient[1] = 0.3f;
	global_ambient[2] = 0.3f;
	global_ambient[3] = 1.0f;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

//Se deben usar las teclas WASD para mover al coche
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		mode = 0;
		break;
	case 'a':
		mode = 1;
		break;
	case 's':
		mode = 2;
		break;
	case 'd':
		mode = 3;
		break;
	case 27:
		//glmDelete( sintel );
		//exit(0);
		break;
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 10);
	glutCreateWindow("SINTEL v.1.0.");
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

/*
Displays characters stored in the "txt" array at position (x,y).
*/
void displayText(int x, int y, char* txt)
{
	GLboolean lighting;
	GLint viewportCoords[4];
	glColor3f(0.0, 1.0, 0.0);
	glGetBooleanv(GL_LIGHTING, &lighting);
	glGetIntegerv(GL_VIEWPORT, viewportCoords);
	if (lighting)
	{
		glDisable(GL_LIGHTING);
	}
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, viewportCoords[2], 0.0, viewportCoords[3]);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, viewportCoords[3] - y);
	while (*txt)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *txt);
		txt++;
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	if (lighting)
	{
		glEnable(GL_LIGHTING);
	}
}