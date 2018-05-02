/*
Oscar Emiliano Cervantes del Valle A01332891
*/

#ifdef _APPLE_
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
//#include "freeglut.h"
#endif

#include <stdio.h>
#include <math.h>
#include <chrono>
#include <thread>
#include <ctime>

#include "Bezier.h"
Carro* carros[370];
Bezier * bezier[370];
Point points[10];

Carro* player;
float playerRotation;
float playerX, playerZ;
float playerSpeed = 0.90f;
GLMmodel*    sintel;
GLfloat*    global_ambient;

// Display text:
void displayText(int x, int y, char* txt);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0, 140, 2, 0, 0, 0, 0, 1, 0);

	player->draw();

	for (int i = 0; i < 5; i++) {
		//carros[i]->draw();
		bezier[i]->draw();
		Sleep(200);
	}

	glutSwapBuffers();

}

void idle(void)
{
	// Compute frames per second:
	player->draw();
	/*for (int i = 0; i < 370; i++) {
	carros[i]->update();
	}*/
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
	sintel = glmReadOBJ("./assets/blue_car.obj");
	playerRotation = 180;//90 de arriba de la pantalla
	playerX = 10;
	playerZ = 20;
	//Se mueve ejes x & z, x positivo es izq, z pos es arriba
	player = new Carro(playerX, 0, playerZ, playerRotation, sintel);

	//Punto inicial en pantalla es:
	//player = new Carro(-10, 0, -30, playerRotation, sintel);
	//Carro(float _x, float _y, float _z, float _f, GLMmodel* _sintel)

	float contador = -4.0;
	//crear carros que están del lado de la reja blanca
	//Total 16 carros, son los que están en medio a la izq
	points[0] = Point(-20, 0, -30, 1.0, 0.0, 0.0, 0.1);
	points[1] = Point(-17.5, 0, 5, 1.0, 0.0, 0.0, 0.1);
	points[2] = Point(-25.5, 0, -31.5, 1.0, 0.0, 0.0, 0.1);
	points[3] = Point(4.5, 0, 6, 1.0, 0.0, 0.0, 0.1);
	points[4] = Point(-36.5, 0, -3, 1.0, 0.0, 0.0, 0.1);
	points[5] = Point(-30, 0, -9, 1.0, 0.0, 0.0, 0.1);
	points[6] = Point(25.5, 0, 18.5, 1.0, 0.0, 0.0, 0.1);
	points[7] = Point(11, 0, -13, 1.0, 0.0, 0.0, 0.1);
	points[8] = Point(-2.5, 0, 1.5, 1.0, 0.0, 0.0, 0.1);
	//bezier[0] = new Bezier(10, points);
	for (int j = 0; j < 8; j++) {
		contador = -4;
		for (int i = 0; i<20; i += 2) {
			points[9] = Point(0 + (j * 8), 0, contador, 1.0, 0.0, 0.0, 0.1);
			//Carros arriba
			bezier[i + (20 * j)] = new Bezier(10, points);
			//carros[i + (20 * j)] = new Carro(0 + (j * 8), 0, contador, 90, sintel);
			//Carros abajo
			points[9] = Point(0 + (j * 8), 0, -contador, 1.0, 0.0, 0.0, 0.1);
			bezier[i + 1 + (20 * j)] = new Bezier(10, points);
			//carros[i + 1 + (20 * j)] = new Carro(2.2 - (j * 8), 0, -contador, 270, sintel);
			contador++;
		}
	}

	//carros que están por los foodtrucks
	contador = -14;
	for (int i = 160; i < 220; i += 3) {

		points[9] = Point(-8, 0, contador, 1.0, 0.0, 0.0, 0.1);
		bezier[i] = new Bezier(10, points);
		//carros[i] = new Carro(-8, 0, contador, 90, sintel);

		points[9] = Point(5.8, 0, -contador, 1.0, 0.0, 0.0, 0.1);
		bezier[i + 1] = new Bezier(10, points);
		//carros[i + 1] = new Carro(5.8, 0, -contador, 270, sintel);

		points[9] = Point(13.8, 0, -contador, 1.0, 0.0, 0.0, 0.1);
		bezier[i + 2] = new Bezier(10, points);
		//carros[i + 2] = new Carro(13.8, 0, -contador, 270, sintel);
		contador++;
	}
	//carros que están en la pate de atrás
	contador = -14;
	for (int i = 220; i < 260; i += 2) {
		points[9] = Point(64, 0, contador, 1.0, 0.0, 0.0, 0.1);
		bezier[i] = new Bezier(10, points);
		//carros[i] = new Carro(64, 0, contador, 90, sintel);

		points[9] = Point(-66.2, 0, -contador, 1.0, 0.0, 0.0, 0.1);
		bezier[i + 1] = new Bezier(10, points);
		//carros[i + 1] = new Carro(-66.2, 0, -contador, 270, sintel);
		contador++;
	}

	//carros que están a la derecha hasta enfrente
	contador = -5;
	for (int i = 260; i < 270; i += 2) {
		points[9] = Point(-66.2, 0, -contador, 1.0, 0.0, 0.0, 0.1);
		bezier[i + 1] = new Bezier(10, points);
		carros[i] = new Carro(15.2, 0, contador + 0.5, 0, sintel);

		points[9] = Point(-66.2, 0, -contador, 1.0, 0.0, 0.0, 0.1);
		bezier[i + 1] = new Bezier(10, points);
		carros[i + 1] = new Carro(-13, 0, -contador - 0.5, 180, sintel);
		//contador += 1.7;
	}

	//carros que están a la derecha después del  grupo anterior
	contador = 10;
	for (int i = 270; i < 330; i += 2) {
		points[9] = Point(15.2, 0, -contador, 1.0, 0.0, 0.0, 0.1);
		bezier[i + 1] = new Bezier(10, points);
		//carros[i] = new Carro(15.2, 0, -contador, 0, sintel);

		points[9] = Point(-13, 0, contador, 1.0, 0.0, 0.0, 0.1);
		bezier[i + 1] = new Bezier(10, points);
		carros[i + 1] = new Carro(-13, 0, contador, 180, sintel);
		//contador += 1.7;
	}

	//carros de hasta la derecha
	contador = 27;
	for (int i = 330; i < 370; i += 2) {
		points[9] = Point(23.3, 0, -contador, 1.0, 0.0, 0.0, 0.1);
		bezier[i + 1] = new Bezier(10, points);
		//carros[i] = new Carro(23.3, 0, -contador, 0, sintel);

		points[9] = Point(-21, 0, contador, 1.0, 0.0, 0.0, 0.1);
		bezier[i + 1] = new Bezier(10, points);
		//carros[i + 1] = new Carro(-21, 0, contador, 180, sintel);
		contador += 1.7;
	}




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

void processKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		player->sintel_pos[0] += playerSpeed;
		break;
	case 'd':
		player->sintel_pos[0] -= playerSpeed;
		break;
	case 'w':
		player->sintel_pos[2] += playerSpeed;
		break;
	case 's':
		player->sintel_pos[2] -= playerSpeed;
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
	init();
	glutKeyboardFunc(processKeys);
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
