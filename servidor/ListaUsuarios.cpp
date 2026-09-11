#include<bits/stdc++.h>
#include "ListaUsuarios.h"
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
    if(ValidaUsuario(nombre)){
      lista.insert({nombre, estado});
      //  mensajerito.anotaMensaje();
    }
    //    mensajerito.anotaMensaje();
    
  }
  void ListaUsuarios:: eliminaUsuario(string nombre){
    lista.erase(nombre);
    //    mensajerito.anotaMensaje();
  }
  void ListaUsuarios:: cambiaStatus(string usuario, string status){
    lista[usuario] = status;
    // mensajerito.anotaMensaje();
  }
  
//private:
  
  bool ListaUsuarios:: ValidaUsuario(string username){    
    if(lista.find(username) == lista.end())     
      return true;          
    return false;    
    
  };    

  
