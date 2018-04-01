//Irvin Uriel Mundo A01333820
//Alfredo Puente A01332573
//  main.cpp
//  OBJ
//
//  Created by Irvin Mundo on 16/03/18.
//  Copyright © 2018 MundoSystems. All rights reserved.
//

/*
 Computer Graphics. TC3022.

 Basic TGA textures.
 Displays a textured OBJ.
 */

#ifdef _APPLE_
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include "freeglut.h"
#endif

#include <stdio.h>
#include <math.h>

#include "../header/cCarro.h"

Carro* carros[200];

GLfloat*    global_ambient;

// Display text:
void displayText( int x, int y, char* txt );

void display( void )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glLoadIdentity();
  gluLookAt(0, 80, 2, 0, 0, 0, 0, 1, 0);

  for(int i = 0; i < 200; i++){
    carros[i] -> draw();
  }

  glutSwapBuffers();

}

void idle( void )
{
    // Compute frames per second:
    for(int i = 0; i < 200; i++){
      carros[i] -> update();
    }
    glutPostRedisplay();
}

void reshape( int w, int h )
{
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    gluPerspective( 60.0, w / h * 1.0, 0.01, 1024.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void init( void )
{
  int contador = -4;
  //crear carros que están del lado de la reja blanca
  for(int j = 0; j < 5; j++){
    contador = -4;
    for(int i = 0; i<20; i+=2){
      carros[i+(20*j)] = new Carro(contador,0,0-(j*8),0);
      carros[i+1+(20*j)] = new Carro(-contador,0,2.2+(j*8),180);
      contador++;
    }
  }
  //carros que están por los foodtrucks
  contador = -14;
  for(int i = 100; i < 160; i+=3){
    carros[i] = new Carro(contador,0,8,0);
    carros[i+1] = new Carro(-contador,0,-5.8,180);
    carros[i+2] = new Carro(-contador,0,-13.8,180);
    contador++;
  }
  //carros que están en la pate de atrás
  contador = -14;
  for(int i = 160; i < 200; i+=2){
    carros[i] = new Carro(contador,0,-40,0);
    carros[i+1] = new Carro(-contador,0,42.2,180);
    contador++;
  }



    glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    GLfloat diffusel0[4]    = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat ambientl0[4]    = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specularl0[4]    = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat position[4]        = { 2.0f, 0.5f, 1.0f, 0.0f };
    glLightfv( GL_LIGHT0, GL_AMBIENT,   ambientl0  );
    glLightfv( GL_LIGHT0, GL_DIFFUSE,   diffusel0  );
    glLightfv( GL_LIGHT0, GL_SPECULAR,  specularl0 );
    glLightfv( GL_LIGHT0, GL_POSITION,  position   );

    global_ambient            = new GLfloat[4];
    global_ambient[0]        = 0.3f;
    global_ambient[1]        = 0.3f;
    global_ambient[2]        = 0.3f;
    global_ambient[3]        = 1.0f;
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, global_ambient );
    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );
}

int main( int argc, char* argv[] )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize( 800, 800 );
    glutInitWindowPosition( 100, 10 );
    glutCreateWindow( "SINTEL v.1.0." );
    glutReshapeFunc( reshape );
    init();
    glutDisplayFunc( display );
    glutIdleFunc( idle );
    glutMainLoop();
    return 0;
}

/*
 Displays characters stored in the "txt" array at position (x,y).
 */
void displayText( int x, int y, char* txt )
{
    GLboolean lighting;
    GLint viewportCoords[4];
    glColor3f( 0.0, 1.0, 0.0 );
    glGetBooleanv( GL_LIGHTING, &lighting       );
    glGetIntegerv( GL_VIEWPORT, viewportCoords );
    if( lighting )
    {
        glDisable( GL_LIGHTING );
    }
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D( 0.0, viewportCoords[2], 0.0, viewportCoords[3] );
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i( x, viewportCoords[3] - y );
    while( *txt )
    {
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *txt );
        txt++;
    }
    glPopMatrix();
    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );

    if( lighting )
    {
        glEnable( GL_LIGHTING );
    }
}
