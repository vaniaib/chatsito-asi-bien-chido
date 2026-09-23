#include<bits/stdc++.h>
#include "Sala.h"
using namespace std;

Sala::Sala(const string& nombre): nombre(nombre){}
ListaUsuarios& Sala:: getUsuarios(){
  lock_guard<mutex> lock(mutexSala);
    return usuariosEnlasala;
}
string Sala:: getNombre(){
  return nombre;
}
void Sala::agregarAlasala(const string& username){
  lock_guard<mutex> lock(mutexSala);
  usuariosEnlasala.agregaUsuario(username); 
}
void Sala::eliminadeSala(const string& username){
  lock_guard<mutex> lock(mutexSala);
  usuariosEnlasala.eliminaUsuario(username); 
}




  



