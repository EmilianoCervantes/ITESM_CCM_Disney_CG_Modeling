#include "../header/cGrupoCarros.h"
#include "../header/cCarro.h"

cGrupoCarros::cGrupoCarros(){
/*
  for(int i = 0; i < 4; i++){
    carros[i] = new Carro();
  }
  /*
  wheels[0]->x = -1;
  wheels[1]->x = -1;
  wheels[0]->z = -1;
  wheels[3]->z = -1;*/
}

cGrupoCarros::~cGrupoCarros(){
}

void cGrupoCarros::draw(){
  /*glPushMatrix();{
    glColor3f(r,g,b);
    glutSolidCube(1);
    for(int i = 0; i < 4; i++){
      wheels[i]->draw();
    }
  }glPopMatrix();
*/
}

void cGrupoCarros::update(){
  /*for(int i = 0; i < 4; i++){
    wheels[i]->update();
  }*/
}
