#include<bits/stdc++.h>
#include "ListaUsuarios.h"
//#include "Mensaje.h";
using namespace std;
//class ListaUsuarios{
//private:
//ListaUsuarios::map<string, string> lista;
// Mensajero mensajerito;
//public:
//  ListaUsuarios(){}
map<string, string>ListaUsuarios::getLista() const{
  return lista;
}

void ListaUsuarios:: agregaUsuario(string nombre){
  string estado = "ACTIVE";
  lista.insert({nombre, estado});
    
}

void ListaUsuarios:: eliminaUsuario(string nombre){
  lista.erase(nombre);
}

void ListaUsuarios:: cambiaStatus(const string& usuario, const string& status){
  lista[usuario] = status;
}

bool ListaUsuarios:: validaUsuario(string username){
  if(lista.find(username) == lista.end()){
    return true;
  }    
  return false;    
    
};    

  
