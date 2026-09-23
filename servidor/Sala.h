#ifndef SALA_H
#define SALA_H
#include<bits/stdc++.h>
#include "ListaUsuarios.h"
using namespace std;

class Sala{
private :
  ListaUsuarios usuariosEnlasala;
  string nombre;
  mutable mutex mutexSala;
  //  bool invitado;
public:
  map<string, bool> invitados;
  Sala(const string& nombre);
  // {
  //   this -> nombre = nombre;
  // };
  //  Sala(){}; 
  string getNombre();  
  ListaUsuarios& getUsuarios();
  void agregarAlasala(const string& s);
  void eliminadeSala(const string& s);
  


  
};
#endif
