#include "../header/cCarro.h"


Carro::Carro(float _x, float _y, float _z, float _f){
  frames            = 0;
  time            = 0;
  timebase        = 0;
  fps                = 0.0f;
  rotation        = _f;
  radius            = 0;
  sintel_pos[0]    = _x;
  sintel_pos[1]    = _y;
  sintel_pos[2]    = _z;
  sintel = glmReadOBJ("../assets/L200-OBJ.obj");
  glmUnitize(sintel);
  glmFacetNormals(sintel);
  glmDimensions(sintel, sintel_dims);
  float center[3] = {
      (sintel_pos[0] + sintel_dims[0])/2.0f, (sintel_pos[1] + sintel_dims[1])/2.0f,(sintel_pos[2] + sintel_dims[2])/2.0f
  };
  radius = sqrt(center[0]*center[0]+center[1]*center[1]+center[2]*center[2]);
  printf("SINTEL_DIMS={%.3f,%.3f,%.3f}\n", sintel_dims[0],sintel_dims[1],sintel_dims[2]);
  printf("radius=%.3f\n", radius);
}

Carro::~Carro(){
}

void Carro::draw(){



  //glLoadIdentity();
  //gluLookAt(0, 60, 2, 0, 0, 0, 0, 1, 0);
  glPushMatrix();
  glRotatef(rotation, 0.0f, 0.1f, 0.0f);
  glTranslatef(sintel_pos[0], sintel_pos[1], sintel_pos[2]);
  glmDraw(sintel, GLM_SMOOTH);
  glPopMatrix();



}

void Carro::update(){
  frames++;
  time = glutGet( GLUT_ELAPSED_TIME );
  if( time - timebase > 1000 )
  {
      fps = frames * 1000.0f / (time - timebase);
      sprintf( bufferFPS, "FPS:%4.2f\n", fps);
      timebase = time;
      frames = 0;
  }
/*
  rotation += 0.05f;
  if( rotation > 360.0f )
  {
      rotation = 0.0f;
  }*/


}
