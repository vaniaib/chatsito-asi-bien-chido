#ifndef SERVIDOR_H
#define SERVIDOR_H
#include<bits/stdc++.h>
#include "ListaUsuarios.h"
using namespace std;

class Servidor{
private:  
  bool continuaEjecucuion;
  ListaUsuarios usuarios;
  //  Bitacora b;
  //Sala general;
  //  set<Sala> salas;
  int puerto;
  
public:
  Servidor(int puerto){
    this -> puerto = puerto;
  };
  void sirve();
  /*    void agregaUsuario(string nombre); */
  /*    void eliminaUsuario(string nombre); */
  /*    void cambiaStatus(string usuario, string status); */
  
  /* private: */
  /*    bool ValidaUsuario(string username); */
};

#endif
