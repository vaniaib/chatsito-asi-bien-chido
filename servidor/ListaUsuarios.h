#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H

#include <bits/stdc++.h>
//#include "Mensajero.h"

using namespace std;

class ListaUsuarios{
  
private:  
  map<string, string> lista;
  //Mensajero mensajerito;

public:
  ListaUsuarios(){};
    map<string, string> getLista() const;
    void agregaUsuario(string nombre);
    void eliminaUsuario(string nombre);
    void cambiaStatus(const string& usuario, const string& status);    
    bool validaUsuario(string username);
};

#endif
