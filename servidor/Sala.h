#ifndef SALA_H
#define SALA_H
#include<bits/stdc++.h>
#include "ListaUsuarios.h"
using namespace std;

class Sala{
private :
  ListaUsuarios usuariosEnlasala;
  string nombre;
  //  bool invitado;
 public:
  Sala(string nombre){
    this -> nombre = nombre;
  };
  //  Sala(){};
  ListaUsuarios getUsuarios();
  // bool estaInvitado();
  void agregarAlasala(string s);
  void eliminadeSala(string s);
  


  
};
#endif
